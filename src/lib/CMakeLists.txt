add_library(guraxcore SHARED
	guraxcore.cpp
	ArgSlot.cpp
	Argument.cpp
	Attribute.cpp
	Binary.cpp
	Codec.cpp
	Common.cpp
	Context.cpp
	DateTime.cpp
	DeclArg.cpp
	DeclCaller.cpp
	DottedSymbol.cpp
	Environment.cpp
	Error.cpp
	Expr.cpp
	Formatter.cpp
	Frame.cpp
	Function.cpp
	Help.cpp
	Iterator.cpp
	Iterators.cpp
	MemoryPool.cpp
	Module.cpp
	Operator.cpp
	Operators.cpp
	Parser.cpp
	Processor.cpp
	Property.cpp
	PUnit.cpp
	Random.cpp
	Referable.cpp
	Stream.cpp
	Streams.cpp
	String.cpp
	SuffixMgr.cpp
	Symbol.cpp
	Symbols.cpp
	Template.cpp
	TimeDelta.cpp
	Token.cpp
	Tokenizer.cpp
	Unicode-EastAsianWidth.cpp
	Value.cpp
	VType.cpp
	VType_Any.cpp
	VType_ArgSlot.cpp
	VType_Argument.cpp
	VType_Attribute.cpp
	VType_Binary.cpp
	VType_Bool.cpp
	VType_DateTime.cpp
	VType_Dict.cpp
	VType_Expr.cpp
	VType_Function.cpp
	VType_Iterator.cpp
	VType_List.cpp
	VType_Member.cpp
	VType_Module.cpp
	VType_Nil.cpp
	VType_Number.cpp
	VType_Object.cpp
	VType_Quote.cpp
	VType_Stream.cpp
	VType_String.cpp
	VType_StringPtr.cpp
	VType_Symbol.cpp
	VType_Template.cpp
	VType_TimeDelta.cpp
	VType_Undefined.cpp
	VType_VType.cpp
)

target_link_libraries(guraxcore dl pthread)

set_target_properties(guraxcore PROPERTIES
	VERSION						${GURAX_VERSION}
	SOVERSION					${GURAX_VERSION_SO}
	BUILD_WITH_INSTALL_RPATH	1
	INSTALL_NAME_DIR			"@executable_path/../lib")

install(TARGETS guraxcore DESTINATION ${GURAX_RELDIR_LIBRARY})
