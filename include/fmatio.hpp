
/**
 * @file fmatio.h
 * 
 * @copyright This file is part of the "Fmatio" project and is distributed under
 * "Fmatio GPLv1" license.
 * 
 * @author joba14
 * 
 * @date 2023-11-09
 */

#ifndef __FMATIO_HPP__
#define __FMATIO_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <cstdint>
#include <cstdio>
#include <cmath>

#ifndef FMATIO_CLANG_VERSION
#	if defined(__clang__) && !defined(__ibmxl__)
#		define FMATIO_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#	else
#		define FMATIO_CLANG_VERSION 0
#	endif
#endif

#ifndef FMATIO_GCC_VERSION
#	if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)
#		define FMATIO_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#	else
#		define FMATIO_GCC_VERSION 0
#	endif
#endif

#ifndef FMATIO_GCC_PRAGMA
#	if FMATIO_GCC_VERSION >= 504
#		define FMATIO_GCC_PRAGMA(arg) _Pragma(arg)
#	else
#		define FMATIO_GCC_PRAGMA(arg)
#	endif
#endif

#ifndef FMATIO_ICC_VERSION
#	ifdef __ICL
#		define FMATIO_ICC_VERSION __ICL
#	elif defined(__INTEL_COMPILER)
#		define FMATIO_ICC_VERSION __INTEL_COMPILER
#	else
#		define FMATIO_ICC_VERSION 0
#	endif
#endif

#ifndef FMATIO_NVCOMPILER_VERSION
#	ifdef __NVCOMPILER
#		define FMATIO_NVCOMPILER_VERSION (__NVCOMPILER_MAJOR__ * 100 + __NVCOMPILER_MINOR__)
#	else
#		define FMATIO_NVCOMPILER_VERSION 0
#	endif
#endif

#ifndef FMATIO_NVCC
#	ifdef __NVCC__
#		define FMATIO_NVCC __NVCC__
#	else
#		define FMATIO_NVCC 0
#	endif
#endif

#ifndef FMATIO_MSC_VER
#	ifdef _MSC_VER
#		define FMATIO_MSC_VER _MSC_VER
#	else
#		define FMATIO_MSC_VER 0
#	endif
#endif

#ifndef FMATIO_MSC_WARNING
#	ifdef _MSC_VER
#		define FMATIO_MSC_WARNING(...) __pragma(warning(__VA_ARGS__))
#	else
#		define FMATIO_MSC_WARNING(...)
#	endif
#endif

#ifndef FMATIO_HAS_FEATURE
#	ifdef __has_feature
#		define FMATIO_HAS_FEATURE(x) __has_feature(x)
#	else
#		define FMATIO_HAS_FEATURE(x) 0
#	endif
#endif

#ifndef FMATIO_CPLUSPLUS
#	ifdef _MSVC_LANG
#		define FMATIO_CPLUSPLUS _MSVC_LANG
#	else
#		define FMATIO_CPLUSPLUS __cplusplus
#	endif
#endif

#ifndef FMATIO_HAS_CPP_ATTRIBUTE
#	ifdef __has_cpp_attribute
#		define FMATIO_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#	else
#		define FMATIO_HAS_CPP_ATTRIBUTE(x) 0
#	endif
#endif

#ifndef FMATIO_HAS_CPP14_ATTRIBUTE
#	define FMATIO_HAS_CPP14_ATTRIBUTE(attribute) (FMATIO_CPLUSPLUS >= 201402L && FMATIO_HAS_CPP_ATTRIBUTE(attribute))
#endif

#ifndef FMATIO_HAS_CPP17_ATTRIBUTE
#	define FMATIO_HAS_CPP17_ATTRIBUTE(attribute) (FMATIO_CPLUSPLUS >= 201703L && FMATIO_HAS_CPP_ATTRIBUTE(attribute))
#endif

#ifndef FMATIO_USE_CONSTEXPR
#	define FMATIO_USE_CONSTEXPR (FMATIO_HAS_FEATURE(cxx_relaxed_constexpr) || FMATIO_MSC_VER >= 1912 || (FMATIO_GCC_VERSION >= 600 && __cplusplus >= 201402L)) && !FMATIO_NVCC && !FMATIO_ICC_VERSION
#endif

#ifdef FMATIO_USE_CONSTEXPR
#	if FMATIO_USE_CONSTEXPR
#		define FMATIO_CONSTEXPR constexpr
#		define FMATIO_CONSTEXPR_DECL constexpr
#	else
#		define FMATIO_CONSTEXPR
#		define FMATIO_CONSTEXPR_DECL
#	endif
#endif

#ifndef FMATIO_NOEXCEPT
#	if defined(_MSC_VER) && (_MSC_VER < 1900)
#		define FMATIO_NOEXCEPT _NOEXCEPT
#	else
#		define FMATIO_NOEXCEPT noexcept
#	endif
#endif

#ifndef FMATIO_INLINE
# 	if FMATIO_GCC_VERSION || FMATIO_CLANG_VERSION
#		define FMATIO_INLINE inline __attribute__((always_inline))
#	else
#		define FMATIO_INLINE inline
#	endif
#endif

