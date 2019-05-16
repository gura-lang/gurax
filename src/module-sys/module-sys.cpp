//==============================================================================
// module-sys.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(sys)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// sys.Exit(exitCode?:Number):void
Gurax_DeclareFunction(Exit)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("exitCode", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Exit)
{
	// Arguments
	ArgPicker args(argument);
	int exitCode = args.IsDefined()? args.PickInt() : 0;
	// Function body
	std::exit(exitCode);
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// sys.path[]:String
Gurax_DeclareModuleProperty_RW(path)
{
	Declare(VTYPE_String, Flag::ListVar);
}

Gurax_ImplementModulePropertyGetter(path)
{
	RefPtr<ValueTypedOwner> pValues(new ValueTypedOwner());
	const StringList& pathList = Basement::Inst.GetPathList();
	pValues->Reserve(pathList.size());
	for (const String& dirName : pathList) {
		pValues->Add(new Value_String(dirName));
	}
	return new Value_List(pValues.release());
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
	// Assignment of value
	Assign("cin", new Value_Stream(Stream::CIn->Reference()));
	Assign("cout", new Value_Stream(Stream::COut->Reference()));
	Assign("cerr", new Value_Stream(Stream::CErr->Reference()));
	// Assignment of function
	Assign(Gurax_CreateFunction(Exit));
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(path));
	Assign(Gurax_CreateModuleProperty(ps1));
	Assign(Gurax_CreateModuleProperty(ps2));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(sys)
