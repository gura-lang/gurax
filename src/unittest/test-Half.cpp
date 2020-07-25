//==============================================================================
// test-Half.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Half)
{
	static const Float tbl[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 20, 30, 40, 50, 60, 70, 80, 90,
		100, 200, 300, 400, 500, 600, 700, 800, 900,
		1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
		10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,
		100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000,
		0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
		0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
		0.001, 0.002, 0.003, 0.004, 0.005, 0.006, 0.007, 0.008, 0.009,
		0.0001, 0.0002, 0.0003, 0.0004, 0.0005, 0.0006, 0.0007, 0.0008, 0.0009,
		0.00001, 0.00002, 0.00003, 0.00004, 0.00005, 0.00006, 0.00007, 0.00008, 0.00009,
		3.14159265f, 1.41421356f
	};
	for (size_t i = 0; i < Gurax_ArraySizeOf(tbl); i++) {
		::printf("%f .. Half:%f\n", tbl[i], static_cast<Float>(Half(tbl[i])));
	}
	do {
		Half a(3);
		::printf("+%f = %f\n", static_cast<Float>(a), static_cast<Float>(+a));
	} while (0);
	do {
		Half a(3);
		::printf("-%f = %f\n", static_cast<Float>(a), static_cast<Float>(-a));
	} while (0);
	do {
		Half a(3), b(5);

		::printf("%f + %f = %f\n", static_cast<Float>(a), static_cast<Float>(b), static_cast<Float>(a + b));
	} while (0);
	do {
		Half a(3), b(5);
		::printf("%f - %f = %f\n", static_cast<Float>(a), static_cast<Float>(b), static_cast<Float>(a - b));
	} while (0);
	do {
		Half a(3), b(5);
		::printf("%f * %f = %f\n", static_cast<Float>(a), static_cast<Float>(b), static_cast<Float>(a * b));
	} while (0);
	do {
		Half a(3), b(5);
		::printf("%f / %f = %f\n", static_cast<Float>(a), static_cast<Float>(b), static_cast<Float>(a / b));
	} while (0);
}

}
