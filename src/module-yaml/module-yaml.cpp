//==============================================================================
// module-yaml.cpp
//==============================================================================
#include "stdafx.h"
#include <yaml.h>
Gurax_BeginModule(yaml)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// yaml.Read(stream as Stream):[multi] {block?}
Gurax_DeclareFunction(Read)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(multi));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Read)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	bool multiFlag = argument.IsSet(Gurax_Symbol(multi));
	// Function body
	RefPtr<Parser> pParser(new Parser(stream.Reference()));
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (!pParser->Parse(*pValueOwner)) return Value::nil();
	if (multiFlag) return new Value_List(pValueOwner.release());
	return pValueOwner->empty()? Value::nil() : pValueOwner->front()->Reference();
}

// yaml.Write(stream:w as Stream, value):[multi]:void
Gurax_DeclareFunction(Write)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::StreamW);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(multi));
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Write)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	const Value& value = args.PickValue();
	bool multiFlag = argument.IsSet(Gurax_Symbol(multi));
	// Function body
	RefPtr<Emitter> pEmitter(new Emitter(stream.Reference()));
	if (!pEmitter->EmitStreamStart()) return Value::nil();
	if (multiFlag) {
		if (value.IsType(VTYPE_List)) {
			for (const Value* pValueEach : Value_List::GetValueOwner(value)) {
				if (!pEmitter->EmitDocumentStart()) return Value::nil();
				if (!pEmitter->Emit(*pValueEach)) return Value::nil();
				if (!pEmitter->EmitDocumentEnd()) return Value::nil();
			}
		} else {
			Error::Issue(ErrorType::ValueError, "the value must be a List");
			return Value::nil();
		}
	} else {
		if (!pEmitter->EmitDocumentStart()) return Value::nil();
		if (!pEmitter->Emit(value)) return Value::nil();
		if (!pEmitter->EmitDocumentEnd()) return Value::nil();
	}
	if (!pEmitter->EmitStreamEnd()) return Value::nil();
	return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of function
	Assign(Gurax_CreateFunction(Read));
	Assign(Gurax_CreateFunction(Write));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(yaml)