#ifndef FMATIO_NOINLINE
#	if FMATIO_GCC_VERSION || FMATIO_CLANG_VERSION
#		define FMATIO_NOINLINE __attribute__((noinline))
#	else
#		define FMATIO_NOINLINE
#	endif
#endif

#ifndef FMATIO_NORETURN
#	if FMATIO_EXCEPTIONS && FMATIO_HAS_CPP_ATTRIBUTE(noreturn) && !FORMAT_MSC_VER && !FORMAT_NVCC
#		define FMATIO_NORETURN [[noreturn]]
#	else
#		define FMATIO_NORETURN
#	endif
#endif

#ifndef FMATIO_NODISCARD
#	if FMATIO_HAS_CPP17_ATTRIBUTE(nodiscard)
#		define FMATIO_NODISCARD [[nodiscard]]
#	else
#		define FMATIO_NODISCARD
#	endif
#endif

#ifndef FMATIO_DEPRECATED
#	if FMATIO_HAS_CPP14_ATTRIBUTE(deprecated) || FMATIO_MSC_VER >= 1900
#		define FMATIO_DEPRECATED [[deprecated]]
#	else
#		if (defined(__GNUC__) && !defined(__LCC__)) || defined(__clang__)
#			define FMATIO_DEPRECATED __attribute__((deprecated))
#		elif FMATIO_MSC_VER
#			define FMATIO_DEPRECATED __declspec(deprecated)
#		else
#			define FMATIO_DEPRECATED /* deprecated */
#		endif
#	endif
#endif

#ifndef FMATIO_DEBUG
#	if _MSC_VER
#		define FMATIO_DEBUG _DEBUG
#	else
#		define FMATIO_DEBUG NDEBUG
#	endif
#endif

#if _WIN32
#	define FMATIO_WINDOWS 1
#else
#	define FMATIO_UNIX 1
#endif

#ifndef FMATIO_COMMA
#	define FMATIO_COMMA ,
#endif

#ifndef COMMA
#	define COMMA FMATIO_COMMA
#endif

#ifndef NONE
#	define NONE
#endif

namespace fmatio
{
	namespace details
	{
		using null = decltype(nullptr);
		using byte = uint8_t;
		using ldouble = long double;

		namespace ascii
		{
			static FMATIO_INLINE FMATIO_CONSTEXPR uint64_t length(const char* pString) FMATIO_NOEXCEPT
			{
				uint64_t count = 0;
				while (pString[count]) count++;
				return count;
			}

			static FMATIO_INLINE FMATIO_CONSTEXPR char* fill(char* pString, char pValue, uint64_t pCount) FMATIO_NOEXCEPT
			{
				char* head = pString;
				for (uint64_t index = 0; index < pCount; index++) head[index] = pValue;
				return pString;
			}

			static FMATIO_INLINE FMATIO_CONSTEXPR char* copy(char* pDestination, const char* pSource) FMATIO_NOEXCEPT
			{
				char* head = pDestination;
				while((*pDestination++ = *pSource++) != '\0');
				return head;
			}

			static FMATIO_INLINE FMATIO_CONSTEXPR char* copy(char* pDestination, const char* pSource, uint64_t pCount) FMATIO_NOEXCEPT
			{
				char* head = pDestination;
				for (uint64_t index = 0; index < pCount; index++) pDestination[index] = pSource[index];
				return head;
			}

			static FMATIO_INLINE FMATIO_CONSTEXPR void reverse(char* pString, uint64_t pLength) FMATIO_NOEXCEPT
			{
				uint64_t start = 0;
				uint64_t end = pLength - 1u;

				while (start < end)
				{
					char temp = pString[start];
					pString[start++] = pString[end];
					pString[end--] = temp;
				}
			}

			static FMATIO_INLINE FMATIO_CONSTEXPR uint64_t itoar(uint64_t pValue, char* pString, uint64_t pBase) FMATIO_NOEXCEPT
			{
				uint64_t index = 0;
				bool isNegative = false;

				if (pValue == 0)
				{
					pString[index++] = '0';
					pString[index] = '\0';
					return index;
				}
			
				if (pValue < 0 && pBase == 10u)
				{
					isNegative = true;
					pValue = -pValue;
				}
			
				while (pValue != 0)
				{
					int32_t remainder = pValue % pBase;
					pString[index++] = (remainder > 9u) ? (remainder - 10u) + 'a' : remainder + '0';
					pValue /= pBase;
				}
			
				if (isNegative)
					pString[index++] = '-';
			
				pString[index] = '\0';
				return index;
			}
		}

		template<typename OldT>
		struct RemoveConst
		{
		public:
			using Type = OldT;
		};
		
		template<typename OldT>
		struct RemoveConst<const OldT>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveVolatile
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveVolatile<volatile OldT>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveConstVolatile
		{
		public:
			using Type = typename RemoveConst<typename RemoveVolatile<OldT>::Type>::Type;
		};

		template<typename OldT>
		struct RemoveReference
		{
		public:
			using Type = OldT;
		};
		
		template<typename OldT>
		struct RemoveReference<OldT&>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveReference<OldT&&>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT, OldT tValue>
		struct IntegralConstant
		{
		public:
			using Type = OldT;

		public:
			static FMATIO_CONSTEXPR const OldT sValue = tValue;

			static FMATIO_INLINE FMATIO_CONSTEXPR const OldT value() FMATIO_NOEXCEPT
			{ return sValue; }
		};

