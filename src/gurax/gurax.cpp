//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

int Main(int argc, char* argv[])
{
	CommandLine cmdLine;
	if (!cmdLine
		.OptBool("debug",	'g')
		.OptBool("list",	'L')
		.Parse(argc, argv)) {
		Stream::CErr->Printf("%s\n", cmdLine.GetError());
		return 1;
	}
	if (argc < 2) {
		Stream::CErr->Printf("usage: gurax file\n");
		return 1;
	}
	const char* fileName = argv[1];
	RefPtr<Stream> pStream(Stream_File::Open(fileName, "rt"));
	if (!pStream) {
		Stream::CErr->Printf("failed to open file '%s'\n", fileName);
		return 1;
	}
	RefPtr<Expr_Root> pExprOfRoot(Parser::ParseStream(*pStream));
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
	if (cmdLine.GetBool("list")) {
		composer.PrintPUnit();
	} else {
		RefPtr<Processor> pProcessor(Processor::Create(cmdLine.GetBool("debug")));
		pProcessor->Eval(composer);
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			return 1;
		}
	}
	return 0;
}

}

int main(int argc, char* argv[])
{
	Gurax::Initialize();
	return Gurax::Main(argc, argv);
}
