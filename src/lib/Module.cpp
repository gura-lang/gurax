//==============================================================================
// Module.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// __help__(lang? as Symbol) {block?}
class Function_help : public Function {
private:
	RefPtr<Module::WeakPtr> _pwModule;
public:
	Function_help(Module& module);
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
};

Function_help::Function_help(Module& module) :
		Function(Type::Function, "__help__", Flag::None), _pwModule(module.GetWeakPtr())
{
	Declare(VTYPE_Help, Flag::Map);
	DeclareArg("lang", VTYPE_Symbol, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Value* Function_help::DoEval(Processor& processor, Argument& argument) const
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pLangCode = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	RefPtr<Module> pModule(_pwModule->Lock());
	const Help* pHelp = pModule? pModule->GetHelpHolder().LookupLoose(pLangCode) : nullptr;
	RefPtr<Value> pValueRtn(Value::nil());
	if (pHelp) pValueRtn.reset(new Value_Help(pHelp->Reference()));
	return argument.ReturnValue(processor, pValueRtn.release());
}

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
ModuleMap Module::_moduleMap;
const char* Module::ExtName_Script = ".gura";
const char* Module::ExtName_Compressed = ".gurc";
const char* Module::ExtName_Binary = ".gurd";

Module::Module(Frame* pFrameOuter, DottedSymbol* pDottedSymbol) :
	_pFrame(new Frame_Module(pFrameOuter, pDottedSymbol->Reference())),
	_pHelpHolder(new HelpHolder()), _pPropSlotMap(new PropSlotMap())
{
	Assign(new Function_help(*this));
}

void Module::GatherMemberSymbol(SymbolList& symbolList) const
{
	GetFrame().GatherSymbol(symbolList);
	GetPropSlotMap().GatherSymbol(symbolList);
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

String Module::MakePathNameForBuiltIn(const char* name)
{
	String pathName = "*builtin*/";
	pathName += name;
	return pathName;
}

bool Module::ImportAllBuiltIns(Processor& processor)
{
	Frame& frame = processor.GetFrameCur();
	ModuleBuiltInFactory::list.SortByName();
	for (const ModuleBuiltInFactory* pFactory : ModuleBuiltInFactory::list) {
		if (!pFactory->Import(frame)) return false;
	}
	return true;
}

bool Module::ImportByNameList(Processor& processor, const StringList& strs)
{
	for (const String& str : strs) {
		StringList moduleNames;
		str.Split(moduleNames, ',');
		for (const String& moduleName : moduleNames) {
			if (!ImportByName(processor, moduleName.c_str())) return false;
		}
	}
	return true;
}

bool Module::ImportByName(Processor& processor, const char* moduleName)
{
	bool binaryFlag = false;
	bool overwriteFlag = false;
	RefPtr<DottedSymbol> pDottedSymbol(DottedSymbol::CreateFromString(moduleName));
	if (!pDottedSymbol) {
		Error::Issue(ErrorType::ImportError, "invalid module name");
		return false;
	}
	RefPtr<Module> pModule(Module::ImportHierarchy(processor, *pDottedSymbol, binaryFlag, overwriteFlag));
	if (!pModule) return false;
	if (!pModule->AssignToFrame(processor, nullptr, overwriteFlag)) return false;
	return true;
}

Module* Module::ImportHierarchy(Processor& processor, const DottedSymbol& dottedSymbol,
								bool binaryFlag, bool overwriteFlag)
{
	size_t nSymbolsAll = dottedSymbol.GetLength();
	for (size_t nSymbols = 1; nSymbols < nSymbolsAll; nSymbols++) {
		RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol(dottedSymbol, nSymbols));
		RefPtr<Module> pModule(Import(processor, *pDottedSymbol, false, false));
		if (!pModule) return nullptr;
	}
	return Import(processor, dottedSymbol, binaryFlag, overwriteFlag);
}

Module* Module::Import(Processor& processor, const DottedSymbol& dottedSymbol,
					   bool binaryFlag, bool overwriteFlag)
{
	enum class Type { None, Script, Binary, Compressed } type = Type::None;
	String fileName = dottedSymbol.ToString();
	String pathName;
	for (const String& dirName : Basement::Inst.GetPathList()) {
		String baseName = PathName(dirName).JoinAfter(fileName.c_str());
		baseName = PathName(baseName).MakeAbsName();
		if (!binaryFlag) {
			pathName = baseName;
			pathName += ExtName_Script;
			if (OAL::IsFileType(pathName.c_str(), OAL::FileType::Normal)) {
				type = Type::Script;
				break;
			}
			pathName = baseName;
			pathName += ExtName_Compressed;
			if (OAL::IsFileType(pathName.c_str(), OAL::FileType::Normal)) {
				type = Type::Compressed;
				break;
			}
		}
		pathName = baseName;
		pathName += ExtName_Binary;
		if (OAL::IsFileType(pathName.c_str(), OAL::FileType::Normal)) {
			type = Type::Binary;
			break;
		}
	}
	if (type == Type::None) {
		Error::Issue(ErrorType::ImportError,
					 "can't find a module named '%s'", dottedSymbol.ToString().c_str());
		return nullptr;
	}
	do {
		Module* pModuleExist = _moduleMap.Lookup(pathName);
		if (pModuleExist) return pModuleExist->Reference();
	} while (0);
	RefPtr<Module> pModule(
		(type == Type::Script)?		ImportScript(processor, dottedSymbol, pathName.c_str()) :
		(type == Type::Binary)?		ImportBinary(processor, dottedSymbol, pathName.c_str()) :
		(type == Type::Compressed)?	ImportCompressed(processor, dottedSymbol, pathName.c_str()) :
		nullptr);
	if (!pModule) return nullptr;
	return pModule.release();
}

Module* Module::ImportScript(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName)
{
	RefPtr<Stream> pStream(Stream::Open(pathName, Stream::OpenFlag::Read));
	if (!pStream) return nullptr;
	RefPtr<Expr_Collector> pExprRoot(Parser::ParseStream(*pStream));
	if (!pExprRoot) return nullptr;
	Composer composer;
	pExprRoot->Compose(composer);
	composer.Flush();
	if (Error::IsIssued()) return nullptr;
	RefPtr<Module> pModule(new Module(processor.GetFrameCur().Reference(), dottedSymbol.Reference()));
	pModule->Assign(Gurax_Symbol(__name__), new Value_String(dottedSymbol.ToString('.')));
	pModule->SetPathName(pathName);
	pModule->AssignToMap();
	processor.PushFrame(pModule->GetFrame().Reference());
	Value::Delete(processor.ProcessPUnit(composer.GetPUnitFirst()));
	processor.PopFrame();
	processor.ClearEvent();
	if (Error::IsIssued()) return nullptr;
	return pModule.release();
}

Module* Module::ImportCompressed(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName)
{
	Error::Issue(ErrorType::ImportError, "can't import a compressed script");
	return nullptr;
}

Module* Module::ImportBinary(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName)
{
	auto GetEntry = [](OAL::DynamicLibrary& dll, const char* funcName) -> void* {
		void* pFunc = dll.GetEntry(funcName);
		if (pFunc) return pFunc;
		Error::Issue(ErrorType::ImportError, "missing function '%s'", funcName);
		return nullptr;
	};
	OAL::DynamicLibrary dll;
	if (!dll.Open(pathName)) {
		Error::Issue(ErrorType::ImportError, "failed to open a module file '%s'", pathName);
		return nullptr;
	}
	auto ModuleValidate = reinterpret_cast<ModuleValidateT>(GetEntry(dll, "GuraxEntry_ModuleValidate"));
	if (!ModuleValidate) return nullptr;
	auto ModuleCreate = reinterpret_cast<ModuleCreateT>(GetEntry(dll, "GuraxEntry_ModuleCreate"));
	if (!ModuleCreate) return nullptr;
	//auto ModuleTerminate = reinterpret_cast<ModuleTerminateT>(GetEntry(dll, "GuraxEntry_ModuleTerminate"));
	//if (!ModuleTerminate) return nullptr;
	if (!ModuleValidate()) return nullptr;
	RefPtr<Module> pModule(ModuleCreate(processor.GetFrameCur().Reference()));
	if (!pModule) return nullptr;
	pModule->Assign(Gurax_Symbol(__name__), new Value_String(dottedSymbol.ToString('.')));
	pModule->SetPathName(pathName);
	pModule->AssignToMap();
	return pModule.release();
}

bool Module::AssignToFrame(Processor& processor, const SymbolList* pSymbolList, bool overwriteFlag) const
{
	Frame& frameCur = processor.GetFrameCur();
	if (pSymbolList && !pSymbolList->empty()) {
		for (const Symbol* pSymbol : *pSymbolList) {
			if (!overwriteFlag && frameCur.IsAssigned(pSymbol)) {
				Error::Issue(ErrorType::ImportError,
							 "the symbol '%s' is already assigned in the current frame",
							 pSymbol->GetName());
				return false;
			}
			RefPtr<Value> pValue(GetFrame().Retrieve(pSymbol));
			if (!pValue) {
				Error::Issue(ErrorType::ImportError,
							 "module %s doesn't have a symbol named '%s'",
							 GetDottedSymbol().ToString().c_str(), pSymbol->GetName());
				return false;
			}
			frameCur.Assign(pSymbol, pValue->Reference());
		}
		return true;
	}
	size_t nSymbolsAll = GetDottedSymbol().GetLength();
	for (size_t nSymbols = 1; nSymbols < nSymbolsAll; nSymbols++) {
		RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol(GetDottedSymbol(), nSymbols));
		if (frameCur.IsAssigned(*pDottedSymbol)) continue;
		RefPtr<Module> pModule(Import(processor, *pDottedSymbol, false, false));
		if (!pModule) return false;
		if (!frameCur.Assign(pModule.release())) {
			Error::Issue(ErrorType::ImportError,
						 "failed to assign module %s", pDottedSymbol->ToString().c_str());
			return false;
		}
	}			
	if (!frameCur.Assign(Reference())) {
		Error::Issue(ErrorType::ImportError,
					 "failed to assign module %s", GetDottedSymbol().ToString().c_str());
		return false;
	}
	return true;
}

