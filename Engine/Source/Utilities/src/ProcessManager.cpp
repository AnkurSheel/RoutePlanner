#include "stdafx.h"
#include "ProcessManager.h"
#include "Process.h"

using namespace Utilities;
using namespace Base;

//  *******************************************************************************************************************
cProcessManager::~cProcessManager()
{	
	m_pProcessList.clear();
}

//  *******************************************************************************************************************
void cProcessManager::VAttachProcess(shared_ptr<cProcess> pProcess)
{
	m_pProcessList.push_back(pProcess);
	pProcess->SetAttached(true);
}

//  *******************************************************************************************************************
void cProcessManager::VUpdateProcesses(const float deltaTime)
{
	shared_ptr<cProcess> pNext;

	auto curProcess = m_pProcessList.begin();

	while(curProcess != m_pProcessList.end())
	{
		shared_ptr<cProcess> p(*curProcess);
		curProcess++;

		if(p->IsDead())
		{
			pNext = p->GetNext();
			if(pNext)
			{
				p->SetNext(shared_ptr<cProcess>((cProcess*)NULL));
				VAttachProcess(pNext);
			}
			VDetachProcess(p);
		}
		else if(p->IsActive() && !p->VIsPaused())
		{
			p->VUpdate(deltaTime);
		}
	}
}

//  *******************************************************************************************************************
void cProcessManager::VDetachProcess(shared_ptr<cProcess> pProcess)
{
	m_pProcessList.remove(pProcess);
	pProcess->SetAttached(false);
}

//  *******************************************************************************************************************
void cProcessManager::VDetachProcess(const cHashedString & Type)
{
	for (auto curProcess = m_pProcessList.begin(); curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->VGetType() == Type)
		{
			p->VKill();
		}
	}
}

//  *******************************************************************************************************************
void cProcessManager::VSetProcessesActive(const cHashedString & Type, const bool Active)
{
	for (auto curProcess = m_pProcessList.begin(); curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->VGetType() == Type)
		{
			p->VSetActive(Active);
		}
	}
}

//  *******************************************************************************************************************
void cProcessManager::VGetProcesses(const cHashedString & Type, ProcessList & pProcessList)
{
	for (auto curProcess = m_pProcessList.begin(); curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->VGetType() == Type)
		{
			pProcessList.push_back(p);
		}
	}
}

//  *******************************************************************************************************************
void cProcessManager::VSetProcessesPaused(const cHashedString & Type, const bool Paused)
{
	for (auto curProcess = m_pProcessList.begin(); curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->VGetType() == Type)
		{
			p->VSetPaused(Paused);
		}
	}
}

//  *******************************************************************************************************************
IProcessManager * IProcessManager::CreateProcessManager()
{
	return DEBUG_NEW cProcessManager();
}