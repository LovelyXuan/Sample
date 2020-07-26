#pragma once
#include "afx.h"



template<char const* f>
class TT
{

};

char const* const x = "je";
//TT<x> t;


extern char const * const s = "hello";
//TT<s> tt;

extern char const ss[] = "hello";
TT<ss> ts;

char const sss[] = "hello";
TT<sss> tss;

void Test1()
{
	constexpr int a = '\7';
	constexpr int b = '\8';
	constexpr int c = '\x8';
	constexpr int aa = '7';
	constexpr int ab = '8';
	constexpr int ac = 'x8';

	constexpr bool bb = '\8' == '8';
}


template<int N>
void printBitset(std::bitset<N> const& bs)
{
	std::cout << bs.template to_string<char, char_traits<char>, allocator<char> >();
}

void Test2()
{
	printBitset(std::bitset<32>());
}





template <typename T, 
	template <typename ELEM, typename = std::allocator<ELEM>> class CONT = std::deque>
	class Stack
{
private:
	CONT<T> elems;

public:
	void push(T const&);
	void pop();
	T top() const;
	bool empty() const
	{
		return elems.empty();
	}

	template <typename T2, 
		template <typename ELEM2, typename = std::allocator<ELEM2>> class CONT2>
	Stack<T, CONT>& operator= (Stack<T2, CONT2> const&);
};


template <typename T, template <typename, typename> class CONT>
template <typename T2, template <typename, typename> class CONT2>
Stack<T, CONT>
& Stack<T, CONT>::operator=(Stack<T2, CONT2> const& op2)
{
	if ((void*)this == (void*)&op2)
	{
		return *this;
	}

	Stack<T2, CONT2> tmp(op2);
	elems.clear();

	while (!tmp.empty())
	{
		elems.push_front(tmp.top());
		tmp.pop();
	}

	return *this;
}

template <typename T,
	template <typename ,
	typename /*= std::allocator<ELEM> */>
	class CONT>
	void Stack<T, CONT>::push(T const& elem)
{
	elems.push_back(elem);
}


template <typename T,
	template <typename ,
	typename /*= std::allocator<ELEM> */>
	class CONT>
	void Stack<T, CONT>::pop()
{
	elems.pop_back();
}


template <typename T,
	template <typename ,
	typename /*= std::allocator<ELEM> */>
	class CONT>
	T Stack<T, CONT>::top() const
{
	return elems.back();
}



