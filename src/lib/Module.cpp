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
	RefPtr<DottedSymbol> pDottedSymbol(DottedSymbol::CreateFromString(name, separator));
	return pDottedSymbol && Prepare(pDottedSymbol.release());
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
	return ImportScript(processor, dottedSymbol, *pStream);
}

Module* Module::ImportScript(Processor& processor, const DottedSymbol& dottedSymbol, Stream& stream)
{
	RefPtr<Expr_Root> pExprOfRoot(Parser::ParseStream(stream));
	if (Error::IsIssued()) return nullptr;
	Composer composer;
	pExprOfRoot->Compose(composer);
	if (Error::IsIssued()) return nullptr;
	RefPtr<Module> pModule(new Module(processor.GetFrameCur().Reference(), dottedSymbol.Reference()));
	processor.PushFrame(pModule->GetFrame().Reference());
	processor.Eval(composer);
	processor.PopFrame();
	if (Error::IsIssued()) return nullptr;
	return pModule.release();
}

Module* Module::ImportBinary(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName)
{
	const char* funcName = "Gurax_ModuleCreate";
	OAL::DynamicLibrary dll;
	if (!dll.Open(pathName)) return nullptr;
	auto ModuleCreate = reinterpret_cast<T_ModuleCreate>(dll.GetEntry(funcName));
	if (!ModuleCreate) {
		Error::Issue(ErrorType::ModuleError, "missing function '%s'", funcName);
		return nullptr;
	}
	return ModuleCreate(processor.GetFrameCur().Reference());
}

String Module::ToString(const StringStyle& ss) const
{
	return GetDottedSymbol().ToString(ss);
}

}
