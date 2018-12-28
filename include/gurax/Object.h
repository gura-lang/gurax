//==============================================================================
// Object.h
//==============================================================================
#ifndef GURAX_OBJECT_H
#define GURAX_OBJECT_H
#include "Function.h"
#include "Help.h"
#include "Referable.h"
#include "Symbol.h"

#define Gurax_DeclareClass() \
class KlassEx : public Klass { \
public: \
	virtual void DoPrepare() override; \
}; \
static KlassEx klass

#define Gurax_ImplementClass(T_Object) \
T_Object::KlassEx T_Object::klass; \
void T_Object::KlassEx::DoPrepare()

namespace Gurax {

class Object;
class Environment;

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
public:
	template<typename T_Map> static RefPtr<ObjectOwner> CollectKeys(const T_Map& map);
};

template<typename T_Map>
RefPtr<ObjectOwner> ObjectOwner::CollectKeys(const T_Map& map)
{
	RefPtr<ObjectOwner> pObjectOwner(new ObjectOwner());
	pObjectOwner->reserve(map.size());
	for (auto pair : map) pObjectOwner->push_back(pair.first->Reference());
	return pObjectOwner;
}

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
	Klass* _pKlassParent;
	const Symbol* _pSymbol;
	RefPtr<ObjectMap> _pObjectMap;
public:
	// Constructor
	Klass() : _pHelpProvider(new HelpProvider()), _pKlassParent(nullptr),
		_pSymbol(nullptr), _pObjectMap(new ObjectMap()) {}
	// Copy constructor/operator
	Klass(Klass& src) = delete;
	Klass& operator=(Klass& src) = delete;
	// Move constructor/operator
	Klass(Klass&& src) = delete;
	Klass& operator=(Klass&& src) noexcept = delete;
	// Destructor
	virtual ~Klass() = default;
public:
	void SetAttrs(const char* name) {
		_pSymbol = Symbol::Add(name);
	}
	void SetAttrs(const char* name, Klass& klassParent) {
		_pSymbol = Symbol::Add(name), _pKlassParent = &klassParent;
	}
	const HelpProvider& GetHelpProvider() const { return *_pHelpProvider; }
	Klass* GetParent() const { return _pKlassParent; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	bool IsIdentical(const Klass& klass) const { return this == &klass; }
	Object* LookupObject(const Symbol* pSymbol) const { return _pObjectMap->Get(pSymbol); }
	void Prepare() { DoPrepare(); }
	virtual void DoPrepare() = 0;
};

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object : public Referable {
public:
	struct EqualTo {
		size_t operator()(const Object* pObject1, const Object* pObject2) const {
			return pObject1->IsIdentical(pObject2);
		}
	};
	struct Hash {
		size_t operator()(const Object* pObjectl) const {
			return 0;
		}
	};
public:
	// Referable declaration
	Gurax_DeclareReferable(Object);
	// Class declaration
	Gurax_DeclareClass();
private:
	static const Object* _pObject_undefined;
	static const Object* _pObject_nil;
	static const Object* _pObject_zero;
	static const Object* _pObject_emptystr;
	static const Object* _pObject_false_;
	static const Object* _pObject_true_;
protected:
	Klass& _klass;
public:
	// Constructor
	Object() = delete;
	Object(Klass& klass) : _klass(klass) {}
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
	Klass& GetKlass() { return _klass; }
	const Klass& GetKlass() const { return _klass; }
	virtual Object* Clone() const = 0;
	size_t CalcHash() { return DoCalcHash(); }
	virtual size_t DoCalcHash() { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Object* pObject) const { return IsIdentical(pObject); }
	virtual String ToString() const { return String::Empty; }
	virtual String GenSource() const { return String::Empty; }
public:
	bool IsIdentical(const Object* pObject) const { return this == pObject; }
	static bool IsIdentical(const Object* pObject1, const Object* pObject2) {
		return pObject1? pObject1->IsIdentical(pObject2) : (!pObject1 && !pObject2);
	}
	bool IsSameType(const Object* pObject) const { return _klass.IsIdentical(pObject->GetKlass()); }
	static bool IsSameType(const Object* pObject1, const Object* pObject2) {
		return pObject1 && pObject1->IsSameType(pObject2);
	}
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
// ObjectDict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectDict :
	public std::unordered_map<Object*, Object*, Object::Hash, Object::EqualTo>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectDict);
protected:
	~ObjectDict() { Clear(); }
public:
	void Clear();
	void Set(Object* pObjectKey, Object* pObject);
	Object* Get(const Object* pObjectKey) const {
		auto pPair = find(const_cast<Object*>(pObjectKey));
		return (pPair == end())? nullptr : pPair->second;
	}
	bool IsSet(const Object* pObjectKey) const { return find(const_cast<Object*>(pObjectKey)) != end(); }
	RefPtr<ObjectOwner> GetKeys() const { return ObjectOwner::CollectKeys(*this); }
	void Print() const;
};

//------------------------------------------------------------------------------
// KlassMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE KlassMap :
	public std::unordered_map<const Symbol*, Klass*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(KlassMap);
protected:
	~KlassMap() = default;
public:
	void Set(const Symbol* pSymbol, Klass* pKlass);
	Klass* Get(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool IsSet(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	void Print() const;
};

}

#endif
