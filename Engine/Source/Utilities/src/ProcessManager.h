//  *******************************************************************************************************************
//  ProcessManager   version:  1.0   Ankur Sheel  date: 2011/04/12
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef ProcessManager_h__
#define ProcessManager_h__

#include "ProcessManager.hxx"

namespace Utilities
{
	class cProcess;
}

namespace Utilities
{
	class cProcessManager
		: public IProcessManager
	{
	public:
		~cProcessManager();

	private:
		void VAttachProcess(shared_ptr<cProcess> pProcess);
		void VDetachProcess(shared_ptr<cProcess> pProcess);
		void VDetachProcess(const Base::cHashedString & Type);
		void VSetProcessesActive(const Base::cHashedString & Type, const bool bActive);
		void VGetProcesses(const Base::cHashedString & Type, ProcessList & pProcessList);
		void VUpdateProcesses(const float deltaTime);
		void VSetProcessesPaused(const Base::cHashedString & Type, const bool Paused);

		bool VHasProcesses() const { return !(m_pProcessList.empty()); }

	protected:
		ProcessList m_pProcessList;
	};
}
#endif // ProcessManager_h__