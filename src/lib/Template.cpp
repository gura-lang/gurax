//=============================================================================
// Template
//=============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// Template
//-----------------------------------------------------------------------------
void Template::Bootup()
{
}

Template::Template() :
	_pExprForInit(new Expr_Block()), _pExprForBody(new Expr_Block()),
	_pValueMap(new ValueMap()), _chLast('\0')				  
{
}

bool Template::ParseStream(Stream& streamSrc, bool autoIndentFlag, bool appendLastEOLFlag)
{
	Parser parser(*this, streamSrc.GetName(), autoIndentFlag, appendLastEOLFlag);
	for (;;) {
		char ch = streamSrc.GetChar();
		if (Error::IsIssued()) return false;
		if (!ch) break;
		if (!parser.FeedChar(ch)) return false;
	}
	return parser.Flush();
}

bool Template::ParseString(String::const_iterator strSrc, String::const_iterator strSrcEnd,
						   bool autoIndentFlag, bool appendLastEOLFlag)
{
	Parser parser(*this, "*string*", autoIndentFlag, appendLastEOLFlag);
	for (String::const_iterator p = strSrc; p != strSrcEnd; p++) {
		if (!parser.FeedChar(*p)) return false;
	}
	return parser.Flush();
}

bool Template::ParseString(const char* strSrc, const char* strSrcEnd,
						   bool autoIndentFlag, bool appendLastEOLFlag)
{
	Parser parser(*this, "*string*", autoIndentFlag, appendLastEOLFlag);
	for (const char* p = strSrc; p != strSrcEnd; p++) {
		if (!parser.FeedChar(*p)) return false;
	}
	return parser.Flush();
}

bool Template::ParseString(const char* strSrc, bool autoIndentFlag, bool appendLastEOLFlag)
{
	Parser parser(*this, "*string*", autoIndentFlag, appendLastEOLFlag);
	for (const char* p = strSrc; *p; p++) {
		if (!parser.FeedChar(*p)) return false;
	}
	return parser.Flush();
}

bool Template::PrepareAndCompose()
{
	//****** Need to implement dynamic memory allocator for PUnit ******
	Composer composer;
	if (!PrepareAndCompose(composer)) return false;
	composer.Add_Terminate();
	return !Error::IsIssued();
}

bool Template::PrepareAndCompose(Composer& composer)
{
#if 0
	auto Sub = [](Composer& composer, Expr& expr) {
		expr.Prepare();
		if (Error::IsIssued()) return false;
		expr.SetPUnitFirst(composer.PeekPUnitCont());
		expr.ComposeOrNil(composer);
		composer.Add_Return(expr);
		expr.SetPUnitEnd(composer.PeekPUnitCont());
		return !Error::IsIssued();
	};
	return Sub(composer, GetExprForInit()) && Sub(composer, GetExprForBody());
#endif
	return GetExprForInit().PrepareAndCompose(composer) && GetExprForBody().PrepareAndCompose(composer);
}

bool Template::Render(Processor& processor, Stream& streamDst)
{
	Template* pTmplTop = this;
	for (Template* pTmpl = this; pTmpl; pTmpl = pTmpl->GetTemplateSuper()) {
		Frame& frame = processor.PushFrame<Frame_Scope>();
		frame.Assign(Gurax_Symbol(__tmpl__), new Value_Template(pTmpl->Reference()));
		pTmpl->SetStreamDst(streamDst.Reference());
		pTmpl->GetValueMap().Clear();
		Value::Delete(pTmpl->GetExprForInit().Eval(processor));
		processor.PopFrame();
		if (Error::IsIssued()) break;
		pTmplTop = pTmpl;
	}
	if (!Error::IsIssued()) {
		Frame& frame = processor.PushFrame<Frame_Scope>();
		frame.Assign(Gurax_Symbol(__tmpl__), new Value_Template(Reference()));
		Value::Delete(pTmplTop->GetExprForBody().Eval(processor));
		processor.PopFrame();
	}
	for (Template* pTmpl = this; pTmpl; pTmpl = pTmpl->GetTemplateSuper()) {
		pTmpl->SetStreamDst(nullptr);
	}
	return !Error::IsIssued();
}

