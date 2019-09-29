//==============================================================================
// gurax.cpp
// Copyright (C) 2011-2019 ypsitau
//==============================================================================
#include "stdafx.h"
#if defined(GURAX_ON_MSWIN)
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif

namespace Gurax {

bool ReadLine(const char* prompt, String& strLine);
void RunREPL();

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int Main(int argc, char* argv[])
{
	if (!Initialize(argc, argv)) {
		Error::Print(*Stream::CErr);
		return 1;
	}
	if (argc < 2) {
		if (!Basement::Inst.GetCommandDoneFlag()) RunREPL();
		return 0;
	}
	const char* fileName = argv[1];
	RefPtr<Stream> pStream(Stream::Open(PathName(fileName).MakeAbsName().c_str(), Stream::OpenFlag::Read));
	if (!pStream) return 1;
	RefPtr<Expr_Collector> pExprOfRoot(Parser::ParseStream(*pStream));
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return 1;
	}
	Composer composer;
	pExprOfRoot->Compose(composer);
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return 1;
	}
	if (Basement::Inst.GetListingFlag()) {
		composer.PrintPUnit();
	} else {
		Processor& processor = Basement::Inst.GetProcessor();
		RefPtr<Value> pValue(processor.ProcessExpr(*pExprOfRoot));
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			return 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
// RunREPL
//------------------------------------------------------------------------------
void RunREPL()
{
	Stream& stream = *Stream::COut;
	RefPtr<Parser> pParser(new Parser("*REPL*"));
	Composer composer(true);
	Processor& processor = Basement::Inst.GetProcessor();
	Expr_Collector& exprRoot = pParser->GetExprRoot();
	Expr* pExprLast = nullptr;
	const PUnit* pPUnit = nullptr;
	stream.Printf("%s\n", Version::GetBanner(false));
	for (;;) {
		String strLine;
		String prompt;
		prompt.Printf("%d:%s", pParser->GetLineNo(),
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
		for (char ch : strLine) {
			pParser->ParseChar(ch);
			if (Error::IsIssued()) break;
		}
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			Error::Clear();
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
			processor.SetPUnitNext(pPUnit);
			while (pPUnit != pPUnitSentinel && processor.GetContFlag()) {
				pPUnit->Exec(processor);
				pPUnit = processor.GetPUnitNext();
				if (Error::IsIssued()) break;
			}
			if (Error::IsIssued()) break;
			RefPtr<Value> pValue(processor.PopValue());
			if (pValue->IsValid()) stream.Printf("%s\n", pValue->ToString().c_str());
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
#if defined(GURAX_ON_MSWIN)
bool ReadLine(const char* prompt, String& strLine)
{
	strLine.clear();
	::printf("%s", prompt);
	for (;;) {
		int chRaw = ::fgetc(stdin);
		if (chRaw < 0) return false;
		char ch = static_cast<UChar>(chRaw);
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
	return Gurax::Main(argc, argv);
}
