//==============================================================================
// Half
//==============================================================================
#ifndef GURAX_HALF_H
#define GURAX_HALF_H
#include "Common.h"
#include "Complex.h"

namespace Gurax {

class GURAX_DLLDECLARE Half {
private:
	UInt16 _num;
private:
	static UInt32 _mantissaTable[];
	static UInt32 _exponentTable[];
	static UInt16 _offsetTable[];
	static UInt16 _baseTable[];
	static Int8 _shiftTable[];
public:
	Half() : _num(0) {}
	Half(const Half& half) : _num(half._num) {}
	Half(Bool num) : _num(FloatToHalf(num)) {}
	Half(Int8 num) : _num(FloatToHalf(num)) {}
	Half(UInt8 num) : _num(FloatToHalf(num)) {}
	Half(Int16 num) : _num(FloatToHalf(num)) {}
	Half(UInt16 num) : _num(FloatToHalf(num)) {}
	Half(Int32 num) : _num(FloatToHalf(num)) {}
	Half(UInt32 num) : _num(FloatToHalf(num)) {}
	Half(Int64 num) : _num(FloatToHalf(num)) {}
	Half(UInt64 num) : _num(FloatToHalf(num)) {}
	Half(Float num) : _num(FloatToHalf(num)) {}
	Half(Double num) : _num(FloatToHalf(num)) {}
	Half(const Complex& num) : _num(0) {}
public:
	Half& operator=(const Half& half) { _num = half._num; return *this; }
public:
	Float ToFloat() const { return HalfToFloat(_num); }
	bool IsZero() const { return _num == 0x0000; }
	explicit operator Bool() const noexcept { return !IsZero(); }
	explicit operator Int8() const noexcept { return static_cast<Int8>(HalfToFloat(_num)); }
	explicit operator UInt8() const noexcept { return static_cast<UInt8>(HalfToFloat(_num)); }
	explicit operator Int16() const noexcept { return static_cast<Int16>(HalfToFloat(_num)); }
	explicit operator UInt16() const noexcept { return static_cast<UInt16>(HalfToFloat(_num)); }
	explicit operator Int32() const noexcept { return static_cast<Int32>(HalfToFloat(_num)); }
	explicit operator UInt32() const noexcept { return static_cast<UInt32>(HalfToFloat(_num)); }
	explicit operator Int64() const noexcept { return static_cast<Int64>(HalfToFloat(_num)); }
	explicit operator UInt64() const noexcept { return static_cast<UInt64>(HalfToFloat(_num)); }
	explicit operator Float() const noexcept { return HalfToFloat(_num); }
	explicit operator Double() const noexcept { return static_cast<Double>(HalfToFloat(_num)); }
	explicit operator Complex() const noexcept { return Complex(static_cast<Complex>(HalfToFloat(_num))); }
	Half& operator+=(Float var) {
		_num = FloatToHalf(ToFloat() + var);
		return *this;
	}
	Half& operator-=(Float var) {
		_num = FloatToHalf(ToFloat() - var);
		return *this;
	}
	Half& operator*=(Float var) {
		_num = FloatToHalf(ToFloat() * var);
		return *this;
	}
	Half& operator/=(Float var) {
		_num = FloatToHalf(ToFloat() / var);
		return *this;
	}
	Half& operator+=(const Half& var) {
		_num = FloatToHalf(ToFloat() + var.ToFloat());
		return *this;
	}
	Half& operator-=(const Half& var) {
		_num = FloatToHalf(ToFloat() - var.ToFloat());
		return *this;
	}
	Half& operator*=(const Half& var) {
		_num = FloatToHalf(ToFloat() * var.ToFloat());
		return *this;
	}
	Half& operator/=(const Half& var) {
		_num = FloatToHalf(ToFloat() / var.ToFloat());
		return *this;
	}
	Half operator-() const { return Half(-HalfToFloat(_num)); }
	Half operator+() const { return *this; }
public:
	static void Bootup();
private:
	static UInt32 ConvertMantissa(int i);
	static void GenerateMantissaTable();
	static void GenerateExponentTable();
	static void GenerateOffsetTable();
	static void GenerateBaseTable();
	static void GenerateShiftTable();
	static Float HalfToFloat(UInt16 num);
	static UInt16 FloatToHalf(Float num);
};

inline Half operator+(const Half& varL, Float varR) {
	return Half(varL) += varR;
}

inline Half operator-(const Half& varL, Float varR) {
	return Half(varL) -= varR;
}

inline Half operator*(const Half& varL, Float varR) {
	return Half(varL) *= varR;
}

inline Half operator/(const Half& varL, Float varR) {
	return Half(varL) /= varR;
}

inline Half operator+(Float varL, const Half& varR) {
	return Half(varL) += varR;
}

inline Half operator-(Float varL, const Half& varR) {
	return Half(varL) -= varR;
}

inline Half operator*(Float varL, const Half& varR) {
	return Half(varL) *= varR;
}

inline Half operator/(Float varL, const Half& varR) {
	return Half(varL) /= varR;
}

inline Half operator+(const Half& varL, const Half& varR) {
	return Half(varL) += varR;
}

inline Half operator-(const Half& varL, const Half& varR) {
	return Half(varL) -= varR;
}

inline Half operator*(const Half& varL, const Half& varR) {
	return Half(varL) *= varR;
}

inline Half operator/(const Half& varL, const Half& varR) {
	return Half(varL) /= varR;
}

inline bool operator<(const Half& varL, const Half& varR) {
	return varL.ToFloat() < varR.ToFloat();
}

inline bool operator>(const Half& varL, const Half& varR) {
	return varL.ToFloat() > varR.ToFloat();
}

inline bool operator<=(const Half& varL, const Half& varR) {
	return varL.ToFloat() <= varR.ToFloat();
}

inline bool operator>=(const Half& varL, const Half& varR) {
	return varL.ToFloat() >= varR.ToFloat();
}

inline bool operator==(const Half& varL, const Half& varR) {
	return varL.ToFloat() == varR.ToFloat();
}

inline bool operator!=(const Half& varL, const Half& varR) {
	return varL.ToFloat() != varR.ToFloat();
}

}

#endif
