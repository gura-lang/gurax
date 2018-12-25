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
};

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object);
public:
	class TypeInfo {
	protected:
		RefPtr<HelpProvider> _pHelpProvider;
		const TypeInfo* _pTypeInfoParent;
		const Symbol* _pSymbol;
		RefPtr<ObjectMap> _pObjMap;
	public:
		// Constructor
		TypeInfo(const TypeInfo* pTypeInfoParent, const char* name) :
			_pHelpProvider(new HelpProvider()), _pTypeInfoParent(pTypeInfoParent),
			_pSymbol(Symbol::Add(name)), _pObjMap(new ObjectMap()) {}
		// Copy constructor/operator
		TypeInfo(const TypeInfo& src) = delete;
		TypeInfo& operator=(const TypeInfo& src) = delete;
		// Move constructor/operator
		TypeInfo(TypeInfo&& src) = delete;
		TypeInfo& operator=(TypeInfo&& src) noexcept = delete;
		// Destructor
		~TypeInfo() = default;
	public:
		void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
			_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
		}
		bool IsIdentical(const TypeInfo& typeInfo) const { return this == &typeInfo; }
		virtual Object* Clone(const Object* pObj) const { return pObj->Reference(); }
	};
private:
	static const Object* _pObj_undefined;
	static const Object* _pObj_nil;
	static const Object* _pObj_zero;
	static const Object* _pObj_emptystr;
	static const Object* _pObj_false_;
	static const Object* _pObj_true_;
protected:
	const TypeInfo& _typeInfo;
public:
	static const TypeInfo typeInfo;
public:
	// Constructor
	Object() = delete;
	Object(const TypeInfo& typeInfo) : _typeInfo(typeInfo) {}
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
	static void Bootup();
	static Object* nil() { return _pObj_nil->Reference(); }
	static Object* undefined() { return _pObj_undefined->Reference(); }
	static Object* zero() { return _pObj_zero->Reference(); }
	static Object* emptystr() { return _pObj_emptystr->Reference(); }
	static Object* false_() { return _pObj_false_->Reference(); }
	static Object* true_() { return _pObj_true_->Reference(); }
public:
	const TypeInfo& GetTypeInfo() const { return _typeInfo; }
	virtual Object* Clone() const { return nullptr; }
public:
	template<typename T> bool IsType() const { return _typeInfo.IsIdentical(T::typeInfo); }
	template<typename T> static bool IsType(const Object* pObj) { return pObj && pObj->IsType<T>(); }
};

}

#endif
