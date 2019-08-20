// DelayTL.cpp: A program using the TL-Engine

#include <sstream>
#include <iostream>
using namespace std;

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

//const float DELAY = 500.0f;
const float DELAY = 60.0f;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	/**** Set up your scene here ****/
	IFont* frontFont = myEngine->LoadFont("Font2.bmp");

	myEngine->Timer();

	//const float frameTotalMax = DELAY / 1000.0f;
	const float frameTotalMax = DELAY;
	float frameTotal = 0.0f;
	int frameCounter = 0;

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		//float updateTime = 1 / 60.0f;

		/**** Update your scene each frame here ****/
		//float updateTime = myEngine->Timer();
		float updateTime = 1 / 60.0f;

		const float fps = 1.0f / updateTime;
		const float frameTime = 1.0f / fps;

		stringstream outText;
		outText << "Frame Time: " << frameTime;    // Can't use endl with TL fonts...
		frontFont->Draw(outText.str(), 0, 0, kRed); // ...use multiple draw calls instead
		outText.str(""); // How to clear outText for further draw calls
		outText << "FPS: " << fps;
		frontFont->Draw(outText.str(), 0, 20, kRed);
		outText.str("");

		if (frameTotal < frameTotalMax)
		{
			frameTotal += frameTime;
		}
		else
		{
			frameCounter += 1;
			cout << frameCounter << endl;
			frameTotal = 0.0f;
		}

		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
