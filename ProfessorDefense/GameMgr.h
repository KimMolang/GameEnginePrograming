#pragma once

#include "Singleton.h"
#include "OgreFrameListener.h"

class CGameMgr : public Ogre::FrameListener
{
	DECLARE_SINGLETON(CGameMgr)

public :
	static enum GameState
	{
		GAME_STATE_COUNTDOWN,
		GAME_STATE_PLAYING,

		GAME_STATE_OVER,
		GAME_STATE_GLEAR
	};

private :
	void update();

private:
	void	_setGameState(GameState _eState);

	int		_countdown();


private :
	GameState	m_eGameState;
	float		m_fPlayTime;
	int			m_iStageNum;


private:
	CGameMgr();
	~CGameMgr();
};

