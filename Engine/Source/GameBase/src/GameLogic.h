// ***************************************************************
//  GameLogic   version:  1.0   Ankur Sheel  date: 2011/05/05
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GameLogic_h__
#define GameLogic_h__

namespace GameBase
{
	class IActor;
	struct ActorParams;

	typedef unsigned int ActorId;

	class IGameLogic
	{
	public:
		virtual shared_ptr<IActor> VGetActor(const ActorId id) = 0;
		virtual void AddActor(shared_ptr<IActor> actor, struct ActorParams * p) = 0;
		virtual void RemoveActor(ActorId id) = 0;
		virtual void OnUpdate(float time, float elapsedTime) = 0;
	};
}
#endif // GameLogic_h__