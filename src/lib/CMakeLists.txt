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
	Property.cpp
	Random.cpp
	Referable.cpp
	Stream.cpp
	Streams.cpp
	String.cpp
	Symbol.cpp
	Symbols.cpp
	Template.cpp
	TimeDelta.cpp
	Token.cpp
	Tokenizer.cpp
	Unicode-EastAsianWidth.cpp
	Value.cpp
	Value_Any.cpp
	Value_ArgSlot.cpp
	Value_Argument.cpp
	Value_Attribute.cpp
	Value_Binary.cpp
	Value_Bool.cpp
	Value_DateTime.cpp
	Value_Dict.cpp
	Value_Expr.cpp
	Value_Function.cpp
	Value_Iterator.cpp
	Value_List.cpp
	Value_Member.cpp
	Value_Module.cpp
	Value_Nil.cpp
	Value_Number.cpp
	Value_Object.cpp
	Value_Quote.cpp
	Value_Stream.cpp
	Value_String.cpp
	Value_StringPtr.cpp
	Value_Symbol.cpp
	Value_Template.cpp
	Value_TimeDelta.cpp
	Value_Undefined.cpp
	Value_VType.cpp
	VType.cpp
)

target_link_libraries(guraxcore dl pthread)

set_target_properties(guraxcore PROPERTIES
	VERSION						${GURAX_VERSION}
	SOVERSION					${GURAX_VERSION_SO}
	BUILD_WITH_INSTALL_RPATH	1
	INSTALL_NAME_DIR			"@executable_path/../lib")

install(TARGETS guraxcore DESTINATION ${GURAX_RELDIR_LIBRARY})
