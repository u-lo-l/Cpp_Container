#ifndef FT_LESS_HPP
# define FT_LESS_HPP

namespace ft
{
	/*
		binary_function은 바이너리 함수 객체의 기초클래스이다.
		일반적으로 함수객체는 함수호출연산자를 멤버함수로서 포함하는 클래스이다.
		이 멤버함수(함수호출 연산자 오버로딩)는 객체를 일반적인 함수의 호출과 같은 문법으로
		사용할 수 있게 해 주는 기능을 한다. 그렇기 때문에, 템플릿 매개변수에서 generic_function_type이 
		요구될 때, 템플릿 매개변수로써 사용될 수 있다.
		- 제너릭함수란?
			제네릭이란 함수나 클래스를 일반화 하는 것이다. 제네릭 함수는 템플릿으로 작성된 함수이다.
	*/
	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	// 함수 객체 functor
	/*
		"함수호출 연산자 : ()" 를 오버로딩하면 객체를 함수처럼 사용할 수 있고, 이를 함수객체라고 한다.
		함수 객체는 일반적인 함수가 가지지 못하는 속성을 가질 수 있다는 장점이 있다.
	*/
	template<class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator() (const T & x, const T & y) const {return (x < y);}
	};
};

#endif