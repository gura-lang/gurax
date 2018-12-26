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
	void Set(size_t pos, Object* pObj);
	Object* Get(size_t pos) const { return at(pos); }
};

//------------------------------------------------------------------------------
// ObjectMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectMap :
	public std::unordered_map<const Symbol*, Object*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectMap);
protected:
	~ObjectMap() { Clear(); }
public:
	void Clear();
	void Set(const Symbol* pSymbol, Object* pObj);
	Object* Get(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool IsSet(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys(SortOrder sortOrder = SortOrder::Ascend) const;
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
	RefPtr<ObjectMap> _pObjMap;
public:
	// Constructor
	Klass(const Klass* pKlassParent, const char* name) :
		_pHelpProvider(new HelpProvider()), _pKlassParent(pKlassParent),
		_pSymbol(Symbol::Add(name)), _pObjMap(new ObjectMap()) {}
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
	Object* Lookup(const Symbol* pSymbol) const { return _pObjMap->Get(pSymbol); }
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
	static const Object* _pObj_undefined;
	static const Object* _pObj_nil;
	static const Object* _pObj_zero;
	static const Object* _pObj_emptystr;
	static const Object* _pObj_false_;
	static const Object* _pObj_true_;
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
	template<typename T> static bool IsType(const Object* pObj) { return pObj && pObj->IsType<T>(); }
public:
	static void Bootup();
	static Object* nil() { return _pObj_nil->Reference(); }
	static Object* undefined() { return _pObj_undefined->Reference(); }
	static Object* zero() { return _pObj_zero->Reference(); }
	static Object* emptystr() { return _pObj_emptystr->Reference(); }
	static Object* false_() { return _pObj_false_->Reference(); }
	static Object* true_() { return _pObj_true_->Reference(); }
};

}

#endif
