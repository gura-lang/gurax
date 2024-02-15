//==============================================================================
// VType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType
//------------------------------------------------------------------------------
VType::UniqId VType::_uniqIdNext = 1;
VType::SerialIdMap VType::_serialIdMap;
VType VType::Invalid;

VType::VType(SerialId serialId) :
	_uniqId(UniqId_Invalid), _serialId(serialId), _pHelpHolder(new HelpHolder()), _pVTypeInh(nullptr),
	_pSymbol(Symbol::Add("")), _flags(0), _pFrame(new Frame_Scope(nullptr, new Frame_OfMember(nullptr)))
{
	if (_serialId != SerialId_Invalid) _serialIdMap[_serialId] = this;
}

VType::VType(const Symbol* pSymbol, SerialId serialId) :
	_uniqId(_uniqIdNext++), _serialId(serialId), _pHelpHolder(new HelpHolder()), _pVTypeInh(nullptr),
	_pSymbol(pSymbol), _flags(0), _pFrame(new Frame_Scope(nullptr, new Frame_OfMember(nullptr)))
{
	if (_serialId != SerialId_Invalid) _serialIdMap[_serialId] = this;
}

void VType::Assign(Function* pFunction)
{
	pFunction->SetVTypeOfOwner(*this);
	GetFrameOfMember().Assign(pFunction);
}

void VType::GatherMemberSymbol(SymbolList& symbolList, bool escalateFlag) const
{
	GetFrameOfMember().GatherSymbol(symbolList);
	if (escalateFlag && _pVTypeInh) _pVTypeInh->GatherMemberSymbol(symbolList, escalateFlag);
}

void VType::GatherMemberSymbolIf(SymbolList& symbolList, const Frame::GatherCriteria& gatherCriteria, bool escalateFlag) const
{
	GetFrameOfMember().GatherSymbolIf(symbolList, gatherCriteria);
	if (escalateFlag && _pVTypeInh) _pVTypeInh->GatherMemberSymbolIf(symbolList, gatherCriteria, escalateFlag);
}

void VType::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	const Help* pHelp = GetHelpHolder().LookupLoose(pLangCode);
	if (pHelp) {
		Basement::Inst.Present(processor, pHelp->GetDocReferable().Reference());
	}
}

VType* VType::SerialIdToVType(SerialId serialId)
{
	auto iter = _serialIdMap.find(serialId);
	return (iter == _serialIdMap.end())? nullptr : iter->second;
}

Value* VType::DoDeserialize(Stream& stream) const
{
	Error::Issue(ErrorType::ValueError,
				"value type %s can not be serialized", MakeFullName().c_str());
	return nullptr;
}

String VType::ToString(const StringStyle& ss) const
{
	String str;
	str += "VType:";
	const Function& constructor = GetConstructor();
	String name = constructor.IsEmpty()? MakeFullName() : constructor.ToString(StringStyle().SetCram());
	if (name.empty()) {
		str += "(noname)";
	} else {
		str += name;
	}
	return str;
}

void VType::Declare(VType& vtypeInh, Flags flags, Constructor* pConstructor)
{
	_pVTypeInh = &vtypeInh;
	GetFrameOfMember().SetFrameOuter(_pVTypeInh->GetFrameOfMember().Reference());
	_flags = flags;
	if (pConstructor) {
		pConstructor->SetFrameOuter(Basement::Inst.GetProcessor().GetFrameCur());
		_pConstructor.reset(pConstructor);
	} else {
		_pConstructor.reset(Constructor::Empty.Reference());
	}
	for (auto pOpEntry : vtypeInh._opEntryList) {
		AddOpEntry(pOpEntry);
		if (pOpEntry->IsUnary()) {
			pOpEntry->ReassignEntry(*this);
		} else {
			VType& vtypeL = pOpEntry->GetVTypeL();
			VType& vtypeR = pOpEntry->GetVTypeR();
			if (vtypeL.IsIdentical(vtypeInh)) pOpEntry->ReassignEntry(*this, vtypeR);
			if (vtypeR.IsIdentical(vtypeInh)) pOpEntry->ReassignEntry(vtypeL, *this);
			if (vtypeL.IsIdentical(vtypeInh) && vtypeR.IsIdentical(vtypeInh)) pOpEntry->ReassignEntry(*this, *this);
		}
	}
}

String VType::MakeFullName() const
{
	return Frame::MakeFullName(GetFrameOuter(), GetName());
}

DottedSymbol* VType::MakeDottedSymbol() const
{
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
	pDottedSymbol->Append(GetSymbol());
	return pDottedSymbol.release();
}

const PropSlot* VType::LookupPropSlot(const Symbol* pSymbol) const
{
	for (const VType* pVType = this; pVType->IsValid(); pVType = &pVType->GetVTypeInh()) {
		const PropSlot* pPropSlot = pVType->GetPropSlotMap().Lookup(pSymbol);
		if (pPropSlot) return pPropSlot;
	}
	return nullptr;
}

