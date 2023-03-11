//==============================================================================
// VType_Diff.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(diff.Diff, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(diff.Diff, `en)}

${help.ComposeMethodHelp(diff.Diff, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// diff.Diff(src1, src2):[icase] {block?}
Gurax_DeclareConstructor(Diff)
{
	Declare(VTYPE_Diff, Flag::None);
	DeclareArg("src1", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src2", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `diff.Diff` instance that includes difference information
between two sources `src1` and `src2`. The source is one of the followings:

- `String` of a whole text.
- `Binary` of a whole text.
- `Stream` of a whole text.
- `Iterator` that returns `String` of each line of a text.
- `List` that contains `String` of each line of a text.

Specifying `:icase` indicates the comparator to ignore character case.
)""");
}

Gurax_ImplementConstructor(Diff)
{
	// Arguments
	ArgPicker args(argument);
	Value& src1 = args.PickValue();
	Value& src2 = args.PickValue();
	// Function body
	bool icaseFlag = argument.IsSet(Gurax_Symbol(icase));
	RefPtr<Diff> pDiff(new Diff(icaseFlag));
	if (!pDiff->Compose(src1, src2)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Diff(pDiff.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// diff.Diff#EachEdit() {block?}
Gurax_DeclareMethod(Diff, EachEdit)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that returns stored edit information.
)""");
}

Gurax_ImplementMethod(Diff, EachEdit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	Diff& Diff = valueThis.GetDiff();
	RefPtr<Iterator> pIterator(new Iterator_Edit(Diff.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// diff.Diff#EachHunk(nLinesCommon?:Number) {block?}
Gurax_DeclareMethod(Diff, EachHunk)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("nLinesCommon", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that returns stored hunk information.
)""");
}

Gurax_ImplementMethod(Diff, EachHunk)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nLinesCommon = args.IsValid()? args.PickNumberNonNeg<size_t>() : 3;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Hunk(valueThis.GetDiff().Reference(), nLinesCommon));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.Diff#distance
Gurax_DeclareProperty_R(Diff, distance)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Difference distance.
)""");
}

Gurax_ImplementPropertyGetter(Diff, distance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDiff().GetDistance());
}

//------------------------------------------------------------------------------
// VType_Diff
//------------------------------------------------------------------------------
VType_Diff VTYPE_Diff("Diff");

void VType_Diff::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Diff));
	// Assignment of method
	Assign(Gurax_CreateMethod(Diff, EachEdit));
	Assign(Gurax_CreateMethod(Diff, EachHunk));
	// Assignment of property
	Assign(Gurax_CreateProperty(Diff, distance));
	//Gura_AssignProperty(diff_at_line, nLinesNew);
	//Gura_AssignProperty(diff_at_line, nLinesOrg);
}

//------------------------------------------------------------------------------
// Value_Diff
//------------------------------------------------------------------------------
VType& Value_Diff::vtype = VTYPE_Diff;

String Value_Diff::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetDiff().ToString(ss));
}

Gurax_EndModuleScope(diff)
