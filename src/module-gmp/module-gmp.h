//==============================================================================
// module-gmp.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_H
#define GURAX_MODULE_GMP_H
#include <gurax.h>
#include <gmpxx.h>
#include "Util.h"
#include "Random.h"
#include "VType_Float.h"
#include "VType_Rational.h"
#include "VType_Int.h"
#include "VType_Random.h"

Gurax_BeginModuleHeader(gmp)

void AssignOperators();

Gurax_EndModuleHeader(gmp)

#endif
