// *******************************************************************************************************************
//  Optional   version:  1.0   Ankur Sheel  date: 2011/04/12
// *******************************************************************************************************************
//  adapted from Game Coding Complete
// *******************************************************************************************************************
#ifndef Optional_h__
#define Optional_h__

#include <assert.h>

namespace Base
{
	class tOptionalEmpty 
	{
	};

	template <unsigned long iSize>
	class tOptionalBase
	{
	public:
		tOptionalBase()
			: m_bValid(false)
		{
		}

		tOptionalBase & operator= (const tOptionalBase & t)
		{
			m_bValid = t.m_bValid;
			return *this;
		}

		tOptionalBase(const tOptionalBase & t)
			: m_bValid(t.m_bValid)
		{
		}

		const bool IsValid() const
		{
			return m_bValid;
		}

		const bool IsInvalid() const
		{
			return !m_bValid;
		}

	protected:
		bool	m_bValid;
		char	m_Data[iSize];
	};

	template<class T>
	class tOptional 
		: public tOptionalBase<sizeof(T)>
	{
	public:
		tOptional()
		{
		}

		tOptional(const T & t)
		{
			construct(t);
			m_bValid = true;
		}

		tOptional(tOptionalEmpty &)
		{
		}

		tOptional & operator= (const T & t)
		{
			if (m_bValid)
			{
				* GetT() = t;
			}
			else
			{
				construct(t);
				m_bValid = true;
			}
			return * this;
		}

		tOptional(const tOptional & t)
		{
			if(t.m_bValid)
			{
				construct(t.GetValue());
				m_bValid = true;
			}
		}

		tOptional & operator= (const tOptional & t)
		{
			//TODO : change to assert later
			assert(! (this  == &t));

			if (m_bValid)
			{
				m_bValid = false;
				Destroy();
			}

			if(t.m_bValid)
			{
				construct(t.GetValue());
				m_bValid = true;
			}
			return * this;
		}

		const bool operator == (const tOptional & t)
		{
			if( (!valid()) && (!t.valid()))
			{
				return true;
			}
			if(valid() ^ t.valid())
			{
				return false;
			}

			return ((* * this) == (*t));
		}

		const bool operator < (const tOptional & t)
		{
			if( (!valid()) && (!t.valid()))
			{
				return false;
			}
			if(!valid())
			{
				return true;
			}

			if(!t.valid())
			{
				return false;
			}

			return ((* * this) < (*t));
		}

		~tOptional()
		{
			if(m_bValid)
			{
				Destroy();
			}
		}

		const T & GetValue() const
		{ 
			assert(m_bValid); 
			return * GetT(); 
		}

		T & GetValue()
		{ 
			assert(m_bValid); 
			return * GetT(); 
		}

		const T * const GetPtr() const	
		{
			assert(m_bValid); 
			return GetT(); 
		}

		T * const GetPtr()
		{ 
			assert(m_bValid); 
			return GetT(); 
		}

		void clear()
		{
			if(m_bValid)
			{
				m_bValid = false;
				Destroy();
			}
		}

	private:

		const T * const GetT() const
		{ 
			return reinterpret_cast<T const * const>(m_Data); 
		}

		T * const GetT()
		{ 
			return reinterpret_cast<T * const>(m_Data);
		}

		void construct(T const & t)
		{ 
			new (GetT()) T(t); 
		}

		void Destroy() 
		{ 
			GetT()->~T(); 
		}
	};
}
#endif // Optional_h__
