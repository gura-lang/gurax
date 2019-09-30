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
	//_pFuncForBody->Declare(VTYPE_Nil, DeclCallable::Flag::DynamicScope);
	//_pFuncForBody->SetFrameOuter(processor.GetFrameCur());
}

//-----------------------------------------------------------------------------
// Template::Parser
//-----------------------------------------------------------------------------
Template::Parser::Parser(bool autoIndentFlag, bool appendLastEOLFlag) :
	_autoIndentFlag(autoIndentFlag), _appendLastEOLFlag(appendLastEOLFlag)
{
}

bool Template::Parser::ParseStream(Template& tmpl, Stream& streamSrc)
{
	RefPtr<StringReferable> pSourceName(new StringReferable(streamSrc.GetName()));
	const char chMarker = '$';
	enum class Stat {
		LineTop, Indent, String, ScriptPre, ScriptFirst, ScriptSecond, Script, ScriptPost,
		Comment, Comment_LineTop, CommentEnd_Second, CommentEnd_SeekR, CommentEnd_Marker, CommentPost,
	} stat = Stat::LineTop;
	bool stringAheadFlag = false;
	String str;
	String strTmplScript;
	String strIndent;
	int cntLine = 0;
	int cntLineTop = 0;
	int nDepth = 0;
	_exprLeaderStack.clear();
	Expr_Block& exprBlockRoot = tmpl.GetExprForBody();
	for (;;) {
		int chRaw = streamSrc.GetChar();
		if (Error::IsIssued()) return false;
		if (chRaw < 0) break;
		char ch = static_cast<char>(chRaw);
		Gurax_BeginPushbackRegion();
		switch (stat) {
		case Stat::LineTop: {
			if (ch == '\n') {
				str += ch;
			} else if (String::IsWhite(ch)) {
				Gurax_Pushback();
				stat = Stat::Indent;
			} else if (ch == chMarker) {
				stat = Stat::ScriptPre;
			} else {
				stringAheadFlag = true;
				Gurax_Pushback();
				stat = Stat::String;
			}
			break;
		}
		case Stat::Indent: {
			if (String::IsWhite(ch)) {
				strIndent += ch;
			} else if (ch == chMarker) {
				stat = Stat::ScriptPre;
			} else {
				str += strIndent;
				strIndent.clear();
				stringAheadFlag = true;
				Gurax_Pushback();
				stat = Stat::String;
			}
			break;
		}
		case Stat::String: {
			if (ch == chMarker) {
				stat = Stat::ScriptPre;
			} else if (ch == '\n') {
				str += ch;
				stringAheadFlag = false;
				stat = Stat::LineTop;
			} else {
				str += ch;
			}
			break;
		}
		case Stat::ScriptPre: {
			if (ch == '{') {
				if (!str.empty()) {
					Expr_Block& exprOfBlock = _exprLeaderStack.empty()?
						exprBlockRoot : *_exprLeaderStack.back();
					RefPtr<Expr> pExpr(new Expr_TmplString(tmpl.Reference(), str));
					pExpr->SetSourceInfo(pSourceName->Reference(), 0, 0);
					exprOfBlock.AddExprElem(pExpr.release());
					str.clear();
				}
				cntLineTop = cntLine;
				nDepth = 1;
				strTmplScript.clear();
				stat = Stat::ScriptFirst;
			} else {
				str += strIndent;
				strIndent.clear();
				str += chMarker;
				stringAheadFlag = true;
				Gurax_Pushback();
				stat = Stat::String;
			}
			break;
		}
		case Stat::ScriptFirst: {
			if (ch == '=') {
				stat = Stat::ScriptSecond;
			} else {
				Gurax_Pushback();
				stat = Stat::Script;
			}
			break;
		}
		case Stat::ScriptSecond: {
			if (ch == '=') {
				stat = Stat::Comment;
			} else {
				strTmplScript += '=';
				Gurax_Pushback();
				stat = Stat::Script;
			}
			break;
		}
		case Stat::Script: {
			if (ch == '{') {
				strTmplScript += ch;
				nDepth++;
			} else if (ch == '}') {
				nDepth--;
				if (nDepth > 0) {
					strTmplScript += ch;
					break;
				}
				stat = Stat::ScriptPost;
			} else {
				strTmplScript += ch;
			}
			break;
		}
		case Stat::ScriptPost: {
			const char *strPost = (ch == '\n')? "\n" : "";
			if (!CreateTmplScript(
					strIndent.c_str(), strTmplScript.c_str(), strPost,
					tmpl, exprBlockRoot, *pSourceName, cntLineTop, cntLine)) return false;
			strIndent.clear();
			strTmplScript.clear();
			if (ch == '\n') {
				stringAheadFlag = false;
				stat = Stat::LineTop;
			} else {
				stringAheadFlag = true;
				Gurax_Pushback();
				stat = Stat::String;
			}
			break;
		}
		case Stat::Comment: {
			if (ch == '=') {
				stat = Stat::CommentEnd_Second;
			} else if (ch == '\n') {
				stringAheadFlag = false;
				stat = Stat::Comment_LineTop;
			} else {
				// nothing to do
			}
			break;
		}
		case Stat::Comment_LineTop: {
			if (ch == '=') {
				stat = Stat::CommentEnd_Second;
			} else if (ch == '\n') {
				// nothing to do
			} else if (String::IsWhite(ch)) {
				// nothing to do
			} else {
				stringAheadFlag = true;
				stat = Stat::Comment;
			}
			break;
		}
		case Stat::CommentEnd_Second: {
			if (ch == '=') {
				stat = Stat::CommentEnd_SeekR;
			} else if (ch == '\n') {
				stringAheadFlag = false;
				stat = Stat::Comment_LineTop;
			} else {
				stringAheadFlag = true;
				stat = Stat::Comment;
			}
			break;
		}
		case Stat::CommentEnd_SeekR: {
			if (ch == '}') {
				stat = Stat::CommentEnd_Marker;
			} else if (ch == '\n') {
				stringAheadFlag = false;
				stat = Stat::Comment_LineTop;
			} else {
				stringAheadFlag = true;
				stat = Stat::Comment;
			}
			break;
		}
		case Stat::CommentEnd_Marker: {
			if (ch == chMarker) {
				stat = Stat::CommentPost;
			} else if (ch == '\n') {
				stringAheadFlag = false;
				stat = Stat::Comment_LineTop;
			} else {
				stringAheadFlag = true;
				stat = Stat::Comment;
			}
			break;
		}
		case Stat::CommentPost: {
			if (!stringAheadFlag && ch == '\n') {
				stringAheadFlag = false;
				stat = Stat::LineTop;
			} else {
				stringAheadFlag = true;
				Gurax_Pushback();
				stat = Stat::String;
			}
			break;
		}
		}
		Gurax_EndPushbackRegion();
		if (ch == '\n') cntLine++;
	}
	if (!strTmplScript.empty()) {
		const char* strPost = "";
		if (!CreateTmplScript(
				strIndent.c_str(), strTmplScript.c_str(), strPost,
				tmpl, exprBlockRoot, *pSourceName, cntLineTop, cntLine)) return false;
	}
	if (!_exprLeaderStack.empty()) {
		Error::Issue(ErrorType::SyntaxError, "missing end statement for block expression");
		return false;
	}
	if (!str.empty()) {
		RefPtr<Expr> pExpr(new Expr_TmplString(tmpl.Reference(), str));
		pExpr->SetSourceInfo(pSourceName->Reference(), 0, 0);
		exprBlockRoot.AddExprElem(pExpr.release());
		str.clear();
	}
	return exprBlockRoot.Prepare();
}

