#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"
#include <deque>

namespace ft {

template <class T, class Container = std::deque<T> >
class stack
{

	public:

		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;
		typedef typename Container::reference	reference;
		typedef typename Container::const_reference	const_reference;
		typedef Container						container_type;

		template <class T1, class Container1>
		friend bool	operator==(const stack<T1, Container1>& x, const stack<T1, Container1>& y);
		template <class T1, class Container1>
		friend bool	operator<(const stack<T1, Container1>& x, const stack<T1, Container1>& y);
		template <class T1, class Container1>
		friend bool	operator!=(const stack<T1, Container1>& x, const stack<T1, Container1>& y);
		template <class T1, class Container1>
		friend bool	operator>(const stack<T1, Container1>& x, const stack<T1, Container1>& y);
		template <class T1, class Container1>
		friend bool	operator>=(const stack<T1, Container1>& x, const stack<T1, Container1>& y);
		template <class T1, class Container1>
		friend bool	operator<=(const stack<T1, Container1>& x, const stack<T1, Container1>& y);
	
	protected:

		Container c;
	
	public:
		
		explicit stack(const Container& copy = Container()) :
			c(copy)
			{ }

		bool	empty(void) const	{ return (c.empty()); }
		size_type	size(void) const	{ return (c.size()); }
		value_type&	top(void) { return (c.back()); }
		const value_type&	top(void) const	{ return (c.back()); }
		void	push(const value_type& x)	{ c.push_back(x); }
		void	pop(void)	{ c.pop_back(); }

};

template <class T, class Container>
bool	operator==(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x.c == y.c);
}

template <class T, class Container>
bool	operator<(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x.c < y.c);
}

template <class T, class Container>
bool	operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x.c != y.c);
}

template <class T, class Container>
bool	operator>(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x.c > y.c);
}

template <class T, class Container>
bool	operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x.c >= y.c);
}

template <class T, class Container>
bool	operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x.c <= y.c);
}

} // namespace ft

#endif
