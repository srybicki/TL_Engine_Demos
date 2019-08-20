
#include "Camera.hpp"

CCamera::CCamera(ICamera* pCamera)
{
	mpCamera = pCamera;
	mpCamera->SetPosition(CAMERA_START_POS.mX, CAMERA_START_POS.mY, CAMERA_START_POS.mZ);
	mpCamera->RotateLocalX(CAMERA_START_ROT);

	mpOriginalMatrix = new float[MATRIX_SIZE * MATRIX_SIZE];
	mpCurrentMatrix = new float[MATRIX_SIZE * MATRIX_SIZE];

	mpCamera->GetMatrix(mpOriginalMatrix);
	mpCamera->GetMatrix(mpCurrentMatrix);

	mAttached = false;
}

CCamera::~CCamera()
{
	delete mpOriginalMatrix; mpOriginalMatrix = nullptr;
	delete mpCurrentMatrix;  mpCurrentMatrix = nullptr;
}

void CCamera::Attach(IModel* pTargetObject)
{
	if (!mAttached)
	{
		mAttached = true;

		mpCamera->AttachToParent(pTargetObject);
		mpCamera->ResetOrientation();
		mpCamera->SetPosition(pTargetObject->GetX(), pTargetObject->GetY(), pTargetObject->GetZ());
		mpCamera->MoveLocalY(CAMERA_POS_OFFSET.mX);
		mpCamera->MoveLocalZ(CAMERA_POS_OFFSET.mY);
		mpCamera->LookAt(pTargetObject);
	}
}

void CCamera::Detach(IModel* pTargetObject)
{
	if (mAttached)
	{
		mAttached = false;

		pTargetObject->GetMatrix(mpCurrentMatrix);
		mpCamera->DetachFromParent();
		mpCamera->SetMatrix(mpCurrentMatrix);
		mpCamera->MoveLocalY(CAMERA_POS_OFFSET.mX);
		mpCamera->MoveLocalZ(CAMERA_POS_OFFSET.mY);
		mpCamera->LookAt(pTargetObject);
	}
}

void CCamera::Reset()
{
	if (mAttached)
	{
		mAttached = false;

		mpCamera->DetachFromParent();
	}

	mpCamera->SetMatrix(mpOriginalMatrix);
}

const bool CCamera::IsAttached() const
{
	return mAttached;
}

const float* CCamera::GetMatrix() const
{
	mpCamera->GetMatrix(mpCurrentMatrix);

	return mpCurrentMatrix;
}

ICamera* CCamera::GetCamera() const
{
	return mpCamera;
}