//-----------------------------------------------------------------------------
// Gura module: gif
//-----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleBody(gif)

//-----------------------------------------------------------------------------
// Object_Header
//-----------------------------------------------------------------------------
Object *Object_Header::Clone() const
{
	return new Object_Header(*this);
}

String Object_Header::ToString(bool exprFlag)
{
	return String("<gif.Header>");
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.Header#Signature
Gura_DeclareProperty_R(Header, Signature)
{
	SetPropAttr(VTYPE_binary);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(Header, Signature)
{
	const Content::Header &hdr = Object_Header::GetObject(valueThis)->GetObjContent()->GetGIF().GetHeader();
	return Value(new Object_binary(env, hdr.Signature, sizeof(hdr.Signature), true));
}

// gif.Header#Version
Gura_DeclareProperty_R(Header, Version)
{
	SetPropAttr(VTYPE_binary);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(Header, Version)
{
	const Content::Header &hdr = Object_Header::GetObject(valueThis)->GetObjContent()->GetGIF().GetHeader();
	return Value(new Object_binary(env, hdr.Version, sizeof(hdr.Version), true));
}

Gura_ImplementUserClass(Header)
{
	Gura_AssignProperty(Header, Signature);
	Gura_AssignProperty(Header, Version);
	// Assignment of value
	Gura_AssignValue(Header, Value(Reference()));
}

//-----------------------------------------------------------------------------
// Object_LogicalScreenDescriptor
//-----------------------------------------------------------------------------
Object *Object_LogicalScreenDescriptor::Clone() const
{
	return new Object_LogicalScreenDescriptor(*this);
}

String Object_LogicalScreenDescriptor::ToString(bool exprFlag)
{
	return String("<gif.LogicalScreenDescriptor>");
}

// gif.LogicalScreenDescriptor#BackgroundColor
Gura_DeclareProperty_R(LogicalScreenDescriptor, BackgroundColor)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, BackgroundColor)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	size_t idx = lsd.BackgroundColorIndex;
	Palette *pPalette = gif.GetGlobalPalette();
	if (pPalette == nullptr || pPalette->CountEntries() < idx) {
		return Value::Nil;
	}
	return pPalette->GetColorValue(env, idx);
}

// gif.LogicalScreenDescriptor#BackgroundColorIndex
Gura_DeclareProperty_R(LogicalScreenDescriptor, BackgroundColorIndex)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, BackgroundColorIndex)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(lsd.BackgroundColorIndex);
}

// gif.LogicalScreenDescriptor#ColorResolution
Gura_DeclareProperty_R(LogicalScreenDescriptor, ColorResolution)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, ColorResolution)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(lsd.ColorResolution());
}

// gif.LogicalScreenDescriptor#GlobalColorTableFlag
Gura_DeclareProperty_R(LogicalScreenDescriptor, GlobalColorTableFlag)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, GlobalColorTableFlag)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(lsd.GlobalColorTableFlag());
}

// gif.LogicalScreenDescriptor#LogicalScreenHeight
Gura_DeclareProperty_R(LogicalScreenDescriptor, LogicalScreenHeight)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, LogicalScreenHeight)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(Gura_UnpackUInt16(lsd.LogicalScreenHeight));
}

// gif.LogicalScreenDescriptor#LogicalScreenWidth
Gura_DeclareProperty_R(LogicalScreenDescriptor, LogicalScreenWidth)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, LogicalScreenWidth)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(Gura_UnpackUInt16(lsd.LogicalScreenWidth));
}

// gif.LogicalScreenDescriptor#PixelAspectRatio
Gura_DeclareProperty_R(LogicalScreenDescriptor, PixelAspectRatio)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, PixelAspectRatio)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(lsd.PixelAspectRatio);
}

// gif.LogicalScreenDescriptor#SizeOfGlobalColorTable
Gura_DeclareProperty_R(LogicalScreenDescriptor, SizeOfGlobalColorTable)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, SizeOfGlobalColorTable)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(static_cast<UInt>(lsd.SizeOfGlobalColorTable()));
}

