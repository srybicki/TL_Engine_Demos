
#ifndef _CAMERA_H
#define _CAMERA_H

#include <TL-Engine.h>
using namespace tle;

#include "Definitions.hpp"

const ECameraType CAMERA_TYPE = kManual;

const SPosition3f CAMERA_START_POS =
{
	0.0f, 50.0f, -100.0f
};

const float CAMERA_START_ROT = 25.0f;

const SPosition2f CAMERA_POS_OFFSET
{
	20.0f, -25.0f
};

class CCamera
{

public:

	// Constructor.
	// Sets new camera default position, original matrix and current matrix.
	CCamera(ICamera* pCamera);

	// Destructor.
	// Clears the matrix data from memory.
	~CCamera();

	// Parents the camera to dummy that has child game object.
	void Attach(IModel* pTargetObject);

	// Unparents the camera from a dummy object.
	void Detach(IModel* pTargetObject);

	// Resets the camera position to the original position.
	void Reset();

	// Returns true is the camera has a parent.
	const bool IsAttached() const;

	// Returns the current camera matrix.
	const float* GetMatrix() const;

	// Returns the camera object.
	ICamera* GetCamera() const;

private:

	// TL camera object.
	ICamera* mpCamera;

	// Matrix (4x4) to store the first camera position.
	float* mpOriginalMatrix;

	// Matrix (4x4) to store the current camera position.
	float* mpCurrentMatrix;

	// Flag to check if the camera has a parent.
	bool mAttached;

};

#endif  // _CAMERA_H