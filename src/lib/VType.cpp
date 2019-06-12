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
	_uniqId(_uniqIdNext++), _pHelpProvider(new HelpProvider()), _pVTypeInh(nullptr),
	_pSymbol(pSymbol), _flags(0), _pFrame(new Frame_VType(nullptr)),
	_pPropHandlerMap(new PropHandlerMap()), _pPropHandlerMapOfClass(new PropHandlerMap())
{
}

void VType::Prepare(Frame& frameOuter)
{
	_pConstructor.reset(Function::Empty.Reference()); // _pConstructor must be initialized here
	frameOuter.Assign(*this);
	DoPrepare(frameOuter);
}

void VType::SetAttrs(VType& vtypeInh, Flags flags)
{
	_pVTypeInh = &vtypeInh;
	_pFrame->SetFrameOuter(_pVTypeInh->GetFrame().Reference());
	_flags = flags;
}

String VType::MakeFullName() const
{
	String str;
	RefPtr<Frame> pFrame(LockFrameOuter());
	if (pFrame) {
		const DottedSymbol* pDottedSymbol = pFrame->GetDottedSymbol();
		if (pDottedSymbol) {
			str += pDottedSymbol->ToString();
			str += ".";
		}
	}
	str += GetName();
	return str;
}

DottedSymbol* VType::MakeDottedSymbol() const
{
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
	pDottedSymbol->Append(GetSymbol());
	return pDottedSymbol.release();
}

const PropHandler* VType::LookupPropHandler(const Symbol* pSymbol) const
{
	for (const VType* pVType = this; pVType; pVType = pVType->GetVTypeInh()) {
		const PropHandler* pPropHandler = pVType->GetPropHandlerMap().Lookup(pSymbol);
		if (pPropHandler) return pPropHandler;
	}
	return nullptr;
}

const PropHandler* VType::LookupPropHandlerOfClass(const Symbol* pSymbol) const
{
	for (const VType* pVType = this; pVType; pVType = pVType->GetVTypeInh()) {
		const PropHandler* pPropHandler = pVType->GetPropHandlerMapOfClass().Lookup(pSymbol);
		if (pPropHandler) return pPropHandler;
	}
	return nullptr;
}

Value* VType::Cast(const Value& value, bool listVarFlag) const
{
	auto IssueError = [](const VType& vtype, const Value& value) {
		Error::Issue(ErrorType::ValueError, "failed to cast from %s to %s",
					 value.GetVType().MakeFullName().c_str(), vtype.MakeFullName().c_str());
	};
	if (listVarFlag) {
		if (!value.IsType(VTYPE_List)) {
			Error::Issue(ErrorType::ValueError, "must be a list value");
			return nullptr;
		}
		const ValueTypedOwner& values = dynamic_cast<const Value_List&>(value).GetValueTypedOwner();

		// type check

		RefPtr<ValueTypedOwner> pValuesCasted(new ValueTypedOwner());
		pValuesCasted->Reserve(values.GetSize());
		for (const Value* pValueElem : values.GetValueOwner()) {
			if (pValueElem->IsInstanceOf(*this)) {
				pValuesCasted->Add(pValueElem->Reference());
			} else {
				RefPtr<Value> pValueElemCasted(DoCastFrom(*pValueElem));
				if (!pValueElemCasted) {
					IssueError(*this, *pValueElem);
					return nullptr;
				}
				pValuesCasted->Add(pValueElemCasted.release());
			}
		}
		return new Value_List(pValuesCasted.release());
	} else if (value.IsInstanceOf(*this)) {
		return value.Reference();
	} else {
		RefPtr<Value> pValueCasted(DoCastFrom(value));
		if (!pValueCasted) {
			IssueError(*this, value);
			return nullptr;
		}
		return pValueCasted.release();
	}
}

Value* VType::DoCastFrom(const Value& value) const
{
	return nullptr;
}

//------------------------------------------------------------------------------
// VTypeMap
//------------------------------------------------------------------------------
void VTypeMap::Assign(const Symbol* pSymbol, VType* pVType)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pVType);
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
