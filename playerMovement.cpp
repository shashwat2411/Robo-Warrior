#include "script.h"
#include "scene.h"
#include "manager.h"

void PlayerMovement::Start()
{
	gameObject->AddComponent<Rigidbody>()->useGravity = true;
	gameObject->rigidbody->groundLevel = 1.01f;

	rotationDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = false;
}

void PlayerMovement::End()
{
}

void PlayerMovement::Update()
{
	//Trash
	/*
	|----------------------------------TRASH--------------------------------
	|gameObject->transform->Rotation.z += 1.0f;
	|
	|OpenWorldControls
	|{
	|	if (Input::GetKeyPress('W'))
	|	{
	|		directionZ = gameObject->GetForwardDirection();
	|	}
	|	else if (Input::GetKeyPress('S'))
	|	{
	|		directionZ = -gameObject->GetForwardDirection();
	|	}
	|	if (Input::GetKeyPress('A'))
	|	{
	|		directionX = -gameObject->GetRightDirection();
	|	}
	|	else if (Input::GetKeyPress('D'))
	|	{
	|		directionX = gameObject->GetRightDirection();
	|	}
	|}
	|gameObject->rigidbody->Speed += -gameObject->GetForwardDirection() * SPEED_VALUE * ACCELERATION_VALUE;
	|
	|if (Input::GetKeyPress('A'))
	|{
	|	gameObject->rigidbody->Speed.x -= SPEED_VALUE * ACCELERATION_VALUE;
	|}
	|else if (Input::GetKeyPress('D'))
	|{
	|	gameObject->rigidbody->Speed.x += SPEED_VALUE * ACCELERATION_VALUE;
	|}
	|if (Input::GetKeyPress('W'))
	|{
	|	gameObject->rigidbody->Speed.z += SPEED_VALUE * ACCELERATION_VALUE;
	|}
	|else if (Input::GetKeyPress('S'))
	|{
	|	gameObject->rigidbody->Speed.z -= SPEED_VALUE * ACCELERATION_VALUE;
	|}
	|
	|if (Input::GetKeyPress('Q'))
	|{
	|	gameObject->transform->Rotation.y -= 1.0f;
	|}
	|else if (Input::GetKeyPress('E'))
	|{
	|	gameObject->transform->Rotation.y += 1.0f;
	|}
	|
	|if (Input::GetKeyTrigger(VK_SPACE))
	|{
	|	//gameObject->rigidbody->Speed.y = 0.3f;
	|	Animator* animator = gameObject->GetComponentInChildren<Animator>();
	|	Animation::ANIMATION_STATUS stat1 = animator->GetAnimationState(0);
	|	Animation::ANIMATION_STATUS stat2 = animator->GetAnimationState(2);
	|	if ((stat1 == Animation::STANDBY || stat1 == Animation::END) && (stat2 == Animation::STANDBY || stat2 == Animation::END))
	|	{
	|		if (animator->GetAnimationState(1) == Animation::PLAYBACK)
	|		{
	|			animator->StopAnimation(1);
	|			animator->PlayAnimation(4);
	|		}
	|		else
	|		{
	|			animator->PlayAnimation(3);
	|		}
	|	}
	|}
	|-----------------------------------------------------------------------
	*/

	D3DXVECTOR3 directionZ(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 directionX(0.0f, 0.0f, 0.0f);

	CHARACTER* character = (CHARACTER*)gameObject->Children[0];
	PLAYER* player = (PLAYER*)gameObject;

	if (player->dead == false)
	{
		//TopDownControls
		if (character->disable == false)
		{
			if (Input::GetKeyPress('W')) { directionZ = gameObject->GetForwardDirection();	move = true; rotationDirection.y = 0.0f; }
			else if (Input::GetKeyPress('S')) { directionZ = -gameObject->GetForwardDirection();	move = true; rotationDirection.y = 180.0f; }
			if (Input::GetKeyPress('A')) { directionX = -gameObject->GetRightDirection();		move = true; rotationDirection.y = 270.0f; }
			else if (Input::GetKeyPress('D')) { directionX = gameObject->GetRightDirection();		move = true; rotationDirection.y = 90.0f; }

			if (Input::GetKeyPress('W') && Input::GetKeyPress('A')) { move = true; rotationDirection.y = 315.0f; }
			else if (Input::GetKeyPress('W') && Input::GetKeyPress('D')) { move = true; rotationDirection.y = 45.0f; }
			else if (Input::GetKeyPress('S') && Input::GetKeyPress('A')) { move = true; rotationDirection.y = 225.0f; }
			else if (Input::GetKeyPress('S') && Input::GetKeyPress('D')) { move = true; rotationDirection.y = 135.0f; }


		}
		D3DXVECTOR3 direction = directionX + directionZ;
		D3DXVec3Normalize(&direction, &direction);

		{
			gameObject->rigidbody->Speed += D3DXVECTOR3(direction.x * SPEED_VALUE * gameObject->rigidbody->Acceleration, 0.0f, direction.z * SPEED_VALUE * gameObject->rigidbody->Acceleration);
		}


		gameObject->transform->Position += gameObject->rigidbody->Speed;

		//Rotation
		{
			float rot = (rotationDirection.y - character->transform->Rotation.y);	//‰ñ“]Šp“x‚Ì·•ª
			if (rot > 90) { rot = rot - 360; }
			if (rot < -90) { rot = rot + 360; }

			if (fabs(rot) < D3DXToRadian(2)) { character->transform->Rotation.y = rotationDirection.y; }
			else { character->transform->Rotation.y += rot * 0.3f; }
		}
	}

	gameObject->rigidbody->Speed.x *= 0.9f;
	gameObject->rigidbody->Speed.z *= 0.9f;

}

void PlayerMovement::Draw()
{

}