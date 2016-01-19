//  *******************************************************************************************************************
//  ProcessManager   version:  1.0   Ankur Sheel  date: 2011/04/12
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef ProcessManager_hxx__
#define ProcessManager_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class cProcess;
}
namespace Utilities
{
	typedef std::list<shared_ptr<cProcess>> ProcessList;

	class IProcessManager
	{
	public:
		UTILITIES_API virtual ~IProcessManager() {}

		UTILITIES_API virtual void VAttachProcess(shared_ptr<cProcess> pProcess) = 0;
		UTILITIES_API virtual void VDetachProcess(shared_ptr<cProcess> pProcess) = 0;
		UTILITIES_API virtual void VDetachProcess(const Base::cHashedString & Type) = 0;
		UTILITIES_API virtual bool VHasProcesses() const = 0;
		UTILITIES_API virtual void VUpdateProcesses(const float deltaTime) = 0;
		UTILITIES_API virtual void VSetProcessesActive(const Base::cHashedString & Type, const bool Active) = 0;
		UTILITIES_API virtual void VGetProcesses(const Base::cHashedString & Type, ProcessList & pProcessList) = 0;
		UTILITIES_API virtual void VSetProcessesPaused(const Base::cHashedString & Type, const bool Paused) = 0;
		UTILITIES_API static IProcessManager * CreateProcessManager();
	};
}
#endif // ProcessManager_h__