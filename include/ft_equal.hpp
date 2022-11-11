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
}

#endif // FT_EQUAL_HPP
