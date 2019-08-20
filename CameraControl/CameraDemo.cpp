
#include <TL-Engine.h>
using namespace tle;

#include <sstream>
#include "Camera.hpp"

const EEngineType ENGINE_TYPE = kTLX;
const string ASSETS_FOLDER = "Media";
const float CUBE_MOVE_SPEED = 50.0f;
const float CUBE_ROT_SPEED = 100.0f;
const float CUBE_POS_OFFSET = 5.0f;

I3DEngine* gpEngine;
IMesh* gpGridMesh;
IMesh* gpCubeMesh;
IMesh* gpDummyMesh;
ISprite* gpDebugSrpite;
IFont* gpDebugFont;
IModel* gpCube1;
IModel* gpCube2;
IModel* gpDummy1;
IModel* gpDummy2;

CCamera* gpCamera;

void Start();
void Update();
void End();

void main()
{
	Start();

	// The main game loop, repeat until engine is stopped
	while (gpEngine->IsRunning())
	{
		// Draw the scene
		gpEngine->DrawScene();

		/**** Update your scene each frame here ****/

		Update();

		if (gpEngine->KeyHit(Key_Escape))
		{
			gpEngine->Stop();
		}
	}

	End();

	// Delete the 3D engine now we are finished with it
	gpEngine->Delete();
}

void Start()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	gpEngine = New3DEngine(ENGINE_TYPE);
	gpEngine->StartWindowed();

	// Add default folder for meshes and other media
	gpEngine->AddMediaFolder(ASSETS_FOLDER);

	/**** Set up your scene here ****/

	gpGridMesh = gpEngine->LoadMesh("Grid.x");
	gpCubeMesh = gpEngine->LoadMesh("Cube.x");
	gpDummyMesh = gpEngine->LoadMesh("Dummy.x");
	gpDebugSrpite = gpEngine->CreateSprite("Debug.png", 10.0f, 10.0f, 0.0f);
	gpDebugFont = gpEngine->LoadFont("Arial", 20);

	gpGridMesh->CreateModel(0.0f, 0.0f, 0.0f);
	gpDummy1 = gpDummyMesh->CreateModel(-25.0f, 10.0f, -25.0f);
	gpDummy2 = gpDummyMesh->CreateModel(25.0f, 10.0f, 25.0f);

	gpCube1 = gpCubeMesh->CreateModel(0.0f, 0.0f, 0.0f);
	gpCube2 = gpCubeMesh->CreateModel(0.0f, 0.0f, 0.0f);

	gpCube1->AttachToParent(gpDummy1);
	gpCube2->AttachToParent(gpDummy2);

	gpCube1->MoveY(-CUBE_POS_OFFSET);
	gpCube2->MoveY(-CUBE_POS_OFFSET);

	gpCamera = new CCamera(gpEngine->CreateCamera(CAMERA_TYPE));

	gpEngine->Timer();
}

void Update()
{
	const float updateTime = gpEngine->Timer();

	// Get camera matrix data.
	const float* cameraMatrix = gpCamera->GetMatrix();

	// Display camera matrix in debug window.
	stringstream outText;
	outText.precision(2);

	// Matrix row X.
	outText << cameraMatrix[0];
	gpDebugFont->Draw(outText.str(), 15, 15, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[1];
	gpDebugFont->Draw(outText.str(), 105, 15, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[2];
	gpDebugFont->Draw(outText.str(), 165, 15, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[3];
	gpDebugFont->Draw(outText.str(), 245, 15, kWhite, kLeft, kTop);
	outText.str("");

	// Matrix row Y.
	outText << cameraMatrix[4];
	gpDebugFont->Draw(outText.str(), 15, 45, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[5];
	gpDebugFont->Draw(outText.str(), 105, 45, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[6];
	gpDebugFont->Draw(outText.str(), 165, 45, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[7];
	gpDebugFont->Draw(outText.str(), 245, 45, kWhite, kLeft, kTop);
	outText.str("");

	// Matrix row Z.
	outText << cameraMatrix[8];
	gpDebugFont->Draw(outText.str(), 15, 75, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[9];
	gpDebugFont->Draw(outText.str(), 105, 75, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[10];
	gpDebugFont->Draw(outText.str(), 165, 75, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[11];
	gpDebugFont->Draw(outText.str(), 245, 75, kWhite, kLeft, kTop);
	outText.str("");

	// Matrix row P.
	outText << cameraMatrix[12];
	gpDebugFont->Draw(outText.str(), 15, 105, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[13];
	gpDebugFont->Draw(outText.str(), 105, 105, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[14];
	gpDebugFont->Draw(outText.str(), 165, 105, kWhite, kLeft, kTop);
	outText.str("");
	outText << cameraMatrix[15];
	gpDebugFont->Draw(outText.str(), 245, 105, kWhite, kLeft, kTop);

	// Movement controls for cube 1.
	if (gpEngine->KeyHeld(Key_W))
	{
		gpDummy1->MoveLocalZ(CUBE_MOVE_SPEED * updateTime);
	}
	else if (gpEngine->KeyHeld(Key_S))
	{
		gpDummy1->MoveLocalZ(-CUBE_MOVE_SPEED * updateTime);
	}
	if (gpEngine->KeyHeld(Key_A))
	{
		gpDummy1->RotateLocalY(-CUBE_ROT_SPEED * updateTime);
	}
	else if (gpEngine->KeyHeld(Key_D))
	{
		gpDummy1->RotateLocalY(CUBE_ROT_SPEED * updateTime);
	}

	if (gpEngine->KeyHit(Key_R))
	{
		gpCamera->Reset();
	}
	else if (gpEngine->KeyHit(Key_1))
	{
		gpCamera->Attach(gpDummy1);
	}
	else if (gpEngine->KeyHit(Key_2))
	{
		gpCamera->Detach(gpDummy1);
	}
}

void End()
{
	gpEngine->RemoveMesh(gpDummyMesh);
	gpEngine->RemoveMesh(gpCubeMesh);
	gpEngine->RemoveMesh(gpGridMesh);
	gpEngine->RemoveSprite(gpDebugSrpite);
	gpEngine->RemoveFont(gpDebugFont);
	gpEngine->RemoveCamera(gpCamera->GetCamera());

	delete gpCamera;
}