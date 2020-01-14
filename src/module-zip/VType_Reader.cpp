//==============================================================================
// VType_Reader.cpp
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
// zip.Reader(stream:Stream:r) {block?}
Gurax_DeclareConstructor(Reader)
{
	Declare(VTYPE_Reader, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `zipReader` instance from the specified stream.");
}

Gurax_ImplementConstructor(Reader)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Reader> pReader(new Reader(stream.Reference()));
	if (!pReader->ReadDirectory()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Reader(pReader.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// zip.Reader#Entry(name:String) {block?}
Gurax_DeclareMethod(Reader, Entry)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Seeks entry in the zip file that matches the specified name\n"
		"and returns a `stream` instance associated with the entry.\n");
}

Gurax_ImplementMethod(Reader, Entry)
{
#if 0
	Signal &sig = env.GetSignal();
	Object_reader *pThis = Object_reader::GetObjectThis(arg);
	Stream *pStreamSrc = pThis->GetStreamSrc();
	if (pStreamSrc == nullptr) {
		sig.SetError(ERR_ValueError, "zip object is not readable");
		return Value::Nil;
	}
	AutoPtr<Object_stream> pObjStream;
	const char *name = arg.GetString(0);
	foreach (CentralFileHeaderList, ppHdr, pThis->GetHeaderList()) {
		const CentralFileHeader *pHdr = *ppHdr;
		const CentralFileHeader::Fields &fields = pHdr->GetFields();
		if (IsMatchedName(pHdr->GetFileName(), name)) {
			long offset = Gurax_UnpackInt32(fields.RelativeOffsetOfLocalHeader);
			Stream *pStream = CreateStream(env, pStreamSrc, pHdr);
			if (sig.IsSignalled()) return Value::Nil;
			pObjStream.reset(new Object_stream(env, pStream));
			break;
		}
	}
	if (pObjStream.IsNull()) {
		sig.SetError(ERR_NameError, "entry not found");
		return Value::Nil;
	}
	return ReturnValue(env, arg, Value(pObjStream.release()));
#endif
	return Value::nil();
}

// zip.Reader#Entries() {block?}
Gurax_DeclareMethod(Reader, Entries)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `iterator` instance that returns `stream` instances\n"
		"associated with each entry in the ZIP file.\n");
}

Gurax_ImplementMethod(Reader, Entries)
{
#if 0
	Signal &sig = env.GetSignal();
	Object_reader *pThis = Object_reader::GetObjectThis(arg);
	if (pThis->GetStreamSrc() == nullptr) {
		sig.SetError(ERR_ValueError, "zip object is not readable");
		return Value::Nil;
	}
	Iterator *pIterator = new Iterator_Entry(Object_reader::Reference(pThis));
	return ReturnIterator(env, arg, pIterator);
#endif
	return Value::nil();
}

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
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Reader));
	// Assignment of method
	Assign(Gurax_CreateMethod(Reader, MethodSkeleton));
	Assign(Gurax_CreateMethod(Reader, Entry));
	Assign(Gurax_CreateMethod(Reader, Entries));
	// Assignment of property
	Assign(Gurax_CreateProperty(Reader, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Reader
//------------------------------------------------------------------------------
VType& Value_Reader::vtype = VTYPE_Reader;

Gurax_EndModuleScope(zip)