bool Template::Parser::CreateTmplScript(
	const char* strIndent, const char* strTmplScript, const char* strPost,
	Template& tmpl, Expr_Block& exprBlock,
	StringReferable& sourceName, int cntLineTop, int cntLineBtm)
{
	//Class *pClass = env.LookupClass(VTYPE_template);
	Expr* pExprLast = nullptr;
	//RefPtr<Expr_TmplScript> pExprTmplScript(
	//	new Expr_TmplScript(
	//		tmpl.Reference(), strIndent, strPost, _autoIndentFlag, _appendLastEOLFlag));
	//pExprTmplScript->SetSourceInfo(pSourceName->Reference(), cntLineTop + 1, cntLineBtm + 1);
	//RefPtr<ExprLink> pExprLink(new ExprLink());
	if (*strTmplScript == '=') {
		// Parsing template directive that looks like "${=foo()}".
		strTmplScript++;
		//RefPtr<ExprOwner> pExprOwnerForInit(new ExprOwner());
#if 0
		do {
			Expr_Block& expr = tmpl.GetExprForInit();
			Gurax::Parser parser(sourceName.GetString(), tmpl.GetExprForInit().Reference());
			// Appends "this.init_" before the script string while parsing
			// so that it generates an expression "this.init_foo()" from the directive "${=foo()}".
			if (!parser.ParseString("this.init_", false)) return false;
			if (!parser.ParseString(strTmplScript, true)) return false;
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
#endif
	}
#if 0
		if ()
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
#endif
	return false;
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
	//_pTemplate->Print(_str.c_str());
}

String Expr_TmplString::ToString(const StringStyle& ss) const
{
	return "";
}

//-----------------------------------------------------------------------------
// Expr_TmplScript
//-----------------------------------------------------------------------------
const Expr::TypeInfo Expr_TmplScript::typeInfo;

void Expr_TmplScript::Compose(Composer& composer)
{
}

#if 0
Value Expr_TmplScript::DoExec(Environment &env) const
{
	if (GetExprOwner().empty()) return Value::Nil;
	Value value;
	foreach_const (ExprList, ppExpr, GetExprOwner()) {
		value = (*ppExpr)->Exec(env, true);
		if (env.IsSignalled()) return Value::Nil;
	}
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

String Expr_TmplScript::ToString(const StringStyle& ss) const
{
	return "";
}

#if 0

bool Template::Read(Environment &env,
			SimpleStream &streamSrc, bool autoIndentFlag, bool appendLastEOLFlag)
{
	Parser parser(autoIndentFlag, appendLastEOLFlag);
	return parser.ParseStream(env, this, streamSrc);
}

bool Template::Parse(Environment &env,
		String::const_iterator strSrc, String::const_iterator strSrcEnd,
		bool autoIndentFlag, bool appendLastEOLFlag)
{
	SimpleStream_StringReader streamSrc(strSrc, strSrcEnd);
	return Read(env, streamSrc, autoIndentFlag, appendLastEOLFlag);
}

bool Template::Parse(Environment &env,
		const char *strSrc, const char *strSrcEnd, bool autoIndentFlag, bool appendLastEOLFlag)
{
	SimpleStream_CStringReader streamSrc(strSrc, strSrcEnd);
	return Read(env, streamSrc, autoIndentFlag, appendLastEOLFlag);
}

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

void Template::PutChar(Signal &sig, char ch)
{
	_pStreamDst->PutChar(sig, ch);
	_chLast = ch;
}

void Template::Print(Signal &sig, const char *str)
{
	_pStreamDst->Print(sig, str);
	size_t len = ::strlen(str);
	if (len > 0) _chLast = str[len - 1];
}

#endif

}
