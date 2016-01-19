//  *******************************************************************************************************************
//  Utilities   version:  1.0   Ankur Sheel  date: 2013/03/16
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BaseUtilities_h__
#define BaseUtilities_h__

const int KILOBYTE = 1024;
const int MEGABYTE = KILOBYTE * KILOBYTE;

const int MAX_FILENAME_WIDTH = 256;
const int MAX_PATH_WIDTH = 260;

const int KEYBOARD_KEYS = 256;

namespace Base
{
	// Safe release of COM objects
	template <typename Interface>
	inline void SafeRelease(Interface **ppInterfaceToRelease)
	{
		if (*ppInterfaceToRelease != NULL)
		{
			(*ppInterfaceToRelease)->Release();
			(*ppInterfaceToRelease) = NULL;
		}
	}

	template <typename Interface>
	inline void SafeDeleteArray(Interface **ppArrayToDelete)
	{
		if (*ppArrayToDelete != NULL)
		{
			delete [] (*ppArrayToDelete);
			(*ppArrayToDelete) = NULL;
		}
	}

	template <typename Interface>
	inline void SafeDelete(Interface **ppInterfaceToDelete)
	{
		if (*ppInterfaceToDelete != NULL)
		{
			delete (*ppInterfaceToDelete);
			(*ppInterfaceToDelete) = NULL;
		}
	}

	template <class T>
	class ArrayDeleter
	{
	public:
		void operator () (T* d) const
		{ 
			SAFE_DELETE_ARRAY(d);
		}
	};

	template <typename T, typename Pred = std::less<T> >
	struct ptr_compare : Pred
	{
		ptr_compare(Pred const & p = Pred()) : Pred(p) { }

		bool operator()(T const * p1, T const * p2) const
		{
			return Pred::operator()(*p1, *p2);
		}
	};

	template <typename T, typename Pred = std::less<T> >
	struct sharedptr_compare : Pred
	{
		sharedptr_compare(Pred const & p = Pred()) : Pred(p) { }

		bool operator()(std::tr1::shared_ptr<T> p1, std::tr1::shared_ptr<T> p2) const
		{
			return Pred::operator()(*p1, *p2);
		}
	};

	template <class T>
	inline T DereferenceToType(void* p)
	{
		return *(T*)(p);
	}

	template <class T>
	inline T DereferenceToType(std::tr1::shared_ptr<void> p)
	{
		return *(T*)(p).get();
	}

	template <class Type>
	std::tr1::shared_ptr<Type> MakeStrongPtr(std::tr1::weak_ptr<Type> pWeakPtr)
	{
		if (!pWeakPtr.expired())
			return std::tr1::shared_ptr<Type>(pWeakPtr);
		else
			return std::tr1::shared_ptr<Type>();
	}

	inline void GetTimeAsHHMMSS(int time, int & hour, int & minutes, int & seconds)
	{
		hour = time / 3600;
		time = time % 3600;
		minutes = time / 60;
		seconds = time % 60;
	}
}

#endif // Utilities_h__
