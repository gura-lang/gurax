add_library(guraxcore SHARED
	guraxcore.cpp
	Argument.cpp
	Attribute.cpp
	Binary.cpp
	Codec.cpp
	Common.cpp
	Context.cpp
	DateTime.cpp
	DeclArg.cpp
	DeclCaller.cpp
	Environment.cpp
	Error.cpp
	Expr.cpp
	Formatter.cpp
	Frame.cpp
	Function.cpp
	Help.cpp
	Iterator.cpp
	MemoryPool.cpp
	Module.cpp
	Object.cpp
	Object_Any.cpp
	Object_Argument.cpp
	Object_Attribute.cpp
	Object_Binary.cpp
	Object_Bool.cpp
	Object_DateTime.cpp
	Object_Dict.cpp
	Object_Expr.cpp
	Object_Function.cpp
	Object_Iterator.cpp
	Object_Klass.cpp
	Object_List.cpp
	Object_Module.cpp
	Object_Nil.cpp
	Object_Number.cpp
	Object_Quote.cpp
	Object_Stream.cpp
	Object_String.cpp
	Object_StringPtr.cpp
	Object_Symbol.cpp
	Object_Template.cpp
	Object_TimeDelta.cpp
	Object_Undefined.cpp
	Operator.cpp
	Operators.cpp
	Parser.cpp
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
)

target_link_libraries(guraxcore dl pthread)

set_target_properties(guraxcore PROPERTIES
	VERSION						${GURAX_VERSION}
	SOVERSION					${GURAX_VERSION_SO}
	BUILD_WITH_INSTALL_RPATH	1
	INSTALL_NAME_DIR			"@executable_path/../lib")

install(TARGETS guraxcore DESTINATION ${GURAX_RELDIR_LIBRARY})
