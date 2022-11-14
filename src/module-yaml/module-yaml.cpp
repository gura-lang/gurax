//==============================================================================
// module-yaml.cpp
//==============================================================================
#include "stdafx.h"
#include <yaml.h>
Gurax_BeginModule(yaml)

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
Gurax_RealizeSymbol(json);

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// yaml.Parse(text as String):[multi] {block?}
Gurax_DeclareFunction(Parse)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("text", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(multi));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementFunction(Parse)
{
	// Arguments
	ArgPicker args(argument);
	const StringReferable& text = args.PickStringReferable();
	bool multiFlag = argument.IsSet(Gurax_Symbol(multi));
	// Function body
	RefPtr<Parser> pParser(new Parser(new Stream_StringReader(text.Reference())));
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (!pParser->Parse(*pValueOwner)) return Value::nil();
	RefPtr<Value> pValueRtn;
	if (multiFlag) {
		pValueRtn.reset(new Value_List(pValueOwner.release()));
	} else if (pValueOwner->empty()) {
		pValueRtn.reset(Value::nil());
	} else {
		pValueRtn.reset(pValueOwner->front()->Reference());
	}
	return argument.ReturnValue(processor, pValueRtn.release());
}

// yaml.Read(stream as Stream):[multi] {block?}
Gurax_DeclareFunction(Read)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(multi));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	RefPtr<Value> pValueRtn;
	if (multiFlag) {
		pValueRtn.reset(new Value_List(pValueOwner.release()));
	} else if (pValueOwner->empty()) {
		pValueRtn.reset(Value::nil());
	} else {
		pValueRtn.reset(pValueOwner->front()->Reference());
	}
	return argument.ReturnValue(processor, pValueRtn.release());
}

// yaml.Write(stream:w as Stream, value):[multi,json]:void
Gurax_DeclareFunction(Write)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::StreamW);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(multi));
	DeclareAttrOpt(Gurax_Symbol(json));
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementFunction(Write)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	const Value& value = args.PickValue();
	bool multiFlag = argument.IsSet(Gurax_Symbol(multi));
	bool jsonFlag = argument.IsSet(Gurax_Symbol(json));
	// Function body
	RefPtr<Emitter> pEmitter(new Emitter(stream.Reference(), jsonFlag));
	if (!pEmitter->EmitStreamStart()) return Value::nil();
	if (multiFlag) {
		if (value.IsType(VTYPE_List)) {
			for (const Value* pValueEach : Value_List::GetValueOwner(value)) {
				if (!pEmitter->EmitDocumentStart()) return Value::nil();
				if (!pEmitter->EmitGeneric(*pValueEach)) return Value::nil();
				if (!pEmitter->EmitDocumentEnd()) return Value::nil();
			}
		} else {
			Error::Issue(ErrorType::ValueError, "the value must be a List");
			return Value::nil();
		}
	} else {
		if (!pEmitter->EmitDocumentStart()) return Value::nil();
		if (!pEmitter->EmitGeneric(value)) return Value::nil();
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
	Assign(Gurax_CreateFunction(Parse));
	Assign(Gurax_CreateFunction(Read));
	Assign(Gurax_CreateFunction(Write));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(yaml)
