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
	_argc(0), _argv(nullptr), _debugFlag(false), _listingFlag(false),
	_pFrame(new Frame_Basement()),
	_pSuffixMgrMap_Number(new SuffixMgrMap()), _pSuffixMgrMap_String(new SuffixMgrMap()),
	_ps1(">>> "), _ps2("... ")
{
}

bool Basement::Initialize(int& argc, char** argv)
{
	CommandLine cmdLine;
	if (!cmdLine
		.OptMultiString	("module-path",	'I')
		.OptBool		("debug",		'g')
		.OptBool		("list",		'L')
		.Parse(argc, argv)) {
		Error::Issue(ErrorType::CommandError, "%s", cmdLine.GetError());
		return false;
	}
	_argc = argc;
	_argv = argv;
	_debugFlag = cmdLine.GetBool("debug");
	_listingFlag = cmdLine.GetBool("list");
	Frame& frame = GetFrame();
	PrepareVType(frame);
	PrepareValue(frame);
	AppendPathList(".");
	AppendPathList(cmdLine.GetStringList("module-path"));
	AppendPathList(OAL::GetEnv("GURAXPATH"));
	Statements::AssignToBasement(frame);
	Functions::AssignToBasement(frame);
	SetStreamCIn(Stream::CIn->Reference());
	SetStreamCOut(Stream::COut->Reference());
	SetStreamCErr(Stream::CErr->Reference());
	frame.Assign(Module_codecs::Create(frame.Reference()));
	frame.Assign(Module_codecs_basic::Create(frame.Reference()));
	frame.Assign(Module_codecs_chinese::Create(frame.Reference()));
	frame.Assign(Module_codecs_iso8859::Create(frame.Reference()));
	frame.Assign(Module_codecs_japanese::Create(frame.Reference()));
	frame.Assign(Module_fs::Create(frame.Reference()));
	frame.Assign(Module_math::Create(frame.Reference()));
	frame.Assign(Module_os::Create(frame.Reference()));
	frame.Assign(Module_path::Create(frame.Reference()));
	frame.Assign(Module_re::Create(frame.Reference()));
	frame.Assign(Module_sys::Create(frame.Reference()));
	return true;
}

void Basement::PrepareVType(Frame& frame)
{
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

void Basement::PrepareValue(Frame& frame)
{
	Value::CreateConstant();
	frame.Assign("nil",		Value::nil());
	frame.Assign("false",	Value::false_());
	frame.Assign("true",	Value::true_());
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

void Basement::AssignSuffixMgr(SuffixMgr* pSuffixMgr, bool numberFlag)
{
	if (numberFlag) {
		GetSuffixMgrMap_Number().Assign(pSuffixMgr);
	} else {
		GetSuffixMgrMap_String().Assign(pSuffixMgr);
	}
}

const SuffixMgr* Basement::LookupSuffixMgr(const Symbol* pSymbolSuffix, bool numberFlag) const
{
	return numberFlag?
		GetSuffixMgrMap_Number().Lookup(pSymbolSuffix) :
		GetSuffixMgrMap_String().Lookup(pSymbolSuffix);
}

}
