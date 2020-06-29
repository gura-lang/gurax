//==============================================================================
// test-PropSlot.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class PropSlotTmp : public PropSlot {
public:
	using PropSlot::PropSlot;
protected:
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override { return nullptr; }
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {}
};

Gurax_TesterEntry(PropSlot)
{
	auto PrintList = [](const PropSlotList& propSlotList) {
		for (PropSlot* pPropSlot : propSlotList.v) {
			::printf("%s\n", pPropSlot->GetSymbol()->GetName());
		}
	};
	RefPtr<PropSlotOwner> pPropSlotOwner(new PropSlotOwner());
	pPropSlotOwner->v.push_back(new PropSlotTmp(Symbol::Add("grape")));
	pPropSlotOwner->v.push_back(new PropSlotTmp(Symbol::Add("orange")));
	pPropSlotOwner->v.push_back(new PropSlotTmp(Symbol::Add("apple")));
	pPropSlotOwner->v.push_back(new PropSlotTmp(Symbol::Add("banana")));
	pPropSlotOwner->v.push_back(new PropSlotTmp(Symbol::Add("pineapple")));
	PrintList(*pPropSlotOwner);
	pPropSlotOwner->SortBySymbolName();
	::printf("----\n");
	PrintList(*pPropSlotOwner);
	pPropSlotOwner->SortBySymbolName(SortOrder::Descend);
	::printf("----\n");
	PrintList(*pPropSlotOwner);
}

}
