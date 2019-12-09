//==============================================================================
// VType_Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// zip.Reader() {block?}
Gurax_DeclareConstructor(Reader)
{
	Declare(VTYPE_Reader, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Reader` instance.");
}

Gurax_ImplementConstructor(Reader)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Reader> pReader(new Reader());
	return argument.ReturnValue(processor, new Value_Reader(pReader.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// zip.Reader#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Reader, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Reader, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// zip.Reader#propSkeleton
Gurax_DeclareProperty_R(Reader, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Reader, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Reader
//------------------------------------------------------------------------------
VType_Reader VTYPE_Reader("Reader");

void VType_Reader::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Reader));
	// Assignment of method
	Assign(Gurax_CreateMethod(Reader, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Reader, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Reader
//------------------------------------------------------------------------------
VType& Value_Reader::vtype = VTYPE_Reader;

Gurax_EndModuleScope(zip)