		template<bool tValue>
		using BoolConstant = IntegralConstant<bool, tValue>;

		using TrueType = IntegralConstant<bool, true>;

		using FalseType = IntegralConstant<bool, false>;

		template<bool, typename, typename>
		struct Conditional;

		template<typename>
		struct IsLValueReference;

		template<typename>
		struct IsRValueReference;

		template<bool tCondition, typename IfTrue, typename IfFalse>
		struct Conditional
		{
		public:
			using Type = IfTrue;
		};

		template<typename IfTrue, typename IfFalse>
		struct Conditional<false, IfTrue, IfFalse>
		{
		public:
			using Type = IfFalse;
		};

		template<typename...>
		struct Or;

		template<>
		struct Or<>
			: public FalseType
		{ };

		template<typename First>
		struct Or<First>
			: public First
		{ };

		template<typename First, typename Second>
		struct Or<First, Second>
			: public Conditional<First::sValue, First, Second>::Type
		{ };

		template<typename First, typename Second, typename Third, typename... Other>
		struct Or<First, Second, Third, Other...>
			: public Conditional<First::sValue, First, Or<Second, Third, Other...>>::Type
		{ };

		template<typename...>
		struct And;

		template<>
		struct And<>
			: public TrueType
		{ };

		template<typename First>
		struct And<First>
			: public First
		{ };

		template<typename First, typename Second>
		struct And<First, Second>
			: public Conditional<First::sValue, Second, First>::Type
		{ };

		template<typename First, typename Second, typename Third, typename... Other>
		struct And<First, Second, Third, Other...>
			: public Conditional<First::sValue, And<Second, Third, Other...>, First>::Type
		{ };

		template<typename Type>
		struct Not
			: public BoolConstant<!bool(Type::sValue)>
		{ };

		template<typename OldT>
		struct Identity
		{
		public:
			using Type = OldT;
		};

		template<typename>
		struct IsVoidHelper
			: public FalseType
		{ };

		template<>
		struct IsVoidHelper<void>
			: public TrueType
		{ };

		template<typename Type>
		struct IsVoid
			: public IsVoidHelper<typename RemoveConstVolatile<Type>::Type>
		{ };

		template<typename>
		struct IsFunction
			: public FalseType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<Result(Arguments...)>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<Result(Arguments...)&>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<Result(Arguments...)&&>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<const Result(Arguments...)>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<const Result(Arguments...)&>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<const Result(Arguments...)&&>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<volatile Result(Arguments...)>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<volatile Result(Arguments...)&>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<volatile Result(Arguments...)&&>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<const volatile Result(Arguments...)>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<const volatile Result(Arguments...)&>
			: public TrueType
		{ };

		template<typename Result, typename... Arguments>
		struct IsFunction<const volatile Result(Arguments...)&&>
			: public TrueType
		{ };

		template<typename Type>
		struct IsReference
			: public Or<IsLValueReference<Type>, IsRValueReference<Type>>
		{ };

		template<typename Type>
		struct IsObject
			: public Not<Or<IsFunction<Type>, IsReference<Type>, IsVoid<Type>>>
		{ };

		template<typename Type>
		struct IsReferenceable
			: public Or<IsObject<Type>, IsReference<Type>>
		{ };

		template<typename Result, typename... Arguments>
		struct IsReferenceable<Result(Arguments...)>
			: public TrueType
		{ };

		template<typename>
		struct IsLValueReference
			: public FalseType
		{ };

		template<typename Type>
		struct IsLValueReference<Type&>
			: public TrueType
		{ };

		template<typename>
		struct IsRValueReference
			: public FalseType
		{ };

		template<typename Type>
		struct IsRValueReference<Type&&>
			: public TrueType
		{ };

		template<bool, typename OldT = void>
		struct EnableIf { };

		template<typename OldT>
		struct EnableIf<true, OldT>
		{
		public:
			using Type = OldT;
		};

		template<typename Type>
		static FMATIO_INLINE FMATIO_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::sValue, Type&&>::Type forward(typename Identity<Type>::Type& pValue) FMATIO_NOEXCEPT
		{
			return static_cast<Type&&>(pValue);
		}

		template<typename Type>
		static FMATIO_INLINE FMATIO_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::sValue, Type&&>::Type forward(typename Identity<Type>::Type&& pValue) FMATIO_NOEXCEPT
		{
			return static_cast<Type&&>(pValue);
		}

		template<typename Type>
		static FMATIO_INLINE FMATIO_CONSTEXPR typename EnableIf<IsLValueReference<Type>::sValue, Type>::Type forward(typename Identity<Type>::Type pValue) FMATIO_NOEXCEPT
		{
			return pValue;
		}

		template<typename Type>
		static FMATIO_INLINE FMATIO_CONSTEXPR typename EnableIf<IsLValueReference<Type>::sValue, Type>::Type forward(typename RemoveReference<Type>::Type&& pValue) FMATIO_NOEXCEPT = delete;

		template<typename Type>
		static FMATIO_INLINE FMATIO_CONSTEXPR typename RemoveReference<Type>::Type&& move(Type&& pValue) FMATIO_NOEXCEPT
		{
			return static_cast<typename RemoveReference<Type>::Type&&>(pValue);
		}
	}

