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
};

//------------------------------------------------------------------------------
// ObjectMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectMap : public std::map<const Symbol*, Object*>, public Referable {
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
		RefPtr<ObjectMap> _pObjMap;
	public:
		// Constructor
		TypeInfo(const TypeInfo* pTypeInfoParent = nullptr) :
			_pHelpProvider(new HelpProvider()),
			_pTypeInfoParent(pTypeInfoParent), _pObjMap(new ObjectMap()) {}
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
		bool IsType(const TypeInfo& typeInfo) const { return this == &typeInfo; }
		virtual Object* Clone(const Object* pObj) const { return pObj->Reference(); }
	};
private:
	static const Object* _pObj_undefined;
	static const Object* _pObj_nil;
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
	~Object() = default;
public:
	static void Bootup();
	const TypeInfo& GetTypeInfo() const { return _typeInfo; }
	static Object* nil() { return _pObj_nil->Reference(); }
	static Object* undefined() { return _pObj_undefined->Reference(); }
public:
	bool IsType(const TypeInfo& typeInfo) const { return _typeInfo.IsType(typeInfo); }
	static bool IsType(Object* pObj, const TypeInfo& typeInfo) {
		return pObj && pObj->IsType(typeInfo);
	}
};

}

#endif
