//==============================================================================
// Number.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// NumberBase
//------------------------------------------------------------------------------
String NumberBase::_formatterFormat_Int("%lld");
String NumberBase::_formatterFormat_Float("%g");

void NumberBase::Bootup()
{
}

//------------------------------------------------------------------------------
// Number
//------------------------------------------------------------------------------
template<> const Bool Number<Bool>::Min		= false;
template<> const Bool Number<Bool>::Max		= true;
template<> const Int8 Number<Int8>::Min		= -0x80;
template<> const Int8 Number<Int8>::Max		= 0x7f;
template<> const UInt8 Number<UInt8>::Min	= 0x00;
template<> const UInt8 Number<UInt8>::Max	= 0xff;
template<> const Int16 Number<Int16>::Min	= -0x8000;
template<> const Int16 Number<Int16>::Max	= 0x7fff;
template<> const UInt16 Number<UInt16>::Min	= 0x0000;
template<> const UInt16 Number<UInt16>::Max	= 0xffff;
template<> const Int32 Number<Int32>::Min	= -0x80000000;
template<> const Int32 Number<Int32>::Max	= 0x7fffffff;
template<> const UInt32 Number<UInt32>::Min	= 0x00000000;
template<> const UInt32 Number<UInt32>::Max	= 0xffffffff;
template<> const Int64 Number<Int64>::Min	= -0x8000000000000000LL;
template<> const Int64 Number<Int64>::Max	= 0x7fffffffffffffffLL;
template<> const UInt64 Number<UInt64>::Min	= 0x0000000000000000LL;
template<> const UInt64 Number<UInt64>::Max	= 0xffffffffffffffffLL;
template<> const Float Number<Float>::Min	= 0;
template<> const Float Number<Float>::Max	= 0;
template<> const Double Number<Double>::Min	= 0;
template<> const Double Number<Double>::Max	= 0;

}
