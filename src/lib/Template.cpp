//=============================================================================
// Template
//=============================================================================
#include "stdafx.h"
#include "../../include/gurax/Template.h"

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
		int chRaw = streamSrc.GetChar();
		if (Error::IsIssued()) return false;
		if (chRaw < 0) break;
		if (!parser.FeedChar(static_cast<char>(chRaw))) return false;
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

bool Template::Render(Stream& streamDst)
{
	//Expr_Block& exprForBody = GetExprForBody();
	return false;
}

bool Template::Render(String& strDst)
{
	return false;
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
			Gurax_Pushback();
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
	return _tmpl.GetExprForBody().Prepare();
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
	if (*pStrTmplScript == '=') {
		// Parsing template directive that looks like "${=foo()}".
		pStrTmplScript++;
		do {
			RefPtr<Gurax::Parser> pParser(new Gurax::Parser(_pSourceName->Reference(), _tmpl.GetExprForInit().Reference()));
			// Appends "this.init_" before the script string while parsing
			// so that it generates an expression "this.init_foo()" from the directive "${=foo()}".
			if (!pParser->FeedString("this.init_") || !pParser->FeedString(pStrTmplScript) ||
				!pParser->Flush()) return false;
		} while (0);
		do {
			RefPtr<Gurax::Parser> pParser(new Gurax::Parser(_pSourceName->Reference(), pExprTmplScript->Reference()));
			// Appends "this." before the script string while parsing
			// so that it generates an expression "this.foo()" from the directive "${=foo()}".
			if (!pParser->FeedString("this.") || !pParser->FeedString(pStrTmplScript) ||
				!pParser->Flush()) return false;
		} while (0);
		Expr_Block& exprOfBlock = _exprLeaderStack.empty()?
			_tmpl.GetExprForBody() : *_exprLeaderStack.back();
		exprOfBlock.AddExprElem(pExprTmplScript->Reference());
		Expr* pExprLast = pExprTmplScript->GetExprElemLast();
		if (!pExprLast->IsType<Expr_Caller>()) return true;
		Expr_Caller* pExprLastCaller = dynamic_cast<Expr_Caller*>(pExprLast);
		if (!pExprLastCaller->GetExprOfBlock()) {
			Value* pValue = nullptr;
			if (pExprLastCaller->GetExprCar().IsType<Expr_Member>()) {
				Expr_Member& exprCar = dynamic_cast<Expr_Member&>(pExprLastCaller->GetExprCar());
				if (exprCar.GetExprTarget().IsType<Expr_Identifier>() &&
					dynamic_cast<const Expr_Identifier&>(exprCar.GetExprTarget()).GetSymbol()->
					IsIdentical(Gurax_Symbol(this_))) {
					exprCar.GetSymbol();
					//pValue = VTYPE_Template.GetFrame().Lookup(exprCar.GetSymbol());
				}
			} else if (pExprLastCaller->GetExprCar().IsType<Expr_Identifier>()) {
				Expr_Identifier& exprCar = dynamic_cast<Expr_Identifier&>(pExprLastCaller->GetExprCar());
				pValue = Basement::Inst.GetFrame().Lookup(exprCar.GetSymbol());
			}
			const DeclCallable* pDeclCallable;
			if (pValue && (pDeclCallable = pValue->GetDeclCallable()) &&
				pDeclCallable->GetDeclBlock().IsOccurOnce()) {
				Expr_Block* pExprOfBlock = new Expr_Block();
				pExprLastCaller->SetExprOfBlock(pExprOfBlock);
				_exprLeaderStack.push_back(pExprOfBlock);
			}
		} else if (!pExprLastCaller->GetExprOfBlock()->HasExprElem()) {
			_exprLeaderStack.push_back(pExprLastCaller->GetExprOfBlock());
		}
	} else {
		// Parsing a normal script other than template directive.
		RefPtr<Gurax::Parser> pParser(new Gurax::Parser(_pSourceName->Reference(), pExprTmplScript->Reference()));
		if (!pParser->FeedString(pStrTmplScript) || !pParser->Flush()) return false;
		Expr* pExprFirst = pExprTmplScript->GetExprElemFirst();
		if (pExprFirst && pExprFirst->IsType<Expr_Caller>()) {
			// check if the first Expr is a trailer
			Expr_Caller* pExprFirstCaller = dynamic_cast<Expr_Caller*>(pExprFirst);
			Value* pValue = nullptr;
			if (pExprFirstCaller->GetExprCar().IsType<Expr_Identifier>()) {
				Expr_Identifier& exprCar = dynamic_cast<Expr_Identifier&>(pExprFirstCaller->GetExprCar());
				pValue = Basement::Inst.GetFrame().Lookup(exprCar.GetSymbol());
			}
			const DeclCallable* pDeclCallable;
			if (pValue && (pDeclCallable = pValue->GetDeclCallable()) &&
				pDeclCallable->IsSet(DeclCallable::Flag::Trailer)) {
				pExprTmplScript->SetStringIndent("");
				if (_exprLeaderStack.empty()) {
					Error::IssueWith(ErrorType::SyntaxError, *pExprTmplScript, "unmatching trailer expression");
					return false;
				}
				if (!pDeclCallable->IsSet(DeclCallable::Flag::EndMarker)) {
					
				}
			}
#if 0
			if (pCallable != nullptr && pCallable->IsTrailer()) {
				if (!pCallable->IsEndMarker()) {
					Expr_Caller *pExprCaller = nullptr;
					if (pExpr->IsCaller()) {
						pExprCaller = dynamic_cast<Expr_Caller *>(Expr::Reference(pExpr));
					} else {
						pExprCaller = new Expr_Caller(
							Expr::Reference(pExpr), nullptr, nullptr, FLAG_None);
						pExprCaller->SetSourceInfo(_pSourceName->Reference(),
										pExpr->GetLineNoTop(), pExpr->GetLineNoBtm());
					}
					_exprLeaderStack.back()->SetTrailer(pExprCaller);
					pExprLast = pExprCaller;
				}
				_exprLeaderStack.pop_back();
				ppExpr++;
			}
#endif
		}
		if (!pExprTmplScript->HasExprElem()) return true;
		AddExpr(pExprTmplScript->Reference());
		//Expr* pExprLast = pExprTmplScript->GetExprElemLast();
#if 0
		if (pExprLast == nullptr) return true;
		if (!pExprLast->IsCaller()) return true;
		Expr_Caller *pExprLastCaller = dynamic_cast<Expr_Caller *>(pExprLast);
		if (pExprLastCaller->GetBlock() == nullptr) {
			Callable *pCallable = nullptr;
			if (pExprLastCaller->GetCar()->IsMember()) {
				Expr_Member *pExprCar = dynamic_cast<Expr_Member *>(pExprLastCaller->GetCar());
				if (pExprCar->GetTarget()->IsIdentifier() &&
						dynamic_cast<const Expr_Identifier *>(pExprCar->GetTarget())->GetSymbol()->
														IsIdentical(Gurax_Symbol(this_))) {
					pCallable = pExprCar->GetSelector()->LookupCallable(*pClass);
				}
			} else {
				pCallable = pExprLastCaller->LookupCallable(env);
			}
			env.ClearSignal();
			if (pCallable != nullptr && pCallable->GetBlockOccurPattern() == OCCUR_Once) {
				Expr_Block *pExprBlock = new Expr_Block();
				pExprLastCaller->SetBlock(pExprBlock);
				_exprLeaderStack.push_back(pExprLastCaller);
				pExprTmplScript->SetStringIndent("");
				pExprTmplScript->SetStringPost("");
			}
		} else if (pExprLastCaller->GetBlock()->GetExprOwner().empty()) {
			_exprLeaderStack.push_back(pExprLastCaller);
			pExprTmplScript->SetStringIndent("");
			pExprTmplScript->SetStringPost("");
		}
#endif
	}
	return true;
}

