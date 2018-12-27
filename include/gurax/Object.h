//==============================================================================
// Object.h
//==============================================================================
#ifndef GURAX_OBJECT_H
#define GURAX_OBJECT_H
#include "Function.h"
#include "Help.h"
#include "Referable.h"
#include "Symbol.h"

namespace Gurax {

class Object;
	
//------------------------------------------------------------------------------
// ObjectList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectList : public std::vector<Object*> {
};

//------------------------------------------------------------------------------
// ObjectOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectOwner : public ObjectList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectOwner);
protected:
	~ObjectOwner() { Clear(); }
public:
	void Clear();
	RefPtr<ObjectOwner> Clone() const;
	RefPtr<ObjectOwner> CloneDeep() const;
	void Set(size_t pos, Object* pObject);
	Object* Get(size_t pos) const { return at(pos); }
};

//------------------------------------------------------------------------------
// ObjectMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectMap :
	public std::unordered_map<const Symbol*, Object*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectMap);
protected:
	~ObjectMap() { Clear(); }
public:
	void Clear();
	void Set(const Symbol* pSymbol, Object* pObject);
	Object* Get(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool IsSet(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	void Print() const;
};

//------------------------------------------------------------------------------
// Klass
//------------------------------------------------------------------------------
class Klass {
protected:
	RefPtr<HelpProvider> _pHelpProvider;
	const Klass* _pKlassParent;
	const Symbol* _pSymbol;
	RefPtr<ObjectMap> _pObjectMap;
public:
	// Constructor
	Klass(const Klass* pKlassParent, const char* name) :
		_pHelpProvider(new HelpProvider()), _pKlassParent(pKlassParent),
		_pSymbol(Symbol::Add(name)), _pObjectMap(new ObjectMap()) {}
	// Copy constructor/operator
	Klass(const Klass& src) = delete;
	Klass& operator=(const Klass& src) = delete;
	// Move constructor/operator
	Klass(Klass&& src) = delete;
	Klass& operator=(Klass&& src) noexcept = delete;
	// Destructor
	~Klass() = default;
public:
	const HelpProvider& GetHelpProvider() const { return *_pHelpProvider; }
	const Klass* GetParent() const { return _pKlassParent; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	bool IsIdentical(const Klass& klass) const { return this == &klass; }
	Object* Lookup(const Symbol* pSymbol) const { return _pObjectMap->Get(pSymbol); }
};

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object);
public:
	class KlassEx : public Klass {
	public:
		// Constructor
		KlassEx() : Klass(nullptr, "object") {}
		// Copy constructor/operator
		KlassEx(const KlassEx& src) = delete;
		KlassEx& operator=(const KlassEx& src) = delete;
		// Move constructor/operator
		KlassEx(KlassEx&& src) = delete;
		KlassEx& operator=(KlassEx&& src) noexcept = delete;
		// Destructor
		~KlassEx() = default;
	};
private:
	static const Object* _pObject_undefined;
	static const Object* _pObject_nil;
	static const Object* _pObject_zero;
	static const Object* _pObject_emptystr;
	static const Object* _pObject_false_;
	static const Object* _pObject_true_;
protected:
	const Klass& _klass;
public:
	static const KlassEx klass;
public:
	// Constructor
	Object() = delete;
	Object(const Klass& klass) : _klass(klass) {}
	// Copy constructor/operator
	Object(const Object& src) = delete;
	Object& operator=(const Object& src) = delete;
	// Move constructor/operator
	Object(Object&& src) = delete;
	Object& operator=(Object&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object() = default;
public:
	const Klass& GetKlass() const { return _klass; }
	virtual Object* Clone() const = 0;
	virtual String ToString() const { return String::Empty; }
	virtual String GenSource() const { return String::Empty; }
public:
	template<typename T> bool IsType() const { return _klass.IsIdentical(T::klass); }
	template<typename T> static bool IsType(const Object* pObject) { return pObject && pObject->IsType<T>(); }
	template<typename T> bool IsInstanceOf() const;
	template<typename T> static bool IsInstanceOf(const Object* pObject) { return pObject && pObject->IsInstanceOf<T>(); }
public:
	static void Bootup();
	static Object* nil()		{ return _pObject_nil->Reference(); }
	static Object* undefined()	{ return _pObject_undefined->Reference(); }
	static Object* zero()		{ return _pObject_zero->Reference(); }
	static Object* emptystr()	{ return _pObject_emptystr->Reference(); }
	static Object* false_()		{ return _pObject_false_->Reference(); }
	static Object* true_()		{ return _pObject_true_->Reference(); }
};

template<typename T> bool Object::IsInstanceOf() const
{
	for (const Klass *pKlass = &_klass; pKlass != nullptr; pKlass = pKlass->GetParent()) {
		if (pKlass->IsIdentical(T::klass)) return true;
	}
	return false;
}

//------------------------------------------------------------------------------
// KlassMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE KlassMap :
	public std::unordered_map<const Symbol*, const Klass*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(KlassMap);
protected:
	~KlassMap() = default;
public:
	void Set(const Symbol* pSymbol, const Klass* pKlass);
	const Klass* Get(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool IsSet(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	void Print() const;
};

}

#endif