Value* VType::Cast(Processor& processor, const Value& value, const Symbol* pSymbol, DeclArg::Flags flags) const
{
	auto IssueError = [](const VType& vtype, const Symbol* pSymbol, const Value& value) {
		if (Error::IsIssued()) {
			// nothing to do
		} else if (value.IsNil()) {
			if (pSymbol) {
				Error::Issue(ErrorType::ValueError, "%s can't accept nil value", pSymbol->GetName());
			} else {
				Error::Issue(ErrorType::ValueError, "can't accept nil value");
			}
		} else {
			if (pSymbol) {
				Error::Issue(ErrorType::ValueError, "%s can't cast from %s to %s",
					pSymbol->GetName(),
					value.GetVTypeCustom().MakeFullName().c_str(), vtype.MakeFullName().c_str());
			} else {
				Error::Issue(ErrorType::ValueError, "can't cast from %s to %s",
					value.GetVTypeCustom().MakeFullName().c_str(), vtype.MakeFullName().c_str());
			}
		}
	};
	if (flags & DeclArg::Flag::ListVar) {
		RefPtr<ValueOwner> pValuesCasted(new ValueOwner());
		if (value.IsType(VTYPE_List)) {
			const ValueTypedOwner& values = dynamic_cast<const Value_List&>(value).GetValueTypedOwner();
			pValuesCasted->reserve(values.GetSize());
			for (const Value* pValueElem : values.GetValueOwner()) {
				if (pValueElem->IsInstanceOf(*this)) {
					pValuesCasted->push_back(pValueElem->Reference());
				} else {
					RefPtr<Value> pValueElemCasted(DoCastFrom(processor, *pValueElem, flags));
					if (!pValueElemCasted) {
						IssueError(*this, pSymbol, *pValueElem);
						return nullptr;
					}
					pValuesCasted->push_back(pValueElemCasted.release());
				}
			}
		} else if (value.IsType(VTYPE_Iterator)) {
			Iterator& iterator = Value_Iterator::GetIterator(value);
			for (;;) {
				RefPtr<Value> pValueElem(iterator.NextValue());
				if (!pValueElem) break;
				if (pValueElem->IsInstanceOf(*this)) {
					pValuesCasted->push_back(pValueElem->Reference());
				} else {
					RefPtr<Value> pValueElemCasted(DoCastFrom(processor, *pValueElem, flags));
					if (!pValueElemCasted) {
						IssueError(*this, pSymbol, *pValueElem);
						return nullptr;
					}
					pValuesCasted->push_back(pValueElemCasted.release());
				}
			}
		} else {
			if (pSymbol) {
				Error::Issue(ErrorType::ValueError, "%s can accept a list or an iterator", pSymbol->GetName());
			} else {
				Error::Issue(ErrorType::ValueError, "a list or an iterator is acceptable");
			}
			return nullptr;
		}
		return new Value_List(pValuesCasted.release());
	} else if (value.IsInstanceOf(*this)) {
		return value.Reference();
	} else if (flags & DeclArg::Flag::NoCast) {
		IssueError(*this, pSymbol, value);
		return nullptr;
	} else if (!IsAny() && value.IsInstanceOf(VTYPE_Tuple)) {
		const Function& constructor = GetConstructor();
		if (constructor.IsEmpty()) {
			Error::Issue(ErrorType::CastError, "%s doesn't have a constructor", MakeFullName().c_str());
			return nullptr;
		}
		RefPtr<Value> pValueCasted(constructor.EvalEasy(processor, Value_Tuple::GetValueOwner(value)));
		return Error::IsIssued()? nullptr : pValueCasted.release();
	} else {
		RefPtr<Value> pValueCasted(DoCastFrom(processor, value, flags));
		if (pValueCasted) return pValueCasted.release();
		pValueCasted.reset(value.GetVTypeCustom().DoCastTo(processor, value, *this, flags));
		if (pValueCasted) return pValueCasted.release();
		IssueError(*this, pSymbol, value);
		return nullptr;
	}
}

bool VType::DoAssignCustomMethod(RefPtr<Function> pFunction)
{
	//RefPtr<Frame> pFrame(new Frame_Scope(
	//	Basement::Inst.GetProcessor().GetFrameCur().Reference(), GetFrame().Reference()));
	//pFunction->SetFrameOuter(*pFrame);
	//pFunction->SetFrameOuter(GetFrame());
	pFunction->SetFrameOuter(Basement::Inst.GetProcessor().GetFrameCur());
	pFunction->SetVTypeOfOwner(*this);
	const Symbol* pSymbol = pFunction->GetSymbol();
	GetFrameOfMember().Assign(pSymbol, new Value_Function(pFunction.release()));
	return true;
}

//------------------------------------------------------------------------------
// VTypeMap
//------------------------------------------------------------------------------
void VTypeMap::Assign(const Symbol* pSymbol, VType* pVType)
{
	auto pPair = _map.find(pSymbol);
	if (pPair == _map.end()) {
		_map.emplace(pSymbol, pVType);
	} else {
		pPair->second = pVType;
	}
}

String VTypeMap::ToString(const StringStyle& ss) const
{
	String str;
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		const VType* pVType = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += " = ";
		str += pVType->MakeFullName();
		str += "\n";
	}
	return str;
}

}