// gif.LogicalScreenDescriptor#SortFlag
Gura_DeclareProperty_R(LogicalScreenDescriptor, SortFlag)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(LogicalScreenDescriptor, SortFlag)
{
	GIF &gif = Object_LogicalScreenDescriptor::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::LogicalScreenDescriptor &lsd = gif.GetLogicalScreenDescriptor();
	return Value(lsd.SortFlag());
}

Gura_ImplementUserClass(LogicalScreenDescriptor)
{
	// Assignment of properties
	Gura_AssignProperty(LogicalScreenDescriptor, BackgroundColor);
	Gura_AssignProperty(LogicalScreenDescriptor, BackgroundColorIndex);
	Gura_AssignProperty(LogicalScreenDescriptor, ColorResolution);
	Gura_AssignProperty(LogicalScreenDescriptor, GlobalColorTableFlag);
	Gura_AssignProperty(LogicalScreenDescriptor, LogicalScreenHeight);
	Gura_AssignProperty(LogicalScreenDescriptor, LogicalScreenWidth);
	Gura_AssignProperty(LogicalScreenDescriptor, PixelAspectRatio);
	Gura_AssignProperty(LogicalScreenDescriptor, SizeOfGlobalColorTable);
	Gura_AssignProperty(LogicalScreenDescriptor, SortFlag);
	// Assignment of value
	Gura_AssignValue(LogicalScreenDescriptor, Value(Reference()));
}

//-----------------------------------------------------------------------------
// Object_CommentExtension
//-----------------------------------------------------------------------------
Object *Object_CommentExtension::Clone() const
{
	return new Object_CommentExtension(*this);
}

String Object_CommentExtension::ToString(bool exprFlag)
{
	return String("<gif.CommentExtension>");
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.CommentExtension#CommentData
Gura_DeclareProperty_R(CommentExtension, CommentData)
{
	SetPropAttr(VTYPE_binary);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(CommentExtension, CommentData)
{
	GIF &gif = Object_CommentExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::Extensions &exts = gif.GetExtensions();
	if (!exts.comment.validFlag) return Value::Nil;
	return Value(new Object_binary(env, exts.comment.CommentData, true));
}

Gura_ImplementUserClass(CommentExtension)
{
	// Assignment of properties
	Gura_AssignProperty(CommentExtension, CommentData);
	// Assignment of value
	Gura_AssignValue(CommentExtension, Value(Reference()));
}

//-----------------------------------------------------------------------------
// Object_PlainTextExtension
//-----------------------------------------------------------------------------
Object *Object_PlainTextExtension::Clone() const
{
	return new Object_PlainTextExtension(*this);
}

String Object_PlainTextExtension::ToString(bool exprFlag)
{
	return String("<gif.PlainTextExtension>");
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.PlainTextExtension#CharacterCellHeight
Gura_DeclareProperty_R(PlainTextExtension, CharacterCellHeight)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, CharacterCellHeight)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(pltxt.CharacterCellHeight);
}

// gif.PlainTextExtension#CharacterCellWidth
Gura_DeclareProperty_R(PlainTextExtension, CharacterCellWidth)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, CharacterCellWidth)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(pltxt.CharacterCellWidth);
}

// gif.PlainTextExtension#PlainTextData
Gura_DeclareProperty_R(PlainTextExtension, PlainTextData)
{
	SetPropAttr(VTYPE_binary);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, PlainTextData)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(new Object_binary(env, pltxt.PlainTextData, true));
}

// gif.PlainTextExtension#TextBackgroundColorIndex
Gura_DeclareProperty_R(PlainTextExtension, TextBackgroundColorIndex)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, TextBackgroundColorIndex)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(pltxt.TextBackgroundColorIndex);
}

// gif.PlainTextExtension#TextForegroundColorIndex
Gura_DeclareProperty_R(PlainTextExtension, TextForegroundColorIndex)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, TextForegroundColorIndex)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(pltxt.TextForegroundColorIndex);
}

// gif.PlainTextExtension#TextGridHeight
Gura_DeclareProperty_R(PlainTextExtension, TextGridHeight)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, TextGridHeight)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(Gura_UnpackUInt16(pltxt.TextGridHeight));
}

