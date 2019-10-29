//==============================================================================
// Basement.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Basement
//------------------------------------------------------------------------------
Basement Basement::Inst;

Basement::Basement() :
	_commandDoneFlag(false), _pFrame(new Frame_Basement()), _pSuffixMgrMap(new SuffixMgrMap()),
	_ps1(">>> "), _ps2("... ")
{
}

bool Basement::Initialize(int argc, char** argv)
{
	if (!_cmdLine
		.OptMultiString	("import",			'i')
		.OptMultiString	("command",			'c')
		.OptMultiString	("module-path",		'I')
		.OptBool		("debug",			'g')
		.OptBool		("list",			'L')
		.OptBool		("shared-script",	'S')
		.Parse(argc, argv)) {
		Error::Issue(ErrorType::CommandError, "%s", _cmdLine.GetError());
		return false;
	}
	_pProcessor.reset(Processor::Create(_cmdLine.GetBool("debug")));
	PrepareVType();
	PrepareValue();
	PreparePathList();
	PrepareFunction();
	PrepareConsoleStream();
	ImportModule();
	return ExecCommand();
}

void Basement::PrepareVType()
{
	Frame& frame = GetFrame();
	VTYPE_Object.Prepare(frame);
	VTYPE_Any.Prepare(frame);
	VTYPE_ArgMapper.Prepare(frame);
	VTYPE_ArgMapper_Multiple.Prepare(frame);
	VTYPE_ArgSlot.Prepare(frame);
	VTYPE_Argument.Prepare(frame);
	VTYPE_Attribute.Prepare(frame);
	VTYPE_Binary.Prepare(frame);
	VTYPE_Bool.Prepare(frame);
	VTYPE_CallableMember.Prepare(frame);
	VTYPE_Codec.Prepare(frame);
	VTYPE_Color.Prepare(frame);
	VTYPE_Complex.Prepare(frame);
	VTYPE_DateTime.Prepare(frame);
	VTYPE_Dict.Prepare(frame);
	VTYPE_Directory.Prepare(frame);
	VTYPE_DirRecord.Prepare(frame);
	VTYPE_DirStructure.Prepare(frame);
	VTYPE_Error.Prepare(frame);
	VTYPE_ErrorType.Prepare(frame);
	VTYPE_Expr.Prepare(frame);
	VTYPE_Frame.Prepare(frame);
	VTYPE_Function.Prepare(frame);
	VTYPE_Iterator.Prepare(frame);
	VTYPE_KeyValuePair.Prepare(frame);
	VTYPE_VType.Prepare(frame);
	VTYPE_List.Prepare(frame);
	VTYPE_Module.Prepare(frame);
	VTYPE_Nil.Prepare(frame);
	VTYPE_Number.Prepare(frame);
	VTYPE_PathMgr.Prepare(frame);
	VTYPE_Palette.Prepare(frame);
	VTYPE_PropHandler.Prepare(frame);
	VTYPE_PUnit.Prepare(frame);
	VTYPE_Quote.Prepare(frame);
	VTYPE_Random.Prepare(frame);
	VTYPE_Stream.Prepare(frame);
	VTYPE_String.Prepare(frame);
	VTYPE_StringPtr.Prepare(frame);
	VTYPE_Symbol.Prepare(frame);
	VTYPE_Template.Prepare(frame);
	VTYPE_TimeDelta.Prepare(frame);
	VTYPE_Undefined.Prepare(frame);
}

void Basement::PrepareValue()
{
	Frame& frame = GetFrame();
	Value::CreateConstant();
	frame.Assign("-",		Value::nil());
	frame.Assign("nil",		Value::nil());
	frame.Assign("false",	Value::false_());
	frame.Assign("true",	Value::true_());
}

void Basement::PreparePathList()
{
	AppendPathList(".");
	AppendPathList(_cmdLine.GetStringList("module-path"));
	AppendPathList(OAL::GetEnv("GURAXPATH"));
	AppendPathList(OAL::GetDirName_Module());
	AppendPathList(PathName(OAL::GetDirName_Module()).JoinAfter("site"));
}

void Basement::PrepareFunction()
{
	Frame& frame = GetFrame();
	Statements::AssignToBasement(frame);
	Functions::AssignToBasement(frame);
}

void Basement::PrepareConsoleStream()
{
	SetStreamCIn(Stream::CIn->Reference());
	SetStreamCOut(Stream::COut->Reference());
	SetStreamCErr(Stream::CErr->Reference());
}

bool Basement::ImportModule()
{
	Frame& frame = GetFrame();
	Processor& processor = GetProcessor();
	if (!Module_codecs::ImportBuiltIn(frame)) return false;
	if (!Module_codecs_basic::ImportBuiltIn(frame)) return false;
	if (!Module_codecs_chinese::ImportBuiltIn(frame)) return false;
	if (!Module_codecs_iso8859::ImportBuiltIn(frame)) return false;
	if (!Module_codecs_japanese::ImportBuiltIn(frame)) return false;
	if (!Module_fs::ImportBuiltIn(frame)) return false;
	if (!Module_math::ImportBuiltIn(frame)) return false;
	if (!Module_os::ImportBuiltIn(frame)) return false;
	if (!Module_path::ImportBuiltIn(frame)) return false;
	//if (!Module_re::ImportBuiltIn(frame)) return false;
	if (!Module_sys::ImportBuiltIn(frame)) return false;
	for (const String& str : _cmdLine.GetStringList("import")) {
		StringList moduleNames;
		str.Split(moduleNames, ',');
		for (const String& moduleName : moduleNames) {
			if (!processor.ImportModule(moduleName.c_str())) return false;
		}
	}
	return true;
}

bool Basement::ExecCommand()
{
	Processor& processor = GetProcessor();
	for (const String& cmd : _cmdLine.GetStringList("command")) {
		if (!processor.EvalCommand(cmd.c_str())) return false;
		_commandDoneFlag = true;
	}
	return true;
}

void Basement::AppendPathList(const String& str)
{
	StringList dirNames;
	str.Split(dirNames, ':');
	for (const String& dirName : dirNames) {
		String dirNameStripped = dirName.Strip(true, true);
		if (!dirNameStripped.empty()) _pathList.push_back(dirNameStripped);
	}
}

void Basement::AppendPathList(const StringList& strs)
{
	for (const String& str : strs) AppendPathList(str);
}

}
