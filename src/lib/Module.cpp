//==============================================================================
// Module.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
ModuleMap Module::_moduleMap;

Module::Module(Frame* pFrameOuter, DottedSymbol* pDottedSymbol) :
	_pFrame(new Frame_Module(pFrameOuter)), _pDottedSymbol(pDottedSymbol),
	_pHelpProvider(new HelpProvider()), _pPropHandlerMap(new PropHandlerMap())
{
}

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
	RefPtr<Module> pModule;
	String fileName = dottedSymbol.ToString();
	String baseName = fileName;
	String pathName = baseName;
	pathName += ".gura";
	pModule.reset(_moduleMap.Lookup(pathName));
	if (pModule) return pModule.release();
	pModule.reset(ImportScript(processor, dottedSymbol, pathName.c_str()));
	if (!pModule) return nullptr;
	_moduleMap.Assign(pModule.Reference());
	return pModule.release();
}

Module* Module::ImportScript(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName)
{
	RefPtr<Stream> pStream(Stream_File::Open(pathName, "rt"));
	if (!pStream) {
		Error::Issue(ErrorType::ModuleError, "failed to open a module file '%s'", pathName);
		return nullptr;
	}
	RefPtr<Expr_Root> pExprOfRoot(Parser::ParseStream(*pStream));
	if (Error::IsIssued()) return nullptr;
	Composer composer;
	pExprOfRoot->Compose(composer);
	if (Error::IsIssued()) return nullptr;
	RefPtr<Module> pModule(new Module(processor.GetFrameCur().Reference(), dottedSymbol.Reference()));
	processor.PushFrame(pModule->GetFrame().Reference());
	processor.ProcessPUnit(composer.GetPUnitFirst());
	processor.PopFrame();
	processor.ClearEvent();
	if (Error::IsIssued()) return nullptr;
	processor.PopValue();	// discard the last value
	pModule->SetPathName(pathName);
	return pModule.release();
}

Module* Module::ImportBinary(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName)
{
	auto GetEntry = [](OAL::DynamicLibrary& dll, const char* funcName) -> void* {
		void* pFunc = dll.GetEntry(funcName);
		if (pFunc) return pFunc;
		Error::Issue(ErrorType::ModuleError, "missing function '%s'", funcName);
		return nullptr;
	};
	OAL::DynamicLibrary dll;
	if (!dll.Open(pathName)) {
		Error::Issue(ErrorType::ModuleError, "failed to open a module file '%s'", pathName);
		return nullptr;
	}
	auto ModuleValidate = reinterpret_cast<ModuleValidateT>(GetEntry(dll, "Gurax_ModuleValidate"));
	if (!ModuleValidate) return nullptr;
	auto ModuleCreate = reinterpret_cast<ModuleCreateT>(GetEntry(dll, "Gurax_ModuleCreate"));
	if (!ModuleCreate) return nullptr;
	//auto ModuleTerminate = reinterpret_cast<ModuleTerminateT>(GetEntry(dll, "Gurax_ModuleTerminate"));
	//if (!ModuleTerminate) return nullptr;
	if (!ModuleValidate()) return nullptr;
	RefPtr<Module> pModule(ModuleCreate(processor.GetFrameCur().Reference()));
	if (!pModule) return nullptr;
	pModule->SetPathName(pathName);
	return pModule.release();
}

String Module::ToString(const StringStyle& ss) const
{
	return GetDottedSymbol().ToString(ss);
}

//------------------------------------------------------------------------------
// ModuleMap
//------------------------------------------------------------------------------
void ModuleMap::Clear()
{
	for (auto& pair : *this) Module::Delete(pair.second);
	clear();
}

void ModuleMap::Assign(Module* pModule)
{
	const char* pathName = pModule->GetPathName();
	iterator pPair = find(pathName);
	if (pPair == end()) {
		emplace(pathName, pModule);
	} else {
		Module::Delete(pPair->second);
		pPair->second = pModule;
	}
}

}
