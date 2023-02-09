#===============================================================================
# CMakeLists for guraxcore library
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(guraxcore)

add_library(guraxcore SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(guraxcore PRIVATE ${PROJECT_SOURCE_DIR}/../../include)
target_link_directories(guraxcore PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(guraxcore PRIVATE cxx_std_17)
target_precompile_headers(guraxcore PRIVATE stdafx.h)
target_compile_options(guraxcore PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3 -bigobj>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_sources(guraxcore PRIVATE
	guraxcore.cpp
	ArgFeeder.cpp
	ArgPicker.cpp
	ArgSlot.cpp
	Argument.cpp
	Array.cpp
	Attribute.cpp
	Basement.cpp
	BasicFunction.cpp
	BasicIterator.cpp
	BasicPointer.cpp
	BasicStatement.cpp
	BasicStream.cpp
	BasicVType.cpp
	Binary.cpp
	Codec-WidthInfo.cpp
	Codec.cpp
	Color.cpp
	CommandLine.cpp
	Common.cpp
	Complex.cpp
	Composer.cpp
	CRC32.cpp
	DateTime.cpp
	DeclArg.cpp
	DeclBlock.cpp
	DeclCallable.cpp
	Directory.cpp
	DirectoryDummy.cpp
	DottedSymbol.cpp
	DumpStyle.cpp
	Error.cpp
	Expr.cpp
	Formatter.cpp
	Frame.cpp
	Function.cpp
	FunctionCustom.cpp
	Half.cpp
	Help.cpp
	Image.cpp
	ImageMgr.cpp
	ImageMgrCustom.cpp
	Index.cpp
	Iterator.cpp
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
	Processor.cpp
	PropSlot.cpp
	PropSlotCustom.cpp
	PUnit.cpp
	Random.cpp
	Rational.cpp
	Referable.cpp
	Stat.cpp
	Stream.cpp
	String.cpp
	StringPicker.cpp
	StringStyle.cpp
	SuffixMgr.cpp
	Symbol.cpp
	Symbols.cpp
	Template.cpp
	ThreadCustom.cpp
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
	Vertex.cpp
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
	VType_DeclArg.cpp
	VType_Dict.cpp
	VType_Directory.cpp
	VType_Error.cpp
	VType_ErrorType.cpp
	VType_Expr.cpp
	VType_Frame.cpp
	VType_Scope.cpp
	VType_Function.cpp
	VType_Help.cpp
	VType_Image.cpp
	VType_ImageMgr.cpp
	VType_Index.cpp
	VType_Iterator.cpp
	VType_KeyValuePair.cpp
	VType_List.cpp
	VType_MemoryPool.cpp
	VType_Module.cpp
	VType_Nil.cpp
	VType_Number.cpp
	VType_NumberTrait.cpp
	VType_Object.cpp
	VType_Operator.cpp
	VType_Palette.cpp
	VType_PathMgr.cpp
	VType_Pixel.cpp
	VType_Pointer.cpp
	VType_PropSlot.cpp
	VType_PUnit.cpp
	VType_Quote.cpp
	VType_Random.cpp
	VType_Rational.cpp
	VType_Semaphore.cpp
	VType_Stat.cpp
	VType_Stream.cpp
	VType_String.cpp
	VType_StringPtr.cpp
	VType_Symbol.cpp
	VType_Template.cpp
	VType_Thread.cpp
	VType_TimeDelta.cpp
	VType_Tuple.cpp
	VType_Undefined.cpp
	VType_Vertex.cpp
	VType_VType.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
target_link_libraries(guraxcore PRIVATE
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:dl>
	$<$<PLATFORM_ID:Linux>:pthread>
	$<$<PLATFORM_ID:Darwin>:dl>
	$<$<PLATFORM_ID:Darwin>:pthread>)
if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
	set_target_properties(guraxcore PROPERTIES
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION}
		BUILD_WITH_INSTALL_NAME_DIR	1
		INSTALL_NAME_DIR "@executable_path/../lib")
endif ()
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS guraxcore
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
)
#-------------------------------------------------------------------------------
# Built-in Module
#-------------------------------------------------------------------------------
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
