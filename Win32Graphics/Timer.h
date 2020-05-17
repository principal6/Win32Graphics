#pragma once

#include "CommonTypes.h"


namespace fs
{
	class Timer final
	{
	public:
		enum class EUnit
		{
			// 1 나노초. 현재 가장 작은 단위
			_0_Nanosecond,

			// 1 마이크로초 == 1,000 나노초
			// 1 us (microsecond) == 1,000 ns (nanosecond)
			_1_Microsecond,

			// 1 밀리초 == 1,000 마이크로초
			// 1 ms (millisecond) == 1,000 us (microsecond)
			_2_Millisecond,

			// 1 초 == 1,000 밀리초
			// 1 s (second) == 1,000 ms (millisecond)
			_3_Second
		};

	public:
		Timer();
		~Timer();
	
	public:
		// 타이머의 시간 간격과 그 단위를 설정한다.
		// 가장 먼저, 최소 한 번은 호출되어야 할 함수.
		void set(uint32 interval, EUnit unit);

	public:
		// 타이머를 작동시킨다.
		// 내부적으로 reset()을 호출한다.
		void start();

		// 타이머를 정지시킨다.
		void stop();

		// set()에서 정한 시간 간격(interval)이 흐르면 _tickCount를 증가시킨다.
		// _tickCount가 0보다 클 때 reset()을 호출하고 true를 return한다.
		// _tickCount가 0일 경우 false를 return한다.
		bool tick();

	public:
		// _tickCount를 0으로 만들고 다시 처음부터 시간을 잰다.
		// tick()을 반복적으로 호출할 경우 이 함수는 호출하지 않아도 된다.
		// ( tick()이 true를 리턴하기 전에 반드시 reset()을 호출하기 때문 )
		void reset();

	private:
		// 경과 시간을 측정해 실제로 _tickCount를 증가시키는 함수.
		void update();

	private:
		// 시간 간격
		uint32	_interval{};

		// 시간 간격의 단위
		EUnit	_intervalUnit{ EUnit::_1_Microsecond };

	private:
		// 타이머의 시작 시간
		uint64	_startTime{};

		// 타이머가 시간을 잰 횟수
		uint64	_tickCount{};

	private:
		// 타이머가 작동 중인가?
		bool	_isTicking{ false };
	};
}
