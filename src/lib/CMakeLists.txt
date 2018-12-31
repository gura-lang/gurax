add_library(guraxcore SHARED
	guraxcore.cpp
	Common.cpp
	Context.cpp
	DateTime.cpp
	Environment.cpp
	Error.cpp
	Expr.cpp
	Frame.cpp
	Function.cpp
	Help.cpp
	Iterator.cpp
	MemoryPool.cpp
	Object.cpp
	Object_bool.cpp
	Object_dict.cpp
	Object_function.cpp
	Object_list.cpp
	Object_nil.cpp
	Object_number.cpp
	Object_string.cpp
	Object_symbol.cpp
	Object_undefined.cpp
	Operator.cpp
	Parser.cpp
	Random.cpp
	Referable.cpp
	Stream.cpp
	String.cpp
	Symbol.cpp
	Symbols.cpp
	TimeDelta.cpp
	Token.cpp
	Tokenizer.cpp
)

target_link_libraries(guraxcore dl pthread)

set_target_properties(guraxcore PROPERTIES
	VERSION						${GURAX_VERSION}
	SOVERSION					${GURAX_VERSION_SO}
	BUILD_WITH_INSTALL_RPATH	1
	INSTALL_NAME_DIR			"@executable_path/../lib")

install(TARGETS guraxcore DESTINATION ${GURAX_RELDIR_LIBRARY})
