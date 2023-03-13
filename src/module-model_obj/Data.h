//==============================================================================
// Data.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_DATA_H
#define GURAX_MODULE_MODEL_OBJ_DATA_H
#include <gurax.h>
#include "Tokenizer.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Data
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Data {
public:
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) = 0;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) = 0;
};

Gurax_EndModuleScope(model_obj)

#endif
