//==============================================================================
// module-os.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(os)

//------------------------------------------------------------------------------
// Module variables
//------------------------------------------------------------------------------
Stream* g_pStreamCIn = nullptr;
Stream* g_pStreamCOut = nullptr;
Stream* g_pStreamCErr = nullptr;

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// os.Exec(pathName:string, args*:String):map:[fork]
Gurax_DeclareFunction(Exec)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathName", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("args", VTYPE_String, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
	DeclareAttrOpt(Gurax_Symbol(fork));
	AddHelp(
		Gurax_Symbol(en),
		"Runs an executable file with argument specified by `args` and waits for the process to finish.\n"
		"\n"
		"If attribute `:fork` is specified, the executable runs in background.\n");
}

Gurax_ImplementFunction(Exec)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	const ValueList& valList = Value_List::GetValueOwner(args.PickValue());
	// Function body
	bool forkFlag = argument.IsSet(Gurax_Symbol(fork));
	OAL::ExecProgram(pathName, valList, g_pStreamCIn, g_pStreamCOut, g_pStreamCErr, forkFlag);
	return Value::nil();
}

// os.Redirect(cin:Stream:nil:r, cout:Stream:nil:w, cerr?:Stream:w) {block}
Gurax_DeclareFunction(Redirect)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cin", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::Nil | DeclArg::Flag::Read, nullptr);
	DeclareArg("cout", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::Nil | DeclArg::Flag::Write, nullptr);
	DeclareArg("cerr", VTYPE_Stream, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::Write, nullptr);
	DeclareAttrOpt(Gurax_Symbol(fork));
	DeclareBlock(DeclBlock::Occur::Once);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Redirect)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStreamCIn = g_pStreamCIn;
	Stream* pStreamCOut = g_pStreamCOut;
	Stream* pStreamCErr = g_pStreamCErr;
	g_pStreamCIn = args.IsValid()? &Value_Stream::GetStream(args.PickValue()) : Stream::Dumb.get();
	g_pStreamCOut = args.IsValid()? &Value_Stream::GetStream(args.PickValue()) : Stream::Dumb.get();
	g_pStreamCErr = args.IsValid()? &Value_Stream::GetStream(args.PickValue()) : Stream::Dumb.get();
	// Function body
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	RefPtr<Argument> pArgument(Argument::CreateForBlockCall(*pExprOfBlock));
	RefPtr<Value> pValueRtn(pExprOfBlock->DoEval(processor, *pArgument));
	g_pStreamCIn = pStreamCIn;
	g_pStreamCOut = pStreamCOut;
	g_pStreamCErr = pStreamCErr;
	return pValueRtn.release();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// os.cin
Gurax_DeclareModuleProperty_RW(cin)
{
	Declare(VTYPE_Stream, Flag::Nil);
}

Gurax_ImplementModulePropertyGetter(cin)
{
	Stream& stream = *g_pStreamCIn;
	return stream.IsDumb()? Value::nil() : new Value_Stream(stream.Reference());
}

Gurax_ImplementModulePropertySetter(cin)
{
	g_pStreamCIn = value.IsNil()?
		Stream::Dumb->Reference() : Value_Stream::GetStream(value).Reference();
}

// os.cout
Gurax_DeclareModuleProperty_RW(cout)
{
	Declare(VTYPE_Stream, Flag::Nil);
}

Gurax_ImplementModulePropertyGetter(cout)
{
	Stream& stream = *g_pStreamCOut;
	return stream.IsDumb()? Value::nil() : new Value_Stream(stream.Reference());
}

Gurax_ImplementModulePropertySetter(cout)
{
	g_pStreamCOut = value.IsNil()?
		Stream::Dumb->Reference() : Value_Stream::GetStream(value).Reference();
}

// os.cerr
Gurax_DeclareModuleProperty_RW(cerr)
{
	Declare(VTYPE_Stream, Flag::Nil);
}

Gurax_ImplementModulePropertyGetter(cerr)
{
	Stream& stream = *g_pStreamCErr;
	return stream.IsDumb()? Value::nil() : new Value_Stream(stream.Reference());
}

Gurax_ImplementModulePropertySetter(cerr)
{
	g_pStreamCErr = value.IsNil()?
		Stream::Dumb->Reference() : Value_Stream::GetStream(value).Reference();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
	// Initialization of module variables
	g_pStreamCIn = Basement::Inst.GetStreamCIn().Reference();
	g_pStreamCOut = Basement::Inst.GetStreamCOut().Reference();
	g_pStreamCErr = Basement::Inst.GetStreamCErr().Reference();
	// Assignment of function
	Assign(Gurax_CreateFunction(Exec));
	Assign(Gurax_CreateFunction(Redirect));
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(cin));
	Assign(Gurax_CreateModuleProperty(cout));
	Assign(Gurax_CreateModuleProperty(cerr));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(os)
