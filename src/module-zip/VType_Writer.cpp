//==============================================================================
// VType_Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// zip.Writer() {block?}
Gurax_DeclareConstructor(Writer)
{
	Declare(VTYPE_Writer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Writer` instance.");
}

Gurax_ImplementConstructor(Writer)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Writer> pWriter(new Writer());
	return argument.ReturnValue(processor, new Value_Writer(pWriter.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// zip.Writer#Add(stream:Stream:r, fileName?:String, compression?:Symbol):map:reduce
Gurax_DeclareMethod(Writer, Add)
{
	Declare(VTYPE_Writer, Flag::Reduce | Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("fileName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("compression", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Reads data from `stream` and adds it to the zip file.\n"
		"Entry name is decided by the file name associated with the stream\n"
		"unless it's specified by argument `filename`.\n"
		"\n"
		"Argument `compression` specifies the compression method and takes one of the following symbols:\n"
		"\n"
		"- `` `store``\n"
		"- `` `deflate``\n"
		"- `` `bzip2``\n");
}

Gurax_ImplementMethod(Writer, Add)
{
#if 0
	Signal &sig = env.GetSignal();
	Object_writer *pThis = Object_writer::GetObjectThis(arg);
	String fileName;
	if (arg.Is_string(1)) {
		fileName = arg.GetString(1);
	} else {
		const char *identifier = arg.GetStream(0).GetIdentifier();
		if (identifier == nullptr) {
			sig.SetError(ERR_ValueError, "stream doesn't have an identifier");
			return Value::Nil;
		}
		PathMgr::SplitFileName(identifier, nullptr, &fileName);
	}
	UInt16 compressionMethod = arg.Is_symbol(2)?
						SymbolToCompressionMethod(arg.GetSymbol(2)) :
						pThis->GetCompressionMethod();
	if (compressionMethod == METHOD_Invalid) {
		sig.SetError(ERR_IOError, "invalid compression method");
		return Value::Nil;
	}
	if (!pThis->Add(env, arg.GetStream(0),
					fileName.c_str(), compressionMethod)) return Value::Nil;
	return arg.GetValueThis();
#endif
	return Value::nil();
}

// zip.Writer#Close():void
Gurax_DeclareMethod(Writer, Close)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Closes the zip file after flushing cached data.");
}

Gurax_ImplementMethod(Writer, Close)
{
#if 0
	Object_writer *pThis = Object_writer::GetObjectThis(arg);
	if (!pThis->Finish()) return Value::Nil;
	return Value::Nil;
#endif
	return Value::nil();
}

// zip.Writer#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Writer, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Writer, MethodSkeleton)
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
// zip.Writer#propSkeleton
Gurax_DeclareProperty_R(Writer, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Writer, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Writer
//------------------------------------------------------------------------------
VType_Writer VTYPE_Writer("Writer");

void VType_Writer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Writer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Writer, MethodSkeleton));
	Assign(Gurax_CreateMethod(Writer, Add));
	Assign(Gurax_CreateMethod(Writer, Close));
	// Assignment of property
	Assign(Gurax_CreateProperty(Writer, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Writer
//------------------------------------------------------------------------------
VType& Value_Writer::vtype = VTYPE_Writer;

Gurax_EndModuleScope(zip)