	enum class FormatArgumentType : uint8_t
	{
		None = 0,
		Bool,
		Char,
		Int8,
		UInt8,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float,
		Double,
		LDouble,
		Pointer,
		Array,
		CString,
		Custom
	};

	template<typename Type>
	struct FormatOf
	{
	public:
		static FMATIO_CONSTEXPR const FormatArgumentType sValue = FormatArgumentType::None;

		static FMATIO_INLINE FMATIO_CONSTEXPR const FormatArgumentType value() FMATIO_NOEXCEPT
		{ return sValue; }
	};

	#define __struct_INTERNAL_FORMAT_OF(Dependencies, Type, FType) \
		template<Dependencies> \
		struct FormatOf<Type> \
		{ \
		public: \
			static FMATIO_CONSTEXPR const FormatArgumentType sValue = FType; \
			\
			static FMATIO_INLINE FMATIO_CONSTEXPR FormatArgumentType value() FMATIO_NOEXCEPT \
			{ return sValue; } \
		}

	__struct_INTERNAL_FORMAT_OF(NONE, bool, FormatArgumentType::Bool);
	__struct_INTERNAL_FORMAT_OF(NONE, char, FormatArgumentType::Char);
	__struct_INTERNAL_FORMAT_OF(NONE, int8_t, FormatArgumentType::Int8);
	__struct_INTERNAL_FORMAT_OF(NONE, uint8_t, FormatArgumentType::UInt8);
	__struct_INTERNAL_FORMAT_OF(NONE, int16_t, FormatArgumentType::Int16);
	__struct_INTERNAL_FORMAT_OF(NONE, uint16_t, FormatArgumentType::UInt16);
	__struct_INTERNAL_FORMAT_OF(NONE, int32_t, FormatArgumentType::Int32);
	__struct_INTERNAL_FORMAT_OF(NONE, uint32_t, FormatArgumentType::UInt32);
	__struct_INTERNAL_FORMAT_OF(NONE, int64_t, FormatArgumentType::Int64);
	__struct_INTERNAL_FORMAT_OF(NONE, uint64_t, FormatArgumentType::UInt64);
	__struct_INTERNAL_FORMAT_OF(NONE, float, FormatArgumentType::Float);
	__struct_INTERNAL_FORMAT_OF(NONE, double, FormatArgumentType::Double);
	__struct_INTERNAL_FORMAT_OF(NONE, details::ldouble, FormatArgumentType::LDouble);
	__struct_INTERNAL_FORMAT_OF(typename Type, Type*, FormatArgumentType::Pointer);
	__struct_INTERNAL_FORMAT_OF(typename Type, const Type*, FormatArgumentType::Pointer);
	__struct_INTERNAL_FORMAT_OF(NONE, details::null, FormatArgumentType::Pointer);
	__struct_INTERNAL_FORMAT_OF(NONE, const char*, FormatArgumentType::CString);
	__struct_INTERNAL_FORMAT_OF(NONE, const char[], FormatArgumentType::CString);
	__struct_INTERNAL_FORMAT_OF(uint32_t tSize, const char[tSize], FormatArgumentType::CString);

	struct FormatterHelpers
	{
	public:
		template<typename Context>
		static FMATIO_INLINE FMATIO_CONSTEXPR void parseIgnore(Context& pContext) FMATIO_NOEXCEPT
		{
			for (; *pContext != '}'; ++pContext);
			++pContext;
		}
	};

	template<typename Type, typename Enabler = void>
	struct Formatter
	{
		static_assert(FormatOf<Type>::value() != FormatArgumentType::None, "Provided type does not have a formatter!");
	};

	template<typename Type>
	using FormatterEnabler = typename details::EnableIf
	<
		details::BoolConstant
		<
			details::IntegralConstant
			<
				FormatArgumentType,
				FormatOf<Type>::value()
			>::value() != FormatArgumentType::None
		>::value()
	>::Type;

	#define __struct_INTERNAL_FORMATTER(Dependencies, Type, PFunc, FFunc) \
	template<Dependencies> \
	struct Formatter<Type, FormatterEnabler<Type>> \
	{ \
	public: \
		template<typename Context> \
		static PFunc \
			\
		template<typename Context> \
		static FFunc \
	}

