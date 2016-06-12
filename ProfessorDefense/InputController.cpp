#include "InputController.h"

const float InputController::CAMERA_MOVE_SPEED = 300.f;


InputController::InputController(Root* root, OIS::Keyboard *keyboard, OIS::Mouse *mouse)
: mRoot(root)
, mKeyboard(keyboard)
, mMouse(mouse)

, mKeyDown_W(false)
, mKeyDown_A(false)
, mKeyDown_S(false)
, mKeyDown_D(false)
, mKeyDown_MouseL(false)
{
	mSceneMgr = root->getSceneManager("main");

	//mAnimationState = mSceneMgr->getEntity("Professor")->getAnimationState("Run");
	//mAnimationState->setLoop(true);
	//mAnimationState->setEnabled(true);

	mCameraYaw = mSceneMgr->getSceneNode("CameraYaw");
	mCameraPitch = mSceneMgr->getSceneNode("CameraPitch");
	mCameraHolder = mSceneMgr->getSceneNode("CameraHolder");

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

	if (mKeyDown_W)	mCameraHolder->translate(Vector3(0.f, 0.f, -(CAMERA_MOVE_SPEED * evt.timeSinceLastFrame)));
	if (mKeyDown_S)	mCameraHolder->translate(Vector3(0.f, 0.f, CAMERA_MOVE_SPEED * evt.timeSinceLastFrame));
	if (mKeyDown_A)	mCameraHolder->translate(Vector3(-(CAMERA_MOVE_SPEED * evt.timeSinceLastFrame), 0.f, 0.f));
	if (mKeyDown_D)	mCameraHolder->translate(Vector3(CAMERA_MOVE_SPEED * evt.timeSinceLastFrame, 0.f, 0.f));


	// when return false, exe is downed
	return true;
}

// Key Linstener Interface Implementation
bool InputController::keyPressed(const OIS::KeyEvent &evt)
{
	switch (evt.key)
	{
	case OIS::KC_A: mKeyDown_A = true; break;
	case OIS::KC_D: mKeyDown_D = true; break;
	case OIS::KC_W: mKeyDown_W = true; break;
	case OIS::KC_S: mKeyDown_S = true; break;

	case OIS::KC_SPACE:
		break;

	case OIS::KC_ESCAPE:
		return false;
	}


	return true;

}

bool InputController::keyReleased(const OIS::KeyEvent &evt)
{
	switch (evt.key)
	{
	case OIS::KC_A: mKeyDown_A = false; break;
	case OIS::KC_D: mKeyDown_D = false; break;
	case OIS::KC_W: mKeyDown_W = false; break;
	case OIS::KC_S: mKeyDown_S = false; break;

	case OIS::KC_SPACE:
		break;

	case OIS::KC_ESCAPE:
		return false;
	}

	return true;
}


// Mouse Listener Interface Implementation
bool InputController::mouseMoved(const OIS::MouseEvent &evt)
{
	//mCameraYaw->yaw(Degree(-evt.state.X.rel));
	//mCameraPitch->pitch(Degree(-evt.state.Y.rel));

	mCameraHolder->yaw(Degree(-evt.state.X.rel) / 2.f, Node::TS_LOCAL);

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