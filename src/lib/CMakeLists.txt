#===============================================================================
# CMakeLists for guraxcore library
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(guraxcore)

add_library(guraxcore SHARED)

add_subdirectory(../module-base64 module-base64)
add_subdirectory(../module-bmp module-bmp)
add_subdirectory(../module-codecs module-codecs)
add_subdirectory(../module-codecs_basic module-codecs_basic)
add_subdirectory(../module-codecs_chinese module-codecs_chinese)
add_subdirectory(../module-codecs_iso8859 module-codecs_iso8859)
add_subdirectory(../module-codecs_japanese module-codecs_japanese)
add_subdirectory(../module-fs module-fs)
add_subdirectory(../module-math module-math)
add_subdirectory(../module-os module-os)
add_subdirectory(../module-path module-path)
add_subdirectory(../module-sys module-sys)

target_sources(guraxcore PRIVATE
	guraxcore.cpp
	ArgFeeder.cpp
	ArgPicker.cpp
	ArgSlot.cpp
	Argument.cpp
	Array.cpp
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
	ImageMgr.cpp
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
	Pixel.cpp
	Pointer.cpp
	Pointers.cpp
	Processor.cpp
	PropSlot.cpp
	PropSlotCustom.cpp
	PUnit.cpp
	Random.cpp
	Rational.cpp
	Referable.cpp
	Stat.cpp
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
	VType_Array.cpp
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
	VType_Pixel.cpp
	VType_Pointer.cpp
	VType_PropSlot.cpp
	VType_PUnit.cpp
	VType_Quote.cpp
	VType_Random.cpp
	VType_Rational.cpp
	VType_Stat.cpp
	VType_Stream.cpp
	VType_String.cpp
	VType_StringPtr.cpp
	VType_Symbol.cpp
	VType_Template.cpp
	VType_TimeDelta.cpp
	VType_Undefined.cpp
	VType_VType.cpp
	${fileNamesModule}
)

include_directories(${PROJECT_SOURCE_DIR}/../../include)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	target_compile_options(guraxcore PUBLIC -bigobj)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Linux)
	target_link_libraries(guraxcore dl pthread)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
	target_link_libraries(guraxcore dl pthread)
	set_target_properties(guraxcore PROPERTIES
		VERSION						${GURAX_VERSION}
		SOVERSION					${GURAX_SOVERSION}
		BUILD_WITH_INSTALL_NAME_DIR	1
		INSTALL_NAME_DIR			"@executable_path/../lib")
else ()
	target_link_libraries(guraxcore dl pthread)
endif ()
target_precompile_headers(guraxcore PUBLIC stdafx.h)
install(TARGETS guraxcore
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
)