bool Template::Render(Processor& processor, String& strDst)
{
	RefPtr<Stream_Binary> pStreamDst(new Stream_Binary(Stream::Flag::Writable));
	if (!Render(processor, *pStreamDst)) return false;
	strDst = pStreamDst->GetBuff().ConvertToString();
	return true;
}

void Template::PutChar(char ch)
{
	if (_pStreamDst) _pStreamDst->PutChar(ch);
	_chLast = ch;
}

void Template::Print(const char* str)
{
	if (_pStreamDst) _pStreamDst->Print(str);
	size_t len = ::strlen(str);
	if (len > 0) _chLast = str[len - 1];
}

bool Template::AssignValue(const Symbol* pSymbol, Value* pValue)
{
	ValueMap& valueMap = GetValueMap();
	if (valueMap.DoesExist(pSymbol)) {
		Error::Issue(ErrorType::KeyError, "duplicated symbol: %s", pSymbol->GetName());
		return false;
	}
	valueMap.Assign(pSymbol, pValue);
	return true;
}

const Value* Template::LookupValue(const Symbol* pSymbol) const
{
	for (const Template* pTmpl = this; pTmpl; pTmpl = pTmpl->GetTemplateSuper()) {
		const ValueMap& valueMap = pTmpl->GetValueMap();
		auto iter = valueMap.GetMap().find(pSymbol);
		if (iter != valueMap.GetMap().end()) return iter->second;
	}
	return nullptr;
}

String Template::ToString(const StringStyle& ss) const
{
	return String().Format("Template");
	//return String().Format("Template:dst=%s", GetStreamDst().ToString(ss).c_str());
}

//-----------------------------------------------------------------------------
// Template::Parser
//-----------------------------------------------------------------------------
Template::Parser::Parser(Template& tmpl, StringReferable* pSourceName, bool autoIndentFlag, bool appendLastEOLFlag) :
	_tmpl(tmpl), _pSourceName(pSourceName), _autoIndentFlag(autoIndentFlag), _appendLastEOLFlag(appendLastEOLFlag),
	_stat(Stat::LineTop), _stringAheadFlag(false), _cntLine(0), _cntLineTop(0), _nDepth(0)
{
}

