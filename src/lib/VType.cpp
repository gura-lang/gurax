//==============================================================================
// VType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType
//------------------------------------------------------------------------------
VType::UniqId VType::_uniqIdNext = 1;
VType VType::Empty("");

VType::VType(const Symbol* pSymbol) :
	_uniqId(_uniqIdNext++), _pHelpHolder(new HelpHolder()), _pVTypeInh(nullptr),
	_pSymbol(pSymbol), _flags(0),
	_pFrame(new Frame_Scope(nullptr, new Frame_OfMember(nullptr)))
{
}

void VType::Assign(Function* pFunction)
{
	pFunction->SetVTypeOfOwner(*this);
	GetFrameOfMember().Assign(pFunction);
}

void VType::GatherMemberSymbol(SymbolList& symbolList) const
{
	GetFrameOfMember().GatherSymbol(symbolList);
	if (_pVTypeInh) _pVTypeInh->GatherMemberSymbol(symbolList);
}

void VType::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	const Help* pHelp = GetHelpHolder().Lookup(pLangCode);
	if (pHelp) {
		Basement::Inst.Present(processor, pHelp->GetDocReferable().Reference());
	}
}

void VType::Prepare(Frame& frameOuter)
{
	frameOuter.Assign(*this);
	DoPrepare(frameOuter);
}

String VType::ToString(const StringStyle& ss) const
{
	String str;
	str += "VType:";
	const Function& constructor = GetConstructor();
	String name = constructor.IsEmpty()?
			MakeFullName() : constructor.ToString(StringStyle().SetCram());
	if (name.empty()) {
		str += "(noname)";
	} else {
		str += name;
	}
	return str;
}

void VType::Declare(VType& vtypeInh, Flags flags, Function* pConstructor)
{
	_pVTypeInh = &vtypeInh;
	GetFrameOfMember().SetFrameOuter(_pVTypeInh->GetFrameOfMember().Reference());
	_flags = flags;
	_pConstructor.reset(pConstructor? pConstructor : Function::Empty.Reference());
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
	for (const VType* pVType = this; pVType; pVType = pVType->GetVTypeInh()) {
		const PropSlot* pPropSlot = pVType->GetPropSlotMap().Lookup(pSymbol);
		if (pPropSlot) return pPropSlot;
	}
	return nullptr;
}

Value* VType::Cast(const Value& value, const Symbol* pSymbol, DeclArg::Flags flags) const
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
					value.GetVType().MakeFullName().c_str(), vtype.MakeFullName().c_str());
			} else {
				Error::Issue(ErrorType::ValueError, "can't cast from %s to %s",
					value.GetVType().MakeFullName().c_str(), vtype.MakeFullName().c_str());
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
					RefPtr<Value> pValueElemCasted(DoCastFrom(*pValueElem, flags));
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
					RefPtr<Value> pValueElemCasted(DoCastFrom(*pValueElem, flags));
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
	} else {
		RefPtr<Value> pValueCasted(DoCastFrom(value, flags));
		if (!pValueCasted) {
			IssueError(*this, pSymbol, value);
			return nullptr;
		}
		return pValueCasted.release();
	}
}

Value* VType::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return nullptr;
}

bool VType::DoAssignCustomMethod(RefPtr<Function> pFunction)
{
	pFunction->SetFrameOuter(GetFrame());
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
