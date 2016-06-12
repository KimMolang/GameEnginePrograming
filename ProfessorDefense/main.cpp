#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include "main.h"
#include "InputController.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
}

void CMainGame::go(void)
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

	//mWindow = mRoot->initialise(true, CLIENT_DESCRIPTION " : Copyleft by Dae-Hyun Lee");
	mWindow = mRoot->initialise(true, "ProfessorDefense");

	mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");

	//mOverlaySystem = new Ogre::OverlaySystem();
	//mSceneMgr->addRenderQueueListener(mOverlaySystem);

	//mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

	mCamera = mSceneMgr->createCamera("main");

	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));
	mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(1000);


	ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


#ifdef _DEBUG
	_drawGridPlane();
#endif
	_setLights();
	_drawGroundPlane();
	//_setOverlay();

	//SceneNode* professorRoot = mSceneMgr->getRootSceneNode()->createChildSceneNode("ProfessorRoot");
	//SceneNode* professorYaw = professorRoot->createChildSceneNode("ProfessorYaw");


	SceneNode* cameraYaw = mSceneMgr->getRootSceneNode()->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
	SceneNode* cameraPitch = cameraYaw->createChildSceneNode("CameraPitch");
	SceneNode* cameraHolder = cameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, 500.0f));
	SceneNode* GunRoot = cameraHolder->createChildSceneNode("Gun", Vector3(55.0f, -55.0f, -100.0f));
	Entity* entityGun = mSceneMgr->createEntity("Gun", "fish.mesh");
	GunRoot->attachObject(entityGun);
	entityGun->setCastShadows(true);
	GunRoot->rotate(Quaternion(Degree(270), Vector3::UNIT_Y));
	GunRoot->scale(20.f, 20.f, 20.f);


	SceneNode* professor = mSceneMgr->getRootSceneNode()->createChildSceneNode("Professor");
	Entity* entityProfessor = mSceneMgr->createEntity("Professor", "DustinBody.mesh");
	professor->attachObject(entityProfessor);
	entityProfessor->setCastShadows(true);

	cameraHolder->attachObject(mCamera);
	mCamera->lookAt(cameraYaw->getPosition());

	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	OIS::ParamList pl;
	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	InputController* inputController = new InputController(mRoot, mKeyboard, mMouse);
	mRoot->addFrameListener(inputController);

	mRoot->startRendering();

	mInputManager->destroyInputObject(mKeyboard);
	mInputManager->destroyInputObject(mMouse);
	OIS::InputManager::destroyInputSystem(mInputManager);

	delete inputController;

	delete mRoot;
}

//void CMainGame::_setOverlay(void)
//{
//	mOverlayMgr = OverlayManager::getSingletonPtr();
//	mTextOverlay = mOverlayMgr->create("TextOverlay");
//
//	mPanel = static_cast<Ogre::OverlayContainer*>
//		(mOverlayMgr->createOverlayElement("Panel", "container1"));
//	mPanel->setDimensions(1, 1);
//	mPanel->setPosition(-0.3f, 0.5f);
//
//	OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID");
//	textBox->setMetricsMode(Ogre::GMM_PIXELS);
//	textBox->setPosition(10, 10);
//	textBox->setWidth(100);
//	textBox->setHeight(20);
//	textBox->setParameter("font_name", "Font/NanumBold18");
//	textBox->setParameter("char_height", "40");
//	textBox->setColour(Ogre::ColourValue::White);
//	textBox->setCaption(L"이대현 교수님 HP");
//
//	mPanel->addChild(textBox);
//	mTextOverlay->add2D(mPanel); mTextOverlay->show();
//}

void CMainGame::_setLights(void)
{
	mSceneMgr->setAmbientLight(ColourValue(0.3f, 0.3f, 0.3f));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	mLightP = mSceneMgr->createLight("LightP");
	mLightP->setType(Light::LT_POINT);
	mLightP->setPosition(Vector3(0.0f, 800.0f, 0.0f));
	mLightP->setVisible(true);
}

void CMainGame::_drawGroundPlane(void)
{
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1800, 1800,
		1, 1,
		true, 1, 5, 5,
		Vector3::NEGATIVE_UNIT_Z
		);

	Entity* groundEntity = mSceneMgr->createEntity("GroundPlane", "Ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setMaterialName("Ground");
	groundEntity->setCastShadows(false);
}

void CMainGame::_drawGridPlane(void)
{
	// 좌표축 표시
	Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
	mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode", Ogre::Vector3(0, 0, 0))->attachObject(mAxesEntity);
	mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

	Ogre::ManualObject* gridPlane = mSceneMgr->createManualObject("GridPlane");
	Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

	Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
	gridPlaneMaterial->setReceiveShadows(false);
	gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

	gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	for (int i = 0; i < 21; i++)
	{
		gridPlane->position(-500.0f, 0.0f, 500.0f - i * 50);
		gridPlane->position(500.0f, 0.0f, 500.0f - i * 50);

		gridPlane->position(-500.f + i * 50, 0.f, 500.0f);
		gridPlane->position(-500.f + i * 50, 0.f, -500.f);
	}

	gridPlane->end();

	gridPlaneNode->attachObject(gridPlane);
}


#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
		CMainGame app;

		try {

			app.go();

	}
		catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
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