bool Template::Parser::FeedChar(char ch)
{
	const char chMarker = '$';
	Gurax_BeginPushbackRegion();
	switch (_stat) {
	case Stat::LineTop: {
		if (ch == '\n') {
			_str += ch;
		} else if (String::IsWhite(ch)) {
			Gurax_Pushback();
			_stat = Stat::Indent;
		} else if (ch == chMarker) {
			_stat = Stat::ScriptPre;
		} else {
			_stringAheadFlag = true;
			Gurax_Pushback();
			_stat = Stat::String;
		}
		break;
	}
	case Stat::Indent: {
		if (String::IsWhite(ch)) {
			_strIndent += ch;
		} else if (ch == chMarker) {
			_stat = Stat::ScriptPre;
		} else {
			_str += _strIndent;
			_strIndent.clear();
			_stringAheadFlag = true;
			Gurax_Pushback();
			_stat = Stat::String;
		}
		break;
	}
	case Stat::String: {
		if (ch == chMarker) {
			_stat = Stat::ScriptPre;
		} else if (ch == '\n') {
			_str += ch;
			_stringAheadFlag = false;
			_stat = Stat::LineTop;
		} else {
			_str += ch;
		}
		break;
	}
	case Stat::ScriptPre: {
		if (ch == '{') {
			CreateTmplString();
			_cntLineTop = _cntLine;
			_nDepth = 1;
			_strTmplScript.clear();
			_stat = Stat::ScriptFirst;
		} else {
			_str += _strIndent;
			_strIndent.clear();
			_str += chMarker;
			_stringAheadFlag = true;
			if (ch != '\\') Gurax_Pushback();
			_stat = Stat::String;
		}
		break;
	}
	case Stat::ScriptFirst: {
		if (ch == '=') {
			_stat = Stat::ScriptSecond;
		} else {
			Gurax_Pushback();
			_stat = Stat::Script;
		}
		break;
	}
	case Stat::ScriptSecond: {
		if (ch == '=') {
			_stat = Stat::Comment;
		} else {
			_strTmplScript += '=';
			Gurax_Pushback();
			_stat = Stat::Script;
		}
		break;
	}
	case Stat::Script: {
		if (ch == '{') {
			_strTmplScript += ch;
			_nDepth++;
		} else if (ch == '}') {
			_nDepth--;
			if (_nDepth > 0) {
				_strTmplScript += ch;
				break;
			}
			_stat = Stat::ScriptPost;
		} else {
			_strTmplScript += ch;
		}
		break;
	}
	case Stat::ScriptPost: {
		if (!CreateTmplScript((ch == '\n')? "\n" : "")) return false;
		_strIndent.clear();
		_strTmplScript.clear();
		if (ch == '\n') {
			_stringAheadFlag = false;
			_stat = Stat::LineTop;
		} else {
			_stringAheadFlag = true;
			Gurax_Pushback();
			_stat = Stat::String;
		}
		break;
	}
	case Stat::Comment: {
		if (ch == '=') {
			_stat = Stat::CommentEnd_Second;
		} else if (ch == '\n') {
			_stringAheadFlag = false;
			_stat = Stat::Comment_LineTop;
		} else {
			// nothing to do
		}
		break;
	}
	case Stat::Comment_LineTop: {
		if (ch == '=') {
			_stat = Stat::CommentEnd_Second;
		} else if (ch == '\n') {
			// nothing to do
		} else if (String::IsWhite(ch)) {
			// nothing to do
		} else {
			_stringAheadFlag = true;
			_stat = Stat::Comment;
		}
		break;
	}
	case Stat::CommentEnd_Second: {
		if (ch == '=') {
			_stat = Stat::CommentEnd_SeekR;
		} else if (ch == '\n') {
			_stringAheadFlag = false;
			_stat = Stat::Comment_LineTop;
		} else {
			_stringAheadFlag = true;
			_stat = Stat::Comment;
		}
		break;
	}
	case Stat::CommentEnd_SeekR: {
		if (ch == '}') {
			_stat = Stat::CommentEnd_Marker;
		} else if (ch == '\n') {
			_stringAheadFlag = false;
			_stat = Stat::Comment_LineTop;
		} else {
			_stringAheadFlag = true;
			_stat = Stat::Comment;
		}
		break;
	}
	case Stat::CommentEnd_Marker: {
		if (ch == chMarker) {
			_stat = Stat::CommentPost;
		} else if (ch == '\n') {
			_stringAheadFlag = false;
			_stat = Stat::Comment_LineTop;
		} else {
			_stringAheadFlag = true;
			_stat = Stat::Comment;
		}
		break;
	}
	case Stat::CommentPost: {
		if (!_stringAheadFlag && ch == '\n') {
			_stringAheadFlag = false;
			_stat = Stat::LineTop;
		} else {
			_stringAheadFlag = true;
			Gurax_Pushback();
			_stat = Stat::String;
		}
		break;
	}
	}
	Gurax_EndPushbackRegion();
	if (ch == '\n') _cntLine++;
	return true;
}

bool Template::Parser::Flush()
{
	if (!_strTmplScript.empty()) {
		if (!CreateTmplScript("")) return false;
	}
	if (!_exprLeaderStack.empty()) {
		Error::Issue(ErrorType::SyntaxError, "missing end statement for block expression");
		return false;
	}
	CreateTmplString();
	return true;
}

void Template::Parser::CreateTmplString()
{
	if (_str.empty()) return;
	RefPtr<Expr> pExpr(new Expr_TmplString(_tmpl.Reference(), _str));
	pExpr->SetSourceInfo(_pSourceName->Reference(), _cntLineTop + 1, _cntLine + 1);
	AddExpr(pExpr.release());
	_str.clear();
}

