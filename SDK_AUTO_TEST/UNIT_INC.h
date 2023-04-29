#ifndef GOOGLETEST_UNIT_INC_H_
#define GOOGLETEST_UNIT_INC_H_
/*  This file includes the necessary headers when you use google test
	Please include this in the compilation unit you would like to write test
 */

#pragma once
#pragma warning(disable : 4819)

#ifdef WIN32
#pragma comment(lib, "./lib/x86/HRSDK.lib" )
#else
#pragma comment(lib, "./lib/x64/HRSDK.lib" )
#endif // WIN32

#if _MSC_VER < 1800
#define _VARIADIC_MAX 10 // suppress tuple error in VC2012
#endif
#include "gtest/gtest.h"

#define DOUBLE_UNIT 0.01

#endif // GOOGLETEST_UNIT_INC_H_
