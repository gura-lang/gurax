//==============================================================================
// Composer.h
//==============================================================================
#ifndef GURAX_COMPOSER_H
#define GURAX_COMPOSER_H
#include "PUnit.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Composer {
private:
	PUnitList _punitList;
	PUnitStack _punitStack;
	PUnit *_pPUnitCont;
public:
	// Constructor
	Composer() : _pPUnitCont(nullptr) {}
	// Copy constructor/operator
	Composer(const Composer& src) = delete;
	Composer& operator=(const Composer& src) = delete;
	// Move constructor/operator
	Composer(Composer&& src) = delete;
	Composer& operator=(Composer&& src) noexcept = delete;
	// Destructor
	virtual ~Composer() = default;
public:
	const PUnitList& GetPUnitList() const { return _punitList; }
	PUnitStack& GetPUnitStack() { return _punitStack; }
	PUnit* GetPUnitCont() { return _pPUnitCont; }
	void Begin() { _pPUnitCont = nullptr; }
	void Add(PUnit* pPUnit);
};

}

#endif