bool Template::Parser::CreateTmplScript(const char* strPost)
{
	RefPtr<Expr_TmplScript> pExprTmplScript(
		new Expr_TmplScript(_tmpl.Reference(), _strIndent, strPost, _autoIndentFlag, _appendLastEOLFlag));
	pExprTmplScript->SetSourceInfo(_pSourceName->Reference(), _cntLineTop + 1, _cntLine + 1);
	const char* pStrTmplScript = _strTmplScript.c_str();
	RefPtr<Expr> pExprLast;
	if (*pStrTmplScript == '=') {
		// Parsing template directive that looks like "${=foo()}".
		pStrTmplScript++;
		do {
			RefPtr<Gurax::Parser> pParser(
				new Gurax::Parser(_pSourceName->Reference(), _tmpl.GetExprForInit().Reference()));
			// Appends "__tmpl__.init_" before the script string while parsing
			// so that it generates an expression "__tmpl__.init_foo()" from the directive "${=foo()}".
			if (!pParser->FeedString("__tmpl__.init_") || !pParser->FeedString(pStrTmplScript) ||
				!pParser->Flush()) return false;
			//if (!_tmpl.GetExprForInit().HasSingleExprElem()) {
			//	Error::Issue(ErrorType::SyntaxError, "template directive must be a single expression");
			//	return false;
			//}
			pExprLast.reset(_tmpl.GetExprForInit().GetExprElemLast()->Reference());
		} while (0);
		do {
			RefPtr<Gurax::Parser> pParser(new Gurax::Parser(_pSourceName->Reference(), pExprTmplScript->Reference()));
			// Appends "__tmpl__." before the script string while parsing
			// so that it generates an expression "__tmpl__.foo()" from the directive "${=foo()}".
			if (!pParser->FeedString("__tmpl__.") || !pParser->FeedString(pStrTmplScript) ||
				!pParser->Flush()) return false;
		} while (0);
		if (pExprTmplScript->HasExprElem()) {
			AddExpr(pExprTmplScript->Reference());
		}
	} else {
		// Parsing a normal script other than template directive.
		RefPtr<Gurax::Parser> pParser(new Gurax::Parser(_pSourceName->Reference(), pExprTmplScript->Reference()));
		if (!pParser->FeedString(pStrTmplScript) || !pParser->Flush()) return false;
		Expr* pExprFirst = pExprTmplScript->GetExprElemFirst();
		if (!pExprFirst) {
			// nothing to do
		} else {
			RefPtr<DeclCallable> pDeclCallable(pExprFirst->RetrieveDeclCallable());
			if (!pDeclCallable) {
				// nothing to do
			} else if (pDeclCallable->IsSet(DeclCallable::Flag::EndMarker)) {
				if (_exprLeaderStack.empty()) {
					Error::Issue(ErrorType::SyntaxError, "unmatching end expression");
					return false;
				}
				_exprLeaderStack.pop_back();
				pExprTmplScript->GetExprLinkElem().RemoveExprFirst();
			} else if (pDeclCallable->IsSet(DeclCallable::Flag::Trailer)) {
				if (_exprLeaderStack.empty()) {
					Error::Issue(ErrorType::SyntaxError, "unmatching trailer expression");
					return false;
				}
				if (pExprFirst->IsType<Expr_Caller>()) {
					pExprLast.reset(pExprFirst->Reference());
					_exprLeaderStack.back()->GetExprTrailerLast().
						SetExprTrailer(dynamic_cast<Expr_Caller*>(pExprFirst)->Reference());
					_exprLeaderStack.pop_back();
					pExprTmplScript->GetExprLinkElem().RemoveExprFirst();
				} else if (pExprFirst->IsType<Expr_Identifier>()) {
					RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
					pExprCaller->SetExprCar(pExprFirst->Reference());
					pExprLast.reset(pExprCaller.Reference());
					_exprLeaderStack.back()->GetExprTrailerLast().
						SetExprTrailer(pExprCaller.release());
					_exprLeaderStack.pop_back();
					pExprTmplScript->GetExprLinkElem().RemoveExprFirst();
				}
			}
		}
		if (pExprTmplScript->HasExprElem()) {
			AddExpr(pExprTmplScript->Reference());
			pExprLast.reset(pExprTmplScript->GetExprElemLast()->Reference());
		}
	}
	if (pExprLast && pExprLast->IsType<Expr_Caller>()) {
		Expr_Caller& exprLastCaller = dynamic_cast<Expr_Caller&>(*pExprLast).GetExprTrailerLast();
		if (exprLastCaller.HasEmptyExprOfBlock()) {
			_exprLeaderStack.push_back(&exprLastCaller);
			pExprTmplScript->SetStringIndent("");
			pExprTmplScript->SetStringPost("");
		} else if (!exprLastCaller.HasExprOfBlock()) {
			RefPtr<DeclCallable> pDeclCallable(exprLastCaller.RetrieveDeclCallable());
			if (pDeclCallable && pDeclCallable->GetDeclBlock().IsOccurOnce()) {
				exprLastCaller.SetExprOfBlock(new Expr_Block());
				_exprLeaderStack.push_back(&exprLastCaller);
				pExprTmplScript->SetStringIndent("");
				pExprTmplScript->SetStringPost("");
			}
		}
	}
	return true;
}

