#pragma once


#ifndef FS_COMMON_TYPES_H
#define FS_COMMON_TYPES_H
// === HEADER BEGINS ===


#include <Core/pch.h>
#include <sal.h>


namespace fs
{
#ifndef FS_INT_TYPE_ALIASES
#define FS_INT_TYPE_ALIASES
	using int8		= int8_t;
	using int16		= int16_t;
	using int32		= int32_t;
	using int64		= int64_t;
	using uint8		= uint8_t;
	using uint16	= uint16_t;
	using uint32	= uint32_t;
	using uint64	= uint64_t;
	using byte		= uint8;

	static constexpr fs::uint32		kUint32Max{ 0xFFFFFFFFui32 };
#endif // FS_INT_TYPE_ALIASES
}


// === HEADER ENDS ===
#endif // !FS_COMMON_TYPES_H
