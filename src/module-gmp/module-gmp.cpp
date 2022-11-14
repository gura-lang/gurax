//==============================================================================
// module-gmp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(gmp)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// gmp.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Adds up the given two numbers and returns the result.
)**");
}

Gurax_ImplementFunction(Test)
{
	// Function body
	mpz_class m;
	m.set_str("12345678901234567890123456789", 10);
	::printf("%s\n", m.get_str().c_str());
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of suffix manager
//------------------------------------------------------------------------------
Gurax_ImplementSuffixMgr_Eval(Number, L)
{
	if (::strchr(str, '.')  || ::strchr(str, 'e') || ::strchr(str, 'E')) {
		mpf_class num;
		if (num.set_str(str, 0) == 0) return new Value_Float(std::move(num));
		Error::Issue(ErrorType::ValueError, "invalid format for gmp.Float value");
	} else {
		mpz_class num;
		if (num.set_str(str, 0) == 0) return new Value_Int(std::move(num));
		Error::Issue(ErrorType::ValueError, "invalid format for gmp.Int value");
	}
	return Value::nil();

}

Gurax_ImplementSuffixMgr_Eval(Number, Lr)
{
	mpq_class num;
	if (num.set_str(str, 0) == 0) return new Value_Rational(std::move(num));
	Error::Issue(ErrorType::ValueError, "invalid format for gmp.Rational value");
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
	// Assignment of VType
	Assign(VTYPE_Float);
	Assign(VTYPE_Rational);
	Assign(VTYPE_Int);
	Assign(VTYPE_Random);
	// Assignment of function
	//Assign(Gurax_CreateFunction(Test));
	// Assignment of operator
	AssignOperators();
	// Assignment of suffix manager
	Gurax_AssignSuffixMgr(Number, L);
	Gurax_AssignSuffixMgr(Number, Lr);
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(gmp)
