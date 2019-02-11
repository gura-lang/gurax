//==============================================================================
// test-Value.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void Test_ValueMap()
{
	RefPtr<ValueMap> pValueMap(new ValueMap());
	pValueMap->Assign(Symbol::Add("foo1"), new Value_Number(1));
	pValueMap->Assign(Symbol::Add("foo2"), new Value_Number(2));
	pValueMap->Assign(Symbol::Add("foo3"), Value::nil());
	pValueMap->Assign(Symbol::Add("foo4"), Value::true_());
	pValueMap->Assign(Symbol::Add("foo5"), Value::false_());
	pValueMap->Assign(Symbol::Add("foo6"), new Value_String("6"));
	pValueMap->Assign(Symbol::Add("foo7"), new Value_Number(7));
	pValueMap->Assign(Symbol::Add("foo8"), Value::undefined());
	pValueMap->Assign(Symbol::Add("foo9"), Value::Zero());
	pValueMap->Assign(Symbol::Add("fooA"), Value::EmptyStr());
	std::cout << pValueMap->ToString();
}

void Test_IsType()
{
	auto func = [](const Value* pValue) {
		::printf("%-12s %d %d %d %d\n",
				 pValue->GetVType().GetName(),
				 pValue->IsInstanceOf(VTYPE_Object),
				 pValue->IsType(VTYPE_Bool),
				 pValue->IsType(VTYPE_Number),
				 pValue->IsType(VTYPE_String));
	};
	func(new Value_Bool(true));
	func(new Value_Number(1));
	func(new Value_String(""));
}

void Test_Sort()
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		pValueOwner->push_back(new Value_String(pSampleRecord->name));
	}
	std::cout << pValueOwner->ToString();
	pValueOwner->Sort();
	for (auto pValue : *pValueOwner) std::cout << pValue->ToString();
	pValueOwner->Sort(SortOrder::Descend);
	for (auto pValue : *pValueOwner) std::cout << pValue->ToString();
}

void Test_Dict()
{
	RefPtr<ValueDict> pValueDict(new ValueDict());
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		pValueDict->Assign(new Value_String(pSampleRecord->name), new Value_String(pSampleRecord->email));
	}
	std::cout << pValueDict->ToString();
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		RefPtr<Value> pValueKey(new Value_String(pSampleRecord->name));
		Value* pValue = pValueDict->Lookup(pValueKey.get());
		::printf("%s: %s\n", pValueKey->ToString().c_str(), pValue->ToString().c_str());
	}
}

Gurax_TesterEntry(Value)
{
	Test_ValueMap();
	Test_IsType();
	Test_Sort();
	Test_Dict();
}

}
