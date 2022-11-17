//==============================================================================
// test-Referable.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class Foo : public Referable {
private:
	const char* _name;
public:
	Foo(const char* name) : _name(name) { ::printf("created: %s\n", _name); }
protected:
	~Foo() { ::printf("deleted: %s\n", _name); }
public:
	// Referable accessor
	Gurax_DeclareReferable(Foo);
public:
	const char* GetName() const { return _name; }
};

class FooList : public ListBase<Foo *> {
};

class FooOwner : public FooList {
public:
	~FooOwner() { Clear(); }
	void Clear() {
		for (auto pFoo : *this) Foo::Delete(pFoo);
		clear();
	}
};

Gurax_TesterEntry(Referable)
{
	do {
		::printf("new/Delete\n");
		auto pFoo1 = new Foo("A");
		auto pFoo2 = new Foo("B");
		auto pFoo3 = new Foo("C");
		Foo::Delete(pFoo1);
		Foo::Delete(pFoo2);
		Foo::Delete(pFoo3);
	} while (0);
	do {
		::printf("RefPtr\n");
		RefPtr<Foo> pFoo1 = new Foo("A");
		RefPtr<Foo> pFoo2 = new Foo("B");
		RefPtr<Foo> pFoo3 = new Foo("C");
	} while (0);
	do {
		::printf("Owner\n");
		FooOwner fooOwner;
		fooOwner.push_back(new Foo("A"));
		fooOwner.push_back(new Foo("B"));
		fooOwner.push_back(new Foo("C"));
	} while (0);
	do {
		::printf("WeakRef\n");
		auto pFoo1 = new Foo("A");
		do {
			RefPtr<Foo::WeakPtr> pwFoo = pFoo1->GetWeakPtr();
			if (auto pFoo = pwFoo->Lock()) {
				::printf("locked:  %s %d\n", pFoo->GetName(), pFoo->GetCntRef());
			}
		} while (0);
		::printf("         %s %d\n", pFoo1->GetName(), pFoo1->GetCntRef());
		do {
			RefPtr<Foo::WeakPtr> pwFoo = pFoo1->GetWeakPtr();
			if (auto pFoo = pwFoo->Lock()) {
				::printf("locked:  %s %d\n", pFoo->GetName(), pFoo->GetCntRef());
			}
		} while (0);
		do {
			RefPtr<Foo::WeakPtr> pwFoo = pFoo1->GetWeakPtr();
			Foo::Delete(pFoo1);
			RefPtr<Foo> pFoo = pwFoo->Lock();
			if (RefPtr<Foo> pFoo = pwFoo->Lock()) {
				::printf("locked:  %s %d\n", pFoo->GetName(), pFoo->GetCntRef());
			} else {
				::printf("locked:  fail\n");
			}
		} while (0);
	} while (0);
	do {
		::printf("WeakRef longevity\n");
		RefPtr<Foo> pFoo1 = new Foo("A");
		Foo::WeakPtr* pwFoo1 = pFoo1->GetWeakPtr();
		::printf("WeakRef: %d\n", pwFoo1->GetCntRef());
		Foo::WeakPtr* pwFoo2 = pwFoo1->Reference();
		::printf("WeakRef: %d\n", pwFoo2->GetCntRef());
		Foo::WeakPtr::Delete(pwFoo1);
		::printf("WeakRef: %d\n", pwFoo2->GetCntRef());
		Foo::WeakPtr::Delete(pwFoo2); // will not die
		::printf("WeakRef: %d\n", pwFoo2->GetCntRef());
	} while (0);
}

}
