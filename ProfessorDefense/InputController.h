#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <Overlay/OgreOverlay.h>

using namespace Ogre;


class InputController : public FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
	InputController(Root* root, OIS::Keyboard *keyboard, OIS::Mouse *mouse);

	bool frameStarted(const FrameEvent &evt);
	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);


private:
	Ogre::Root* mRoot;
	Ogre::SceneManager* mSceneMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;
};