// gif.PlainTextExtension#TextGridLeftPosition
Gura_DeclareProperty_R(PlainTextExtension, TextGridLeftPosition)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, TextGridLeftPosition)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(Gura_UnpackUInt16(pltxt.TextGridLeftPosition));
}

// gif.PlainTextExtension#TextGridTopPosition
Gura_DeclareProperty_R(PlainTextExtension, TextGridTopPosition)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, TextGridTopPosition)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(Gura_UnpackUInt16(pltxt.TextGridTopPosition));
}

// gif.PlainTextExtension#TextGridWidth
Gura_DeclareProperty_R(PlainTextExtension, TextGridWidth)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(PlainTextExtension, TextGridWidth)
{
	GIF &gif = Object_PlainTextExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::PlainTextExtension &pltxt = gif.GetExtensions().plainText;
	if (!pltxt.validFlag) return Value::Nil;
	return Value(Gura_UnpackUInt16(pltxt.TextGridWidth));
}

Gura_ImplementUserClass(PlainTextExtension)
{
	// Assignment of properties
	Gura_AssignProperty(PlainTextExtension, CharacterCellHeight);
	Gura_AssignProperty(PlainTextExtension, CharacterCellWidth);
	Gura_AssignProperty(PlainTextExtension, PlainTextData);
	Gura_AssignProperty(PlainTextExtension, TextBackgroundColorIndex);
	Gura_AssignProperty(PlainTextExtension, TextForegroundColorIndex);
	Gura_AssignProperty(PlainTextExtension, TextGridHeight);
	Gura_AssignProperty(PlainTextExtension, TextGridLeftPosition);
	Gura_AssignProperty(PlainTextExtension, TextGridTopPosition);
	Gura_AssignProperty(PlainTextExtension, TextGridWidth);
	// Assignment of value
	Gura_AssignValue(PlainTextExtension, Value(Reference()));
}

//-----------------------------------------------------------------------------
// Object_ApplicationExtension
//-----------------------------------------------------------------------------
Object *Object_ApplicationExtension::Clone() const
{
	return new Object_ApplicationExtension(*this);
}

String Object_ApplicationExtension::ToString(bool exprFlag)
{
	return String("<gif.ApplicationExtension>");
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.ApplicationExtension#ApplicationData
Gura_DeclareProperty_R(ApplicationExtension, ApplicationData)
{
	SetPropAttr(VTYPE_binary);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ApplicationExtension, ApplicationData)
{
	GIF &gif = Object_ApplicationExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::ApplicationExtension &app = gif.GetExtensions().application;
	if (!app.validFlag) return Value::Nil;
	return Value(new Object_binary(env, app.ApplicationData, true));
}

// gif.ApplicationExtension#ApplicationIdentifier
Gura_DeclareProperty_R(ApplicationExtension, ApplicationIdentifier)
{
	SetPropAttr(VTYPE_binary);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ApplicationExtension, ApplicationIdentifier)
{
	GIF &gif = Object_ApplicationExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::ApplicationExtension &app = gif.GetExtensions().application;
	if (!app.validFlag) return Value::Nil;
	return Value(new Object_binary(env, app.ApplicationIdentifier, sizeof(app.ApplicationIdentifier), true));
}

// gif.ApplicationExtension#AuthenticationCode
Gura_DeclareProperty_R(ApplicationExtension, AuthenticationCode)
{
	SetPropAttr(VTYPE_binary);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ApplicationExtension, AuthenticationCode)
{
	GIF &gif = Object_ApplicationExtension::GetObject(valueThis)->GetObjContent()->GetGIF();
	Content::ApplicationExtension &app = gif.GetExtensions().application;
	if (!app.validFlag) return Value::Nil;
	return Value(new Object_binary(env, app.AuthenticationCode, sizeof(app.AuthenticationCode), true));
}

Gura_ImplementUserClass(ApplicationExtension)
{
	Gura_AssignProperty(ApplicationExtension, ApplicationData);
	Gura_AssignProperty(ApplicationExtension, ApplicationIdentifier);
	Gura_AssignProperty(ApplicationExtension, AuthenticationCode);
	// Assignment of value
	Gura_AssignValue(ApplicationExtension, Value(Reference()));
}


//-----------------------------------------------------------------------------
// Object_content
//-----------------------------------------------------------------------------
Object_content::~Object_content()
{
}

Object *Object_content::Clone() const
{
	return nullptr;
}

String Object_content::ToString(bool exprFlag)
{
	String str = "<gif.content:";
	do {
		char buff[32];
		const ValueList &valList = _gif.GetList();
		::sprintf(buff, "%luimages", valList.size());
		str += buff;
	} while (0);
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_content
//-----------------------------------------------------------------------------
// gif.content#write(stream:stream:w):reduce
Gura_DeclareMethod(content, write)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Write);
	AddHelp(
		Gura_Symbol(en),
		"Writes a GIF image to a stream.\n"
		"\n"
		"This method returns the reference to the target instance itself.\n");
}

