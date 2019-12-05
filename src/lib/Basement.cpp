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
	_cmdLine
		.OptMultiString	("import",			'i')
		.OptMultiString	("command",			'c')
		.OptMultiString	("module-path",		'I')
		.OptBool		("debug",			'g')
		.OptBool		("naked");
	if (!_cmdLine.Parse(argc, argv)) {
		Error::Issue(ErrorType::CommandError, "%s", _cmdLine.GetError());
		return false;
	}
	_pProcessor.reset(Processor::Create(_cmdLine.GetBool("debug")));
	PrepareVType();
	PrepareValue();
	PreparePathList();
	PrepareFunction();
	PrepareConsoleStream();
	if (!Module::ImportAllBuiltIns(GetProcessor())) return false;
	if (!Module::ImportByNameList(GetProcessor(), _cmdLine.GetStringList("import"))) return false;
	for (const String& cmd : _cmdLine.GetStringList("command")) {
		if (!ExecCommand(GetProcessor(), cmd.c_str())) return false;
		_commandDoneFlag = true;
	}
	return true;
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
	VTYPE_Help.Prepare(frame);
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

void Basement::Present(Processor& processor, RefPtr<Value> pValue)
{
	if (_pFuncPresenter) Value::Delete(_pFuncPresenter->EvalEasy(processor, pValue.release()));
}

bool Basement::ExecCommand(Processor& processor, const char* cmd)
{
	RefPtr<Expr_Collector> pExprOfRoot(Parser::ParseString(cmd));
	if (!pExprOfRoot) return false;
	Composer composer;
	pExprOfRoot->Compose(composer);
	if (Error::IsIssued()) return false;
	Value::Delete(pExprOfRoot->Eval(processor));
	return !Error::IsIssued();
}

}
