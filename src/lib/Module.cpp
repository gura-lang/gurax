//==============================================================================
// Module.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
bool Module::Prepare(DottedSymbol* pDottedSymbol)
{
	SetDottedSymbol(pDottedSymbol);
	return DoPrepare();
}

bool Module::Prepare(const char* name, char separator)
{
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
	pDottedSymbol->AppendFromString(name, separator);
	return Prepare(pDottedSymbol.release());
}

Module* Module::Import(Processor& processor, const DottedSymbol& dottedSymbol)
{
	String fileName = dottedSymbol.ToString();
	fileName += ".gura";
	RefPtr<Stream> pStream(Stream_File::Open(fileName.c_str(), "rt"));
	if (!pStream) {
		Error::Issue(ErrorType::ModuleError, "failed to open a module file '%s'", fileName.c_str());
		return nullptr;
	}
	RefPtr<Expr_Root> pExprOfRoot(Parser::ParseStream(*pStream));
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return nullptr;
	}
	Composer composer;
	pExprOfRoot->Compose(composer);
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return nullptr;
	}
	RefPtr<Module> pModule(new Module(processor.GetFrameCur().Reference(), dottedSymbol.Reference()));
	processor.PushFrame(pModule->GetFrame().Reference());
	processor.Eval(composer);
	processor.PopFrame();
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return nullptr;
	}
	return pModule.release();
}

String Module::ToString(const StringStyle& ss) const
{
	return GetDottedSymbol().ToString(ss);
}

}