#if 0
bool Template::Parser::CreateTmplScript(
	const char *strIndent, const char *strTmplScript, const char *strPost,
	Template *pTemplate, Expr_Block *pExprBlockRoot,
	StringShared *pSourceName, int cntLineTop, int cntLineBtm)
{
	Class *pClass = env.LookupClass(VTYPE_template);
	Expr *pExprLast = nullptr;
	AutoPtr<Expr_TmplScript> pExprTmplScript(new Expr_TmplScript(
			pTemplate, strIndent, strPost, _autoIndentFlag, _appendLastEOLFlag));
	pExprTmplScript->SetSourceInfo(pSourceName->Reference(), cntLineTop + 1, cntLineBtm + 1);
	if (*strTmplScript == '=') {
		// Parsing template directive that looks like "${=foo()}".
		strTmplScript++;
		AutoPtr<ExprOwner> pExprOwnerForInit(new ExprOwner());
		do {
			Gura::Parser parser(env, pSourceName->GetString(), cntLineTop, false);
			// Appends "this.init_" before the script string while parsing
			// so that it generates an expression "this.init_foo()" from the directive "${=foo()}".
			if (!parser.ParseString(env, *pExprOwnerForInit, "this.init_", false)) return false;
			if (!parser.ParseString(env, *pExprOwnerForInit, strTmplScript, true)) return false;
		} while (0);
		do {
			ExprOwner &exprOwner = pExprTmplScript->GetExprOwner();
			Gura::Parser parser(env, pSourceName->GetString(), cntLineTop, false);
			// Appends "this." before the script string while parsing
			// so that it generates an expression "this.foo()" from the directive "${=foo()}".
			if (!parser.ParseString(env, exprOwner, "this.", false)) return false;
			if (!parser.ParseString(env, exprOwner, strTmplScript, true)) return false;
		} while (0);
		do {
			ExprOwner &exprOwnerForPresent = _exprLeaderStack.empty()?
				pExprBlockRoot->GetExprOwner() :
				_exprLeaderStack.back()->GetBlock()->GetExprOwner();
			exprOwnerForPresent.push_back(Expr::Reference(pExprTmplScript.get()));
		} while (0);
		do {
			ExprOwner &exprOwnerForInit = pTemplate->GetExprOwnerForInit();
			foreach (ExprOwner, ppExpr, *pExprOwnerForInit) {
				Expr *pExpr = *ppExpr;
				exprOwnerForInit.push_back(Expr::Reference(pExpr));
				pExprLast = pExpr;
			}
		} while (0);
		if (!pExprLast->IsCaller()) return true;
		Expr_Caller *pExprLastCaller = dynamic_cast<Expr_Caller *>(pExprLast);
		if (pExprLastCaller->GetBlock() == nullptr) {
			Callable *pCallable = nullptr;
			if (pExprLastCaller->GetCar()->IsMember()) {
				Expr_Member *pExprCar = dynamic_cast<Expr_Member *>(pExprLastCaller->GetCar());
				if (pExprCar->GetTarget()->IsIdentifier() &&
					dynamic_cast<const Expr_Identifier *>(pExprCar->GetTarget())->
									GetSymbol()->IsIdentical(Gurax_Symbol(this_))) {
					pCallable = pExprCar->GetSelector()->LookupCallable(*pClass);
				}
			} else {
				pCallable = pExprLastCaller->LookupCallable(env);
			}
			env.ClearSignal();
			if (pCallable != nullptr && pCallable->GetBlockOccurPattern() == OCCUR_Once) {
				Expr_Block *pExprBlock = new Expr_Block();
				pExprLastCaller->SetBlock(pExprBlock);
				_exprLeaderStack.push_back(pExprLastCaller);
			}
		} else if (pExprLastCaller->GetBlock()->GetExprOwner().empty()) {
			_exprLeaderStack.push_back(pExprLastCaller);
		}
	} else {
		// Parsing a normal script other than template directive.
		AutoPtr<ExprOwner> pExprOwnerPart(new ExprOwner());
		Gura::Parser parser(env, pSourceName->GetString(), cntLineTop, false);
		if (!parser.ParseString(env, *pExprOwnerPart, strTmplScript, true)) return false;
		ExprOwner::iterator ppExpr = pExprOwnerPart->begin();
		//::printf("[%s], [%s], [%s]\n", strIndent, strTmplScript, strPost);
		if (ppExpr != pExprOwnerPart->end()) {
			// check if the first Expr is a trailer
			Expr *pExpr = *ppExpr;
			Callable *pCallable = pExpr->LookupCallable(env);
			env.ClearSignal();
			if (pCallable != nullptr && pCallable->IsTrailer()) {
				pExprTmplScript->SetStringIndent("");
				if (_exprLeaderStack.empty()) {
					env.SetError(ERR_SyntaxError, "unmatching trailer expression");
					env.GetSignal().AddExprCause(pExprTmplScript.get());
					return false;
				}
				if (!pCallable->IsEndMarker()) {
					Expr_Caller *pExprCaller = nullptr;
					if (pExpr->IsCaller()) {
						pExprCaller = dynamic_cast<Expr_Caller *>(Expr::Reference(pExpr));
					} else {
						pExprCaller = new Expr_Caller(
							Expr::Reference(pExpr), nullptr, nullptr, FLAG_None);
						pExprCaller->SetSourceInfo(pSourceName->Reference(),
										pExpr->GetLineNoTop(), pExpr->GetLineNoBtm());
					}
					_exprLeaderStack.back()->SetTrailer(pExprCaller);
					pExprLast = pExprCaller;
				}
				_exprLeaderStack.pop_back();
				ppExpr++;
			}
		}
		if (ppExpr != pExprOwnerPart->end()) {
			for ( ; ppExpr != pExprOwnerPart->end(); ppExpr++) {
				Expr *pExpr = *ppExpr;
				pExprTmplScript->GetExprOwner().push_back(Expr::Reference(pExpr));
				pExprLast = pExpr;
			}
			ExprOwner &exprOwnerForPresent = _exprLeaderStack.empty()?
					pExprBlockRoot->GetExprOwner() :
					_exprLeaderStack.back()->GetBlock()->GetExprOwner();
			exprOwnerForPresent.push_back(Expr::Reference(pExprTmplScript.get()));
		}
		if (pExprLast == nullptr) return true;
		if (!pExprLast->IsCaller()) return true;
		Expr_Caller *pExprLastCaller = dynamic_cast<Expr_Caller *>(pExprLast);
		if (pExprLastCaller->GetBlock() == nullptr) {
			Callable *pCallable = nullptr;
			if (pExprLastCaller->GetCar()->IsMember()) {
				Expr_Member *pExprCar = dynamic_cast<Expr_Member *>(pExprLastCaller->GetCar());
				if (pExprCar->GetTarget()->IsIdentifier() &&
						dynamic_cast<const Expr_Identifier *>(pExprCar->GetTarget())->GetSymbol()->
														IsIdentical(Gurax_Symbol(this_))) {
					pCallable = pExprCar->GetSelector()->LookupCallable(*pClass);
				}
			} else {
				pCallable = pExprLastCaller->LookupCallable(env);
			}
			env.ClearSignal();
			if (pCallable != nullptr && pCallable->GetBlockOccurPattern() == OCCUR_Once) {
				Expr_Block *pExprBlock = new Expr_Block();
				pExprLastCaller->SetBlock(pExprBlock);
				_exprLeaderStack.push_back(pExprLastCaller);
				pExprTmplScript->SetStringIndent("");
				pExprTmplScript->SetStringPost("");
			}
		} else if (pExprLastCaller->GetBlock()->GetExprOwner().empty()) {
			_exprLeaderStack.push_back(pExprLastCaller);
			pExprTmplScript->SetStringIndent("");
			pExprTmplScript->SetStringPost("");
		}
	}
	return true;
}
#endif

