//==============================================================================
// module-gmp.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_H
#define GURAX_MODULE_GMP_H
#include <gurax.h>
#include <mpirxx.h>
#include "Util.h"
#include "VType_mpf.h"
#include "VType_mpq.h"
#include "VType_mpz.h"

Gurax_BeginModuleHeader(gmp)

void AssignOperators();

Gurax_EndModuleHeader(gmp)

#endif