Gura_ImplementMethod(content, write)
{
	Signal &sig = env.GetSignal();
	GIF &gif = Object_content::GetObjectThis(arg)->GetGIF();
	Stream &stream = arg.GetStream(0);
	UInt16 loopCount = 0;
	if (!gif.Write(env, stream, Color::zero, false, loopCount)) {
		return Value::Nil;
	}
	return arg.GetValueThis();
}

// gif.content#addimage(image:image, delayTime:number => 0, 
//	leftPos:number => 0, topPos:number => 0, disposalMethod:symbol => `none):map:reduce
Gura_DeclareMethod(content, addimage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "image", VTYPE_image);
	DeclareArg(env, "delayTime", VTYPE_number, OCCUR_Once,
			   FLAG_None, 0, new Expr_Value(10));
	DeclareArg(env, "leftPos", VTYPE_number, OCCUR_Once,
			   FLAG_None, 0, new Expr_Value(0));
	DeclareArg(env, "topPos", VTYPE_number, OCCUR_Once,
			   FLAG_None, 0, new Expr_Value(0));
	DeclareArg(env, "disposalMethod", VTYPE_symbol, OCCUR_Once,
			   FLAG_None, 0, new Expr_Value(Gura_UserSymbol(none)));
	AddHelp(
		Gura_Symbol(en), 
		"Adds an image to GIF information.\n"
		"\n"
		"You can add multiple images that can be played as a motion picture.\n"
		"\n"
		"The argument `delayTime` specifies the delay time in 10 milli seconds between images.\n"
		"\n"
		"The arguments `leftPost` and `topPos` specifies the rendered offset in the screen.\n"
		"\n"
		"The argument `disposalMethod` takes one of following symbols that specifies\n"
		"how the image will be treated after being rendered.\n"
		"\n"
		"- `` `none`` .. \n"
		"- `` `keep`` .. \n"
		"- `` `background``.. \n"
		"- `` `previous`` .. \n"
		"\n"
		"This method returns the reference to the target instance itself.\n");
}

