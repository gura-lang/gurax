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

VType::VType(const char* name) :
	_uniqId(_uniqIdNext++), _pHelpProvider(new HelpProvider()), _pVTypeInherited(nullptr),
	_pSymbol(Symbol::Add(name)), _flags(0), _pFrame(new Frame_VType(nullptr)),
	_pPropHandlerMap(new PropHandlerMap()), _pPropHandlerMapOfClass(new PropHandlerMap())
{
}

void VType::PrepareBasic(Frame& frame)
{
	VTYPE_Object.Prepare(frame);
	VTYPE_Any.Prepare(frame);
	VTYPE_ArgMapper.Prepare(frame);
	VTYPE_ArgMapper_Multiple.Prepare(frame);
	VTYPE_ArgSlot.Prepare(frame);
	VTYPE_Argument.Prepare(frame);
	VTYPE_Attribute.Prepare(frame);
	VTYPE_Binary.Prepare(frame);
	VTYPE_Bool.Prepare(frame);
	VTYPE_DateTime.Prepare(frame);
	VTYPE_Dict.Prepare(frame);
	VTYPE_Error.Prepare(frame);
	VTYPE_ErrorType.Prepare(frame);
	VTYPE_Expr.Prepare(frame);
	VTYPE_Frame.Prepare(frame);
	VTYPE_Function.Prepare(frame);
	VTYPE_Iterator.Prepare(frame);
	VTYPE_VType.Prepare(frame);
	VTYPE_List.Prepare(frame);
	VTYPE_Member.Prepare(frame);
	VTYPE_Module.Prepare(frame);
	VTYPE_Nil.Prepare(frame);
	VTYPE_Number.Prepare(frame);
	VTYPE_PUnit.Prepare(frame);
	VTYPE_Quote.Prepare(frame);
	VTYPE_Stream.Prepare(frame);
	VTYPE_String.Prepare(frame);
	VTYPE_StringPtr.Prepare(frame);
	VTYPE_Symbol.Prepare(frame);
	VTYPE_Template.Prepare(frame);
	VTYPE_TimeDelta.Prepare(frame);
	VTYPE_Undefined.Prepare(frame);
}

void VType::SetAttrs(VType& vtypeInherited, Flags flags)
{
	_pVTypeInherited = &vtypeInherited;
	_pFrame->SetFrameOuter(_pVTypeInherited->GetFrame().Reference());
	_flags = flags;
}

String VType::MakeFullName() const
{
	String str;
	RefPtr<Frame> pFrame(LockFrameParent());
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
	for (const VType* pVType = this; pVType; pVType = pVType->GetVTypeInherited()) {
		const PropHandler* pPropHandler = pVType->GetPropHandlerMap().Lookup(pSymbol);
		if (pPropHandler) return pPropHandler;
	}
	return nullptr;
}

const PropHandler* VType::LookupPropHandlerOfClass(const Symbol* pSymbol) const
{
	for (const VType* pVType = this; pVType; pVType = pVType->GetVTypeInherited()) {
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
