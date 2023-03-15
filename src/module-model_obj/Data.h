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
	virtual const char* GetName() const = 0;
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) = 0;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) = 0;
};

//------------------------------------------------------------------------------
// DataDummy
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DataDummy : public Data {
private:
	String _name;
public:
	void SetName(String name) { _name = name; }
public:
	virtual const char* GetName() const override { return _name.c_str(); }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override { return true; }
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override {
		Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
		return false;
	}
};

Gurax_EndModuleScope(model_obj)

#endif
