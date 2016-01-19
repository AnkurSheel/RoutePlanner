#include "stdafx.h"
#include "ServiceLocator.h"

using namespace Base;

cServiceLocator * cServiceLocator::m_pInstance = NULL;

//  ********************************************************************************************************************
cServiceLocator::cServiceLocator()
{

}

//  ********************************************************************************************************************
cServiceLocator::~cServiceLocator()
{
	for (auto iter = m_RegisteredTypes.begin(); iter != m_RegisteredTypes.end(); iter++)
	{
		iter->second.reset();
	}
	m_RegisteredTypes.clear();
}

//  ********************************************************************************************************************
cServiceLocator * const Base::cServiceLocator::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = DEBUG_NEW cServiceLocator();
	}
	return m_pInstance;
}

//  ********************************************************************************************************************
void Base::cServiceLocator::Destroy()
{
	SafeDelete(&m_pInstance);
}
