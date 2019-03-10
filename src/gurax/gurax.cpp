//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

int Main(int argc, char* argv[])
{
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
	composer.GetPUnitList().Print();
	RefPtr<Processor> pProcessor(Processor::Debug());
	pProcessor->Run(composer.GetPUnitTop());
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return 1;
	}
	return 0;
}

}

int main(int argc, char* argv[])
{
	Gurax::Initialize();
	return Gurax::Main(argc, argv);
}
