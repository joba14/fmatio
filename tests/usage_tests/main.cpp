
/**
 * @file main.h
 * 
 * @copyright This file is part of the "Fmatio" project and is distributed under
 * "Fmatio GPLv1" license.
 * 
 * @author joba14
 * 
 * @date 2023-11-09
 */

#include <fmatio.hpp>

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