// *****************************************************************************
//  BaseComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "BaseComponent.h"

using namespace GameBase;
using namespace Base;

// *****************************************************************************
cBaseComponent::cBaseComponent()
	: m_pOwner(NULL)
{
}

// *****************************************************************************
cBaseComponent::~cBaseComponent()
{
}

// *****************************************************************************
cBaseComponent::cBaseComponent(const cBaseComponent & other)
	: m_pOwner(other.m_pOwner)
{

}

// *****************************************************************************
cBaseComponent & cBaseComponent::operator=(const cBaseComponent & other)
{
	m_pOwner = other.m_pOwner;
	return *this;
}

// *****************************************************************************
void cBaseComponent::VOnAttached(IBaseEntity * const pOwner)
{
	m_pOwner = pOwner;
}
