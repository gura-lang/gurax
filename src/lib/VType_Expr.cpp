//==============================================================================
// VType_Expr.cpp
//==============================================================================
#include "stdafx.h"

#define Gurax_DeclareMethodAlias(nameVType, name, strName)	\
class Method_##nameVType##_##name : public Function { \
public: \
	Method_##nameVType##_##name(const char* name_ = strName); \
	virtual Value* DoEval(Processor& processor, Argument& argument) const override; \
}; \
Method_##nameVType##_##name::Method_##nameVType##_##name(const char* name_) : Function(Function::Type::Method, name_) \

#define Gurax_DeclareMethod(nameVType, name) Gurax_DeclareMethodAlias(nameVType, name, #name)

#define Gurax_ImplementMethod(nameVType, name) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateMethod(nameVType, name) (new Method_##nameVType##_##name())

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
VType_Expr VTYPE_Expr("Expr");

Gurax_DeclareMethod(Expr, Eval)
{
}

Gurax_ImplementMethod(Expr, Eval)
{
	return Value::nil();
}

void VType_Expr::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.Assign(*this);
	Assign(Gurax_CreateMethod(Expr, Eval));
}

//------------------------------------------------------------------------------
// Value_Expr
//------------------------------------------------------------------------------

}
