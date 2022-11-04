#include "common.hpp"
#include <list>

#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

static int iter = 0;

void pp(int n) { std::cout << "[[" << n << "]]" << std::endl; }

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "ret: " << mp.erase(param) << std::endl;
	printSize(mp);
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 6;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	pp(1);
	printSize(mp);

	pp(2);
	for (int i = 2; i < 4; ++i)
		ft_erase(mp, i);

	pp(3);
	ft_erase(mp, mp.begin()->first);
	pp(4);
	ft_erase(mp, (--mp.end())->first);

	mp[-1] = "Hello";
	mp[10] = "Hi there";
	mp[10] = "Hi there";
	pp(4);
	printSize(mp);

	pp(5);
	ft_erase(mp, 0);
	pp(6);
	ft_erase(mp, 1);

	return (0);
}
