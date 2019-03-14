//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class CommandLineEx : public CommandLine {
public:
	CommandLineEx() {
		AddInfo("debug",		'g', Type::Flag);
		AddInfo("punitlist",	'L', Type::Flag);
	}
};

int Main(int argc, char* argv[])
{
	CommandLineEx cmdLine;
	if (!cmdLine.Parse(argc, argv)) {
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
		Stream::CErr->Printf("failed to open file: %s", fileName);
		return 1;
	}
	RefPtr<Expr_Root> pExprRoot(Parser::ParseStream(*pStream));
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return 1;
	}
	Composer composer;
	pExprRoot->Compose(composer);
	if (cmdLine.IsSet("punitlist")) {
		composer.PrintPUnit();
	} else {
		RefPtr<Processor> pProcessor(cmdLine.IsSet("debug")? Processor::Debug() : Processor::Normal());
		pProcessor->Run(composer);
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
