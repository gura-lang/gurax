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
	_pSymbol(pSymbol), _flags(0), _pFrame(new Frame_VType(nullptr)),
	_pPropHandlerMap(new PropHandlerMap()), _pPropHandlerMapOfClass(new PropHandlerMap())
{
}

void VType::Assign(Function* pFunction)
{
	pFunction->SetVTypeOfOwner(*this);
	GetFrame().Assign(pFunction);
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
	RefPtr<Frame> pFrame(LockFrameOuter());
	return Frame::MakeFullName(pFrame.get(), GetName());
#if 0
	String str;
	if (pFrame) {
		const DottedSymbol& dottedSymbol = pFrame->GetDottedSymbol();
		if (!dottedSymbol.IsEmpty()) {
			str += dottedSymbol.ToString();
			str += ".";
		}
	}
	str += GetName();
	return str;
#endif
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
		pPropHandler = pVType->GetPropHandlerMapOfClass().Lookup(pSymbol);
		if (pPropHandler) return pPropHandler;
	}
	return nullptr;
}

Value* VType::Cast(const Value& value, DeclArg::Flags flags) const
{
	auto IssueError = [](const VType& vtype, const Value& value) {
		if (value.IsNil()) {
			Error::Issue(ErrorType::ValueError, "can't accept nil value");
		} else {
			Error::Issue(ErrorType::ValueError, "failed to cast from %s to %s",
						 value.GetVType().MakeFullName().c_str(), vtype.MakeFullName().c_str());
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
						IssueError(*this, *pValueElem);
						return nullptr;
					}
					pValuesCasted->push_back(pValueElemCasted.release());
				}
			}
		} else if (value.IsType(VTYPE_Iterator)) {
			RefPtr<Iterator> pIterator(Value_Iterator::GetIterator(value).Clone());
			for (;;) {
				RefPtr<Value> pValueElem(pIterator->NextValue());
				if (!pValueElem) break;
				if (pValueElem->IsInstanceOf(*this)) {
					pValuesCasted->push_back(pValueElem->Reference());
				} else {
					RefPtr<Value> pValueElemCasted(DoCastFrom(*pValueElem, flags));
					if (!pValueElemCasted) {
						IssueError(*this, *pValueElem);
						return nullptr;
					}
					pValuesCasted->push_back(pValueElemCasted.release());
				}
			}
		} else {
			Error::Issue(ErrorType::ValueError, "a list or an iterator is acceptable");
			return nullptr;
		}
		return new Value_List(pValuesCasted.release());
	} else if (value.IsInstanceOf(*this)) {
		return value.Reference();
	} else {
		RefPtr<Value> pValueCasted(DoCastFrom(value, flags));
		if (!pValueCasted) {
			IssueError(*this, value);
			return nullptr;
		}
		return pValueCasted.release();
	}
}

Value* VType::DoCastFrom(const Value& value, DeclArg::Flags flags) const
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
