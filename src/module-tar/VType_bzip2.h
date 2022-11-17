//==============================================================================
// VType_bzip2.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_VTYPE_BZIP2_H
#define GURAX_MODULE_TAR_VTYPE_BZIP2_H
#include <gurax.h>
#include "Writer.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// VType_bzip2
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_bzip2 : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_bzip2 VTYPE_bzip2;

Gurax_EndModuleScope(tar)

#endif
