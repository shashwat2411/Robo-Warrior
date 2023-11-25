#include "component.h"

void Camera::Start()
{
	gameObject->transform->Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	fov = 60.0f;

	at = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx, vz;
	vx = gameObject->transform->Position.x - at.x;
	vz = gameObject->transform->Position.z - at.z;
	len = sqrtf(vx * vx + vz * vz);

	rad = 0.0f;

	shake = false;
	shakeCounter = 0;
	shakeValue = 0.0f;
}

void Camera::End()
{
}

void Camera::Update()
{
	//if (Input::GetKeyPress('C'))
	//{
	//	rad += 1.0f;
	//}
	//if (Input::GetKeyPress('V'))
	//{
	//	rad -= 1.0f;
	//}

	//float X = ((gameObject->transform->Position.x * cosf(rad)) - (gameObject->transform->Position.y * sinf(rad)));
	//float Y = ((gameObject->transform->Position.x * sinf(rad)) + (gameObject->transform->Position.y * cosf(rad)));

	//gameObject->transform->Position.x = gameObject->transform->Position.x + X;
	//gameObject->transform->Position.y = gameObject->transform->Position.y + Y;
}

void Camera::Draw()
{
	if (Target != nullptr) { at = Target->transform->GlobalPosition; }

	D3DXMatrixLookAtLH(&mtxView, &gameObject->transform->Position, &at, &Up);
	Renderer::SetViewMatrix(&mtxView);

	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	Renderer::SetProjectionMatrix(&mtxProjection);
}

void Camera::CameraShake(float value)
{
	if (shake == false)
	{
		shake = true;
		shakeValue = value * 2;
		shakeCounter = 0;
	}
}