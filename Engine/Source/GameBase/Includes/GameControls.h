// ********************************************************************************************************************
//  GameControls   version:  1.0   Ankur Sheel  date: 2013/03/19
// ********************************************************************************************************************
// 
// ********************************************************************************************************************
#ifndef GameControls_h__
#define GameControls_h__

#include "GameBaseDefines.h"

namespace GameBase
{
	struct stGameControl
	{
		unsigned int	m_KeyCode;
		Base::cString	m_DisplayName;

		stGameControl()
			: m_KeyCode(0)
		{
		}

		stGameControl(const Base::cString & inDisplayName,	const unsigned int inKeyCode)
			: m_DisplayName(inDisplayName)
			, m_KeyCode(inKeyCode)
		{
		}
	};

	class cGameControls
		: public Base::cNonCopyable
	{
	public:
		typedef std::unordered_map<unsigned int, stGameControl> KeyMapping;

		GAMEBASE_API cGameControls(const Base::cString & inFileName);
		GAMEBASE_API virtual ~cGameControls();

		virtual void VSetDefaults() = 0;

		GAMEBASE_API void Save();
		GAMEBASE_API void Load();
		GAMEBASE_API Base::cString GetKeyName(const unsigned int inKey) const;	
		GAMEBASE_API void SetKey(const int inKeyIndex, const unsigned int inKey);

		GAMEBASE_API KeyMapping GetKeyMap() const { return m_KeyMap; }
		GAMEBASE_API unsigned int GetKeyCode(const unsigned int index) const;	

	protected:
		KeyMapping	m_KeyMap;

	private:
		Base::cString	m_KeysFile;
	};
}
#endif