//-----------------------------------------------------------------------------
// Expr_TmplString
//-----------------------------------------------------------------------------
const Expr::TypeInfo Expr_TmplString::typeInfo;

void Expr_TmplString::Compose(Composer& composer)
{
	composer.SetFactory(new PUnitFactory_TmplString(GetTemplate().Reference(), GetStringSTL(), Reference()));
}

String Expr_TmplString::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%sT", GetStringSTL().MakeQuoted(true).c_str());
	return str;
}

//-----------------------------------------------------------------------------
// Expr_TmplScript
//-----------------------------------------------------------------------------
const Expr::TypeInfo Expr_TmplScript::typeInfo;

void Expr_TmplScript::Compose(Composer& composer)
{
	ComposeSequence(composer, GetExprElemFirst());						// [Any]
	composer.SetFactory(new PUnitFactory_TmplScript(GetTemplate().Reference(), Reference()));
}

String Expr_TmplScript::ToString(const StringStyle& ss) const
{
	String str;
	str += "$";
	if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
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

#if 0
bool Template::Render(Environment &env, SimpleStream *pStreamDst)
{
	Template *pTemplateTop = nullptr;
	for (Template *pTemplate = this; pTemplate != nullptr;
							pTemplate = pTemplate->GetTemplateSuper()) {
		if (!pTemplate->Prepare(env)) return false;
		pTemplate->SetStreamDst(pStreamDst);
		pTemplateTop = pTemplate;
	}
	if (pTemplateTop->GetFuncForBody() == nullptr) return true;
	AutoPtr<Argument> pArg(new Argument(pTemplateTop->GetFuncForBody()));
	pArg->SetValueThis(Value(new Object_template(env, Reference())));
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_local));
	pTemplateTop->GetFuncForBody()->Eval(*pEnvBlock, *pArg);
	for (Template *pTemplate = this; pTemplate != nullptr;
							pTemplate = pTemplate->GetTemplateSuper()) {
		pTemplate->SetStreamDst(nullptr);
	}
	return !env.IsSignalled();
}

