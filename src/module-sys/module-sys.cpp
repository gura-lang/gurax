//==============================================================================
// module-sys.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(sys)

RefPtr<Value> g_pValue_argv;

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// sys.Exit(exitCode?:Number):void
Gurax_DeclareFunction(Exit)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("exitCode", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Exit)
{
	// Arguments
	ArgPicker args(argument);
	int exitCode = args.IsDefined()? args.PickNumberNonNeg<Int>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	std::exit(exitCode);
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// sys.argv
Gurax_DeclareModuleProperty_R(argv)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A list of `string` that represents arguments in the command line.");
}

Gurax_ImplementModulePropertyGetter(argv)
{
	return g_pValue_argv->Reference();
}

// sys.cin
Gurax_DeclareModuleProperty_RW(cin)
{
	Declare(VTYPE_Stream, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"A `stream` instance used for standard input on a console.");
}

Gurax_ImplementModulePropertyGetter(cin)
{
	Stream& stream = Basement::Inst.GetStreamCIn();
	return stream.IsDumb()? Value::nil() : new Value_Stream(stream.Reference());
}

Gurax_ImplementModulePropertySetter(cin)
{
	Basement::Inst.SetStreamCIn(
		value.IsNil()? Stream::Dumb->Reference() : Value_Stream::GetStream(value).Reference());
}

// sys.cout
Gurax_DeclareModuleProperty_RW(cout)
{
	Declare(VTYPE_Stream, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"A `stream` instance used for standard output on a console.");
}

Gurax_ImplementModulePropertyGetter(cout)
{
	Stream& stream = Basement::Inst.GetStreamCOut();
	return stream.IsDumb()? Value::nil() : new Value_Stream(stream.Reference());
}

Gurax_ImplementModulePropertySetter(cout)
{
	Basement::Inst.SetStreamCOut(
		value.IsNil()? Stream::Dumb->Reference() : Value_Stream::GetStream(value).Reference());
}

// sys.cerr
Gurax_DeclareModuleProperty_RW(cerr)
{
	Declare(VTYPE_Stream, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"A `stream` instance used for standard error output on a console.");
}

Gurax_ImplementModulePropertyGetter(cerr)
{
	Stream& stream = Basement::Inst.GetStreamCErr();
	return stream.IsDumb()? Value::nil() : new Value_Stream(stream.Reference());
}

Gurax_ImplementModulePropertySetter(cerr)
{
	Basement::Inst.SetStreamCErr(
		value.IsNil()? Stream::Dumb->Reference() : Value_Stream::GetStream(value).Reference());
}

// sys.dirFont
Gurax_DeclareModuleProperty_R(dirFont)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the directory for font files.");
}

Gurax_ImplementModulePropertyGetter(dirFont)
{
	return new Value_String("");
}

// sys.dirInclude
Gurax_DeclareModuleProperty_R(dirInclude)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the directory for include files.");
}

Gurax_ImplementModulePropertyGetter(dirInclude)
{
	return new Value_String("");
}

// sys.dirLib
Gurax_DeclareModuleProperty_R(dirLib)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the directory for library files.");
}

Gurax_ImplementModulePropertyGetter(dirLib)
{
	return new Value_String("");
}

// sys.dirLocal
Gurax_DeclareModuleProperty_R(dirLocal)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the base directory for local files.");
}

Gurax_ImplementModulePropertyGetter(dirLocal)
{
	return new Value_String("");
}

// sys.dirMain
Gurax_DeclareModuleProperty_R(dirMain)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the main directory.");
}

Gurax_ImplementModulePropertyGetter(dirMain)
{
	return new Value_String("");
}

// sys.dirModule
Gurax_DeclareModuleProperty_R(dirModule)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the base directory for module files.");
}

Gurax_ImplementModulePropertyGetter(dirModule)
{
	return new Value_String("");
}

// sys.dirScript
Gurax_DeclareModuleProperty_R(dirScript)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the base directory for script files.");
}

Gurax_ImplementModulePropertyGetter(dirScript)
{
	return new Value_String("");
}

// sys.executable
Gurax_DeclareModuleProperty_R(executable)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the executable.");
}

Gurax_ImplementModulePropertyGetter(executable)
{
	return new Value_String(OAL::GetExecutablePath());
}

// sys.path[]:String
Gurax_DeclareModuleProperty_RW(path)
{
	Declare(VTYPE_String, Flag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"A list of path names in which imported Gura modules are searched.");
}

Gurax_ImplementModulePropertyGetter(path)
{
	RefPtr<ValueOwner> pValues(new ValueOwner());
	const StringList& pathList = Basement::Inst.GetPathList();
	pValues->reserve(pathList.size());
	for (const String& dirName : pathList) {
		pValues->push_back(new Value_String(dirName));
	}
	return new Value_List(VTYPE_String, pValues.release());
}

Gurax_ImplementModulePropertySetter(path)
{
	const ValueOwner& values = Value_List::GetValueTypedOwner(value).GetValueOwner();
	StringList& pathList = Basement::Inst.GetPathList();
	pathList.clear();
	pathList.reserve(values.size());
	for (const Value* pValue : values) {
		pathList.push_back(Value_String::GetStringSTL(*pValue));
	}
}

// sys.ps1:String
Gurax_DeclareModuleProperty_RW(ps1)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The first-level prompt in REPL.");
}

Gurax_ImplementModulePropertyGetter(ps1)
{
	return new Value_String(Basement::Inst.GetPS1());
}

Gurax_ImplementModulePropertySetter(ps1)
{
	Basement::Inst.SetPS1(Value_String::GetString(value));
}

// sys.ps2:String
Gurax_DeclareModuleProperty_RW(ps2)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The second-level prompt in REPL.");
}

Gurax_ImplementModulePropertyGetter(ps2)
{
	return new Value_String(Basement::Inst.GetPS2());
}

Gurax_ImplementModulePropertySetter(ps2)
{
	Basement::Inst.SetPS2(Value_String::GetString(value));
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
	// Initialization of global variable
	do {
		RefPtr<ValueOwner> pValues(new ValueOwner());
		int argc = Basement::Inst.GetArgc();
		char** argv = Basement::Inst.GetArgv();
		if (argc > 1) {
			pValues->reserve(argc - 1);
			for (int iArg = 1; iArg < argc; iArg++) {
				pValues->push_back(new Value_String(argv[iArg]));
			}
		}
		g_pValue_argv.reset(new Value_List(VTYPE_String, pValues.release()));
	} while (0);
	// Assignment of function
	Assign(Gurax_CreateFunction(Exit));
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(argv));
	Assign(Gurax_CreateModuleProperty(cin));
	Assign(Gurax_CreateModuleProperty(cout));
	Assign(Gurax_CreateModuleProperty(cerr));
	Assign(Gurax_CreateModuleProperty(dirFont));
	Assign(Gurax_CreateModuleProperty(dirInclude));
	Assign(Gurax_CreateModuleProperty(dirLib));
	Assign(Gurax_CreateModuleProperty(dirLocal));
	Assign(Gurax_CreateModuleProperty(dirMain));
	Assign(Gurax_CreateModuleProperty(dirModule));
	Assign(Gurax_CreateModuleProperty(dirScript));
	Assign(Gurax_CreateModuleProperty(executable));
	Assign(Gurax_CreateModuleProperty(path));
	Assign(Gurax_CreateModuleProperty(ps1));
	Assign(Gurax_CreateModuleProperty(ps2));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(sys)
