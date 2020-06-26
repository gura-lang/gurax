//==============================================================================
// Frame.cpp
//==============================================================================
#include "stdafx.h"

#undef SetProp
#undef GetProp

namespace Gurax {

//------------------------------------------------------------------------------
// FrameMap
//------------------------------------------------------------------------------
void FrameMap::Clear()
{
	for (auto& pair : *this) Frame::Delete(pair.second);
	clear();
}

void FrameMap::Assign(const Symbol* pSymbol, Frame* pFrame)
{
	auto pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pFrame);
	} else {
		Frame::Delete(pPair->second);
		pPair->second = pFrame;
	}
}

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
Value* Frame::Retrieve(const Symbol* pSymbol)
{
	const Frame* pFrameSrc = nullptr;
	RefPtr<Value> pValue(DoRetrieve(pSymbol, &pFrameSrc));
	if (pValue) {
		if (!_pFrameMap) _pFrameMap.reset(new FrameMap());
		_pFrameMap->Assign(pSymbol, pFrameSrc->Reference());
	}
	return pValue.release();
}

Value* Frame::Retrieve(const DottedSymbol& dottedSymbol, size_t nTail)
{
	const SymbolList& symbolList = dottedSymbol.GetSymbolList();
	if (symbolList.size() <= nTail) return nullptr;
	auto ppSymbol = symbolList.begin();
	const Symbol* pSymbol = *ppSymbol++;
	RefPtr<Value> pValue(Retrieve(pSymbol));
	while (pValue && ppSymbol + nTail != symbolList.end()) {
		const Symbol* pSymbol = *ppSymbol++;
		pValue.reset(pValue->GetProperty(pSymbol, *Attribute::Empty, false));
	}
	return pValue.release();
}

Value* Frame::RetrieveLocal(const Symbol* pSymbol)
{
	const Frame* pFrameSrc = nullptr;
	return DoRetrieveLocal(pSymbol, &pFrameSrc);
}

void Frame::Assign(const Symbol* pSymbol, Value* pValue)
{
	Frame* pFrame = nullptr;
	if (!_pFrameMap || !(pFrame = _pFrameMap->Lookup(pSymbol))) pFrame = this;
	pFrame->DoAssign(pSymbol, pValue);
}

bool Frame::Assign(const DottedSymbol& dottedSymbol, Value* pValue)
{
	if (dottedSymbol.IsEmpty()) return false;
	if (dottedSymbol.IsDotted()) {
		RefPtr<Value> pValueTarget(Retrieve(dottedSymbol, 1));
		if (!pValueTarget) return false;
		return pValueTarget->SetProperty(dottedSymbol.GetSymbolLast(), pValue, *Attribute::Empty);
	} else {
		Assign(dottedSymbol.GetSymbolLast(), pValue);
		return true;
	}
}

bool Frame::AssignWithCast(DeclArg& declArg, const Value& value)
{
	RefPtr<Value> pValueCasted(declArg.Cast(*this, value));
	if (!pValueCasted) return false;
	AssignFromArgument(declArg.GetSymbol(), pValueCasted.release());
	return true;
}

bool Frame::Assign(Module* pModule)
{
	return Assign(pModule->GetDottedSymbol(), new Value_Module(pModule));
}

void Frame::Assign(VType& vtype)
{
	vtype.SetFrameOuter(*this);
	Assign(vtype.GetSymbol(), new Value_VType(vtype));
}

void Frame::Assign(Function* pFunction)
{
	pFunction->SetFrameOuter(*this);
	Assign(pFunction->GetSymbol(), new Value_Function(pFunction));
}

String Frame::MakeFullName(const Frame* pFrame, const char* name)
{
	String str;
	if (pFrame) {
		const DottedSymbol& dottedSymbol = pFrame->GetDottedSymbol();
		if (!dottedSymbol.IsEmpty()) {
			str += dottedSymbol.ToString();
			str += ".";
		}
	}
	str += name;
	return str;
}

//------------------------------------------------------------------------------
// FrameList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// FrameOwner
//------------------------------------------------------------------------------
void FrameOwner::Clear()
{
	for (Frame* pFrame : v) Frame::Delete(pFrame);
	v.clear();
}