void Template::Parser::AddExpr(Expr* pExpr)
{
	(_exprLeaderStack.empty()? _tmpl.GetExprForBody() : *_exprLeaderStack.back()->GetExprOfBlock()).
		AddExprElem(pExpr);
}

//-----------------------------------------------------------------------------
// Expr_TmplString
//-----------------------------------------------------------------------------
const Expr::TypeInfo Expr_TmplString::typeInfo(TypeId::TmplString, "TmplString");

void Expr_TmplString::Compose(Composer& composer)
{
	composer.Add_TmplString(GetTemplate().Reference(), GetStringSTL(), *this);
}

String Expr_TmplString::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	str.Format("%sT", GetStringSTL().EnquoteAuto().c_str());
	return str;
}

//-----------------------------------------------------------------------------
// Expr_TmplScript
//-----------------------------------------------------------------------------
const Expr::TypeInfo Expr_TmplScript::typeInfo(TypeId::TmplScript, "TmplScript");

void Expr_TmplScript::Compose(Composer& composer)
{
	ComposeSequence(composer, GetExprElemFirst());								// [Any]
	composer.Add_TmplScript(Reference(), *this);
}

String Expr_TmplScript::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	str += "$";
	if (ss.IsMultiLine()) {
		String indent = ss.MakeIndent(indentLevel);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		str += indent;
		str += "{\n";
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			str += indentDown;
			str += pExpr->ToString(ss);
			str += '\n';
		}
		str += indent;
		str += "}\n";
	} else {
		str += '{';
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss);
		}
		str += '}';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Template : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Template::typeInfo(TypeId::Template, "Template");

void Expr_Template::Compose(Composer& composer)
{
	bool autoIndentFlag = true;
	bool appendLastEOLFlag = false;
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_Jump(*this);
	RefPtr<Template> pTmpl(new Template());
	if (!pTmpl->ParseString(GetString(), autoIndentFlag, appendLastEOLFlag) ||
		!pTmpl->PrepareAndCompose(composer)) return;
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	if (_embedFlag) {
		composer.Add_TmplEmbedded(pTmpl.release(), *this);
	} else {
		composer.Add_Value(new Value_Template(pTmpl.release()), *this);
	}
}

String Expr_Template::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	str += _embedFlag? 'e' : 't';
	str += GetStringSTL().EnquoteAuto();
	return str;
}

