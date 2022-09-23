/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_integral.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:42:58 by dkim2             #+#    #+#             */
/*   Updated: 2022/09/22 18:38:40 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IS_INTEGRAL_HPP
# define FT_IS_INTEGRAL_HPP
namespace ft
{
	template<class T, T v>
	struct integral_constant
	{
		const static T value = v;

		typedef T value_type;
		typedef integral_constant<T, v> type;

		operator value_type() const { return value; }
	};

	typedef integral_constant<bool, true> true_type;

	typedef integral_constant<bool, false> false_type;

	template< typename T >
	struct is_integral : public false_type {};

	//Specialization for integral types
	template <> struct is_integral<bool> 					: public true_type{};
	template <> struct is_integral<char>					: public true_type{};
	template <> struct is_integral<wchar_t>					: public true_type{};
	template <> struct is_integral<signed char>				: public true_type{};
	template <> struct is_integral<short int>				: public true_type{};
	template <> struct is_integral<int>						: public true_type{};
	template <> struct is_integral<long int>				: public true_type{};
	template <> struct is_integral<long long int>			: public true_type{};
	template <> struct is_integral<unsigned char>			: public true_type{};
	template <> struct is_integral<unsigned short int>		: public true_type{};
	template <> struct is_integral<unsigned int>			: public true_type{};
	template <> struct is_integral<unsigned long int>		: public true_type{};
	template <> struct is_integral<unsigned long long int>	: public true_type{};

	//Specialization for integral types
	template <> struct is_integral<const bool> 						: public true_type{};
	template <> struct is_integral<const char>						: public true_type{};
	template <> struct is_integral<const wchar_t>					: public true_type{};
	template <> struct is_integral<const signed char>				: public true_type{};
	template <> struct is_integral<const short int>					: public true_type{};
	template <> struct is_integral<const int>						: public true_type{};
	template <> struct is_integral<const long int>					: public true_type{};
	template <> struct is_integral<const long long int>				: public true_type{};
	template <> struct is_integral<const unsigned char>				: public true_type{};
	template <> struct is_integral<const unsigned short int>		: public true_type{};
	template <> struct is_integral<const unsigned int>				: public true_type{};
	template <> struct is_integral<const unsigned long int>			: public true_type{};
	template <> struct is_integral<const unsigned long long int>	: public true_type{};

	//Specialization for integral types
	template <> struct is_integral<volatile bool> 					: public true_type{};
	template <> struct is_integral<volatile char>					: public true_type{};
	template <> struct is_integral<volatile wchar_t>				: public true_type{};
	template <> struct is_integral<volatile signed char>			: public true_type{};
	template <> struct is_integral<volatile short int>				: public true_type{};
	template <> struct is_integral<volatile int>					: public true_type{};
	template <> struct is_integral<volatile long int>				: public true_type{};
	template <> struct is_integral<volatile long long int>			: public true_type{};
	template <> struct is_integral<volatile unsigned char>			: public true_type{};
	template <> struct is_integral<volatile unsigned short int>		: public true_type{};
	template <> struct is_integral<volatile unsigned int>			: public true_type{};
	template <> struct is_integral<volatile unsigned long int>		: public true_type{};
	template <> struct is_integral<volatile unsigned long long int>	: public true_type{};

	//Specialization for integral types
	template <> struct is_integral<const volatile bool> 					: public true_type{};
	template <> struct is_integral<const volatile char>						: public true_type{};
	template <> struct is_integral<const volatile wchar_t>					: public true_type{};
	template <> struct is_integral<const volatile signed char>				: public true_type{};
	template <> struct is_integral<const volatile short int>				: public true_type{};
	template <> struct is_integral<const volatile int>						: public true_type{};
	template <> struct is_integral<const volatile long int>					: public true_type{};
	template <> struct is_integral<const volatile long long int>			: public true_type{};
	template <> struct is_integral<const volatile unsigned char>			: public true_type{};
	template <> struct is_integral<const volatile unsigned short int>		: public true_type{};
	template <> struct is_integral<const volatile unsigned int>				: public true_type{};
	template <> struct is_integral<const volatile unsigned long int>		: public true_type{};
	template <> struct is_integral<const volatile unsigned long long int>	: public true_type{};
};

#endif //FT_IS_INTEGRAL_HPP