
<!--
<a href="https://gitlab.com/joba14/fmatio">
	<img src="./logo.svg" alt="Logo" width="400">
</a>
-->

[![License](https://img.shields.io/badge/license-Fmatio_GPLv1-brightgreen.svg?style=for-the-badge)](./license.md)
![Language Support](https://img.shields.io/badge/languages-CPP-brightgreen.svg?style=for-the-badge)
![Platform Support](https://img.shields.io/badge/platforms-Linux_|_Windows-brightgreen.svg?style=for-the-badge)

# Fmatio
**The Fmatio formatting library for C++**<br>[Report a bug](https://github.com/joba14/fmatio/issues/new) · [Request a feature](https://github.com/joba14/fmatio/issues/new)


## Table of Contents
 - [Overview](#overview)
 - [Features](#features)
 - [Getting Started](#getting-started)
 - [License](#license)


## Overview
The **fmatio** library is a conceptual, header-only, C++ formatting library designed to simplify the process of formatting strings in C++ applications. It provides a flexible and intuitive way to handle string formatting, making it easy for developers to create well-formatted and readable output.

[(to the top)](#fmatio)


## Features
The library consists of the following features:
- Simple Syntax: With fmatio, you can format strings using a straightforward and easy-to-understand syntax, reducing the complexity of your code.
- Universal API: The library provides various functions for formatting in various circumstances (using heap, stack, printing, or just formattign and saving the result)
- Type-Safe Formatting: The library ensures type safety, preventing common formatting errors and improving the robustness of your code.
- Extensibility: fmatio is designed to be extensible, allowing you to define custom formatting options and adapt the library to your specific needs. In addition, the library provides the user with default formatters for most of the c++'s stdlib's containers.

[(to the top)](#fmatio)


## Getting Started

### Installation
To use fmatio in your C++ project, follow these simple steps:
- Download the Source Code:Clone the fmatio repository from GitHub or download the latest release.
- Include in Your Project: Add the fmatio source files to your project.
- Include the Header File: Include the fmatio header file in your C++ source files where you want to use the formatting library.

### Formatting Strings
Using fmatio is straightforward. Here's a basic example:
```cpp
#include "fmatio.hpp"
#include <iostream>

signed int main(void)
{
	const int32_t value = 42;
	std::string message = fmatio::format("The answer is: {}", value);
	std::cout << message << std::endl;
	return 0;
}
```

### Customization
fmatio allows you to customize formatting options. For example:
```cpp
#include "fmatio.hpp"
#include <iostream>

struct Vec3f { float x, y, z; };

struct_CUSTOM_FORMAT_OF(NONE, Vec3f);
struct_CUSTOM_FORMATTER(NONE, Vec3f,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const Vec3f& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<float>::format(pContext COMMA pValue.x);
		Formatter<char>::format(pContext COMMA ' ');
		Formatter<float>::format(pContext COMMA pValue.y);
		Formatter<char>::format(pContext COMMA ' ');
		Formatter<float>::format(pContext COMMA pValue.z);
		Formatter<char>::format(pContext COMMA ']');
	}
);

signed int main(const int argc, const char* const * const argv)
{
	const Vec3f v = { 1, 2, 3 };
	std::string message = fmatio::format("The vector is: {}", v);
	std::cout << message << std::endl;
	return 0;
}
```

[(to the top)](#fmatio)


## License
The Fmatio project is released under the **Fmatio GPLv1** license. Users and contributors are required to review and comply with the license terms specified in the [license.md file](./license.md). The license outlines the permitted usage, distribution, and intellectual property rights associated with the Fmatio project.

Please refer to the [license.md file](./license.md) for more details. By using, modifying, or distributing the Fmatio project, you agree to be bound by the terms and conditions of the license.

[(to the top)](#fmatio)
