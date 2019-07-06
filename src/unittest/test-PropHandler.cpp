//==============================================================================
// test-PropHandler.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class PropHandlerTmp : public PropHandler {
public:
	using PropHandler::PropHandler;
protected:
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override { return nullptr; }
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {}
};

Gurax_TesterEntry(PropHandler)
{
	auto PrintList = [](const PropHandlerList& propHandlerList) {
		for (PropHandler* pPropHandler : propHandlerList) {
			::printf("%s\n", pPropHandler->GetSymbol()->GetName());
		}
	};
	RefPtr<PropHandlerOwner> pPropHandlerOwner(new PropHandlerOwner());
	pPropHandlerOwner->push_back(new PropHandlerTmp(Symbol::Add("grape")));
	pPropHandlerOwner->push_back(new PropHandlerTmp(Symbol::Add("orange")));
	pPropHandlerOwner->push_back(new PropHandlerTmp(Symbol::Add("apple")));
	pPropHandlerOwner->push_back(new PropHandlerTmp(Symbol::Add("banana")));
	pPropHandlerOwner->push_back(new PropHandlerTmp(Symbol::Add("pineapple")));
	PrintList(*pPropHandlerOwner);
	pPropHandlerOwner->Sort();
	::printf("----\n");
	PrintList(*pPropHandlerOwner);
	pPropHandlerOwner->Sort(SortOrder::Descend);
	::printf("----\n");
	PrintList(*pPropHandlerOwner);
}

}
