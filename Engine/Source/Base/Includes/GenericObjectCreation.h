//  *******************************************************************************************************************
//  GenericObjectCreation version:  1.0   Ankur Sheel  date: 2013/05/07
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef GenericObjectCreation_h__
#define GenericObjectCreation_h__

namespace Base
{
	template <class BaseType, class SubType>
	BaseType * GenericObjectCreationFunction() 
	{ 
		return DEBUG_NEW SubType; 
	}

	template <class BaseType, class SubType>
	BaseType * GenericObjectDuplicationFunction(const BaseType * const pObject) 
	{ 
		const SubType * const pSubObject = dynamic_cast<const SubType * const>(pObject);
		if(pSubObject != NULL)
		{
			return DEBUG_NEW SubType(*pSubObject); 
		}
		return NULL;
	}

	template <class BaseClass, class IdType>
	class GenericObjectFactory
	{
		typedef BaseClass* (*ObjectCreationFunction)(void);
		std::map<IdType, ObjectCreationFunction> m_creationFunctions;

		typedef BaseClass* (*ObjectDuplicationFunction)(const BaseClass * const);
		std::map<IdType, ObjectDuplicationFunction> m_DuplicationFunctions;

	public:
		template <class SubClass>
		bool Register(IdType id)
		{
			auto findIt = m_creationFunctions.find(id);
			if (findIt == m_creationFunctions.end())
			{
				m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;
				m_DuplicationFunctions[id] = &GenericObjectDuplicationFunction<BaseClass, SubClass>; 
				return true;
			}
			return false;
		}

		BaseClass * Create(IdType id)
		{
			auto findIt = m_creationFunctions.find(id);
			if (findIt != m_creationFunctions.end())
			{
				ObjectCreationFunction pFunc = findIt->second;
				return pFunc();
			}

			return NULL;
		}

		BaseClass * Duplicate(IdType id, const BaseClass * const pObject)
		{
			auto findIt = m_DuplicationFunctions.find(id);
			if (findIt != m_DuplicationFunctions.end())
			{
				ObjectDuplicationFunction pFunc = findIt->second;
				return pFunc(pObject);
			}
			return NULL;
		}
	};
}
#endif // GenericObjectCreation
