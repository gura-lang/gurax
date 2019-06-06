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
private:
	size_t _iProp;
public:
	PropHandlerCustom(const Symbol* pSymbol, size_t iProp) : PropHandler(pSymbol), _iProp(iProp) {}
protected:
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override;
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override;
};

}

#endif
