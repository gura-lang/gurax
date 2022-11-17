//==============================================================================
// Template.h
//==============================================================================
#ifndef GURAX_TEMPLATE_H
#define GURAX_TEMPLATE_H
#include "Expr.h"

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
		using ExprLeaderStack = std::vector<Expr_Caller*>;
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
		bool Finish();
	private:
		static bool PrepareAndCompose(Expr& expr);
		void CreateTmplString();
		bool CreateTmplScript(const char* strPost);
		void AddExpr(Expr* pExpr);
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
	void SetTemplateSuper(Template* pTemplateSuper) { _pTemplateSuper.reset(pTemplateSuper); }
	Template* GetTemplateSuper() { return _pTemplateSuper.get(); }
	const Template* GetTemplateSuper() const { return _pTemplateSuper.get(); }
	Expr_Block& GetExprForInit() { return *_pExprForInit; }
	const Expr_Block& GetExprForInit() const { return *_pExprForInit; }
	Expr_Block& GetExprForBody() { return *_pExprForBody; }
	const Expr_Block& GetExprForBody() const { return *_pExprForBody; }
	ValueMap& GetValueMap() { return *_pValueMap; }
	const ValueMap& GetValueMap() const { return *_pValueMap; }
	void SetStreamDst(Stream* pStream) { _pStreamDst.reset(pStream); }
	Stream& GetStreamDst() { return *_pStreamDst; }
	const Stream& GetStreamDst() const { return *_pStreamDst; }
	void ClearLastChar()  { _chLast = '\0'; }
	char GetLastChar() const { return _chLast; }
public:
	bool ParseStream(Stream& streamSrc, bool autoIndentFlag, bool appendLastEOLFlag);
	bool ParseString(String::const_iterator strSrc, String::const_iterator strSrcEnd,
					 bool autoIndentFlag, bool appendLastEOLFlag);
	bool ParseString(const char* strSrc, bool autoIndentFlag, bool appendLastEOLFlag);
	bool ParseString(const char* strSrc, const char* strSrcEnd,
					 bool autoIndentFlag, bool appendLastEOLFlag);
	bool PrepareAndCompose();
	bool PrepareAndCompose(Composer& composer);
	bool Render(Processor& processor, Stream& streamDst);
	bool Render(Processor& processor, String& strDst);
	void PutChar(char ch);
	void Print(const char* str);
	bool AssignValue(const Symbol* pSymbol, Value* pValue);
	const Value* LookupValue(const Symbol* pSymbol) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Template& templ) const { return this == &templ; }
	bool IsEqualTo(const Template& templ) const { return IsIdentical(templ); }
	bool IsLessThan(const Template& templ) const { return this < &templ; }
	String ToString(const StringStyle& ss) const;
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
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
};

//-----------------------------------------------------------------------------
// Expr_TmplScript
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_TmplScript : public Expr_Collector {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_TmplScript);
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
	const char* GetStringPost() const { return _strPost.c_str(); }
	const char* GetStringIndent() const { return _strIndent.c_str(); }
	void SetStringPost(const String& strPost) { _strPost = strPost; }
	void SetStringIndent(const String& strIndent) { _strIndent = strIndent; }
	bool GetAutoIndentFlag() const { return _autoIndentFlag; }
	bool GetAppendLastEOLFlag() const { return _appendLastEOLFlag; }
public:
	virtual void Compose(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
};

//------------------------------------------------------------------------------
// Expr_Template : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Template : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Template);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<StringReferable> _pStr;
	bool _embedFlag;
public:
	Expr_Template(StringReferable* pStr, bool embedFlag) :
		Expr_Node(typeInfo), _pStr(pStr), _embedFlag(embedFlag) {}
	const StringReferable& GetStringReferable() const { return *_pStr; }
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
};

//------------------------------------------------------------------------------
// PUnit_TmplString
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_TmplString : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Template> _pTmpl;
	String _str;
public:
	// Constructor
	PUnit_TmplString(Template* pTmpl, String str, Expr* pExprSrc) :
					PUnit(pExprSrc), _pTmpl(pTmpl), _str(std::move(str)) {}
public:
	Template& GetTemplate() const { return *_pTmpl; }
	const char* GetString() const { return _str.c_str(); }
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
	String _str;
public:
	PUnitFactory_TmplString(Template* pTmpl, String str, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pTmpl(pTmpl), _str(std::move(str)) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_TmplString<false>) : sizeof(PUnit_TmplString<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_TmplScript
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_TmplScript : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Expr_TmplScript> _pExprTmplScript;
public:
	// Constructor
	PUnit_TmplScript(Expr_TmplScript* pExprTmplScript, Expr* pExprSrc) :
						PUnit(pExprSrc), _pExprTmplScript(pExprTmplScript) {}
public:
	Template& GetTemplate() const { return _pExprTmplScript->GetTemplate(); }
	const char* GetStringPost() const { return _pExprTmplScript->GetStringPost(); }
	const char* GetStringIndent() const { return _pExprTmplScript->GetStringIndent(); }
	bool GetAutoIndentFlag() const { return _pExprTmplScript->GetAutoIndentFlag(); }
	bool GetAppendLastEOLFlag() const { return _pExprTmplScript->GetAppendLastEOLFlag(); }
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
	void RenderValue(const Value& value) const;
	void PrintScriptResult(const char* str) const;
};

class PUnitFactory_TmplScript : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_TmplScript");
private:
	RefPtr<Expr_TmplScript> _pExprTmplScript;
public:
	PUnitFactory_TmplScript(Expr_TmplScript* pExprTmplScript, Expr* pExprSrc) : PUnitFactory(pExprSrc), _pExprTmplScript(pExprTmplScript) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_TmplScript<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_TmplEmbedded
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_TmplEmbedded : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Template> _pTmpl;
public:
	// Constructor
	//PUnit_TmplEmbedded(Template* pTmpl) : _pTmpl(pTmpl) {}
	PUnit_TmplEmbedded(Template* pTmpl, Expr* pExprSrc) :
							PUnit(pExprSrc), _pTmpl(pTmpl) {}
public:
	Template& GetTemplate() const { return *_pTmpl; }
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

class PUnitFactory_TmplEmbedded : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_TmplEmbedded");
private:
	RefPtr<Template> _pTmpl;
public:
	PUnitFactory_TmplEmbedded(Template* pTmpl, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pTmpl(pTmpl) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_TmplEmbedded<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

}

#endif
