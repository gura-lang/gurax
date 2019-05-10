//==============================================================================
// Basement.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Basement
//------------------------------------------------------------------------------
Basement Basement::Inst;


Basement::Basement() : _pFrame(new Frame_Basement()), _ps1(">>> "), _ps2("... ")
{
	_pathList.push_back(".");
}

void Basement::Prepare()
{
	Frame& frame = GetFrame();
	VType::PrepareBasic(frame);
	Value::PrepareBasic(frame);
	Statements::PrepareBasic(frame);
	Functions::PrepareBasic(frame);
	frame.Assign(Module_codecs::Create(frame.Reference()));
	frame.Assign(Module_fs::Create(frame.Reference()));
	frame.Assign(Module_math::Create(frame.Reference()));
	frame.Assign(Module_os::Create(frame.Reference()));
	frame.Assign(Module_path::Create(frame.Reference()));
	frame.Assign(Module_re::Create(frame.Reference()));
	frame.Assign(Module_sys::Create(frame.Reference()));
}

}
