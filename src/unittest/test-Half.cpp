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
		0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
		0.01f, 0.02f, 0.03f, 0.04f, 0.05f, 0.06f, 0.07f, 0.08f, 0.09f,
		0.001f, 0.002f, 0.003f, 0.004f, 0.005f, 0.006f, 0.007f, 0.008f, 0.009f,
		0.0001f, 0.0002f, 0.0003f, 0.0004f, 0.0005f, 0.0006f, 0.0007f, 0.0008f, 0.0009f,
		0.00001f, 0.00002f, 0.00003f, 0.00004f, 0.00005f, 0.00006f, 0.00007f, 0.00008f, 0.00009f,
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
