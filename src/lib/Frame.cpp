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
	for (auto& pair : _map) Frame::Delete(pair.second);
	_map.clear();
}

void FrameMap::Assign(const Symbol* pSymbol, Frame* pFrame)
{
	auto pPair = _map.find(pSymbol);
	if (pPair == _map.end()) {
		_map.emplace(pSymbol, pFrame);
	} else {
		Frame::Delete(pPair->second);
		pPair->second = pFrame;
	}
}

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
Frame* Frame::GetFrameExtern(const Symbol* pSymbol)
{
	Frame* pFrame = GetFrameOuter();
	if (pFrame && pFrame->DoRetrieve(pSymbol, &pFrame)) return pFrame;
	return nullptr;
}

Value* Frame::Retrieve(const Symbol* pSymbol)
{
	Frame* pFrameSrc = nullptr;
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
	Frame* pFrameSrc = nullptr;
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
	vtype.DoPrepare(*this);
	vtype.SetFrameOuter(Reference());
	Assign(vtype.GetSymbol(), new Value_VType(vtype));
}

void Frame::Assign(Function* pFunction)
{
	pFunction->SetFrameOuter(*this);
	Assign(pFunction->GetSymbol(), new Value_Function(pFunction));
}

String Frame::MakeId() const
{
	return String().Format("#%08zu", GetId());
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

void Frame::PrintTree(Stream& stream, int indentLevel) const
{
	stream.Printf("%*s%s:%s\n", indentLevel * 2, "", GetTypeName(), MakeId().c_str());
	if (_pFrameOuter) _pFrameOuter->PrintTree(stream, indentLevel + 1);
}

String Frame::ToString(const StringStyle& ss) const
{
	return String().Format("Frame:%s:%s", GetTypeName(), MakeId().c_str());
}

//------------------------------------------------------------------------------
// FrameList
//------------------------------------------------------------------------------
void FrameList::Print(Stream& stream) const
{
	for (const Frame* pFrame : *this) {
		const Frame& frame = *pFrame;
		stream.Printf("%s:%s\n", frame.GetTypeName(), frame.MakeId().c_str());
	}
}

//------------------------------------------------------------------------------
// FrameOwner
//------------------------------------------------------------------------------
void FrameOwner::Clear()
{
	for (Frame* pFrame : *this) Frame::Delete(pFrame);
	clear();
}

//------------------------------------------------------------------------------
// FrameStack
//------------------------------------------------------------------------------
void FrameStack::Shrink(size_t cnt)
{
	if (cnt >= size()) return;
	auto ppFrameEnd = rbegin() + size() - cnt;
	for (auto ppFrame = rbegin(); ppFrame != ppFrameEnd; ppFrame++) {
		Frame::Delete(*ppFrame);
	}
	erase(begin() + cnt, end());
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

Value* Frame_ValueMap::DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	Value* pValue = _pValueMap->Lookup(pSymbol);
	if (pValue) {
		*ppFrameSrc = this;
		return pValue->Reference();
	}
	return nullptr;
}

Value* Frame_ValueMap::DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	// Lookup a frame in which DoAssign() assigns values.
	Value* pValue = _pValueMap->Lookup(pSymbol);
	if (pValue) {
		*ppFrameSrc = this;
		return pValue->Reference();
	}
	return nullptr;
}

bool Frame_ValueMap::ExportTo(Frame& frameDst, bool overwriteFlag) const
{
	return _pValueMap->ExportTo(frameDst, overwriteFlag);
}

void Frame_ValueMap::GatherSymbol(SymbolList& symbolList) const
{
	_pValueMap->GatherSymbol(symbolList);
}

void Frame_ValueMap::GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const
{
	_pValueMap->GatherSymbolIf(symbolList, gatherCriteria);
}

//------------------------------------------------------------------------------
// Frame_OfMember
//------------------------------------------------------------------------------
const char* Frame_OfMember::name = "OfMember";

Frame_OfMember::Frame_OfMember(Frame* pFrameOuter) :
	Frame(pFrameOuter), _pValueMap(new ValueMap()), _pPropSlotMap(new PropSlotMap())
{
}

Frame_OfMember::~Frame_OfMember()
{
	ValueMap::Delete(_pValueMap);
	PropSlotMap::Delete(_pPropSlotMap);
}

void Frame_OfMember::DoAssign(const Symbol* pSymbol, Value* pValue)
{
	_pValueMap->Assign(pSymbol, pValue);
}

void Frame_OfMember::DoAssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	Value::Delete(pValue);
}

