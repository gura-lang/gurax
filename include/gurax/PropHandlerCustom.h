//==============================================================================
// PropHandlerCustom.h
//==============================================================================
#ifndef GURAX_PROPHANDLERCUSTOM_H
#define GURAX_PROPHANDLERCUSTOM_H
#include "PropHandler.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropHandlerCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropHandlerCustom : public PropHandler {
public:
	PropHandlerCustom(const Symbol* pSymbol) : PropHandler(pSymbol) {}
protected:
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override;
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override;
};

}

#endif
