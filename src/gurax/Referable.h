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
static T* Reference(const T* p) { \
	T* pCasted = const_cast<T*>(p); \
	if (pCasted != nullptr) pCasted->_cntRef++; \
	return pCasted; \
} \
T* Reference() const { \
	T* pCasted = const_cast<T*>(this); \
	pCasted->_cntRef++; \
	return pCasted; \
} \
static void Delete(T* p) { \
	if (p == nullptr) return; \
	p->_cntRef--; \
	if (p->_cntRef <= 0) delete p; \
} \
int GetCntRef() const { return _cntRef; }

namespace Gurax {

//------------------------------------------------------------------------------
// Referable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Referable {
protected:
	int _cntRef;
public:
	// Default constructor
	Referable() : _cntRef(1) {}
	// Copy constructor/operator
	Referable(const Referable& src) = delete;
	Referable& operator=(const Referable& src) = delete;
	// Move constructor/operator
	Referable(Referable&& src) = delete;
	Referable& operator=(Referable&& src) noexcept = delete;
protected:
	// Destructor
	~Referable() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(Referable);
};

}

#endif
