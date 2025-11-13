# Gurax Programming Language

**Gurax** is a programming language that provides powerful functions for the generation and processing of iterators.

The following **Gurax** code prints content of a text file with line numbers.

```java
Printf('%d %s', 1.., ReadLines('foo.txt'))
```

Installation
------------
Fow Windows, download the following installer for installation.

- [gurax-0.1.0-x64.exe](https://github.com/gura-lang/gurax/releases/download/0.1.0/gurax-0.1.0-x64.exe)

To get a quick start, download the following sample archive that contains Gurax scripts and try them.

- [gurax-sample.zip](https://github.com/gura-lang/gurax/releases/download/0.1.0/gurax-sample.zip)

For instance, run `gurax gurax-sample/sample/cairo/SampleGUI.gura` to see a sample GUI application that uses the Cairo graphics library.

![SampleGUI](/image/SampleGUI.png)

Build for Windows
-----------------
1. Clone the Gurax source code from GitHub repository.

   ```text
   $ git clone --depth 1 https://github.com/gura-lang/gurax.git
   ```

2. Run the PowerShell script `gurax\guest\prepare-for-mswin.ps1` to create all the necessary guest libraries.

3. Move to the directory `gurax` and run the following commands:

   ```text
   $ cmake -B build
   $ cmake --build build --config Release
   $ cmake --build build --config Release --target install
   ```

   When you use Visual Source Code to build it, make sure to do the command `CMake: Select Variant` and choose `Release`.

Setup Build Environment on Windows
---------------------------------
To build Gurax on Windows, you need to set up the build environment as follows:

1. Install meson, ninja, and setuptools using pip:

   ```text
   $ pip install meson ninja --target DIRECTORY
   $ pip install setuptools
   ```

   and add `DIRECTORY` to the PATH environment variable.
