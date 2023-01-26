//==============================================================================
// module-glu.cpp
//==============================================================================
#include "stdafx.h"

#define AssignConst(name) frame.Assign(#name, new Value_Number(name))

Gurax_BeginModule(glu)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	Frame& frame = GetFrame();
	// Assignment of constant
	AssignConst(GLU_VERSION_1_1);
	AssignConst(GLU_VERSION_1_2);
	AssignConst(GLU_INVALID_ENUM);
	AssignConst(GLU_INVALID_VALUE);
	AssignConst(GLU_OUT_OF_MEMORY);
	AssignConst(GLU_INCOMPATIBLE_GL_VERSION);
	AssignConst(GLU_VERSION);
	AssignConst(GLU_EXTENSIONS);
	AssignConst(GLU_SMOOTH);
	AssignConst(GLU_FLAT);
	AssignConst(GLU_NONE);
	AssignConst(GLU_POINT);
	AssignConst(GLU_LINE);
	AssignConst(GLU_FILL);
	AssignConst(GLU_SILHOUETTE);
	AssignConst(GLU_OUTSIDE);
	AssignConst(GLU_INSIDE);
	AssignConst(GLU_TESS_MAX_COORD);
	AssignConst(GLU_TESS_WINDING_RULE);
	AssignConst(GLU_TESS_BOUNDARY_ONLY);
	AssignConst(GLU_TESS_TOLERANCE);
	AssignConst(GLU_TESS_WINDING_ODD);
	AssignConst(GLU_TESS_WINDING_NONZERO);
	AssignConst(GLU_TESS_WINDING_POSITIVE);
	AssignConst(GLU_TESS_WINDING_NEGATIVE);
	AssignConst(GLU_TESS_WINDING_ABS_GEQ_TWO);
	AssignConst(GLU_TESS_BEGIN);
	AssignConst(GLU_TESS_VERTEX);
	AssignConst(GLU_TESS_END);
	AssignConst(GLU_TESS_ERROR);
	AssignConst(GLU_TESS_EDGE_FLAG);
	AssignConst(GLU_TESS_COMBINE);
	AssignConst(GLU_TESS_BEGIN_DATA);
	AssignConst(GLU_TESS_VERTEX_DATA);
	AssignConst(GLU_TESS_END_DATA);
	AssignConst(GLU_TESS_ERROR_DATA);
	AssignConst(GLU_TESS_EDGE_FLAG_DATA);
	AssignConst(GLU_TESS_COMBINE_DATA);
	AssignConst(GLU_TESS_ERROR1);
	AssignConst(GLU_TESS_ERROR2);
	AssignConst(GLU_TESS_ERROR3);
	AssignConst(GLU_TESS_ERROR4);
	AssignConst(GLU_TESS_ERROR5);
	AssignConst(GLU_TESS_ERROR6);
	AssignConst(GLU_TESS_ERROR7);
	AssignConst(GLU_TESS_ERROR8);
	AssignConst(GLU_AUTO_LOAD_MATRIX);
	AssignConst(GLU_CULLING);
	AssignConst(GLU_SAMPLING_TOLERANCE);
	AssignConst(GLU_DISPLAY_MODE);
	AssignConst(GLU_PARAMETRIC_TOLERANCE);
	AssignConst(GLU_SAMPLING_METHOD);
	AssignConst(GLU_U_STEP);
	AssignConst(GLU_V_STEP);
	AssignConst(GLU_PATH_LENGTH);
	AssignConst(GLU_PARAMETRIC_ERROR);
	AssignConst(GLU_DOMAIN_DISTANCE);
	AssignConst(GLU_MAP1_TRIM_2);
	AssignConst(GLU_MAP1_TRIM_3);
	AssignConst(GLU_OUTLINE_POLYGON);
	AssignConst(GLU_OUTLINE_PATCH);
	AssignConst(GLU_NURBS_ERROR1);
	AssignConst(GLU_NURBS_ERROR2);
	AssignConst(GLU_NURBS_ERROR3);
	AssignConst(GLU_NURBS_ERROR4);
	AssignConst(GLU_NURBS_ERROR5);
	AssignConst(GLU_NURBS_ERROR6);
	AssignConst(GLU_NURBS_ERROR7);
	AssignConst(GLU_NURBS_ERROR8);
	AssignConst(GLU_NURBS_ERROR9);
	AssignConst(GLU_NURBS_ERROR10);
	AssignConst(GLU_NURBS_ERROR11);
	AssignConst(GLU_NURBS_ERROR12);
	AssignConst(GLU_NURBS_ERROR13);
	AssignConst(GLU_NURBS_ERROR14);
	AssignConst(GLU_NURBS_ERROR15);
	AssignConst(GLU_NURBS_ERROR16);
	AssignConst(GLU_NURBS_ERROR17);
	AssignConst(GLU_NURBS_ERROR18);
	AssignConst(GLU_NURBS_ERROR19);
	AssignConst(GLU_NURBS_ERROR20);
	AssignConst(GLU_NURBS_ERROR21);
	AssignConst(GLU_NURBS_ERROR22);
	AssignConst(GLU_NURBS_ERROR23);
	AssignConst(GLU_NURBS_ERROR24);
	AssignConst(GLU_NURBS_ERROR25);
	AssignConst(GLU_NURBS_ERROR26);
	AssignConst(GLU_NURBS_ERROR27);
	AssignConst(GLU_NURBS_ERROR28);
	AssignConst(GLU_NURBS_ERROR29);
	AssignConst(GLU_NURBS_ERROR30);
	AssignConst(GLU_NURBS_ERROR31);
	AssignConst(GLU_NURBS_ERROR32);
	AssignConst(GLU_NURBS_ERROR33);
	AssignConst(GLU_NURBS_ERROR34);
	AssignConst(GLU_NURBS_ERROR35);
	AssignConst(GLU_NURBS_ERROR36);
	AssignConst(GLU_NURBS_ERROR37);
	AssignConst(GLU_CW);
	AssignConst(GLU_CCW);
	AssignConst(GLU_INTERIOR);
	AssignConst(GLU_EXTERIOR);
	AssignConst(GLU_UNKNOWN);
	// Assignment of function
	AssignFunctions(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(glu)
