#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>

using namespace Ogre;

const float		MAX_MOVE_POS_Z = 250.f;
const float		MIN_MOVE_POS_Z = -250.f;

const float		PROFESSOR_ROTATE_RANGE = 180.f;
const float		PROFESSOR_ROTATE_SPEED = 2.f;

const float		FISH_DISTANCE_FROM_CENTER = 100.f;
const float		FISH_ROTATE_SPEED = 1.f;


class ESCListener : public FrameListener {
	OIS::Keyboard *mKeyboard;

public:
	ESCListener(OIS::Keyboard *keyboard) : mKeyboard(keyboard) {}
  bool frameStarted(const FrameEvent &evt)
  {
    mKeyboard->capture();
	return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
  }
};


class MainListener : public FrameListener {
  OIS::Keyboard *mKeyboard;
  Root* mRoot;
  SceneNode *mProfessorNode, *mFishNode;
  SceneNode *mFishAxisNode;
  
  // --------------------------
  float		mProfessorVelocity;
  Vector3	mProfessorRotation;

  static enum ProfessorMoveState { BASIC, TUNING };
  ProfessorMoveState	mProfessorMoveState;

public:
  MainListener(Root* root, OIS::Keyboard *keyboard)
	  : mKeyboard(keyboard)
	  , mRoot(root) 
	  , mProfessorVelocity(150.f)
	  , mProfessorRotation(0.f, 0.f, 0.f)
	  , mProfessorMoveState(BASIC)
  {
    mProfessorNode = mRoot->getSceneManager("main")->getSceneNode("Professor");
	mFishAxisNode = mRoot->getSceneManager("main")->getSceneNode("FishAxisNode");
	mFishNode = mRoot->getSceneManager("main")->getSceneNode("Fish");

	mFishNode->setScale(5.f, 5.f, 5.f);
	//mFishNode->rotate(Quaternion(Degree(90), Vector3::UNIT_Y));
	// 첫 위치를 모델의 방향을 생각하여 놓아주면, 따로 로테이트 시켜 줄 필요가 없습니다.
  }

  bool frameStarted(const FrameEvent &evt)
  {
    // Fill Here ----------------------------------------------

	  static bool bTurning = false;
	  // 이 함수 안에서만 사용되는 거면 멤버 변수로 쓰지 마십시오.

	  if (mProfessorNode->getPosition().z > MAX_MOVE_POS_Z
		  || mProfessorNode->getPosition().z < MIN_MOVE_POS_Z)
	  {
		  mProfessorVelocity *= -1;

		  Vector3 vCurrentPos = mProfessorNode->getPosition();
		  vCurrentPos.z = MAX_MOVE_POS_Z * ((0 < vCurrentPos.z) ? 1.f : -1.f);

		  mProfessorNode->setPosition(vCurrentPos);
		  mProfessorMoveState = TUNING;
		  bTurning = true;
	  }


	  // 상태 변화를 체크하는 부분
	  switch (mProfessorMoveState)
	  {
	  case MainListener::BASIC:
		  break;

	  case MainListener::TUNING:
		  if (mProfessorRotation.y >= PROFESSOR_ROTATE_RANGE)
		  {
			  mProfessorRotation = 0.f;
			  bTurning = false;
		  }
		  break;

	  default:
		  break;
	  }

	  // 상태에 따라 처리하는 부분 이 두 가지를 나누어서 처리한다.
	  switch (mProfessorMoveState)
	  {
	  case MainListener::BASIC:
		  break;

	  case MainListener::TUNING:
		  mProfessorRotation.y += PROFESSOR_ROTATE_SPEED;
		  mProfessorNode->rotate(Vector3(0.f, 1.f, 0.f), Degree(PROFESSOR_ROTATE_SPEED));
		  break;

	  default:
		  break;
	  }


	  mProfessorNode->translate(0.f, 0.f, mProfessorVelocity * evt.timeSinceLastFrame);
	  mFishAxisNode->translate(0.f, 0.f, mProfessorVelocity * evt.timeSinceLastFrame);
	  mFishAxisNode->rotate(Vector3(0.f, 1.f, 0.f), Degree(-FISH_ROTATE_SPEED));
	  
    // --------------------------------------------------------

    return true;
  }

};

