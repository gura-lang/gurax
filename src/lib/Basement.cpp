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
	Frame& frame = GetFrame();
	_cmdLine
		.OptMultiString	("import",			'i')
		.OptMultiString	("command",			'c')
		.OptMultiString	("command-p",		'p')
		.OptMultiString	("module-path",		'I')
		.OptBool		("debug",			'g')
		.OptBool		("naked");
	if (!_cmdLine.Parse(argc, argv)) {
		Error::Issue(ErrorType::CommandError, "%s", _cmdLine.GetError());
		return false;
	}
	_pProcessor.reset(Processor::Create(_cmdLine.GetBool("debug")));
	Processor& processor = *_pProcessor;
	BasicVType::Prepare(frame);
	BasicStatement::Prepare(frame);
	BasicFunction::Prepare(frame);
	PrepareValue();
	PreparePathList();
	PrepareConsoleStream();
	if (!Module::ImportAllBuiltIns(processor)) return false;
	SetConsoleStreamCodec();
	if (!_cmdLine.GetBool("naked")) {
		if (!Module::ImportByName(processor, "markdown")) return false;
		if (!Module::ImportByName(processor, "zip")) return false;
		if (!Module::ImportByName(processor, "help")) return false;
	}
	if (!Module::ImportByNameList(processor, _cmdLine.GetStringList("import"))) return false;
	for (const String& cmd : _cmdLine.GetStringList("command")) {
		if (!ExecCommand(processor, cmd.c_str(), false)) return false;
		_commandDoneFlag = true;
	}
	for (const String& cmd : _cmdLine.GetStringList("command-p")) {
		if (!ExecCommand(processor, cmd.c_str(), true)) return false;
		_commandDoneFlag = true;
	}
	return true;
}

void Basement::PrepareValue()
{
	Frame& frame = GetFrame();
	Value::CreateConstant();
	frame.Assign(Gurax_Symbol(__name__),	new Value_String("__main__"));
	frame.Assign(Gurax_Symbol(__root__),	new Value_Frame(GetFrame().Reference()));
	frame.Assign(Gurax_SymbolMark(Sub),		Value::nil());   	// symbol '-'
	frame.Assign(Gurax_Symbol(nil),			Value::nil());		// symbol 'nil'
	frame.Assign(Gurax_Symbol(false_),		Value::false_());	// symbol 'false'
	frame.Assign(Gurax_Symbol(true_),		Value::true_());	// symbol 'true'
}

void Basement::PreparePathList()
{
	AppendPathList(".");
	AppendPathList(_cmdLine.GetStringList("module-path"));
	AppendPathList(OAL::GetEnv("GURAX_PATH"));
	AppendPathList(OAL::GetDirName_Module());
	AppendPathList(PathName(OAL::GetDirName_Module()).JoinAfter("site"));
}

void Basement::PrepareConsoleStream()
{
	SetStreamCIn(Stream::CIn->Reference());
	SetStreamCOut(Stream::COut->Reference());
	SetStreamCErr(Stream::CErr->Reference());
}

void Basement::SetConsoleStreamCodec()
{
	CodecFactory* pCodecFactory = CodecFactory::Lookup(OAL::GetEncodingForConsole());
	if (pCodecFactory) {
		Stream::CIn->SetCodec(pCodecFactory->CreateCodec(true, false));
		Stream::COut->SetCodec(pCodecFactory->CreateCodec(true, false));
		Stream::CErr->SetCodec(pCodecFactory->CreateCodec(true, false));
	}
}

void Basement::AppendPathList(const String& str)
{
	StringList dirNames;
	str.Split(dirNames, OAL::SepPathList);
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

bool Basement::ExecCommand(Processor& processor, const char* cmd, bool printFlag)
{
	RefPtr<Expr_Collector> pExprOfRoot(Parser::ParseString(cmd));
	if (!pExprOfRoot) return false;
	Composer composer;
	pExprOfRoot->Compose(composer);
	if (Error::IsIssued()) return false;
	RefPtr<Value> pValue(pExprOfRoot->Eval(processor));
	if (printFlag && pValue->IsValid()) {
		Stream::COut->Printf("%s", pValue->ToString().c_str());
	}
	return !Error::IsIssued();
}

}
