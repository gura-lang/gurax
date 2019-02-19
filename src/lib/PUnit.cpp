//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PUnit);
protected:
	const PUnit *_pPUnitNext;
public:
	// Constructor
	PUnit() : _pPUnitNext(nullptr) {}
	// Copy constructor/operator
	PUnit(const PUnit& src) = delete;
	PUnit& operator=(const PUnit& src) = delete;
	// Move constructor/operator
	PUnit(PUnit&& src) = delete;
	PUnit& operator=(PUnit&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~PUnit() = default;
public:
	void SetPUnitNext(const PUnit* pPUnit) { _pPUnitNext = pPUnit; }
	const PUnit* GetPUnitNext() const { return _pPUnitNext; }
public:
	// Virtual functions
	virtual void Exec() const = 0;
};

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_UnaryOp : public PUnit {
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_UnaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
};

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_BinaryOp : public PUnit {
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_BinaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
};

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
void PUnit_UnaryOp::Exec() const
{
	RefPtr<Value> pValueChild(Context::PopStack());
	RefPtr<Value> pValue(GetOperator()->EvalUnary(pValueChild.release()));
	if (!pValue) return;
	Context::PushStack(pValue.release());
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
void PUnit_BinaryOp::Exec() const
{
	RefPtr<Value> pValueRight(Context::PopStack());
	RefPtr<Value> pValueLeft(Context::PopStack());
	RefPtr<Value> pValue(GetOperator()->EvalBinary(pValueLeft.release(), pValueRight.release()));
	if (!pValue) return;
	Context::PushStack(pValue.release());
}

}
