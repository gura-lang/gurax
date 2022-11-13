//==============================================================================
// module-opengl.cpp
//==============================================================================
#include "stdafx.h"
//#include "ref/glm/glm/glm.hpp"
//#include "ref/glm/glm/gtc/matrix_transform.hpp"
//#include "ref/glm/glm/gtc/type_ptr.hpp"

Gurax_BeginModule(opengl)

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
// opengl.glReadAsImage():[rgb,rgba]
Gurax_DeclareFunction(glReadAsImage)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunction(glReadAsImage)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumberPos<GLsizei>();
	GLsizei height = args.PickNumberPos<GLsizei>();
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(width, height)) return Value::nil();
	GLint param_PACK_ALIGNMENT;
	glGetIntegerv(GL_PACK_ALIGNMENT, &param_PACK_ALIGNMENT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//glReadBuffer(GL_FRONT);
	glReadPixels(x, y, width, height,
		format.IsIdentical(Image::Format::RGB)? GL_BGR : GL_BGRA, GL_UNSIGNED_BYTE,
		pImage->GetPointerC());
	glPixelStorei(GL_PACK_ALIGNMENT, param_PACK_ALIGNMENT);
	return argument.ReturnValue(processor, new Value_Image(pImage->Flip(false, true)));
}

// opengl.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunction(Test)
{
#if 0
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
#endif
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
	Assign(Gurax_CreateFunction(glReadAsImage));
	//Assign(Gurax_CreateFunction(Test));
	AssignFunctions(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(opengl)
