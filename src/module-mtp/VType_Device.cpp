//==============================================================================
// VType_Device.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mtp.Device#EnumStorage()
Gurax_DeclareMethod(Device, EnumStorage)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Device, EnumStorage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<StorageOwner> pStorageOwner(valueThis.GetDevice().EnumStorage());
	if (!pStorageOwner) return Value::nil();
	return new Value_Iterator(new Iterator_Storage(pStorageOwner.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// mtp.Device#friendlyName
Gurax_DeclareProperty_R(Device, friendlyName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Device, friendlyName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetDevice().GetFriendlyName());
}

// mtp.Device#manufacturer
Gurax_DeclareProperty_R(Device, manufacturer)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Device, manufacturer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetDevice().GetManufacturer());
}

// mtp.Device#description
Gurax_DeclareProperty_R(Device, description)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Device, description)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetDevice().GetDescription());
}

//------------------------------------------------------------------------------
// VType_Device
//------------------------------------------------------------------------------
VType_Device VTYPE_Device("Device");

void VType_Device::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Device, EnumStorage));
	// Assignment of property
	Assign(Gurax_CreateProperty(Device, friendlyName));
	Assign(Gurax_CreateProperty(Device, manufacturer));
	Assign(Gurax_CreateProperty(Device, description));
}

//------------------------------------------------------------------------------
// Value_Device
//------------------------------------------------------------------------------
VType& Value_Device::vtype = VTYPE_Device;

String Value_Device::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetDevice().ToString(ss));
}

Gurax_EndModuleScope(mtp)
