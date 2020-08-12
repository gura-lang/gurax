//==============================================================================
// module-opengl.cpp
//==============================================================================
#include "stdafx.h"
#include "ref/glm/glm/glm.hpp"
#include "ref/glm/glm/gtc/matrix_transform.hpp"
#include "ref/glm/glm/gtc/type_ptr.hpp"

Gurax_BeginModule(opengl)

// opengl.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Test)
{
	glm::mat4 mat = glm::mat4(1.0f);
	//mat = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	//mat = glm::rotate(mat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, -3.0f));
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			::printf("%f\n", mat[i][j]);
		}
		::printf("\n");
	}
	return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of value
	AssignConsts(GetFrame());
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	AssignFunctions(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(opengl)
