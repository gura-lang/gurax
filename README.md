# Gurax Programming Language

**Gurax** is a programming language that provides powerful functions for the generation and processing of iterators.

The following **Gurax** code prints content of a text file with line numbers.

```java
Printf('%d %s', 1.., ReadLines('foo.txt'))
```

Installation on Windows
------------------------
For Windows, download the following installer to install Gurax.

▶️ [gurax-0.1.0-x64.exe](https://github.com/gura-lang/gurax/releases/download/0.1.0/gurax-0.1.0-x64.exe)

To get a quick start, download the following sample archive that contains Gurax scripts.

▶️ [gurax-sample.zip](https://github.com/gura-lang/gurax/releases/download/0.1.0/gurax-sample.zip)

Following is an example to see a sample GUI application that demonstrates the use of the Cairo graphics library.

```bash
$ cd gurax-sample/cairo
$ gurax SampleGUI.gura
```

![SampleGUI](/image/SampleGUI.png)

`gurax-sample/test` directory contains regression tests for Gurax, which can also be a good reference to learn Gurax programming. For instance, `gurax-sample/test/test-Iterator.gura` demonstrates various ways to use iterators in Gurax.

Build for Windows
-----------------
1. Clone the Gurax source code from GitHub repository.

   ```bash
   $ git clone --depth 1 https://github.com/gura-lang/gurax.git
   ```

2. Run the PowerShell script `gurax\guest\prepare-for-mswin.ps1` to create all the necessary guest libraries.

3. Move to the directory `gurax` and run the following commands:

   ```bash
   $ cmake -B build
   $ cmake --build build --config Release
   $ cmake --build build --config Release --target install
   ```

   When you use Visual Source Code to build it, make sure to do the command `CMake: Select Variant` and choose `Release`.

Setup Build Environment on Windows
---------------------------------
To build Gurax on Windows, you need to set up the build environment as follows:

1. Install meson, ninja, and setuptools using pip:

   ```bash
   $ pip install meson ninja --target DIRECTORY
   $ pip install setuptools
   ```

   and add `DIRECTORY` to the PATH environment variable.
