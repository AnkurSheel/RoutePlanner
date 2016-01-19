// *****************************************************************************
//  SystemChecker   version:  1.0   Ankur Sheel  date: 2013/04/24
// *****************************************************************************
//  purpose:	apdapted from Game Coding Complete
// *****************************************************************************
#ifndef SystemChecker_h__
#define SystemChecker_h__

#include "SystemChecker.hxx"

namespace Utilities
{
	class cSystemChecker
		: public ISystemChecker
		, public Base::cNonCopyable
	{
	public:
		~cSystemChecker();

	private:
		cSystemChecker();
		bool VIsOnlyInstance(const Base::cString & gameTitle);
		void VCheckHardDiskSpace(const unsigned int diskSpaceNeeded); 
		void VCheckMemory(const unsigned int physicalRAMNeeded, const unsigned int virtualRAMNeeded); 
		void VCheckCPUSpeed(const unsigned int minSpeedNeeded);
		unsigned int VGetTotalPhysicalMemory() const { return m_TotalPhysicalMemory; }
		unsigned int VGetAvailablePhysicalMemory() const { return m_AvailablePhysicalMemory; }
		unsigned int VGetTotalVirtualMemory() const { return m_TotalVirtualMemory; }
		unsigned int VGetAvailableVirtualMemory() const { return m_AvailableVirtualMemory; }
		unsigned int VGetTotalHardDiskSpace() const { return m_TotalHardDiskSpace; }
		unsigned int VGetAvailableHardDiskSpace() const { return m_AvailableHardDiskSpace; }
		unsigned int VGetCPUSpeed() const { return m_CPUSpeed; }
		////////////////////////////////////////////////////////////////////////
		/// Initializes the System checker and calculates all the values
		///
		/// @return True if initialization is successful. False otherwise
		///
		////////////////////////////////////////////////////////////////////////
		bool Initialize();
		////////////////////////////////////////////////////////////////////////
		/// Calculates the total and available hard disk space
		///
		///
		///
		////////////////////////////////////////////////////////////////////////
		void CalculateHardDiskSpace();
		////////////////////////////////////////////////////////////////////////
		/// Calculates the total and available System RAM and VRAM
		///
		///
		///
		////////////////////////////////////////////////////////////////////////
		void CalculateRAM();
		////////////////////////////////////////////////////////////////////////
		/// Calculates the CPU Speed
		///
		///
		///
		////////////////////////////////////////////////////////////////////////
		void CalculateCPUSpeed();

	private:
		unsigned int	m_TotalPhysicalMemory;	/// The total system RAM (in MB)
		unsigned int	m_AvailablePhysicalMemory; /// The available system RAM (in MB) 
		unsigned int	m_TotalVirtualMemory;	/// The total VRAM (in MB) 
		unsigned int	m_AvailableVirtualMemory;	/// The available VRAM (in MB) 
		unsigned int	m_TotalHardDiskSpace;	/// The total hard disk space (in MB)
		unsigned int	m_AvailableHardDiskSpace;	/// The available hard disk space (in MB)
		unsigned int	m_CPUSpeed;		/// The CPU speed (in Mhz)
		bool			m_Initialized;	/// True if initialized. False otherwise
		static cSystemChecker * m_pResourceChecker;

	private:
		friend static ISystemChecker * ISystemChecker::Instance();
		friend static void ISystemChecker::Destroy();
	};
}
#endif // Checks_h__
