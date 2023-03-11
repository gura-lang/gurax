//==============================================================================
// VType_Device.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(mtp.Device, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(mtp.Device, `en)}

${help.ComposeMethodHelp(mtp.Device, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// mtp.Device(iDevice? as Number) {block?}
Gurax_DeclareConstructor(Device)
{
	Declare(VTYPE_Device, Flag::None);
	DeclareArg("iDevice", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Create an `mtp.Device` instance.
)""");
}

Gurax_ImplementConstructor(Device)
{
	// Arguments
	ArgPicker args(argument);
	size_t iDevice = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Device> pDevice(Device::OpenDevice(iDevice));
	if (!pDevice) return Value::nil();
	return argument.ReturnValue(processor, new Value_Device(pDevice.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mtp.Device#EnumStorage() {block?}
Gurax_DeclareMethod(Device, EnumStorage)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Device, EnumStorage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<StorageOwner> pStorageOwner(valueThis.GetDevice().EnumStorage());
	if (!pStorageOwner) return Value::nil();
	return argument.ReturnIterator(processor, new Iterator_Storage(pStorageOwner.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// mtp.Device#friendlyName
Gurax_DeclareProperty_R(Device, friendlyName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Device));
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
