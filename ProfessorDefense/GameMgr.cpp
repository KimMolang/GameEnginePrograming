#include "GameMgr.h"

IMPLEMENT_SINGLETON(CGameMgr)


CGameMgr::CGameMgr()
: m_eGameState(GAME_STATE_COUNTDOWN)
, m_fPlayTime(0.0f)
, m_iStageNum(0)
{
}


CGameMgr::~CGameMgr()
{
}

void CGameMgr::update()
{
	switch (m_eGameState)
	{
	case CGameMgr::GAME_STATE_COUNTDOWN:
		break;

	case CGameMgr::GAME_STATE_PLAYING:
		break;

	case CGameMgr::GAME_STATE_OVER:
		break;

	case CGameMgr::GAME_STATE_GLEAR:
		break;

	default:
		break;
	}
}

void CGameMgr::_setGameState(GameState _eState)
{
	switch (_eState)
	{
	case CGameMgr::GAME_STATE_COUNTDOWN:
		break;

	case CGameMgr::GAME_STATE_PLAYING:
		break;

	case CGameMgr::GAME_STATE_OVER:
		break;

	case CGameMgr::GAME_STATE_GLEAR:
		break;

	default:
		break;
	}
}

int CGameMgr::_countdown()
{
	return 0;
}