Gura_ImplementMethod(content, addimage)
{
	Signal &sig = env.GetSignal();
	GIF &gif = Object_content::GetObjectThis(arg)->GetGIF();
	UChar disposalMethod = Content::DisposalMethodFromSymbol(sig, arg.GetSymbol(4));
	if (sig.IsSignalled()) return Value::Nil;
	gif.AddImage(arg.GetValue(0), arg.GetUInt16(1),
					arg.GetUInt16(2), arg.GetUInt16(3), disposalMethod);
	return arg.GetValueThis();
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.content#ApplicationExtension
Gura_DeclareProperty_R(content, ApplicationExtension)
{
	SetPropAttr(VTYPE_ApplicationExtension);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(content, ApplicationExtension)
{
	Object_content *pObjThis = Object_content::GetObject(valueThis);
	Content::Extensions &exts = pObjThis->GetGIF().GetExtensions();
	if (!exts.application.validFlag) return Value::Nil;
	return Value(new Object_ApplicationExtension(Object_content::Reference(pObjThis)));
}

// gif.content#CommentExtension
Gura_DeclareProperty_R(content, CommentExtension)
{
	SetPropAttr(VTYPE_CommentExtension);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(content, CommentExtension)
{
	Object_content *pObjThis = Object_content::GetObject(valueThis);
	Content::Extensions &exts = pObjThis->GetGIF().GetExtensions();
	if (!exts.comment.validFlag) return Value::Nil;
	return Value(new Object_CommentExtension(Object_content::Reference(pObjThis)));
}

// gif.content#Header
Gura_DeclareProperty_R(content, Header)
{
	SetPropAttr(VTYPE_Header);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(content, Header)
{
	Object_content *pObjThis = Object_content::GetObject(valueThis);
	return Value(new Object_Header(Object_content::Reference(pObjThis)));
}

// gif.content#LogicalScreenDescriptor
Gura_DeclareProperty_R(content, LogicalScreenDescriptor)
{
	SetPropAttr(VTYPE_LogicalScreenDescriptor);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(content, LogicalScreenDescriptor)
{
	Object_content *pObjThis = Object_content::GetObject(valueThis);
	return Value(new Object_LogicalScreenDescriptor(Object_content::Reference(pObjThis)));
}

// gif.content#PlainTextExtension
Gura_DeclareProperty_R(content, PlainTextExtension)
{
	SetPropAttr(VTYPE_PlainTextExtension);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(content, PlainTextExtension)
{
	Object_content *pObjThis = Object_content::GetObject(valueThis);
	Content::Extensions &exts = pObjThis->GetGIF().GetExtensions();
	if (!exts.plainText.validFlag) return Value::Nil;
	return Value(new Object_PlainTextExtension(Object_content::Reference(pObjThis)));
}

// gif.content#images
Gura_DeclareProperty_R(content, images)
{
	SetPropAttr(VTYPE_list);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(content, images)
{
	Object_content *pObjThis = Object_content::GetObject(valueThis);
	GIF &gif = pObjThis->GetGIF();
	return Value(new Object_list(env, gif.GetList()));
}

// implementation of class GIF
Gura_ImplementUserClass(content)
{
	// Assignment of properties
	Gura_AssignProperty(content, ApplicationExtension);
	Gura_AssignProperty(content, CommentExtension);
	Gura_AssignProperty(content, Header);
	Gura_AssignProperty(content, LogicalScreenDescriptor);
	Gura_AssignProperty(content, PlainTextExtension);
	Gura_AssignProperty(content, images);
	// Assignment of methods
	Gura_AssignMethod(content, addimage);
	Gura_AssignMethod(content, write);
}

//-----------------------------------------------------------------------------
// Object_GraphicControl
//-----------------------------------------------------------------------------
Object_GraphicControl::~Object_GraphicControl()
{
}

Object *Object_GraphicControl::Clone() const
{
	return nullptr;
}

String Object_GraphicControl::ToString(bool exprFlag)
{
	return String("<gif.GraphicControl>");
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.GraphicControl#DelayTime
Gura_DeclareProperty_R(GraphicControl, DelayTime)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(GraphicControl, DelayTime)
{
	const Content::GraphicControlExtension &gctl =
		*Object_GraphicControl::GetObject(valueThis)->GetGraphicControl();
	return Value(Gura_UnpackUInt16(gctl.DelayTime));
}

// gif.GraphicControl#DisposalMethod
Gura_DeclareProperty_R(GraphicControl, DisposalMethod)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(GraphicControl, DisposalMethod)
{
	const Content::GraphicControlExtension &gctl =
		*Object_GraphicControl::GetObject(valueThis)->GetGraphicControl();
	return Value(Content::DisposalMethodToSymbol(gctl.DisposalMethod()));
}

// gif.GraphicControl#TransparentColorFlag
Gura_DeclareProperty_R(GraphicControl, TransparentColorFlag)
{
	SetPropAttr(VTYPE_boolean);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(GraphicControl, TransparentColorFlag)
{
	const Content::GraphicControlExtension &gctl =
		*Object_GraphicControl::GetObject(valueThis)->GetGraphicControl();
	return Value(gctl.TransparentColorFlag()? true : false);
}

// gif.GraphicControl#TransparentColorIndex
Gura_DeclareProperty_R(GraphicControl, TransparentColorIndex)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(GraphicControl, TransparentColorIndex)
{
	const Content::GraphicControlExtension &gctl =
		*Object_GraphicControl::GetObject(valueThis)->GetGraphicControl();
	return Value(gctl.TransparentColorIndex);
}

// gif.GraphicControl#UserInputFlag
Gura_DeclareProperty_R(GraphicControl, UserInputFlag)
{
	SetPropAttr(VTYPE_boolean);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(GraphicControl, UserInputFlag)
{
	const Content::GraphicControlExtension &gctl =
		*Object_GraphicControl::GetObject(valueThis)->GetGraphicControl();
	return Value(gctl.UserInputFlag()? true : false);
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_GraphicControl
//-----------------------------------------------------------------------------
// implementation of class GraphicControl
Gura_ImplementUserClass(GraphicControl)
{
	// Assignment of properties
	Gura_AssignProperty(GraphicControl, DelayTime);
	Gura_AssignProperty(GraphicControl, DisposalMethod);
	Gura_AssignProperty(GraphicControl, TransparentColorFlag);
	Gura_AssignProperty(GraphicControl, TransparentColorIndex);
	Gura_AssignProperty(GraphicControl, UserInputFlag);
	// Assignment of value
	Gura_AssignValue(GraphicControl, Value(Reference()));
}

//-----------------------------------------------------------------------------
// Object_ImageDescriptor
//-----------------------------------------------------------------------------
Object_ImageDescriptor::~Object_ImageDescriptor()
{
}

Object *Object_ImageDescriptor::Clone() const
{
	return nullptr;
}

String Object_ImageDescriptor::ToString(bool exprFlag)
{
	return String("<gif.ImageDescriptor>");
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.ImageDescriptor#ImageHeight
Gura_DeclareProperty_R(ImageDescriptor, ImageHeight)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, ImageHeight)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(Gura_UnpackUInt16(desc.ImageHeight));
}

// gif.ImageDescriptor#ImageLeftPosition
Gura_DeclareProperty_R(ImageDescriptor, ImageLeftPosition)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, ImageLeftPosition)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(Gura_UnpackUInt16(desc.ImageLeftPosition));
}

// gif.ImageDescriptor#ImageTopPosition
Gura_DeclareProperty_R(ImageDescriptor, ImageTopPosition)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, ImageTopPosition)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(Gura_UnpackUInt16(desc.ImageTopPosition));
}

// gif.ImageDescriptor#ImageWidth
Gura_DeclareProperty_R(ImageDescriptor, ImageWidth)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, ImageWidth)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(Gura_UnpackUInt16(desc.ImageWidth));
}

// gif.ImageDescriptor#InterlaceFlag
Gura_DeclareProperty_R(ImageDescriptor, InterlaceFlag)
{
	SetPropAttr(VTYPE_boolean);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, InterlaceFlag)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(desc.InterlaceFlag()? true : false);
}

// gif.ImageDescriptor#LocalColorTableFlag
Gura_DeclareProperty_R(ImageDescriptor, LocalColorTableFlag)
{
	SetPropAttr(VTYPE_boolean);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, LocalColorTableFlag)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(desc.LocalColorTableFlag()? true : false);
}

// gif.ImageDescriptor#SizeOfLocalColorTable
Gura_DeclareProperty_R(ImageDescriptor, SizeOfLocalColorTable)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, SizeOfLocalColorTable)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(static_cast<UInt>(desc.SizeOfLocalColorTable()));
}

