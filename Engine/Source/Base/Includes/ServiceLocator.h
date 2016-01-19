//  *******************************************************************************************************************
//  ServiceLocator   version:  1.0   Ankur Sheel  date: 2014/11/17
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SERVICELOCATOR_H__
#define __SERVICELOCATOR_H__

#include "BaseDefines.h"

namespace Base
{
	class cServiceLocator
	{
		typedef std::map<cString, shared_ptr<void> > ServiceMap; 

	public:
		~cServiceLocator();

		template<class T> 
		void Register(const shared_ptr<T> pObject);

		template<class T> 
		weak_ptr<T> GetService();

		template<class T> 
		bool IsServiceRegistered();

		BASE_API static cServiceLocator * const GetInstance();
		BASE_API static void Destroy();

	private:
		cServiceLocator();

	private:
		ServiceMap m_RegisteredTypes;
		static cServiceLocator * m_pInstance;
	};

	//  *****************************************************************************************************************
	template<class T> 
	void cServiceLocator::Register(const shared_ptr<T> pObject) 
	{
		cString name = typeid(T).name();
		if(!IsServiceRegistered<T>())
		{
			m_RegisteredTypes[name] = static_pointer_cast<void>(pObject);
		}
		else
		{
			SP_ASSERT(false)(name).SetCustomMessage("Service is already registered");
		}
	}

	//  *****************************************************************************************************************
	template<class T>
	weak_ptr<T> cServiceLocator::GetService() 
	{
		cString name = typeid(T).name();
		if (IsServiceRegistered<T>())
		{
			return static_pointer_cast<T>(m_RegisteredTypes[typeid(T).name()]);
		}
		return std::weak_ptr<T>();;
	}

	//  *****************************************************************************************************************
	template<class T>
	bool cServiceLocator::IsServiceRegistered()
	{
		cString name = typeid(T).name();
		auto findIt = m_RegisteredTypes.find(name);
		return (findIt != m_RegisteredTypes.end());
	}
};

#endif  // __SERVICELOCATOR_H__
