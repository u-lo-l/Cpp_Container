/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_equal.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:40:30 by dkim2             #+#    #+#             */
/*   Updated: 2022/09/25 14:52:09 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EQUAL_HPP
# define FT_EQUAL_HPP

namespace ft
{
	template <class Iter1, class Iter2>
	bool equal(Iter1 first1, Iter1 last1, Iter2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return (false);
		}
		return (true);
	}

	template <class Iter1, class Iter2, class BinaryPredicate>
	bool equal(Iter1 first1, Iter1 last1, Iter2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return (false);
		}
		return (true);
	}
};

#endif // FT_EQUAL_HPP