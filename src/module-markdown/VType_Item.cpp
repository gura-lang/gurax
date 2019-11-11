//==============================================================================
// VType_Item.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Item() {block?}
Gurax_DeclareFunction(Item)
{
	Declare(VTYPE_Item, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Item` instance.");
}

Gurax_ImplementFunction(Item)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Item> pItem(new Item());
	return argument.ReturnValue(processor, new Value_Item(pItem.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// markdown.Item#MethodSkeleton(num1:Number, num2:Number):reduce
Gurax_DeclareMethod(Item, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Item, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// markdown.Item#propSkeleton
Gurax_DeclareProperty_R(Item, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Item
//------------------------------------------------------------------------------
VType_Item VTYPE_Item("Item");

void VType_Item::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateFunction(Item));
	// Assignment of method
	Assign(Gurax_CreateMethod(Item, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Item, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Item
//------------------------------------------------------------------------------
VType& Value_Item::vtype = VTYPE_Item;

Gurax_EndModuleScope(markdown)