class LectureApp {

  Root* mRoot;
  RenderWindow* mWindow;
  SceneManager* mSceneMgr;
  Camera* mCamera;
  Viewport* mViewport;
  OIS::Keyboard* mKeyboard;
  OIS::InputManager *mInputManager;

  MainListener* mMainListener;
  ESCListener* mESCListener;

public:

  LectureApp() {}

  ~LectureApp() {}

  void go(void)
  {
    // OGRE의 메인 루트 오브젝트 생성
#if !defined(_DEBUG)
    mRoot = new Root("plugins.cfg", "ogre.cfg", "ogre.log");
#else
    mRoot = new Root("plugins_d.cfg", "ogre.cfg", "ogre.log");
#endif


    // 초기 시작의 컨피규레이션 설정 - ogre.cfg 이용
    if (!mRoot->restoreConfig()) {
      if (!mRoot->showConfigDialog()) return;
    }

    mWindow = mRoot->initialise(true, "Rotate : Copyleft by Dae-Hyun Lee");


    // ESC key를 눌렀을 경우, 오우거 메인 렌더링 루프의 탈출을 처리
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem(pl);
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));


    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");
    mCamera = mSceneMgr->createCamera("main");


    mCamera->setPosition(0.0f, 100.0f, 700.0f);
    mCamera->lookAt(0.0f, 100.0f, 0.0f);

    mCamera->setNearClipDistance(5.0f);

    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.0f,0.0f,0.5f));
    mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));


    ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    // 좌표축 표시
    Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
    mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode",Ogre::Vector3(0,0,0))->attachObject(mAxesEntity);
    mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

    _drawGridPlane();


    SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Professor", Vector3(0.0f, 0.0f, 0.0f));
	node1->attachObject(mSceneMgr->createEntity("Professor", "DustinBody.mesh"));

	SceneNode* EmptyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("FishAxisNode", Vector3(0.0f, 0.0f, 0.0f));

	SceneNode* node2 = EmptyNode->createChildSceneNode("Fish", Vector3(0.0f, 0.0f, FISH_DISTANCE_FROM_CENTER));
	node2->attachObject(mSceneMgr->createEntity("Fish", "fish.mesh"));

    mESCListener =new ESCListener(mKeyboard);
    mRoot->addFrameListener(mESCListener);

    mMainListener = new MainListener(mRoot, mKeyboard);
    mRoot->addFrameListener(mMainListener);


    mRoot->startRendering();

    mInputManager->destroyInputObject(mKeyboard);
    OIS::InputManager::destroyInputSystem(mInputManager);

    delete mRoot;
  }

private:
  void _drawGridPlane(void)
  {
    Ogre::ManualObject* gridPlane =  mSceneMgr->createManualObject("GridPlane"); 
    Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode"); 

    Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial","General"); 
    gridPlaneMaterial->setReceiveShadows(false); 
    gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,0); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1,1,1); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,1,1); 

    gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
    for(int i=0; i<21; i++)
    {
      gridPlane->position(-500.0f, 0.0f, 500.0f-i*50);
      gridPlane->position(500.0f, 0.0f, 500.0f-i*50);

      gridPlane->position(-500.f+i*50, 0.f, 500.0f);
      gridPlane->position(-500.f+i*50, 0.f, -500.f);
    }

    gridPlane->end(); 

    gridPlaneNode->attachObject(gridPlane);
  }
};


#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
  INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
  int main(int argc, char *argv[])
#endif
  {
    LectureApp app;

    try {

      app.go();

    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::cerr << "An exception has occured: " <<
        e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
  }

#ifdef __cplusplus
}
#endif