Value* Frame_OfMember::DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	Value* pValue = _pValueMap->Lookup(pSymbol);
	if (pValue) {
		*ppFrameSrc = this;
		return pValue->Reference();
	}
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_OfMember::DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	Value* pValue = _pValueMap->Lookup(pSymbol);
	if (pValue) {
		*ppFrameSrc = this;
		return pValue->Reference();
	}
	return nullptr;
}

bool Frame_OfMember::ExportTo(Frame& frameDst, bool overwriteFlag) const
{
	return _pValueMap->ExportTo(frameDst, overwriteFlag);
}

void Frame_OfMember::GatherSymbol(SymbolList& symbolList) const
{
	_pValueMap->GatherSymbol(symbolList);
	_pPropSlotMap->GatherSymbol(symbolList);
}

void Frame_OfMember::GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const
{
	_pValueMap->GatherSymbolIf(symbolList, gatherCriteria);
}

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------
const char* Frame_Branch::name = "Branch";

void Frame_Branch::PrintTree(Stream& stream, int indentLevel) const
{
	stream.Printf("%*s%s:%s\n", indentLevel * 2, "", GetTypeName(), MakeId().c_str());
	if (_pFrameOuter) _pFrameOuter->PrintTree(stream, indentLevel + 1);
	if (_pFrameLocal) _pFrameLocal->PrintTree(stream, indentLevel + 1);
}

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

Value* Frame_Basement::DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	return _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc);
}

Value* Frame_Basement::DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	// Lookup a frame in which DoAssign() assigns values.
	return nullptr;
}

void Frame_Basement::GatherSymbol(SymbolList& symbolList) const
{
	_pFrameOuter->GatherSymbol(symbolList);
}

void Frame_Basement::GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const
{
	_pFrameOuter->GatherSymbolIf(symbolList, gatherCriteria);
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

Value* Frame_Module::DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	if (_pFrameLocal) {
		RefPtr<Value> pValue(_pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc));
		if (pValue) return pValue.release();
	}
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_Module::DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	// Lookup a frame in which DoAssign() assigns values.
	return _pFrameLocal? _pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

void Frame_Module::GatherSymbol(SymbolList& symbolList) const
{
	if (_pFrameLocal) _pFrameLocal->GatherSymbol(symbolList);
}

void Frame_Module::GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const
{
	if (_pFrameLocal) _pFrameLocal->GatherSymbolIf(symbolList, gatherCriteria);
}

//------------------------------------------------------------------------------
// Frame_Scope
//------------------------------------------------------------------------------
const char* Frame_Scope::name = "Scope";

Frame_Scope::Frame_Scope(Frame* pFrameOuter, Frame* pFrameLocal) : Frame_Branch(pFrameOuter, pFrameLocal)
{
	//::printf("Frame_Scope %p %p\n", this, _pFrameOuter.get());
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

Value* Frame_Scope::DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	if (_pFrameLocal) {
		RefPtr<Value> pValue(_pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc));
		if (pValue) return pValue.release();
	}
	//::printf("DoRetrieve %p %p\n", this, _pFrameOuter.get());
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_Scope::DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	// Lookup a frame in which DoAssign() assigns values.
	return _pFrameLocal? _pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

void Frame_Scope::GatherSymbol(SymbolList& symbolList) const
{
	if (_pFrameLocal) _pFrameLocal->GatherSymbol(symbolList);
}

void Frame_Scope::GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const
{
	if (_pFrameLocal) _pFrameLocal->GatherSymbolIf(symbolList, gatherCriteria);
}

//------------------------------------------------------------------------------
// Frame_Function
//------------------------------------------------------------------------------
const char* Frame_Function::name = "Function";

Frame_Function::Frame_Function(Frame* pFrameOuter, Frame* pFrameLocal) : Frame_Scope(pFrameOuter, pFrameLocal)
{
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

Value* Frame_Block::DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	RefPtr<Value> pValue(_pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc));
	if (pValue) return pValue.release();
	return _pFrameOuter? _pFrameOuter->DoRetrieve(pSymbol, ppFrameSrc) : nullptr;
}

Value* Frame_Block::DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc)
{
	// Lookup a frame in which DoAssign() assigns values.
	return _pFrameLocal->DoRetrieve(pSymbol, ppFrameSrc);
}

void Frame_Block::GatherSymbol(SymbolList& symbolList) const
{
	_pFrameLocal->GatherSymbol(symbolList);
}

void Frame_Block::GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const
{
	_pFrameLocal->GatherSymbolIf(symbolList, gatherCriteria);
}

}