// gif.ImageDescriptor#SortFlag
Gura_DeclareProperty_R(ImageDescriptor, SortFlag)
{
	SetPropAttr(VTYPE_boolean);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(ImageDescriptor, SortFlag)
{
	Content::ImageDescriptor &desc = *Object_ImageDescriptor::GetObject(valueThis)->GetImageDescriptor();
	return Value(desc.SortFlag()? true : false);
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_ImageDescriptor
//-----------------------------------------------------------------------------
// implementation of class ImageDescriptor
Gura_ImplementUserClass(ImageDescriptor)
{
	// Assignment of properties
	Gura_AssignProperty(ImageDescriptor, ImageHeight);
	Gura_AssignProperty(ImageDescriptor, ImageLeftPosition);
	Gura_AssignProperty(ImageDescriptor, ImageTopPosition);
	Gura_AssignProperty(ImageDescriptor, ImageWidth);
	Gura_AssignProperty(ImageDescriptor, InterlaceFlag);
	Gura_AssignProperty(ImageDescriptor, LocalColorTableFlag);
	Gura_AssignProperty(ImageDescriptor, SizeOfLocalColorTable);
	Gura_AssignProperty(ImageDescriptor, SortFlag);
	// Assignment of value
	Gura_AssignValue(ImageDescriptor, Value(Reference()));
}

//-----------------------------------------------------------------------------
// Object_imgprop
//-----------------------------------------------------------------------------
Object_imgprop::~Object_imgprop()
{
}

Object *Object_imgprop::Clone() const
{
	return nullptr;
}

String Object_imgprop::ToString(bool exprFlag)
{
	return String("<gif.imgprop>");
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gif.imgprop#GraphicControl
Gura_DeclareProperty_R(imgprop, GraphicControl)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(imgprop, GraphicControl)
{
	Object_GraphicControl *pObjGraphicControl =
		Object_imgprop::GetObject(valueThis)->GetObjGraphicControl();
	return Value(Object_GraphicControl::Reference(pObjGraphicControl));
}

// gif.imgprop#ImageDescriptor
Gura_DeclareProperty_R(imgprop, ImageDescriptor)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(imgprop, ImageDescriptor)
{
	Object_ImageDescriptor *pObjImageDescriptor =
		Object_imgprop::GetObject(valueThis)->GetObjImageDescriptor();
	return Value(Object_ImageDescriptor::Reference(pObjImageDescriptor));
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_imgprop
//-----------------------------------------------------------------------------
// implementation of class imgprop
Gura_ImplementUserClass(imgprop)
{
	// Assignment of properties
	Gura_AssignProperty(imgprop, GraphicControl);
	Gura_AssignProperty(imgprop, ImageDescriptor);
	// Assignment of value
	Gura_AssignValue(imgprop, Value(Reference()));
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_image
// These methods are available after importing gif module.
//-----------------------------------------------------------------------------
// image#read@gif(stream:stream:r):reduce
Gura_DeclareMethodAlias(image, read_at_gif, "read@gif")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	AddHelp(
		Gura_Symbol(en),
		"Reads a GIF image from a stream.\n"
		"\n"
		"This method returns the reference to the target instance itself.\n");
}

Gura_ImplementMethod(image, read_at_gif)
{
	Signal &sig = env.GetSignal();
	Object_image *pThis = Object_image::GetObjectThis(arg);
	Image *pImage = pThis->GetImage();
	if (!pImage->CheckEmpty(sig)) return Value::Nil;
	Stream &stream = arg.GetStream(0);
	if (!GIF().Read(env, stream, pImage, pImage->GetFormat())) {
		return Value::Nil;
	}
	return arg.GetValueThis();
}

// image#write@gif(stream:stream:w):reduce
Gura_DeclareMethodAlias(image, write_at_gif, "write@gif")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Write);
	AddHelp(
		Gura_Symbol(en),
		"Writes a GIF image to a stream.\n"
		"\n"
		"This method returns the reference to the target instance itself.\n");
}

Gura_ImplementMethod(image, write_at_gif)
{
	Signal &sig = env.GetSignal();
	Object_image *pThis = Object_image::GetObjectThis(arg);
	Image *pImage = pThis->GetImage();
	if (!pImage->CheckValid(sig)) return Value::Nil;
	Stream &stream = arg.GetStream(0);
	GIF gif;
	gif.AddImage(arg.GetValueThis(), 0, 0, 0, 1);
	UInt16 loopCount = 0;
	if (!gif.Write(env, stream, Color::zero, false, loopCount)) {
		return Value::Nil;
	}
	return arg.GetValueThis();
}

//-----------------------------------------------------------------------------
// Gura module functions: content
//-----------------------------------------------------------------------------
// gif.content(stream?:stream:r, format.symbol => `rgba) {block?}
Gura_DeclareFunction(content)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Read);
	DeclareArg(env, "format", VTYPE_symbol, OCCUR_Once,
			   FLAG_None, 0, new Expr_Value(Gura_Symbol(rgba)));
	SetClassToConstruct(Gura_UserClass(content));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), 
		"Reads a GIF data from a stream and returns an object that contains\n"
		"GIF related information and images of a specified format. format is\n"
		"is `rgb, `rgba or `noimage. If `noimage is specified, only the\n"
		"information data is read");
}

