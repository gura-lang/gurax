﻿//==============================================================================
// VType_Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

${help.ComposePropertyHelp(Frame, `en)}

# Cast Operation

${help.ComposeConstructorHelp(Frame, `en)}

${help.ComposeMethodHelp(Frame, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Frame() {block?}
Gurax_DeclareConstructor(Frame)
{
	Declare(VTYPE_Frame, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Frame` instance of the current scope.
)""");
}

Gurax_ImplementConstructor(Frame)
{
	// Arguments
	ArgPicker args(argument);
	// Function body
	RefPtr<Value> pValueRtn(new Value_Frame(processor.GetFrameCur().Reference()));
	return argument.ReturnValue(processor, pValueRtn.release());
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Frame##__functions__() {block?}
Gurax_DeclareHybridMethod(Frame, __functions__)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementHybridMethod(Frame, __functions__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	Frame& frame = valueThis.GetFrame();
	SymbolList symbolList;
	frame.GatherSymbolIf(symbolList, Value_Function::GatherCriteria_Function());
	symbolList.Sort();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	for (const Symbol* pSymbol : symbolList) {
		RefPtr<Value> pValue(frame.Retrieve(pSymbol));
		if (pValue) pValueOwner->push_back(pValue.release());
	}
	RefPtr<Iterator> pIterator(new Iterator_Each(pValueOwner.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Frame##__statements__() {block?}
Gurax_DeclareHybridMethod(Frame, __statements__)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementHybridMethod(Frame, __statements__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	Frame& frame = valueThis.GetFrame();
	SymbolList symbolList;
	frame.GatherSymbolIf(symbolList, Value_Function::GatherCriteria_Statement());
	symbolList.Sort();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	for (const Symbol* pSymbol : symbolList) {
		RefPtr<Value> pValue(frame.Retrieve(pSymbol));
		if (pValue) pValueOwner->push_back(pValue.release());
	}
	RefPtr<Iterator> pIterator(new Iterator_Each(pValueOwner.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Frame##__vtypes__() {block?}
Gurax_DeclareHybridMethod(Frame, __vtypes__)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementHybridMethod(Frame, __vtypes__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	Frame& frame = valueThis.GetFrame();
	SymbolList symbolList;
	frame.GatherSymbolIf(symbolList, Value_VType::GatherCriteria());
	symbolList.Sort();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	for (const Symbol* pSymbol : symbolList) {
		RefPtr<Value> pValue(frame.Retrieve(pSymbol));
		if (pValue) pValueOwner->push_back(pValue.release());
	}
	RefPtr<Iterator> pIterator(new Iterator_Each(pValueOwner.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Frame.GetCurrent() as Frame
Gurax_DeclareClassMethod(Frame, GetCurrent)
{
	Declare(VTYPE_Frame, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementClassMethod(Frame, GetCurrent)
{
	return new Value_Frame(processor.GetFrameCur().Reference());
}

// Frame.PrintStack():void
Gurax_DeclareClassMethod(Frame, PrintStack)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementClassMethod(Frame, PrintStack)
{
	processor.GetFrameStack().Print(Basement::Inst.GetStreamCOut());
	return Value::nil();
}

// Frame.Where(symbol as Symbol) {block?}
Gurax_DeclareClassMethod(Frame, Where)
{
	Declare(VTYPE_Frame, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Searches a value in the current environment and returns a `Frame` instance where it's found.
If the symbol is not found, it returns `nil`.
)""");
}

Gurax_ImplementClassMethod(Frame, Where)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	bool raiseFlag = argument.IsSet(Gurax_Symbol(raise));
	// Function body
	Frame* pFrameSrc = nullptr;
	RefPtr<Value> pValue(processor.GetFrameCur().DoRetrieve(pSymbol, &pFrameSrc));
	RefPtr<Value> pValueRtn(Value::nil());
	if (pValue) {
		pValueRtn.reset(new Value_Frame(pFrameSrc->Reference()));
	} else if (raiseFlag) {
		Error::Issue(ErrorType::SymbolError, "symbol is not found: %s", pSymbol->GetName());
		return Value::nil();
	}
	return argument.ReturnValue(processor, pValueRtn.release());
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Frame#Assign(symbol as Symbol, value as any):reduce
Gurax_DeclareMethod(Frame, Assign)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Frame, Assign)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Frame& frame = valueThis.GetFrame();
	// Argument
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	const Value& value = args.PickValue();
	// Function body
	frame.Assign(pSymbol, value.Reference());
	return valueThis.Reference();
}

// Frame#PrintTree():void
Gurax_DeclareMethod(Frame, PrintTree)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints the frame's information.
)""");
}

Gurax_ImplementMethod(Frame, PrintTree)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetFrame().PrintTree(Basement::Inst.GetStreamCOut());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Frame#id
Gurax_DeclareProperty_R(Frame, id)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Frame, id)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetFrame().MakeId());
}

// Frame#local
Gurax_DeclareProperty_R(Frame, local)
{
	Declare(VTYPE_Frame, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Frame, local)
{
	auto& valueThis = GetValueThis(valueTarget);
	Frame* pFrame = valueThis.GetFrame().DoGetFrameLocal();
	if (!pFrame) return Value::nil();
	return new Value_Frame(pFrame->Reference());
}

// Frame#outer
Gurax_DeclareProperty_R(Frame, outer)
{
	Declare(VTYPE_Frame, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Frame, outer)
{
	auto& valueThis = GetValueThis(valueTarget);
	Frame* pFrame = valueThis.GetFrame().GetFrameOuter();
	if (!pFrame) return Value::nil();
	return new Value_Frame(pFrame->Reference());
}

// Frame#symbols
Gurax_DeclareProperty_R(Frame, symbols)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Frame, symbols)
{
	auto& valueThis = GetValueThis(valueTarget);
	SymbolList symbols;
	valueThis.GetFrame().GatherSymbol(symbols);
	symbols.Sort();
	RefPtr<ValueOwner> pValues(new ValueOwner());
	pValues->reserve(symbols.size());
	for (const Symbol* pSymbol : symbols) {
		pValues->push_back(new Value_Symbol(pSymbol));
	}
	return new Value_List(VTYPE_Symbol, pValues.release());
}

// Frame#typeName
Gurax_DeclareProperty_R(Frame, typeName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Frame, typeName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetFrame().GetTypeName());
}

//------------------------------------------------------------------------------
// VType_Frame
//------------------------------------------------------------------------------
VType_Frame VTYPE_Frame("Frame");

void VType_Frame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Frame));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Frame, GetCurrent));
	Assign(Gurax_CreateClassMethod(Frame, PrintStack));
	Assign(Gurax_CreateClassMethod(Frame, Where));
	// Assignment of method
	Assign(Gurax_CreateMethod(Frame, __functions__));
	Assign(Gurax_CreateMethod(Frame, __statements__));
	Assign(Gurax_CreateMethod(Frame, __vtypes__));
	Assign(Gurax_CreateMethod(Frame, Assign));
	Assign(Gurax_CreateMethod(Frame, PrintTree));
	// Assignment of property
	Assign(Gurax_CreateProperty(Frame, id));
	Assign(Gurax_CreateProperty(Frame, outer));
	Assign(Gurax_CreateProperty(Frame, symbols));
	Assign(Gurax_CreateProperty(Frame, typeName));
}

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------
VType& Value_Frame::vtype = VTYPE_Frame;

String Value_Frame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetFrame().ToString(ss));
}

}
