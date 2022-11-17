//==============================================================================
// gurax.cpp
// Copyright (C) 2011-2020 ypsitau
//==============================================================================
#include "stdafx.h"
//#if defined(GURAX_ON_MSWIN)
#if 1
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif

namespace Gurax {

bool ReadLine(const char* prompt, String& strLine);
void RunREPL();

const char* g_strHelp =
	"usage: gurax [option] [script-file] [arg] ...\n"
	"available options:\n"
	"-h               prints this help\n"
	"-t               enters interactive mode after running script file if specified\n"
	"-i module[,..]   imports module(s) before evaluating scripts\n"
	"-I dir           specifies a directory to search for modules\n"
	"-c cmd           executes a script from command line\n"
	"-p cmd           executes a script from command line and prints the last result\n"
	"-q               suppresses version banner at the beginning of interactive mode\n"
	"-T template[,..] evaluates script code embedded in template\n"
	"-C dir           changes directory before executing scripts\n"
	"-d coding        sets character coding to describe script\n"
	"-g               enables debug mode\n"
	"-v               prints version string\n"
	"-S               searches a script file stored in shared directory\n";

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
bool Main(int argc, char* argv[])
{
	CommandLine& cmdLine = Basement::Inst.GetCommandLine();
	cmdLine
		.OptBool("help",			'h')
		.OptBool("list",			'L')
		.OptBool("quiet",			'q')
		.OptBool("shared-script",	'S')
		.OptString("template",		'T')
		.OptBool("version",			'v');
	if (!Initialize(argc, argv)) return false;
	if (cmdLine.GetBool("help")) {
		Stream::COut->Printf("%s", g_strHelp);
		return true;
	} else if (cmdLine.GetBool("version")) {
		Stream::COut->Printf("%s\n", Version::GetBanner(false));
		return true;
	}
	const char* pathNameTemplate = cmdLine.GetString("template", nullptr);
	if (pathNameTemplate) {
		RefPtr<Stream> pStream(Stream::Open(pathNameTemplate, Stream::OpenFlag::Read));
		if (!pStream) return false;
		RefPtr<Template> pTemplate(new Template());
		bool autoIndentFlag = true;
		bool appendLastEOLFlag = true;
		if (!pTemplate->ParseStream(*pStream, autoIndentFlag, appendLastEOLFlag) || !pTemplate->PrepareAndCompose()) return false;
		Processor& processor = Basement::Inst.GetProcessor();
		pTemplate->Render(processor, *Stream::COut);
		return !Error::IsIssued();
	} else if (cmdLine.argc < 2) {
		if (!Basement::Inst.GetCommandDoneFlag()) RunREPL();
		return true;
	} else {
		const char* arg = cmdLine.argv[1];
		String pathName =
			PathName(arg).IsAbsName()? arg :
			cmdLine.GetBool("shared-script")? PathName(arg).JoinBefore(OAL::GetDirName_Script().c_str()) :
			PathName(arg).MakeAbsName();
		RefPtr<Stream> pStream(Stream::Open(pathName.c_str(), Stream::OpenFlag::Read));
		if (!pStream) return false;
		RefPtr<Expr_Collector> pExprRoot(Parser::ParseStream(*pStream));
		if (!pExprRoot) return false;
		Composer composer;
		pExprRoot->Compose(composer);
		if (Error::IsIssued()) return false;
		if (cmdLine.GetBool("list")) {
			composer.PrintPUnit();
			return true;
		}
		Processor& processor = Basement::Inst.GetProcessor();
		RefPtr<Value> pValue(pExprRoot->Eval(processor));
		return !Error::IsIssued();
	}
}

//------------------------------------------------------------------------------
// RunREPL
//------------------------------------------------------------------------------
void RunREPL()
{
	const CommandLine& cmdLine = Basement::Inst.GetCommandLine();
	StringStyle ssResult(StringStyle::Flag::QuoteString | StringStyle::Flag::QuoteSymbol);
	RefPtr<Parser> pParser(new Parser("*REPL*"));
	Composer composer(true);
	Processor& processor = Basement::Inst.GetProcessor();
	Expr_Collector& exprRoot = pParser->GetExprRoot();
	Expr* pExprLast = nullptr;
	const PUnit* pPUnit = nullptr;
	if (!cmdLine.GetBool("quiet")) Stream::COut->Printf("%s\n", Version::GetBanner(false));
	for (;;) {
		String strLine;
		String prompt;
		prompt.Format("%d:%s", pParser->GetLineNo(),
					  pParser->IsContinued()? Basement::Inst.GetPS2() : Basement::Inst.GetPS1());
		if (!ReadLine(prompt.c_str(), strLine)) break;
		bool blankLineFlag = true;
		for (char ch : strLine) {
			if (!String::IsSpace(ch)) {
				blankLineFlag = false;
				break;
			}
		}
		if (blankLineFlag) continue;
		if (!pParser->FeedString(strLine.c_str())) {
			Error::Print(*Stream::CErr);
			Error::Clear();
			pParser->RecoverError();
			continue;
		}
		Expr* pExpr = pExprLast? pExprLast->GetExprNext() : exprRoot.GetExprElemFirst();
		for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
			pExprLast = pExpr;
			if (!pExpr->Prepare()) break;
			if (Error::IsIssued()) break;
			pExpr->Compose(composer);
			composer.Flush();
			if (Error::IsIssued()) break;
			const PUnit* pPUnitSentinel = composer.PeekPUnitCont();
			if (!pPUnit && !(pPUnit = composer.GetPUnitFirst())) continue;
			processor.SetPUnitCur(pPUnit);
			while (pPUnit != pPUnitSentinel && processor.GetContFlag()) {
				pPUnit->Exec(processor);
				pPUnit = processor.GetPUnitCur();
				if (Error::IsIssued()) break;
			}
			if (Error::IsIssued()) break;
			RefPtr<Value> pValueResult(processor.PopValue());
			if (pValueResult->IsValid()) {
				Stream::COut->Printf("%s\n", pValueResult->ToString(ssResult).c_str());
			}
		}
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			processor.ClearValueStack();
			processor.ClearError();
			pPUnit = composer.PeekPUnitCont();
		}
	}
}

//------------------------------------------------------------------------------
// ReadLine
//------------------------------------------------------------------------------
//#if defined(GURAX_ON_MSWIN)
#if 1
bool ReadLine(const char* prompt, String& strLine)
{
	strLine.clear();
	::printf("%s", prompt);
	for (;;) {
		char ch = Stream::CIn->GetChar();
		if (ch == '\0') break;
		strLine += ch;
		if (ch == '\n') break;
	}
	return true;
}
#else
bool ReadLine(const char* prompt, String& strLine)
{
	char* lineBuff = readline(prompt);
	if (lineBuff == nullptr) return false;
	if (lineBuff[0] != '\0') add_history(lineBuff);
	strLine = lineBuff;
	::free(lineBuff);
	strLine += '\n';
	return true;
}
#endif

}

int main(int argc, char* argv[])
{
	if (Gurax::Main(argc, argv)) return 0;
	Gurax::Error::Print(*Gurax::Stream::CErr);
	return 1;
}
