//  *******************************************************************************************************************
//  HumanView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef HumanView_h__
#define HumanView_h__

#include "GameBaseDefines.h"
#include "GameView.hxx"
#include "Structures.h"

namespace GameBase
{
	class cBaseApp;
}

namespace Graphics
{
	class ISprite;
	class IBaseControl;
	class ICamera;
	struct stUIEventCallbackParam;
	class cLabelControlDef;
}
namespace Sound
{
	class ISoundProcess;
}

namespace GameBase
{
	//typedef std::list<shared_ptr<Graphics::IScreenElement> > ScreenElementList;

	class cHumanView 
		: public IGameView
	{
	public:
		GAMEBASE_API cHumanView();
		GAMEBASE_API virtual ~cHumanView();
		GAMEBASE_API virtual void VOnCreateDevice(IBaseApp* pBaseApp);
		GAMEBASE_API virtual bool VOnMsgProc( const Base::AppMsg & msg );	
		GAMEBASE_API virtual void VOnRender(const TICK tickCurrent, const float fElapsedTime);
		GAMEBASE_API virtual void VOnUpdate(const TICK tickCurrent, const float fElapsedTime);
		GAMEBASE_API virtual void VOnDestroyDevice();
		GAMEBASE_API void SetCursorVisible(bool bVisible);
		GAMEBASE_API GAMEVIEWTYPE VGetType();
		GAMEBASE_API GameViewId VGetId() const;
		GAMEBASE_API const Graphics::ICamera * const GetCamera() const;
		GAMEBASE_API void PlaySFX(const Base::cString & strSoundFile);
		GAMEBASE_API void PlayMusic(const Base::cString & strMusicFile, const bool bLooping);
		GAMEBASE_API void MusicCheckBoxPressed(const Graphics::stUIEventCallbackParam & params);
		GAMEBASE_API void SfxCheckBoxPressed(const Graphics::stUIEventCallbackParam & params);
		GAMEBASE_API void FullScreenCheckBoxPressed(const Graphics::stUIEventCallbackParam & params);
		GAMEBASE_API void SetMusicVolume();
		GAMEBASE_API void SetSFXVolume();

	protected:
		GAMEBASE_API virtual void VRenderPrivate();
		GAMEBASE_API HRESULT OnBeginRender(TICK tickCurrent);
		GAMEBASE_API void OnEndRender(const HRESULT hr);
		GAMEBASE_API void VOnAttach(GameViewId id);
		GAMEBASE_API bool CheckZones(Base::cString & strHitZoneName);
		GAMEBASE_API void CreateFPSLabel(const Graphics::cLabelControlDef & def);

	protected:
		Graphics::ICamera *					m_pCamera;
		shared_ptr<Graphics::IBaseControl>	m_pFpsLabel;
		GameBase::IBaseApp	*			m_pGame;

	private:
		GameViewId						m_idView;
		TICK							m_tickCurrent;
		TICK							m_tickLastDraw;
		bool							m_bRunFullSpeed;
		//shared_ptr<Graphics::ISprite>	m_pCursorSprite;		// the sprite for the cursor
		bool							m_bDisplayFPS;
		const Base::cHashedString		m_hashSFXChannel;
		const Base::cHashedString		m_hashMusicChannel;

	public:
		Graphics::IBaseControl *		m_pAppWindowControl;
	};
}
#endif // HumanView_h__