//------------------------------------------------------------------------------
// PUnit_TmplString
// Stack View: [] -> [nil] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_TmplString<discardValueFlag>::Exec(Processor& processor) const
{
	GetTemplate().Print(GetString());
	if (!discardValueFlag) processor.PushValue(Value::nil());
	processor.SetPUnitCur(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_TmplString<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("TmplString()");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_TmplString::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_TmplString<true>(_pTmpl.release(), std::move(_str), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_TmplString<false>(_pTmpl.release(), std::move(_str), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_TmplScript
// Stack View: [Any] -> [nil] (continue)
//                   -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_TmplScript<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	String strLast;
	if (!pValue->IsValid()) {
		// nothing to do
	} else if (pValue->IsType(VTYPE_String)) {
		GetTemplate().Print(GetStringIndent());
		PrintScriptResult(dynamic_cast<Value_String&>(*pValue).GetString());
	} else if (pValue->IsType(VTYPE_List) || pValue->IsType(VTYPE_Iterator)) {
		RefPtr<Iterator> pIterator(pValue->GenIterator());
		bool firstFlag = true;
		for (;;) {
			RefPtr<Value> pValue(pIterator->NextValue());
			if (!pValue) {
				if (Error::IsIssued()) {
					processor.ErrorDone();
					return;
				}
				break;
			}
			if (firstFlag) {
				firstFlag = false;
				GetTemplate().Print(GetStringIndent());
			}
			for (auto p = strLast.c_str(); *p; p++) {
				char ch = *p;
				if (ch == '\n') {
					GetTemplate().PutChar(ch);
					if (GetAutoIndentFlag() && pValue->IsValid()) {
						GetTemplate().Print(GetStringIndent());
					}
				} else {
					GetTemplate().PutChar(ch);
				}
			}
			if (pValue->IsType(VTYPE_String)) {
				strLast = dynamic_cast<Value_String&>(*pValue).GetStringSTL();
			} else if (!pValue->IsValid()) {
				strLast.clear();
			} else if (pValue->IsType(VTYPE_Number)) {
				strLast = pValue->ToString();
				if (Error::IsIssued()) {
					processor.ErrorDone();
					return;
				}
			} else if (pValue->IsType(VTYPE_Symbol)) {
				strLast = dynamic_cast<Value_Symbol&>(*pValue).GetSymbol()->GetName();
			} else if (pValue->IsType(VTYPE_Expr)) {
				strLast = dynamic_cast<Value_Expr&>(*pValue).GetExpr().ToString();
			} else {
				Error::Issue(ErrorType::TypeError, "template script must return nil, String, Symbol or Number");
				processor.ErrorDone();
				return;
			}
		}
		if (!firstFlag) PrintScriptResult(strLast.c_str());
	} else if (pValue->IsType(VTYPE_Number)) {
		GetTemplate().Print(GetStringIndent());
		PrintScriptResult(pValue->ToString().c_str());
	} else if (pValue->IsType(VTYPE_Symbol)) {
		GetTemplate().Print(GetStringIndent());
		PrintScriptResult(dynamic_cast<Value_Symbol&>(*pValue).GetSymbol()->GetName());
	} else if (pValue->IsType(VTYPE_Expr)) {
		GetTemplate().Print(GetStringIndent());
		PrintScriptResult(dynamic_cast<Value_Expr&>(*pValue).GetExpr().ToString().c_str());
	} else {
		Error::Issue(ErrorType::TypeError, "template script must return nil, String, Symbol or number");
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(Value::nil());
	processor.SetPUnitCur(_GetPUnitCont());
}

template<bool discardValueFlag>
void PUnit_TmplScript<discardValueFlag>::PrintScriptResult(const char* str) const
{
	for (auto p = str; *p; p++) {
		char ch = *p;
		if (ch != '\n') {
			GetTemplate().PutChar(ch);
		} else if (*(p + 1)) {
			GetTemplate().PutChar(ch);
			if (GetAutoIndentFlag()) {
				GetTemplate().Print(GetStringIndent());
			}
		} else if (GetAppendLastEOLFlag()) {
			GetTemplate().PutChar(ch);
		}
	}
	GetTemplate().Print(GetStringPost());
}

template<bool discardValueFlag>
String PUnit_TmplScript<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("TmplScript()");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_TmplScript::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_TmplScript<true>(_pExprTmplScript.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_TmplScript<false>(_pExprTmplScript.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_TmplEmbedded
// Stack View: [] -> [Value] (continue)
//                -> []      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_TmplEmbedded<discardValueFlag>::Exec(Processor& processor) const
{
	String strDst;
	if (!GetTemplate().Render(processor, strDst)) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(new Value_String(strDst));
	processor.SetPUnitCur(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_TmplEmbedded<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("TmplEmbedded()");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_TmplEmbedded::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_TmplEmbedded<true>(_pTmpl.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_TmplEmbedded<false>(_pTmpl.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

}
