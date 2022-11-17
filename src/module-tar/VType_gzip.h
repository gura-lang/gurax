//==============================================================================
// VType_gzip.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_VTYPE_GZIP_H
#define GURAX_MODULE_TAR_VTYPE_GZIP_H
#include <gurax.h>
#include "Writer.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// VType_gzip
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_gzip : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_gzip VTYPE_gzip;

Gurax_EndModuleScope(tar)

#endif
