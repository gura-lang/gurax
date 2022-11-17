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
// os.Clock() {block?}
Gurax_DeclareFunction(Clock)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the time duration in second since the system has started.

If `block` is specified, it would calculate how much time has been spent
during evaluating the block.\n 
)**");
}

Gurax_ImplementFunction(Clock)
{
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	if (!pExprOfBlock) return new Value_Number(OAL::GetTickTime());
	Double timeBegin = OAL::GetTickTime();
	RefPtr<Value> pValueRtn(pExprOfBlock->Eval(processor));
	Double timeEnd = OAL::GetTickTime();
	return new Value_Number(timeEnd - timeBegin);
}

// os.Exec(pathName:string, args*:String):map:[fork]
Gurax_DeclareFunction(Exec)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(fork));
	AddHelp(Gurax_Symbol(en), u8R"**(
Runs an executable file with argument specified by `args` and waits for the process to finish.

If attribute `:fork` is specified, the executable runs in background.
)**");
}

Gurax_ImplementFunction(Exec)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	const ValueList& valList = Value_List::GetValueOwner(args.PickValue());
	bool forkFlag = argument.IsSet(Gurax_Symbol(fork));
	// Function body
	int rtn = OAL::ExecProgram(pathName, valList, g_pStreamCIn, g_pStreamCOut, g_pStreamCErr, forkFlag);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(rtn);
}

// os.Redirect(cin:Stream:nil:r, cout:Stream:nil:w, cerr?:Stream:w) {block}
Gurax_DeclareFunction(Redirect)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cin", VTYPE_Stream, ArgOccur::Once, ArgFlag::Nil | ArgFlag::StreamR);
	DeclareArg("cout", VTYPE_Stream, ArgOccur::Once, ArgFlag::Nil | ArgFlag::StreamW);
	DeclareArg("cerr", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(fork));
	DeclareBlock(DeclBlock::Occur::Once);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	RefPtr<Value> pValueRtn(pExprOfBlock->Eval(processor));
	g_pStreamCIn = pStreamCIn;
	g_pStreamCOut = pStreamCOut;
	g_pStreamCErr = pStreamCErr;
	return pValueRtn.release();
}

// os.Sleep(secs:Number)
Gurax_DeclareFunction(Sleep)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("secs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Sleeps for a time specified in seconds.
)**");
}

Gurax_ImplementFunction(Sleep)
{
	// Arguments
	ArgPicker args(argument);
	Double secs = args.PickNumberNonNeg<Double>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	OAL::Sleep(secs);
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// os.cin
Gurax_DeclareModuleProperty_RW(cin)
{
	Declare(VTYPE_Stream, Flag::Nil | Flag::StreamR | Flag::Writable);
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
	Declare(VTYPE_Stream, Flag::Nil | Flag::StreamW | Flag::Writable);
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
	Declare(VTYPE_Stream, Flag::Nil | Flag::StreamW | Flag::Writable);
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
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Initialization of module variables
	g_pStreamCIn = Basement::Inst.GetStreamCIn().Reference();
	g_pStreamCOut = Basement::Inst.GetStreamCOut().Reference();
	g_pStreamCErr = Basement::Inst.GetStreamCErr().Reference();
	// Assignment of function
	Assign(Gurax_CreateFunction(Clock));
	Assign(Gurax_CreateFunction(Exec));
	Assign(Gurax_CreateFunction(Redirect));
	Assign(Gurax_CreateFunction(Sleep));
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
