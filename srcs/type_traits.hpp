#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {
	
	// true and false types
	// these types are used to overload some templates based on some condition
	struct true_type { };
	struct false_type { };

	// enable_if
	// if the first template argument is a true type
	// declare 'type' of the type of the second arguent
	// else no type is declared
	template <bool, typename T>
	struct enable_if { };

	template <typename T>
	struct enable_if<true, T> {
		typedef T	type;
	};

	// integer types
	// default template = not an integral type
	template <typename T>
	struct is_integral {
		enum { value = 0 };
		typedef false_type	type;
	};

	// template specializations of is_integral

	template <>
	struct is_integral<bool> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<char> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<signed char> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<unsigned char> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<short> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<unsigned short> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<int> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<unsigned int> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<long> {
		enum { value = 1 };
		typedef true_type	type;
	};

	template <>
	struct is_integral<unsigned long> {
		enum { value = 1 };
		typedef true_type	type;
	};

	// are_same trait
	template <typename T1, typename T2>
	struct are_same { 
		enum { value = 0 };
		typedef false_type	type;
	};

	template <typename T>
	struct are_same<T, T> {
		enum { value = 1 };
		typedef true_type	type;
	};

}

#endif
