#include "Timer.h"

#include <chrono>


namespace fs
{
	Timer::Timer()
	{
	}

	Timer::~Timer()
	{
	}

	void Timer::set(uint32 interval, EUnit unit)
	{
		_intervalUnit = unit;

		_interval = interval;

		start();
	}

	void Timer::start()
	{
		_isTicking = true;

		reset();
	}

	void Timer::stop()
	{
		_isTicking = false;
	}

	bool Timer::tick()
	{
		update();

		if (_isTicking == true && _tickCount > 0)
		{
			reset();

			return true;
		}
		else
		{
			return false;
		}
	}

	void Timer::reset()
	{
		_startTime = std::chrono::steady_clock::now().time_since_epoch().count();

		_tickCount = 0;
	}

	void Timer::update()
	{
		uint64 elapsed{ std::chrono::steady_clock::now().time_since_epoch().count() - _startTime };

		switch (_intervalUnit)
		{
		case fs::Timer::EUnit::_0_Nanosecond:
			__noop;
			break;
		case fs::Timer::EUnit::_1_Microsecond:
			elapsed /= 1'000;
			break;
		case fs::Timer::EUnit::_2_Millisecond:
			elapsed /= 1'000'000;
			break;
		case fs::Timer::EUnit::_3_Second:
			elapsed /= 1'000'000'000;
			break;
		default:
			break;
		}

		if (elapsed >= _interval)
		{
			++_tickCount;
		}
	}
}
