//==============================================================================
// Constructor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Constructor::Constructor(VTypeCustom& vtypeCustom, Function* pFuncInitializer) :
	Function(Type::Function, Symbol::Empty, pFuncInitializer->GetDeclCallable().Reference()),
	_vtypeCustom(vtypeCustom), _pFuncInitializer(pFuncInitializer)
{
}

Value* Constructor::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<Value> pValueThis(new ValueCustom(GetVTypeCustom()));
	argument.SetValueThis(pValueThis.Reference());
	RefPtr<Value> pValue(GetFuncInitializer().DoEval(processor, argument));
	return pValueThis.release();
}

String Constructor::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