String Module::ToString(const StringStyle& ss) const
{
	return String().Format("Module:%s:%s",
				GetDottedSymbol().ToString(ss).c_str(), GetPathName());
}

//------------------------------------------------------------------------------
// ModuleMap
//------------------------------------------------------------------------------
void ModuleMap::Clear()
{
	for (auto& pair : _map) Module::Delete(pair.second);
	_map.clear();
}

void ModuleMap::Assign(Module* pModule)
{
	const char* pathName = pModule->GetPathName();
	auto pPair = _map.find(pathName);
	if (pPair == _map.end()) {
		_map.emplace(pathName, pModule);
	} else {
		Module::Delete(pPair->second);
		pPair->second = pModule;
	}
}

//------------------------------------------------------------------------------
// ModuleBuiltInFactoryList
//------------------------------------------------------------------------------
ModuleBuiltInFactoryList& ModuleBuiltInFactoryList::SortByName()
{
	std::sort(begin(), end(), ModuleBuiltInFactory::LessThan_Name());
	return *this;
}

//------------------------------------------------------------------------------
// ModuleBuiltInFactory
//------------------------------------------------------------------------------
ModuleBuiltInFactoryList ModuleBuiltInFactory::list;

bool ModuleBuiltInFactory::Import(Frame& frame) const
{
	RefPtr<Module> pModule(DoCreate(frame.Reference()));
	if (!pModule) return false;
	pModule->SetPathName(Module::MakePathNameForBuiltIn(_name.c_str()));
	pModule->AssignToMap();
	frame.Assign(pModule.release());
	return true;
}

}