//------------------------------------------------------------------------------
// FrameStack
//------------------------------------------------------------------------------
void FrameStack::Shrink(size_t cnt)
{
	if (cnt >= v.size()) return;
	auto ppFrameEnd = v.rbegin() + v.size() - cnt;
	for (auto ppFrame = v.rbegin(); ppFrame != ppFrameEnd; ppFrame++) {
		Frame::Delete(*ppFrame);
	}
	v.erase(v.begin() + cnt, v.end());
}

//------------------------------------------------------------------------------
// Frame_ValueMap
//------------------------------------------------------------------------------
const char* Frame_ValueMap::name = "ValueMap";

Frame_ValueMap::Frame_ValueMap() : Frame(nullptr), _pValueMap(new ValueMap())
{
}

Frame_ValueMap::~Frame_ValueMap()
{
	ValueMap::Delete(_pValueMap);
}

void Frame_ValueMap::DoAssign(const Symbol* pSymbol, Value* pValue)
{
	_pValueMap->Assign(pSymbol, pValue);
}

void Frame_ValueMap::DoAssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	_pValueMap->Assign(pSymbol, pValue);
}

Value* Frame_ValueMap::DoRetrieve(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	Value* pValue = _pValueMap->Lookup(pSymbol);
	if (!pValue) return nullptr;
	*ppFrameSrc = this;
	return pValue->Reference();
}

Value* Frame_ValueMap::DoRetrieveLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	// Lookup a frame in which DoAssign() assigns values.
	Value* pValue = _pValueMap->Lookup(pSymbol);
	if (!pValue) return nullptr;
	*ppFrameSrc = this;
	return pValue->Reference();
}

bool Frame_ValueMap::ExportTo(Frame& frameDst, bool overwriteFlag) const
{
	for (auto pair : *_pValueMap) {
		const Symbol* pSymbol = pair.first;
		const Value* pValue = pair.second;
		if (pSymbol->StartsWith('_')) {
			// nothing to do
		} else if (overwriteFlag || !frameDst.IsAssignedLocal(pSymbol)) {
			frameDst.Assign(pSymbol, pValue->Reference());
		} else {
			Error::Issue(ErrorType::ValueError,
							"can't overwrite the symbol: %s", pSymbol->GetName());
			return false;
		}
	}
	return true;
}

void Frame_ValueMap::GatherSymbol(SymbolList& symbolList) const
{
	for (auto pair : *_pValueMap) {
		const Symbol* pSymbol = pair.first;
		symbolList.push_back(pSymbol);
	}
}

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------
const char* Frame_Branch::name = "Branch";

//------------------------------------------------------------------------------
// Frame_Basement
// _pFrameLocal is always nullptr.
//------------------------------------------------------------------------------
const char* Frame_Basement::name = "Basement";

Frame_Basement::Frame_Basement() : Frame_Branch(new Frame_ValueMap(), nullptr)
{
}

void Frame_Basement::DoAssign(const Symbol* pSymbol, Value* pValue)
{
	_pFrameOuter->DoAssign(pSymbol, pValue);
}

void Frame_Basement::DoAssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	Value::Delete(pValue);
}

Value* Frame_Basement::DoRetrieve(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	return _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc);
}

Value* Frame_Basement::DoRetrieveLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	// Lookup a frame in which DoAssign() assigns values.
	return nullptr;
}

void Frame_Basement::GatherSymbol(SymbolList& symbolList) const
{
	_pFrameOuter->GatherSymbol(symbolList);
}

//------------------------------------------------------------------------------
// Frame_VType
//------------------------------------------------------------------------------
const char* Frame_VType::name = "VType";

Frame_VType::Frame_VType(Frame* pFrameOuter) : Frame_Branch(pFrameOuter, new Frame_ValueMap())
{
}

void Frame_VType::DoAssign(const Symbol* pSymbol, Value* pValue)
{
	_pFrameLocal->DoAssign(pSymbol, pValue);
}

void Frame_VType::DoAssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	Value::Delete(pValue);
}