	__struct_INTERNAL_FORMATTER(NONE, bool,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA bool pValue) FMATIO_NOEXCEPT
		{
			pContext.append(pValue ? "true" : "false" FMATIO_COMMA pValue ? 4u : 5u);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, char,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA char pValue) FMATIO_NOEXCEPT
		{
			pContext.append(pValue);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, int8_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA int8_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 33u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(pValue FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, uint8_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA uint8_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 33u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(pValue FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, int16_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA int16_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 33u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(pValue FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, uint16_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA uint16_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 33u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(pValue FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, int32_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA int32_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 33u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(pValue FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, uint32_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA uint32_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 33u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(pValue FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, int64_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA int64_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 65u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(static_cast<int32_t>(pValue) FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, uint64_t,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA uint64_t pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 65u;
			char buffer[size] = { };
			const uint32_t length = details::ascii::itoar(static_cast<int32_t>(pValue) FMATIO_COMMA buffer FMATIO_COMMA 10);
			pContext.appendReversed(buffer FMATIO_COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, float,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA float pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 65u;
			char buffer[size] = { };
			const int32_t written = ::snprintf(buffer FMATIO_COMMA size FMATIO_COMMA "%f" FMATIO_COMMA pValue);

			if (written >= 0)
			{
				pContext.append(buffer FMATIO_COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, double,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA double pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 65u;
			char buffer[size] = { };
			const int32_t written = ::snprintf(buffer FMATIO_COMMA size FMATIO_COMMA "%f" FMATIO_COMMA pValue);

			if (written >= 0)
			{
				pContext.append(buffer FMATIO_COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::ldouble,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA details::ldouble pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 65u;
			char buffer[size] = { };
			const int32_t written = ::snprintf(buffer FMATIO_COMMA size FMATIO_COMMA "%Lf" FMATIO_COMMA pValue);

			if (written >= 0)
			{
				pContext.append(buffer FMATIO_COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(typename Type, Type*,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA Type* pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 19u;
			char buffer[size] = { };
			const int32_t written = ::snprintf(buffer FMATIO_COMMA size FMATIO_COMMA "0x%p" FMATIO_COMMA (void*)pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer FMATIO_COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(typename Type, const Type*,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const Type* pValue) FMATIO_NOEXCEPT
		{
			const uint32_t size = 19u;
			char buffer[size] = { };
			const int32_t written = ::snprintf(buffer FMATIO_COMMA size FMATIO_COMMA "0x%p" FMATIO_COMMA (const void*)pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer FMATIO_COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::null,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA details::null pValue) FMATIO_NOEXCEPT
		{
			pContext.append("nullptr" FMATIO_COMMA 7u);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, const char*,
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const char* pValue) FMATIO_NOEXCEPT
		{
			pContext.append(pValue FMATIO_COMMA details::ascii::length(pValue));
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, const char[],
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const char pValue[]) FMATIO_NOEXCEPT
		{
			pContext.append(pValue FMATIO_COMMA details::ascii::length(pValue));
		}
	);

	__struct_INTERNAL_FORMATTER(uint32_t tSize, const char[tSize],
		FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const char pValue[tSize]) FMATIO_NOEXCEPT
		{
			pContext.append(pValue FMATIO_COMMA tSize - 1);
		}
	);

	struct ANSITextColor
	{
	public:
		static FMATIO_CONSTEXPR const char* reset = "\033[0m";
		static FMATIO_CONSTEXPR const char* black = "\033[30m";
		static FMATIO_CONSTEXPR const char* red = "\033[31m";
		static FMATIO_CONSTEXPR const char* green = "\033[32m";
		static FMATIO_CONSTEXPR const char* yellow = "\033[33m";
		static FMATIO_CONSTEXPR const char* blue = "\033[34m";
		static FMATIO_CONSTEXPR const char* magenta = "\033[35m";
		static FMATIO_CONSTEXPR const char* cyan = "\033[36m";
		static FMATIO_CONSTEXPR const char* white = "\033[37m";
	};

	struct ANSIBackgroundColor
	{
	public:
		static FMATIO_CONSTEXPR const char* reset = "\033[0m";
		static FMATIO_CONSTEXPR const char* black = "\033[40m";
		static FMATIO_CONSTEXPR const char* red = "\033[41m";
		static FMATIO_CONSTEXPR const char* green = "\033[42m";
		static FMATIO_CONSTEXPR const char* yellow = "\033[43m";
		static FMATIO_CONSTEXPR const char* blue = "\033[44m";
		static FMATIO_CONSTEXPR const char* magenta = "\033[45m";
		static FMATIO_CONSTEXPR const char* cyan = "\033[46m";
		static FMATIO_CONSTEXPR const char* white = "\033[47m";
	};

	struct ANSIDecorations
	{
	public:
		static FMATIO_CONSTEXPR const char reset[] = "\033[0m";
		static FMATIO_CONSTEXPR const char bold[] = "\033[1m";
		static FMATIO_CONSTEXPR const char underline[] = "\033[4m";
		static FMATIO_CONSTEXPR const char reversed[] = "\033[7m";
	};

	template<typename Iterator, typename Writer>
	static FMATIO_INLINE FMATIO_CONSTEXPR void formatHandle(Iterator pIterator, Writer& pWriter) FMATIO_NOEXCEPT
	{
		pWriter.append(pIterator, details::ascii::length(pIterator));
	}

	template<typename Iterator, typename Writer, typename Argument, typename... Arguments>
	static FMATIO_INLINE FMATIO_CONSTEXPR void formatHandle(Iterator pIterator, Writer& pWriter, Argument&& pArgument, Arguments&&... pArguments) FMATIO_NOEXCEPT
	{
		Iterator previous = pIterator;
		for (; *pIterator != '{' && pIterator; ++pIterator);

		if (*pIterator == '{')
		{
			pWriter.append(previous, static_cast<uint32_t>(pIterator - previous));
			using DRefArgument = typename details::RemoveConst<typename details::RemoveVolatile<typename details::RemoveReference<Argument>::Type>::Type>::Type;
			Formatter<DRefArgument>::template parse<Iterator>(pIterator);
			Formatter<DRefArgument>::template format<Writer>(pWriter, pArgument);
		}

		formatHandle<Iterator, Writer>(pIterator, pWriter, pArguments...);
	}

	class DynamicWriter
	{
	private:
		char* mData;
		uint64_t mSize;
		uint64_t mCapacity;

	public:
		explicit DynamicWriter(uint64_t pCapacity = 4u) FMATIO_NOEXCEPT
			: mData(nullptr), mSize(0), mCapacity(pCapacity)
		{
			allocate(pCapacity);
		}

	private:
		FMATIO_INLINE void allocate(uint64_t pCapacity) FMATIO_NOEXCEPT
		{
			this->mCapacity = pCapacity;
			this->mData = new char[pCapacity + 1u];
			this->mData[this->mSize] = details::move('\0');
		}

		FMATIO_INLINE void reallocate(uint64_t pCapacity) FMATIO_NOEXCEPT
		{
			char* local = new char[pCapacity + 1u];

			if (this->mSize > pCapacity)
				this->mSize = pCapacity;
			
			for (uint64_t index = 0; index < this->mSize; index++)
				local[index] = details::move(this->mData[index]);

			delete[] this->mData;
			this->mCapacity = pCapacity;
			this->mData = local;
		}

	public:
		FMATIO_INLINE FMATIO_CONSTEXPR uint64_t size() const FMATIO_NOEXCEPT
		{
			return this->mSize;
		}

		FMATIO_INLINE void FMATIO_CONSTEXPR append(char pChar) FMATIO_NOEXCEPT
		{
			if (this->mSize + 1u > this->mCapacity)
				reallocate(this->mCapacity + this->mCapacity / 2);
			
			this->mData[this->mSize++] = pChar;
		}

		FMATIO_INLINE FMATIO_CONSTEXPR void append(const char* const pData, uint64_t pSize) FMATIO_NOEXCEPT
		{
			if (this->mSize + pSize > this->mCapacity)
				reallocate(pSize + this->mCapacity + this->mCapacity / 2);

			for (uint64_t index = 0; index < pSize; index++)
				this->mData[this->mSize + index] = pData[index];

			this->mSize += pSize;
		}

		FMATIO_INLINE FMATIO_CONSTEXPR void appendReversed(const char* const pData, uint64_t pSize) FMATIO_NOEXCEPT
		{
			if (this->mSize + pSize > this->mCapacity)
				reallocate(pSize + this->mCapacity + this->mCapacity / 2);

			for (uint64_t index = 0; index < pSize; index++)
				this->mData[this->mSize + index] = pData[pSize - index - 1u];

			this->mSize += pSize;
		}

		FMATIO_INLINE FMATIO_CONSTEXPR char* get() FMATIO_NOEXCEPT
		{
			this->mData[this->mSize] = '\0';
			return this->mData;
		}
	};

	class StaticWriter
	{
	private:
		char* mData;
		uint64_t mSize;
		uint64_t mCapacity;

	public:
		explicit StaticWriter(char* pData, uint64_t pCapacity) FMATIO_NOEXCEPT
			: mData(pData), mSize(0), mCapacity(pCapacity)
		{ }

	public:
		FMATIO_INLINE FMATIO_CONSTEXPR uint64_t size() const FMATIO_NOEXCEPT
		{
			return this->mSize;
		}
		
		FMATIO_INLINE FMATIO_CONSTEXPR void append(char pChar) FMATIO_NOEXCEPT
		{
			if (this->mSize + 1u <= this->mCapacity + 1u)
				this->mData[this->mSize++] = pChar;
		}

		FMATIO_INLINE FMATIO_CONSTEXPR void append(const char* const pData, uint64_t pSize) FMATIO_NOEXCEPT
		{
			if (this->mSize + pSize <= this->mCapacity + 1u)
			{
				for (uint64_t index = 0; index < pSize; index++)
					this->mData[this->mSize + index] = pData[index];
				
				this->mSize += pSize;
			}
		}

		FMATIO_INLINE FMATIO_CONSTEXPR void appendReversed(const char* const pData, uint64_t pSize) FMATIO_NOEXCEPT
		{
			if (this->mSize + pSize <= this->mCapacity + 1u)
			{
				for (uint64_t index = 0; index < pSize; index++)
					this->mData[this->mSize + index] = pData[pSize - index - 1u];
				
				this->mSize += pSize;
			}
		}

		FMATIO_INLINE FMATIO_CONSTEXPR char* get() FMATIO_NOEXCEPT
		{
			this->mData[this->mSize] = '\0';
			return this->mData;
		}
	};

	template<typename... Arguments>
	static FMATIO_INLINE char* format(const char* const pPattern, Arguments&&... pArguments) FMATIO_NOEXCEPT
	{
		DynamicWriter writer = DynamicWriter(details::ascii::length(pPattern) + sizeof...(pArguments) * 2u);
		formatHandle<const char*, DynamicWriter, Arguments...>(pPattern, writer, details::forward<Arguments>(pArguments)...);
		return writer.get();
	}

	template<typename... Arguments>
	static FMATIO_INLINE uint64_t formatTo(char pBuffer[], uint64_t pSize, const char* const pPattern, Arguments&&... pArguments) FMATIO_NOEXCEPT
	{
		StaticWriter writer = StaticWriter(pBuffer, pSize);
		formatHandle<const char*, StaticWriter, Arguments...>(pPattern, writer, details::forward<Arguments>(pArguments)...);
		return writer.size();
	}

	template<typename Stream, typename... Arguments>
	static FMATIO_INLINE void print(Stream& pStream, const char* const pPattern, Arguments&&... pArguments) FMATIO_NOEXCEPT
	{
		char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
		pStream << formatted;
		delete[] formatted;
	}

	template<typename... Arguments>
	static FMATIO_INLINE void cprint(::FILE* pStream, const char* const pPattern, Arguments&&... pArguments) FMATIO_NOEXCEPT
	{
		char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
		::fwrite(formatted, sizeof(char), details::ascii::length(formatted), pStream);
		delete[] formatted;
	}
}

/**
 * Helper macros and cleanup.
 */
#undef __struct_INTERNAL_FORMAT_OF
#undef __struct_INTERNAL_FORMATTER
#undef __struct_INTERNAL_SPECIFIER_OF

#define PARSE_IGNORE(pContext) \
FormatterHelpers::template parseIgnore<Context>(pContext);

#define struct_CUSTOM_FORMAT_OF(Dependencies, Type) \
namespace fmatio \
{ \
	template<Dependencies> \
	struct FormatOf<Type> \
	{ \
	public: \
		static FMATIO_CONSTEXPR const FormatArgumentType sValue = FormatArgumentType::Custom; \
		 \
		static FMATIO_INLINE FMATIO_CONSTEXPR const FormatArgumentType value() FMATIO_NOEXCEPT \
		{ return sValue; } \
	}; \
}

#define struct_CUSTOM_FORMATTER(Dependencies, Type, PFunc, FFunc) \
namespace fmatio \
{ \
	template<Dependencies> \
	struct Formatter<Type, FormatterEnabler<Type>> \
	{ \
	public: \
		template<typename Context> \
		static PFunc \
			\
		template<typename Context> \
		static FFunc \
	}; \
}

#endif

/**
 * Standard string formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_STRING_FORMATTER == 1

#ifndef STD_STRING_FORMATTER
#define STD_STRING_FORMATTER

#include <string>

struct_CUSTOM_FORMAT_OF(typename Char FMATIO_COMMA typename Traits FMATIO_COMMA typename Allocator, ::std::basic_string<Char FMATIO_COMMA Traits FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Char FMATIO_COMMA typename Traits FMATIO_COMMA typename Allocator, ::std::basic_string<Char FMATIO_COMMA Traits FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::basic_string<Char FMATIO_COMMA Traits FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		pContext.append(pValue.data() FMATIO_COMMA static_cast<uint32_t>(pValue.size()));
	}
);

#endif

#endif

/**
 * Standard initializer list formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_INITIALIZER_LIST_FORMATTER == 1

#ifndef STD_INITIALIZER_LIST_FORMATTER
#define STD_INITIALIZER_LIST_FORMATTER

#include <initializer_list>

struct_CUSTOM_FORMAT_OF(typename Type, ::std::initializer_list<Type>);
struct_CUSTOM_FORMATTER(typename Type, ::std::initializer_list<Type>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::initializer_list<Type>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Type>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::initializer_list<Type>::const_iterator;
		for (ConstIterator iterator = pValue.begin() + 1; iterator != pValue.end(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Type>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard forward list formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_FORWARD_LIST_FORMATTER == 1

#ifndef STD_FORWARD_LIST_FORMATTER
#define STD_FORWARD_LIST_FORMATTER

#include <forward_list>

struct_CUSTOM_FORMAT_OF(typename Type, ::std::forward_list<Type>);
struct_CUSTOM_FORMATTER(typename Type, ::std::forward_list<Type>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::forward_list<Type>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Type>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::forward_list<Type>::const_iterator;
		for (ConstIterator iterator = ++pValue.begin(); iterator != pValue.end(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Type>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard array formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_ARRAY_FORMATTER == 1

#ifndef STD_ARRAY_FORMATTER
#define STD_ARRAY_FORMATTER

#include <array>

struct_CUSTOM_FORMAT_OF(typename Type FMATIO_COMMA typename ::std::size_t tSize, ::std::array<Type FMATIO_COMMA tSize>);
struct_CUSTOM_FORMATTER(typename Type FMATIO_COMMA typename ::std::size_t tSize, ::std::array<Type FMATIO_COMMA tSize>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::array<Type FMATIO_COMMA tSize>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Type>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::array<Type FMATIO_COMMA tSize>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Type>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard vector formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_VECTOR_FORMATTER == 1

#ifndef STD_VECTOR_FORMATTER
#define STD_VECTOR_FORMATTER

#include <vector>

struct_CUSTOM_FORMAT_OF(typename Type FMATIO_COMMA typename Allocator, ::std::vector<Type FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type FMATIO_COMMA typename Allocator, ::std::vector<Type FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::vector<Type FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Type>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::vector<Type FMATIO_COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Type>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard list formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_LIST_FORMATTER == 1

#ifndef STD_LIST_FORMATTER
#define STD_LIST_FORMATTER

#include <list>

struct_CUSTOM_FORMAT_OF(typename Type FMATIO_COMMA typename Allocator, ::std::list<Type FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type FMATIO_COMMA typename Allocator, ::std::list<Type FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::list<Type FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Type>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::list<Type FMATIO_COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Type>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard deque formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_DEQUE_FORMATTER == 1

#ifndef STD_DEQUE_FORMATTER
#define STD_DEQUE_FORMATTER

#include <deque>

struct_CUSTOM_FORMAT_OF(typename Type FMATIO_COMMA typename Allocator, ::std::deque<Type FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type FMATIO_COMMA typename Allocator, ::std::deque<Type FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::deque<Type FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Type>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::deque<Type FMATIO_COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Type>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard set formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_SET_FORMATTER == 1

#ifndef STD_SET_FORMATTER
#define STD_SET_FORMATTER

#include <set>

struct_CUSTOM_FORMAT_OF(typename Type FMATIO_COMMA typename Compare FMATIO_COMMA typename Allocator, ::std::set<Type FMATIO_COMMA Compare FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type FMATIO_COMMA typename Compare FMATIO_COMMA typename Allocator, ::std::set<Type FMATIO_COMMA Compare FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::set<Type FMATIO_COMMA Compare FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Type>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::set<Type FMATIO_COMMA Compare FMATIO_COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Type>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard unordered set formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_UNORDERED_SET_FORMATTER == 1

#ifndef STD_UNORDERED_SET_FORMATTER
#define STD_UNORDERED_SET_FORMATTER

#include <unordered_set>

struct_CUSTOM_FORMAT_OF(typename Value FMATIO_COMMA typename Hash FMATIO_COMMA typename Predicate FMATIO_COMMA typename Allocator, ::std::unordered_set<Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Value FMATIO_COMMA typename Hash FMATIO_COMMA typename Predicate FMATIO_COMMA typename Allocator, ::std::unordered_set<Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::unordered_set<Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Value>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::unordered_set<Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Value>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard pair formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_PAIR_FORMATTER == 1

#ifndef STD_PAIR_FORMATTER
#define STD_PAIR_FORMATTER

#include <utility>

struct_CUSTOM_FORMAT_OF(typename Key FMATIO_COMMA typename Value, ::std::pair<Key FMATIO_COMMA Value>);
struct_CUSTOM_FORMATTER(typename Key FMATIO_COMMA typename Value, ::std::pair<Key FMATIO_COMMA Value>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::pair<Key FMATIO_COMMA Value>& pValue) FMATIO_NOEXCEPT
	{
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Key>::format(pContext FMATIO_COMMA pValue.first);
		Formatter<char>::format(pContext FMATIO_COMMA ' ');
		Formatter<Value>::format(pContext FMATIO_COMMA pValue.second);
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard map formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_MAP_FORMATTER == 1

#ifndef STD_MAP_FORMATTER
#define STD_MAP_FORMATTER

#include <map>

struct_CUSTOM_FORMAT_OF(typename Key FMATIO_COMMA typename Value FMATIO_COMMA typename Compare FMATIO_COMMA typename Allocator, ::std::map<Key FMATIO_COMMA Value FMATIO_COMMA Compare FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Key FMATIO_COMMA typename Value FMATIO_COMMA typename Compare FMATIO_COMMA typename Allocator, ::std::map<Key FMATIO_COMMA Value FMATIO_COMMA Compare FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::map<Key FMATIO_COMMA Value FMATIO_COMMA Compare FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		using Pair = typename ::std::pair<Key FMATIO_COMMA Value>;
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Pair>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::map<Key FMATIO_COMMA Value FMATIO_COMMA Compare FMATIO_COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Pair>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif

/**
 * Standard unordered map formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_UNORDERED_MAP_FORMATTER == 1

#ifndef STD_UNORDERED_MAP_FORMATTER
#define STD_UNORDERED_MAP_FORMATTER

#include <utility>
#include <unordered_map>

struct_CUSTOM_FORMAT_OF(typename Key FMATIO_COMMA typename Value FMATIO_COMMA typename Hash FMATIO_COMMA typename Predicate FMATIO_COMMA typename Allocator, ::std::unordered_map<Key FMATIO_COMMA Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Key FMATIO_COMMA typename Value FMATIO_COMMA typename Hash FMATIO_COMMA typename Predicate FMATIO_COMMA typename Allocator, ::std::unordered_map<Key FMATIO_COMMA Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>,
	FMATIO_INLINE FMATIO_CONSTEXPR void parse(Context& pContext) FMATIO_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FMATIO_INLINE FMATIO_CONSTEXPR void format(Context& pContext FMATIO_COMMA const ::std::unordered_map<Key FMATIO_COMMA Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>& pValue) FMATIO_NOEXCEPT
	{
		using Pair = typename ::std::pair<Key FMATIO_COMMA Value>;
		Formatter<char>::format(pContext FMATIO_COMMA '[');
		Formatter<Pair>::format(pContext FMATIO_COMMA *pValue.begin());

		using ConstIterator = typename ::std::unordered_map<Key FMATIO_COMMA Value FMATIO_COMMA Hash FMATIO_COMMA Predicate FMATIO_COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext FMATIO_COMMA ' ');
			Formatter<Pair>::format(pContext FMATIO_COMMA *iterator);
		}
	
		Formatter<char>::format(pContext FMATIO_COMMA ']');
	}
);

#endif

#endif
