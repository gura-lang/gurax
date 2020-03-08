//==============================================================================
// module-jpeg.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(jpeg)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// jpeg.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Test)
{
#if 0
	// Arguments
	//ArgPicker args(argument);
	// Function body
	struct jpeg_decompress_struct cinfo;
	FILE* fp = fopen("test.jpg", "rb");
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return Value::nil();
	}
	jpeg_read_header(&cinfo, TRUE);
#endif
	::printf("%d\n", sizeof(jpeg_decompress_struct));
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
	// Assignment of VType
	Assign(VTYPE_Exif);
	Assign(VTYPE_IFD);
	Assign(VTYPE_Tag);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	// Assignment of ImageMgr
	ImageMgr::Assign(new ImageMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(jpeg)
