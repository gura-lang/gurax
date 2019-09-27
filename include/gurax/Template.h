//==============================================================================
// Template.h
//==============================================================================
#ifndef GURAX_TEMPLATE_H
#define GURAX_TEMPLATE_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Template
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Template : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Template);
public:
	class GURAX_DLLDECLARE Parser {
	public:
		using ExprLeaderStack = std::vector<Expr_Block*>;
	private:
		bool _autoIndentFlag;
		bool _appendLastEOLFlag;
		ExprLeaderStack _exprLeaderStack;
	public:
		Parser(bool autoIndentFlag, bool appendLastEOLFlag);
		bool ParseStream(Template& tmpl, Stream &streamSrc);
	private:
		bool CreateTmplScript(
			const char* strIndent, const char* strTmplScript, const char* strPost,
			Template& tmpl, Expr_Block& exprBlock,
			StringReferable& sourceName, int cntLineTop, int cntLineBtm);
	};
private:
	RefPtr<Template> _pTemplateSuper;
	RefPtr<ExprOwner> _pExprOwnerForInit;
	RefPtr<Expr_Block> _pExprForBody;
	RefPtr<ValueMap> _pValueMap;
	RefPtr<Stream> _pStreamDst;
	char _chLast;
public:
	// Constructor
	Template();
	// Copy constructor/operator
	Template(const Template& src) = delete;
	Template& operator=(const Template& src) = delete;
	// Move constructor/operator
	Template(Template&& src) = delete;
	Template& operator=(Template&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Template() = default;
public:
	static void Bootup();
public:
	void SetTemplateSuper(Template *pTemplateSuper) { _pTemplateSuper.reset(pTemplateSuper); }
	Template& GetTemplateSuper() { return *_pTemplateSuper; }
	const Template& GetTemplateSuper() const { return *_pTemplateSuper; }
	ExprOwner &GetExprOwnerForInit() { return *_pExprOwnerForInit; }
	Expr_Block& GetExprForBody() { return *_pExprForBody; }
	const Expr_Block& GetExprForBody() const { return *_pExprForBody; }
	ValueMap &GetValueMap() { return *_pValueMap; }
	const ValueMap &GetValueMap() const { return *_pValueMap; }
	void SetStreamDst(Stream *pStream) { _pStreamDst.reset(pStream); }
	Stream& GetStreamDst() { return *_pStreamDst; }
	void ClearLastChar()  { _chLast = '\0'; }
	char GetLastChar() const { return _chLast; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Template& templ) const { return this == &templ; }
	bool IsEqualTo(const Template& templ) const { return IsIdentical(templ); }
	bool IsLessThan(const Template& templ) const { return this < &templ; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(template)"; }
};

//-----------------------------------------------------------------------------
// Expr_TmplString
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_TmplString : public Expr_Node {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Template> _pTemplate;
	String _str;
public:
	Expr_TmplString(Template* pTemplate, const String& str) :
		Expr_Node(typeInfo), _pTemplate(pTemplate), _str(str) {}
public:
	Template& GetTemplate() { return *_pTemplate; }
	const char *GetString() const { return _str.c_str(); }
public:
	virtual void Compose(Composer& composer) override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Expr_TmplScript
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_TmplScript : public Expr_Collector {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Template> _pTemplate;
	String _strIndent;
	String _strPost;
	bool _autoIndentFlag;
	bool _appendLastEOLFlag;
public:
	Expr_TmplScript(ExprLink* pExprLinkElem, Template *pTemplate,
					const String& strIndent, const String& strPost,
					bool autoIndentFlag, bool appendLastEOLFlag) :
		Expr_Collector(typeInfo, pExprLinkElem), _pTemplate(pTemplate),
		_strIndent(strIndent), _strPost(strPost),
		_autoIndentFlag(autoIndentFlag), _appendLastEOLFlag(appendLastEOLFlag) {}
public:
	Template& GetTemplate() { return *_pTemplate; }
	void SetStringIndent(const String &strIndent) { _strIndent = strIndent; }
	void SetStringPost(const String &strPost) { _strPost = strPost; }
public:
	virtual void Compose(Composer& composer) override;
	virtual String ToString(const StringStyle& ss) const override;
};

#if 0
//-----------------------------------------------------------------------------
// Template
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Template {
public:
private:
	int _cntRef;
	AutoPtr<Template> _pTemplateSuper;
	AutoPtr<ExprOwner> _pExprOwnerForInit;
	AutoPtr<FunctionCustom> _pFuncForBody;
	AutoPtr<ValueExMap> _pValueExMap;
	SimpleStream *_pStreamDst;
	char _chLast;
public:
	Gura_DeclareReferenceAccessor(Template);
public:
	Template();
private:
	inline ~Template() {}
public:
	bool Read(Environment &env,
			  SimpleStream &streamSrc, bool autoIndentFlag, bool appendLastEOLFlag);
	bool Parse(Environment &env,
			   String::const_iterator strSrc, String::const_iterator strSrcEnd,
			   bool autoIndentFlag, bool appendLastEOLFlag);
	bool Parse(Environment &env,
			   const char *strSrc, const char *strSrcEnd,
			   bool autoIndentFlag, bool appendLastEOLFlag);
	bool Render(Environment &env, SimpleStream *pStreamDst);
	bool Render(Environment &env, String &strDst);
	bool Prepare(Environment &env);
	const ValueEx *LookupValue(const Symbol *pSymbol) const;
	void PutChar(Signal &sig, char ch);
	void Print(Signal &sig, const char *str);
	inline void SetTemplateSuper(Template *pTemplateSuper) {
		_pTemplateSuper.reset(pTemplateSuper);
	}
	inline Template *GetTemplateSuper() { return _pTemplateSuper.get(); }
	inline const Template *GetTemplateSuper() const { return _pTemplateSuper.get(); }
	inline void SetFuncForBody(FunctionCustom *pFuncForBody) { _pFuncForBody.reset(pFuncForBody); }
	inline ExprOwner &GetExprOwnerForInit() { return *_pExprOwnerForInit; }
	inline FunctionCustom *GetFuncForBody() { return _pFuncForBody.get(); }
	inline const FunctionCustom *GetFuncForBody() const { return _pFuncForBody.get(); }
	inline ValueExMap &GetValueExMap() { return *_pValueExMap; }
	inline const ValueExMap &GetValueExMap() const { return *_pValueExMap; }
	inline void SetStreamDst(SimpleStream *pStreamDst) { _pStreamDst = pStreamDst; }
	inline SimpleStream *GetStreamDst() { return _pStreamDst; }
	inline void ClearLastChar()  { _chLast = '\0'; }
	inline char GetLastChar() const { return _chLast; }
};

#endif

}

#endif
