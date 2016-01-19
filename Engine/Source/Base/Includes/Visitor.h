//  *******************************************************************************************************************
//  Visitor   version:  1.0   Ankur Sheel  date: 2014/12/10
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __VISITOR_H__
#define __VISITOR_H__

namespace Base
{
#include <iostream>

	//  *******************************************************************************************************************
	class BaseVisitor
	{
	public:
		virtual ~BaseVisitor() {};
	};

	template <class ParamType, typename ReturnType = void>
	class Visitor
	{
	public:
		virtual ~Visitor(){}
		virtual ReturnType visit(ParamType &) = 0;
	};

	//  *******************************************************************************************************************
	template <typename R = void>
	class BaseVisitable
	{
	public:
		typedef R ReturnType;
		virtual ~BaseVisitable() {};
		virtual ReturnType accept(BaseVisitor & )
		{
			return ReturnType(0);
		}

	protected:
		template <class T>
		static ReturnType acceptVisitor(T &visited, BaseVisitor &visitor)
		{
			if (Visitor<T> *p = dynamic_cast< Visitor<T> *> (&visitor))
			{
				return p->visit(visited);
			}
			return ReturnType(-1);
		}

#define VISITABLE() \
			virtual ReturnType accept(BaseVisitor &v) \
			{ return acceptVisitor(*this, v); }
	};
}
#endif  // __VISITOR_H__
