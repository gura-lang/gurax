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
		enum class Stat {
			LineTop, Indent, String, ScriptPre, ScriptFirst, ScriptSecond, Script, ScriptPost,
			Comment, Comment_LineTop, CommentEnd_Second, CommentEnd_SeekR, CommentEnd_Marker, CommentPost,
		} stat = Stat::LineTop;
	private:
		Template& _tmpl;
		RefPtr<StringReferable> _pSourceName;
		bool _autoIndentFlag;
		bool _appendLastEOLFlag;
		Stat _stat;
		bool _stringAheadFlag;
		int _cntLine;
		int _cntLineTop;
		int _nDepth;
		String _str;
		String _strTmplScript;
		String _strIndent;
		ExprLeaderStack _exprLeaderStack;
	public:
		Parser(Template& tmpl, StringReferable* pSourceName, bool autoIndentFlag, bool appendLastEOLFlag);
		Parser(Template& tmpl, String sourceName, bool autoIndentFlag, bool appendLastEOLFlag) :
			Parser(tmpl, new StringReferable(std::move(sourceName)), autoIndentFlag, appendLastEOLFlag) {}
		bool FeedChar(char ch);
		bool Flush();
	private:
		void CreateTmplString();
		bool CreateTmplScript(const char* strPost);
		void AddExpr(Expr* pExpr) {
			(_exprLeaderStack.empty()? _tmpl.GetExprForBody() : *_exprLeaderStack.back()).AddExprElem(pExpr);
		}
	};
private:
	RefPtr<Template> _pTemplateSuper;
	RefPtr<Expr_Block> _pExprForInit;
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
	Expr_Block& GetExprForInit() { return *_pExprForInit; }
	const Expr_Block& GetExprForInit() const { return *_pExprForInit; }
	Expr_Block& GetExprForBody() { return *_pExprForBody; }
	const Expr_Block& GetExprForBody() const { return *_pExprForBody; }
	ValueMap &GetValueMap() { return *_pValueMap; }
	const ValueMap &GetValueMap() const { return *_pValueMap; }
	void SetStreamDst(Stream *pStream) { _pStreamDst.reset(pStream); }
	Stream& GetStreamDst() { return *_pStreamDst; }
	void ClearLastChar()  { _chLast = '\0'; }
	char GetLastChar() const { return _chLast; }
public:
	bool ParseStream(Stream& streamSrc, bool autoIndentFlag, bool appendLastEOLFlag);
	bool ParseString(String::const_iterator strSrc, String::const_iterator strSrcEnd,
					 bool autoIndentFlag, bool appendLastEOLFlag);
	bool ParseString(const char* strSrc, bool autoIndentFlag, bool appendLastEOLFlag);
	bool ParseString(const char* strSrc, const char* strSrcEnd,
					 bool autoIndentFlag, bool appendLastEOLFlag);
	bool Render(Stream& streamDst);
	bool Render(String& strDst);
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
	const char* GetString() const { return _str.c_str(); }
	const String& GetStringSTL() const { return _str; }
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
	Expr_TmplScript(Template* pTemplate, const String& strIndent, const String& strPost,
					bool autoIndentFlag, bool appendLastEOLFlag) :
		Expr_Collector(typeInfo, new ExprLink()), _pTemplate(pTemplate),
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

//------------------------------------------------------------------------------
// PUnit_TmplString
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_TmplString : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Template> _pTmpl;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_TmplString(Template* pTmpl) : _pTmpl(pTmpl) {}
	PUnit_TmplString(Template* pTmpl, Expr* pExpr) : PUnit_TmplString(pTmpl) { _ppExprSrc[0] = pExpr; }
public:
	const Template& GetTemplate() const { return *_pTmpl; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_TmplString : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_TmplString");
private:
	RefPtr<Template> _pTmpl;
public:
	PUnitFactory_TmplString(Template* pTmpl, Expr* pExprSrc) : PUnitFactory(pExprSrc), _pTmpl(pTmpl) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_TmplString<1, false>) : sizeof(PUnit_TmplString<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_TmplScript
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_TmplScript : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Template> _pTmpl;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_TmplScript(Template* pTmpl) : _pTmpl(pTmpl) {}
	PUnit_TmplScript(Template* pTmpl, Expr* pExpr) : PUnit_TmplScript(pTmpl) { _ppExprSrc[0] = pExpr; }
public:
	const Template& GetTemplate() const { return *_pTmpl; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_TmplScript : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_TmplScript");
private:
	RefPtr<Template> _pTmpl;
public:
	PUnitFactory_TmplScript(Template* pTmpl, Expr* pExprSrc) : PUnitFactory(pExprSrc), _pTmpl(pTmpl) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_TmplScript<1, false>) : sizeof(PUnit_TmplScript<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
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
