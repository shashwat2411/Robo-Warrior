#include "component.h"

void Rigidbody::Start()
{
	gameObject->rigidbody = this;
	Speed = D3DXVECTOR3(0.00001f, 0.0f, 0.0f);
	Acceleration = ACCELERATION_VALUE;
	useGravity = false;
	mass = 1.0f;
	groundLevel = 0.0f;
}

void Rigidbody::End()
{

}

void Rigidbody::Update()
{
	if (FollowTarget != nullptr)
	{
		D3DXVECTOR3 diff = FollowTarget->transform->Position - gameObject->transform->Position;

		gameObject->transform->Position = FollowTarget->transform->Position - (*D3DXVec3Normalize(&diff, &diff) * distance);

		gameObject->FaceTowardsXYZ(FollowTarget);
	}
	else
	{
	}

	if (useGravity == true)
	{
		gameObject->rigidbody->Speed.y -= GRAVITY_CONSTANT / 60.0f * GRAVITY_ACCELERATION * mass;

		if (gameObject->transform->Position.y <= groundLevel)
		{
			gameObject->transform->Position.y = groundLevel;
			gameObject->rigidbody->Speed.y = 0.0f;
		}
	}
}

void Rigidbody::Draw()
{
}
