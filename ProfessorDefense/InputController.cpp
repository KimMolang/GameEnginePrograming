#include "InputController.h"


InputController::InputController(Root* root, OIS::Keyboard *keyboard, OIS::Mouse *mouse)
: mRoot(root)
, mKeyboard(keyboard)
, mMouse(mouse)
{
	mSceneMgr = root->getSceneManager("main");

	//mAnimationState = mSceneMgr->getEntity("Professor")->getAnimationState("Run");
	//mAnimationState->setLoop(true);
	//mAnimationState->setEnabled(true);

	//mCameraYaw = mSceneMgr->getSceneNode("CameraYaw");
	//mCameraPitch = mSceneMgr->getSceneNode("CameraPitch");
	//mCameraHolder = mSceneMgr->getSceneNode("CameraHolder");

	//mPanel = static_cast<Ogre::OverlayContainer*>(OverlayManager::getSingletonPtr()->getOverlayElement("container1"));

	//mContinue = true;

	keyboard->setEventCallback(this);
	mouse->setEventCallback(this);
}


bool InputController::frameStarted(const FrameEvent &evt)
{
	mKeyboard->capture();
	mMouse->capture();

	//mAnimationState->addTime(evt.timeSinceLastFrame);
	//static float panelX = -0.3f;
	//mPanel->setPosition(panelX, 0.5f);
	//panelX = panelX > 1.0f ? -0.3f : panelX + 0.1f * evt.timeSinceLastFrame;


	// when return false, exe is downed
	return true;
}

// Key Linstener Interface Implementation
bool InputController::keyPressed(const OIS::KeyEvent &evt)
{

	return true;

}

bool InputController::keyReleased(const OIS::KeyEvent &evt)
{
	switch (evt.key)
	{
	case OIS::KC_ESCAPE :
		break;
	}

	return true;
}


// Mouse Listener Interface Implementation
bool InputController::mouseMoved(const OIS::MouseEvent &evt)
{
	//mCameraYaw->yaw(Degree(-evt.state.X.rel));
	//mCameraPitch->pitch(Degree(-evt.state.Y.rel));

	//mCameraHolder->translate(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.1f));

	return true;
}

bool InputController::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

bool InputController::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}