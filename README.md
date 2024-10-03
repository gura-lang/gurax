# Gurax Programming Language

**Gurax** is a programming language that provides powerful functions for the generation and processing of iterators.

The following **Gurax** code prints content of a text file with line numbers.

    Printf('%d %s', 1.., ReadLines('foo.txt'))

Build for Windows
-----------------
1. Clone the Gurax source code from GitHub repository.

        $ git clone --depth 1 https://github.com/gura-lang/gurax.git

2. Run the PowerShell script `gurax\guest\prepare-for-mswin.ps1` to create all the necessary guest libraries.

3. Move to the directory `gurax` and run the following commands:

        $ cmake -B build
		$ cmake --build build --config Release
		$ cmake --build build --config Release --target install

   When you use Visual Source Code to build it, make sure to do the command `CMake: Select Variant` and choose `Release`.
