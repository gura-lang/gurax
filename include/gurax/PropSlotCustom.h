//==============================================================================
// PropSlotCustom.h
//==============================================================================
#ifndef GURAX_PROPSLOTCUSTOM_H
#define GURAX_PROPSLOTCUSTOM_H
#include "PropSlot.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropSlotCustom_Instance
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropSlotCustom_Instance : public PropSlot {
private:
	size_t _iProp;
public:
	PropSlotCustom_Instance(const Symbol* pSymbol, size_t iProp) : PropSlot(pSymbol), _iProp(iProp) {}
public:
	size_t GetIndex() const { return _iProp; }
protected:
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override;
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override;
};

//------------------------------------------------------------------------------
// PropSlotCustom_Class
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropSlotCustom_Class : public PropSlot {
private:
	size_t _iProp;
public:
	PropSlotCustom_Class(const Symbol* pSymbol, size_t iProp) : PropSlot(pSymbol), _iProp(iProp) {}
public:
	size_t GetIndex() const { return _iProp; }
protected:
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override;
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override;
};

}

#endif