bool Template::Render(Environment &env, String &strDst)
{
	SimpleStream_StringWriter streamDst(strDst);
	return Render(env, &streamDst);
}

bool Template::Prepare(Environment &env)
{
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_local));
	pEnvBlock->AssignValue(Gurax_Symbol(this_),
				Value(new Object_template(env, Reference())), EXTRA_Public);
	_pValueExMap->clear();
	_pExprOwnerForInit->Exec(*pEnvBlock);
	return !env.IsSignalled();
}

const ValueEx *Template::LookupValue(const Symbol *pSymbol) const
{
	for (const Template *pTemplate = this; pTemplate != nullptr;
							pTemplate = pTemplate->GetTemplateSuper()) {
		const ValueExMap &valueExMap = pTemplate->GetValueExMap();
		ValueExMap::const_iterator iter = valueExMap.find(pSymbol);
		if (iter != valueExMap.end()) return &iter->second;
	}
	return nullptr;
}

#endif

//------------------------------------------------------------------------------
// PUnit_TmplString
// Stack View: [] -> []
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_TmplString<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	GetTemplate().Print(GetString());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_TmplString<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("TmplString()");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_TmplString::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_TmplString<1, true>(_pTmpl.release(), std::move(_str), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_TmplString<1, false>(_pTmpl.release(), std::move(_str), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_TmplString<0, true>(_pTmpl.release(), std::move(_str));
		} else {
			_pPUnitCreated = new PUnit_TmplString<0, false>(_pTmpl.release(), std::move(_str));
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_TmplScript
// Stack View: [Any] -> []
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_TmplScript<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
#if 0
	if (!discardValueFlag) processor.PushValue(GetValue()->Reference());
	processor.SetPUnitNext(_GetPUnitCont());
#endif
}

#if 0
Value Expr_TmplScript::DoExec(Environment &env) const
{
	if (value.IsInvalid()) return Value::Nil;
	String strLast;
	if (value.Is_string()) {
		_pTemplate->Print(env, _strIndent.c_str());
		strLast = value.GetStringSTL();
	} else if (value.Is_list() || value.Is_iterator()) {
		AutoPtr<Iterator> pIterator(value.CreateIterator(env));
		if (env.IsSignalled()) return Value::Nil;
		bool firstFlag = true;
		Value valueElem;
		while (pIterator->Next(env, valueElem)) {
			if (firstFlag) {
				firstFlag = false;
				_pTemplate->Print(env, _strIndent.c_str());
			}
			foreach_const (String, p, strLast) {
				char ch = *p;
				if (ch == '\n') {
					_pTemplate->PutChar(env, ch);
					if (_autoIndentFlag && valueElem.IsValid()) {
						_pTemplate->Print(env, _strIndent.c_str());
					}
				} else {
					_pTemplate->PutChar(env, ch);
				}
			}
			if (valueElem.Is_string()) {
				strLast = valueElem.GetStringSTL();
			} else if (valueElem.IsInvalid()) {
				strLast.clear();
			} else if (valueElem.Is_number()) {
				strLast = valueElem.ToString();
				if (env.IsSignalled()) return Value::Nil;
			} else {
				env.SetError(ERR_TypeError,
							 "an iterable returned by a template script must contain "
							 "elements of nil, string or number");
				env.GetSignal().AddExprCause(this);
				return Value::Nil;
			}
		}
		if (firstFlag) return Value::Nil;
	} else if (value.Is_number()) {
		_pTemplate->Print(env, _strIndent.c_str());
		strLast = value.ToString();
		if (env.IsSignalled()) return Value::Nil;
	} else {
		env.SetError(ERR_TypeError,
			"template script must return nil, string or number");
		env.GetSignal().AddExprCause(this);
		return Value::Nil;
	}
	foreach_const (String, p, strLast) {
		char ch = *p;
		if (ch != '\n') {
			_pTemplate->PutChar(env, ch);
		} else if (p + 1 != strLast.end()) {
			_pTemplate->PutChar(env, ch);
			if (_autoIndentFlag) {
				_pTemplate->Print(env, _strIndent.c_str());
			}
		} else if (_appendLastEOLFlag) {
			_pTemplate->PutChar(env, ch);
		}
	}
	_pTemplate->Print(env, _strPost.c_str());
	return Value::Nil;
}
#endif

template<int nExprSrc, bool discardValueFlag>
String PUnit_TmplScript<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("TmplScript()");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_TmplScript::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_TmplScript<1, true>(_pTmpl.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_TmplScript<1, false>(_pTmpl.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_TmplScript<0, true>(_pTmpl.release());
		} else {
			_pPUnitCreated = new PUnit_TmplScript<0, false>(_pTmpl.release());
		}
	}
	return _pPUnitCreated;
}

}
