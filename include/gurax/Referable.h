//==============================================================================
// Referable.h
//==============================================================================
#ifndef GURAX_REFERABLE_H
#define GURAX_REFERABLE_H
#include "Common.h"

//------------------------------------------------------------------------------
// Macro
//------------------------------------------------------------------------------
#define Gurax_DeclareReferable(T) \
class WeakPtr : public WeakPtrBase { \
public: \
	WeakPtr(T* p) : WeakPtrBase(p) {} \
	static WeakPtr* Reference(const WeakPtr* pw) { return static_cast<WeakPtr*>(WeakPtrBase::Reference(pw)); } \
	WeakPtr* Reference() const { return static_cast<WeakPtr*>(WeakPtrBase::Reference()); } \
	T* Lock() { return T::Reference(static_cast<T*>(_p)); } \
}; \
static T* Reference(const T* p) { \
	T* pCasted = const_cast<T*>(p); \
	if (pCasted) pCasted->_cntRef++; \
	return pCasted; \
} \
T* Reference() const { \
	T* pCasted = const_cast<T*>(this); \
	pCasted->_cntRef++; \
	return pCasted; \
} \
WeakPtr* GetWeakPtr() const {\
	T* pCasted = const_cast<T*>(this); \
	if (pCasted->_pwBase) { \
		return static_cast<WeakPtr*>(pCasted->_pwBase)->Reference(); \
	} \
	pCasted->_pwBase = new WeakPtr(pCasted); \
	return static_cast<WeakPtr*>(pCasted->_pwBase); \
} \
static void Delete(T* p) { \
	if (!p) return; \
	p->_cntRef--; \
	if (p->_cntRef > 0) return; \
	WeakPtr::DeleteReferable(p->_pwBase); \
	delete p; \
} \
int GetCntRef() const { return _cntRef; }

namespace Gurax {

//------------------------------------------------------------------------------
// RefPtr
//------------------------------------------------------------------------------
template<typename T> class RefPtr {
private:
	T* _p;
public:
	// Default constructor
	RefPtr(T* p = nullptr) noexcept : _p(p) {}
	// Copy constructor/operator
	RefPtr(const RefPtr& obj) = delete;
	RefPtr& operator=(const RefPtr& obj) = delete;
	// Move constructor/operator
	RefPtr(RefPtr&& obj) : _p(obj._p) { obj._p = nullptr; }
	RefPtr& operator=(RefPtr&& obj) noexcept {
		T::Delete(_p);
		_p = obj._p;
		obj._p = nullptr;
		return *this;
	}
	// Destructor
	~RefPtr() { T::Delete(_p); }
public:
	T& operator*() { return *_p; }
	T& operator*() const { return *_p; }
	T* operator->() { return _p; }
	T* operator->() const { return _p; }
	void reset(T* p = nullptr) { T::Delete(_p); _p = p; }
	T* get() { return _p; }
	T* get() const { return _p; }
	T* release() { T* p = _p; _p = nullptr; return p; }
	explicit operator bool() const { return static_cast<bool>(_p); }
};

//------------------------------------------------------------------------------
// Referable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Referable {
public:
	class WeakPtrBase {
	protected:
		int _cntRef;
		Referable* _p;
	public:
		WeakPtrBase(Referable* p) : _cntRef(2), _p(p) {}
	public:
		static WeakPtrBase* Reference(const WeakPtrBase* p) {
			WeakPtrBase* pCasted = const_cast<WeakPtrBase*>(p);
			if (pCasted) pCasted->_cntRef++;
			return pCasted;
		}
		WeakPtrBase* Reference() const {
			WeakPtrBase* pCasted = const_cast<WeakPtrBase*>(this);
			pCasted->_cntRef++;
			return pCasted;
		}
		static void Delete(WeakPtrBase* p) {
			if (!p) return;
			p->_cntRef--;
			if (p->_cntRef <= 0) delete p;
		}
		static void DeleteReferable(WeakPtrBase* p) {
			if (!p) return;
			p->_cntRef--;
			p->_p = nullptr;
			if (p->_cntRef <= 0) delete p;
		}
		int GetCntRef() const { return _cntRef; }
	public:
		friend class Referable;
	};
protected:
	int _cntRef;
	WeakPtrBase* _pwBase;
public:
	// Constructor
	Referable() : _cntRef(1), _pwBase(nullptr) {}
	// Copy constructor/operator
	Referable(const Referable& src) = delete;
	Referable& operator=(const Referable& src) = delete;
	// Move constructor/operator
	Referable(Referable&& src) = delete;
	Referable& operator=(Referable&& src) noexcept = delete;
protected:
	// Destructor
	~Referable() = default;
};

}

#endif
