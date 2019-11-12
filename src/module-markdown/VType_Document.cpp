//==============================================================================
// VType_Document.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// markdown.Document(stream?:Stream:r) {block?}
Gurax_DeclareFunction(Document)
{
	Declare(VTYPE_Document, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns an instance of `markdown.document`.\n"
		"If `stream` is specified, the content of the instance shall be initialized\n"
		"with the result of parsing the stream.\n");
}

Gurax_ImplementFunction(Document)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Document> pDocument(new Document());
	return argument.ReturnValue(processor, new Value_Document(pDocument.release()));
}

#if 0
// markdown.document(stream?:stream:r) {block?}
Gurax_DeclareFunction(document)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Read);
	SetClassToConstruct(Gurax_UserClass(document));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns an instance of `markdown.document`.\n"
		"If `stream` is specified, the content of the instance shall be initialized\n"
		"with the result of parsing the stream.\n"
	);
}

Gurax_ImplementFunction(document)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Document> pDocument(new Document());
	if (arg.Is_stream(0)) {
		if (!pDocument->ParseStream(sig, arg.GetStream(0))) return Value::Nil;
	}
	AutoPtr<Object_document> pObj(new Object_document(pDocument.release()));
	return ReturnValue(env, arg, Value(pObj.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// markdown.Document#MethodSkeleton(num1:Number, num2:Number):reduce
Gurax_DeclareMethod(Document, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Document, MethodSkeleton)
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

// markdown.document#countitem(type:symbol)
Gurax_DeclareMethod(document, countitem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "type", VTYPE_symbol);
	AddHelp(
		Gurax_Symbol(en),
		"Count the number of items of the specified type.");
}

Gurax_ImplementMethod(document, countitem)
{
	Document *pDocument = Object_document::GetObjectThis(arg)->GetDocument();
	const Symbol *pSymbol = arg.GetSymbol(0);
	Item::Type type = Item::NameToType(pSymbol->GetName());
	if (type == Item::TYPE_None) {
		env.SetError(ERR_ValueError, "invalid symbol for item type: `%s", pSymbol->GetName());
		return Value::Nil;
	}
	size_t cnt = Item::CountByType(*pDocument->GetItemRoot()->GetItemOwner(), type, true);
	return Value(cnt);
}

// markdown.document#parse(str:string):void
Gurax_DeclareMethod(document, parse)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "str", VTYPE_string);
	AddHelp(
		Gurax_Symbol(en),
		"Parses a Markdown text in a string.");
}

Gurax_ImplementMethod(document, parse)
{
	Signal &sig = env.GetSignal();
	Document *pDocument = Object_document::GetObjectThis(arg)->GetDocument();
	pDocument->ParseString(sig, arg.GetString(0));
	return Value::Nil;
}

// markdown.document#read(stream:stream:r):void
Gurax_DeclareMethod(document, read)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	AddHelp(
		Gurax_Symbol(en),
		"Parses a Markdown text from a stream.");
}

Gurax_ImplementMethod(document, read)
{
	Signal &sig = env.GetSignal();
	Document *pDocument = Object_document::GetObjectThis(arg)->GetDocument();
	pDocument->ParseStream(sig, arg.GetStream(0));
	return Value::Nil;
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// markdown.document#refs
Gurax_DeclareProperty_R(document, refs)
{
	SetPropAttr(VTYPE_iterator);
	AddHelp(
		Gurax_Symbol(en),
		"An `iterator` that returns referee items as `markdown.item`.");
}

Gurax_ImplementPropertyGetter(document, refs)
{
	Document *pDocument = Object_document::GetObject(valueThis)->GetDocument();
	const ItemOwner *pItemOwner = pDocument->GetItemRefereeOwner();
	Iterator *pIterator = new Iterator_item(pItemOwner->Reference());
	return Value(new Object_iterator(env, pIterator));
}

// markdown.document#root
Gurax_DeclareProperty_R(document, root)
{
	SetPropAttr(VTYPE_item);
	AddHelp(
		Gurax_Symbol(en),
		"The root item of the parsed Markdown document.");
}

Gurax_ImplementPropertyGetter(document, root)
{
	Document *pDocument = Object_document::GetObject(valueThis)->GetDocument();
	pDocument->ResolveReference();
	return Value(new Object_item(pDocument->GetItemRoot()->Reference()));
}

// markdown.Document#propSkeleton
Gurax_DeclareProperty_R(Document, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Document, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// Implementation of operators
//------------------------------------------------------------------------------
// operator <<
Gurax_ImplementBinaryOperator(Shl, document, string)
{
	Signal &sig = env.GetSignal();
	Document *pDocument = Object_document::GetObject(valueLeft)->GetDocument();
	const char *text = valueRight.GetString();
	if (!pDocument->ParseString(sig, text)) return Value::Nil;
	return valueLeft;
}
#endif

//------------------------------------------------------------------------------
// VType_Document
//------------------------------------------------------------------------------
VType_Document VTYPE_Document("Document");

void VType_Document::DoPrepare(Frame& frameOuter)
{
#if 0
	// Assignment of property
	Gurax_AssignProperty(document, refs);
	Gurax_AssignProperty(document, root);
	// Assignment of function
	Gurax_AssignFunction(document);
	// Assignment of method
	Gurax_AssignMethod(document, countitem);
	Gurax_AssignMethod(document, parse);
	Gurax_AssignMethod(document, read);
#endif
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateFunction(Document));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Document, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Document, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Document
//------------------------------------------------------------------------------
VType& Value_Document::vtype = VTYPE_Document;

#if 0
Object *Object_document::Clone() const
{
	return nullptr;
}

#if 0
bool Object_document::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = GetSignal();
	if (!Object::DoDirProp(env, symbols)) return false;
	symbols.insert(Gurax_Symbol(refs));
	symbols.insert(Gurax_Symbol(root));
	return true;
}

Value Object_document::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gurax_Symbol(refs))) {
		const ItemOwner *pItemOwner = _pDocument->GetItemRefereeOwner();
		Iterator *pIterator = new Iterator_item(pItemOwner->Reference());
		return Value(new Object_iterator(env, pIterator));
	} else if (pSymbol->IsIdentical(Gurax_Symbol(root))) {
		_pDocument->ResolveReference();
		return Value(new Object_item(_pDocument->GetItemRoot()->Reference()));
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value Object_document::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}
#endif

String Object_document::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<markdown.document";
	rtn += ">";
	return rtn;
}
#endif

Gurax_EndModuleScope(markdown)
