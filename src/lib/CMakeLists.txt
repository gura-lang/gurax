set(GURAX_RELDIR ../module-codecs)
include(module-codecs/build)

set(GURAX_RELDIR ../module-codecs_basic)
include(module-codecs_basic/build)

set(GURAX_RELDIR ../module-codecs_chinese)
include(module-codecs_chinese/build)

set(GURAX_RELDIR ../module-codecs_iso8859)
include(module-codecs_iso8859/build)

set(GURAX_RELDIR ../module-codecs_japanese)
include(module-codecs_japanese/build)

set(GURAX_RELDIR ../module-fs)
include(module-fs/build)

set(GURAX_RELDIR ../module-math)
include(module-math/build)

set(GURAX_RELDIR ../module-os)
include(module-os/build)

set(GURAX_RELDIR ../module-path)
include(module-path/build)

set(GURAX_RELDIR ../module-sys)
include(module-sys/build)

add_library(guraxcore SHARED
	guraxcore.cpp
	ArgFeeder.cpp
	ArgPicker.cpp
	ArgSlot.cpp
	Argument.cpp
	Attribute.cpp
	Basement.cpp
	Binary.cpp
	Codec-WidthInfo.cpp
	Codec.cpp
	Color.cpp
	CommandLine.cpp
	Common.cpp
	Complex.cpp
	Composer.cpp
	DateTime.cpp
	DeclArg.cpp
	DeclBlock.cpp
	DeclCallable.cpp
	Directory.cpp
	DottedSymbol.cpp
	Error.cpp
	Expr.cpp
	Formatter.cpp
	Frame.cpp
	Function.cpp
	FunctionCustom.cpp
	Functions.cpp
	Help.cpp
	Image.cpp
	Index.cpp
	Iterator.cpp
	Iterators.cpp
	Math.cpp
	Memory.cpp
	MemoryPool.cpp
	Module.cpp
	Number.cpp
	OAL.cpp
	Operator.cpp
	Packer.cpp
	Palette.cpp
	Parser.cpp
	PathMgr.cpp
	PathName.cpp
	Pointer.cpp
	Pointers.cpp
	Processor.cpp
	PropHandler.cpp
	PropHandlerCustom.cpp
	PUnit.cpp
	Random.cpp
	Referable.cpp
	Statements.cpp
	Stream.cpp
	Streams.cpp
	String.cpp
	StringPicker.cpp
	SuffixMgr.cpp
	Symbol.cpp
	Symbols.cpp
	Template.cpp
	TimeDelta.cpp
	Token.cpp
	Tokenizer.cpp
	Value.cpp
	ValueDeque.cpp
	ValueDict.cpp
	ValueList.cpp
	ValueMap.cpp
	ValueOwner.cpp
	ValueTypedOwner.cpp
	Version.cpp
	VType.cpp
	VTypeCustom.cpp
	VType_Any.cpp
	VType_ArgMapper.cpp
	VType_ArgMapper_Multiple.cpp
	VType_ArgSlot.cpp
	VType_Argument.cpp
	VType_Attribute.cpp
	VType_Binary.cpp
	VType_Bool.cpp
	VType_CallableMember.cpp
	VType_Codec.cpp
	VType_Color.cpp
	VType_Complex.cpp
	VType_DateTime.cpp
	VType_Dict.cpp
	VType_Directory.cpp
	VType_Error.cpp
	VType_ErrorType.cpp
	VType_Expr.cpp
	VType_Frame.cpp
	VType_Function.cpp
	VType_Help.cpp
	VType_Image.cpp
	VType_Index.cpp
	VType_Iterator.cpp
	VType_KeyValuePair.cpp
	VType_List.cpp
	VType_Module.cpp
	VType_Nil.cpp
	VType_Number.cpp
	VType_Object.cpp
	VType_Palette.cpp
	VType_PathMgr.cpp
	VType_Pointer.cpp
	VType_PropHandler.cpp
	VType_PUnit.cpp
	VType_Quote.cpp
	VType_Random.cpp
	VType_Stream.cpp
	VType_String.cpp
	VType_StringPtr.cpp
	VType_Symbol.cpp
	VType_Template.cpp
	VType_TimeDelta.cpp
	VType_Undefined.cpp
	VType_VType.cpp
	${files-module}
)

target_link_libraries(guraxcore dl pthread)

set_target_properties(guraxcore PROPERTIES
	VERSION						${GURAX_VERSION}
	SOVERSION					${GURAX_VERSION_SO}
	BUILD_WITH_INSTALL_NAME_DIR	1
	INSTALL_NAME_DIR			"@executable_path/../lib")

target_precompile_headers(guraxcore PUBLIC stdafx.h)

install(TARGETS guraxcore DESTINATION ${GURAX_RELDIR_LIBRARY})
