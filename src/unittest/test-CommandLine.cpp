//==============================================================================
// test-CommandLine.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(CommandLine)
{
	auto Tester = [](CommandLine& cmdLine, int argc, const char* argv[]) {
		::printf("--------\n");
		::printf("argc=%d:", argc);
		for (int i = 0; i < argc; i++) {
			::printf(" %s", argv[i]);
		}
		::printf("\n");
		cmdLine.ClearMap();
		if (!cmdLine.Parse(argc, argv)) {
			::printf("Error: %s\n", cmdLine.GetError());
			return;
		}
		::printf("argc=%d:", argc);
		for (int i = 0; i < argc; i++) {
			::printf(" %s", argv[i]);
		}
		::printf("\n");
		::printf("  flag_a %d\n", cmdLine.GetBool("flag_a"));
		::printf("  flag_b %d\n", cmdLine.GetBool("flag_b"));
		::printf("  flag_c %d\n", cmdLine.GetBool("flag_c"));
		::printf("  str_d  %s\n", cmdLine.GetString("str_d", "(none)"));
		::printf("  str_e  %s\n", cmdLine.GetString("str_e", "(none)"));
		::printf("  str_f  %s\n", cmdLine.GetString("str_f", "(none)"));
		::printf("  int_g  %d\n", cmdLine.GetInt("int_g", 0));
		::printf("  int_h  %d\n", cmdLine.GetInt("int_h", 0));
		::printf("  int_i  %d\n", cmdLine.GetInt("int_i", 0));
		::printf("  mstr_j");
		for (auto str : cmdLine.GetStringList("mstr_j")) ::printf(" %s", str.c_str());
		::printf("\n");
	};
	CommandLine cmdLine;
	cmdLine
		.OptBool("flag_a", 'a')
		.OptBool("flag_b", 'b')
		.OptBool("flag_c", 'c')
		.OptString("str_d", 'd')
		.OptString("str_e", 'e')
		.OptString("str_f", 'f')
		.OptInt("int_g", 'g')
		.OptInt("int_h", 'h')
		.OptInt("int_i", 'i')
		.OptMultiString("mstr_j", 'j');
	do {
		const char* argv[] = {"gurax"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--flag_a"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "-a"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--str_d=value"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "-dvalue", "-e", "value2"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--int_g=123"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "-g123", "-h", "456"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--flag_a", "--str_d=value", "--int_g=1234"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {
			"gurax",
			"--flag_a", "--flag_b", "--flag_c",
			"--str_d=value1", "--str_e=value2", "--str_f=value3",
			"--int_g=123", "--int_h=456", "--int_i=789",
		};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--mstr_j=aaa", "--mstr_j=bbb", "-jccc", "-j", "ddd"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--hoge"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--str_d=aaa", "--str_d=bbb"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "-daaa", "-dbbb"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
	do {
		const char* argv[] = {"gurax", "--int_g=a123"};
		int argc = Gurax_ArraySizeOf(argv);
		Tester(cmdLine, argc, argv);
	} while (0);
}

}