Value* Frame_VType::DoRetrieve(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	RefPtr<Value> pValue(_pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc));
	if (pValue) return pValue.release();
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_VType::DoRetrieveLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	// Lookup a frame in which DoAssign() assigns values.
	return _pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc);
}

void Frame_VType::GatherSymbol(SymbolList& symbolList) const
{
	_pFrameLocal->GatherSymbol(symbolList);
}

//------------------------------------------------------------------------------
// Frame_Module
//------------------------------------------------------------------------------
const char* Frame_Module::name = "Module";

Frame_Module::Frame_Module(Frame* pFrameOuter, DottedSymbol* pDottedSymbol) :
	Frame_Branch(pFrameOuter, nullptr), _pDottedSymbol(pDottedSymbol)
{
}

void Frame_Module::DoAssign(const Symbol* pSymbol, Value* pValue)
{
	if (!_pFrameLocal) _pFrameLocal.reset(new Frame_ValueMap());
	_pFrameLocal->DoAssign(pSymbol, pValue);
}

void Frame_Module::DoAssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	if (!_pFrameLocal) _pFrameLocal.reset(new Frame_ValueMap());
	_pFrameLocal->DoAssign(pSymbol, pValue);
}

Value* Frame_Module::DoRetrieve(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	if (_pFrameLocal) {
		RefPtr<Value> pValue(_pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc));
		if (pValue) return pValue.release();
	}
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_Module::DoRetrieveLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	// Lookup a frame in which DoAssign() assigns values.
	return _pFrameLocal? _pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

void Frame_Module::GatherSymbol(SymbolList& symbolList) const
{
	if (_pFrameLocal) _pFrameLocal->GatherSymbol(symbolList);
}

//------------------------------------------------------------------------------
// Frame_Scope
//------------------------------------------------------------------------------
const char* Frame_Scope::name = "Scope";

Frame_Scope::Frame_Scope(Frame* pFrameOuter) : Frame_Branch(pFrameOuter, nullptr)
{
}

void Frame_Scope::DoAssign(const Symbol* pSymbol, Value* pValue)
{
	if (!_pFrameLocal) _pFrameLocal.reset(new Frame_ValueMap());
	_pFrameLocal->DoAssign(pSymbol, pValue);
}

void Frame_Scope::DoAssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	if (!_pFrameLocal) _pFrameLocal.reset(new Frame_ValueMap());
	_pFrameLocal->DoAssign(pSymbol, pValue);
}

Value* Frame_Scope::DoRetrieve(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	if (_pFrameLocal) {
		RefPtr<Value> pValue(_pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc));
		if (pValue) return pValue.release();
	}
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_Scope::DoRetrieveLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	// Lookup a frame in which DoAssign() assigns values.
	return _pFrameLocal? _pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

void Frame_Scope::GatherSymbol(SymbolList& symbolList) const
{
	if (_pFrameLocal) _pFrameLocal->GatherSymbol(symbolList);
}

//------------------------------------------------------------------------------
// Frame_Block
//------------------------------------------------------------------------------
const char* Frame_Block::name = "Block";

Frame_Block::Frame_Block(Frame* pFrameOuter) : Frame_Branch(pFrameOuter, new Frame_ValueMap())
{
}

void Frame_Block::DoAssign(const Symbol* pSymbol, Value* pValue)
{
	_pFrameOuter->DoAssign(pSymbol, pValue);
}

void Frame_Block::DoAssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	_pFrameLocal->DoAssign(pSymbol, pValue);
	if (!_pFrameMap) _pFrameMap.reset(new FrameMap());
	_pFrameMap->Assign(pSymbol, _pFrameLocal->Reference());
}

Value* Frame_Block::DoRetrieve(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	RefPtr<Value> pValue(_pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc));
	if (pValue) return pValue.release();
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_Block::DoRetrieveLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const
{
	// Lookup a frame in which DoAssign() assigns values.
	return _pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc);
}

void Frame_Block::GatherSymbol(SymbolList& symbolList) const
{
	_pFrameLocal->GatherSymbol(symbolList);
}

}