Gura_ImplementFunction(content)
{
	Signal &sig = env.GetSignal();
	Object_content *pObjContent = new Object_content();
	if (arg.Is_stream(0)) {
		Stream &stream = arg.GetStream(0);
		const Symbol *pSymbol = arg.GetSymbol(1);
		Image::Format format = Image::FORMAT_None;
		if (!pSymbol->IsIdentical(Gura_UserSymbol(noimage))) {
			format = Image::SymbolToFormat(sig, pSymbol);
			if (sig.IsSignalled()) return Value::Nil;
		}
		if (!pObjContent->GetGIF().Read(env, stream, nullptr, format)) {
			return Value::Nil;
		}
	}
	return ReturnValue(env, arg, Value(pObjContent));
}

//-----------------------------------------------------------------------------
// Module Entries
//-----------------------------------------------------------------------------
Gura_ModuleValidate()
{
	return Version::CheckCoreVersion(GURA_VERSION, nullptr);
}

Gura_ModuleEntry()
{
	// Realization of symbols
	Gura_RealizeUserSymbol(noimage);
	Gura_RealizeUserSymbol(none);
	Gura_RealizeUserSymbol(keep);
	Gura_RealizeUserSymbol(background);
	Gura_RealizeUserSymbol(previous);
	Gura_RealizeUserSymbol(gif);
	// Realization of classes
	Gura_RealizeAndPrepareUserClass(content, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(Header, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(LogicalScreenDescriptor, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(CommentExtension, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(PlainTextExtension, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(ApplicationExtension, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(GraphicControl, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(ImageDescriptor, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(imgprop, env.LookupClass(VTYPE_object));
	// Assignment of methods to image class
	Gura_AssignMethodTo(VTYPE_image, image, read_at_gif);
	Gura_AssignMethodTo(VTYPE_image, image, write_at_gif);
	// function assignment
	Gura_AssignFunction(content);
	// Registration of image streamer
	ImageStreamer::Register(new ImageStreamer_GIF());
	return true;
}

Gura_ModuleTerminate()
{
}

//-----------------------------------------------------------------------------
// ImageStreamer_GIF
//-----------------------------------------------------------------------------
bool ImageStreamer_Content::IsResponsible(Signal &sig, Stream &stream)
{
	if (stream.IsReadable()) {
		char buff[6];
		size_t bytesPeeked = stream.Peek(sig, buff, 6);
		if (sig.IsSignalled()) return false;
		return bytesPeeked == 6 &&
			(::memcmp(buff, "GIF87a", 6) == 0 || ::memcmp(buff, "GIF89a", 6) == 0);
	}
	return stream.HasNameSuffix(".gif");
}

bool ImageStreamer_Content::Read(Environment &env,
										Image *pImage, Stream &stream)
{
	Signal &sig = env.GetSignal();
	if (!pImage->CheckEmpty(sig)) return false;
	return GIF().Read(env, stream, pImage, pImage->GetFormat());
}

bool ImageStreamer_Content::Write(Environment &env,
										Image *pImage, Stream &stream)
{
	Signal &sig = env.GetSignal();
	if (!pImage->CheckValid(sig)) return false;
	GIF gif;
	Value value(new Object_image(env, Image::Reference(pImage)));
	gif.AddImage(value, 0, 0, 0, 1);
	UInt16 loopCount = 0;
	return gif.Write(env, stream, Color::zero, false, loopCount);
}

Gura_EndModuleBody(gif, gif)

Gura_RegisterModule(gif)
