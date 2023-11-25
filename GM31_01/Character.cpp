#include "prefab.h"
#include "manager.h"
#include "scene.h"
#include "soundReader.h"

void CHARACTER::Start()
{
	Init();

	SCENE* scene = Manager::GetScene();

	sprintf(tag, "character");

	transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	transform->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float divider = 6.0f;

	body = scene->AddGameObject<EMPTYOBJECT>();
	body->SetParent(this);
	body->transform->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	body->transform->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parts.push_back(body);

	innerbody = scene->AddGameObject<EMPTYOBJECT>();
	innerbody->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\body.obj");
	innerbody->SetParent(body);
	innerbody->transform->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	innerbody->transform->Rotation = D3DXVECTOR3(0.0f, 0.0f, 180.0f);
	parts.push_back(innerbody);

	AddComponent<SphereCollider>()->SetCollisionSize(0.4f);

	//左腕
	{
		//L_arm1 = scene->AddGameObject<EMPTYOBJECT>();
		//L_arm2 = scene->AddGameObject<EMPTYOBJECT>();
		//L_arm3 = scene->AddGameObject<EMPTYOBJECT>();
		L_joint1 = scene->AddGameObject<EMPTYOBJECT>();
		L_joint2 = scene->AddGameObject<EMPTYOBJECT>();
		L_joint3 = scene->AddGameObject<EMPTYOBJECT>();
		L_hand = scene->AddGameObject<EMPTYOBJECT>();
		L_fist = scene->AddGameObject<EMPTYOBJECT>();
		L_arm1_cover = scene->AddGameObject<EMPTYOBJECT>();
		L_arm2_cover = scene->AddGameObject<EMPTYOBJECT>();
		L_arm3_cover = scene->AddGameObject<EMPTYOBJECT>();

		L_joint1->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\joint.obj");
		L_joint2->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\joint.obj");
		L_joint3->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\joint.obj");
		//L_arm1->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm.obj");
		//L_arm2->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm.obj");
		//L_arm3->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm.obj");
		L_hand->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\hand.obj");
		L_fist->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\fist.obj");
		L_arm1_cover->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm1_cover.obj");
		L_arm2_cover->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm2_cover.obj");
		L_arm3_cover->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm3_cover.obj");

		L_joint1->SetParent(body);
		L_joint2->SetParent(L_joint1);
		L_joint3->SetParent(L_joint2);
		//L_arm1->SetParent(L_joint1);
		//L_arm2->SetParent(L_joint2);
		//L_arm3->SetParent(L_joint3);
		L_hand->SetParent(L_joint3);
		L_fist->SetParent(L_hand);
		L_arm1_cover->SetParent(L_joint1);
		L_arm2_cover->SetParent(L_joint2);
		L_arm3_cover->SetParent(L_joint3);

		L_joint1->transform->Position = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		L_joint2->transform->Position = D3DXVECTOR3(-1.235f / divider, 0.0f, 2.679f / divider);
		L_joint3->transform->Position = D3DXVECTOR3(-3.262f / divider, 0.0f, 2.133f / divider);
		//L_arm1->transform->Position = D3DXVECTOR3(-0.369f / divider, 0.0f, 0.811f / divider);
		//L_arm2->transform->Position = D3DXVECTOR3(-1.507f / divider, 0.0f, 0.987f / divider);
		//L_arm3->transform->Position = D3DXVECTOR3(-2.156f / divider, 0.0f, -0.006f / divider);
		L_hand->transform->Position = D3DXVECTOR3(-5.086f / divider, 0.0f, 0.0f);
		L_fist->transform->Position = D3DXVECTOR3(-2.489f / divider, 0.0f, -0.594f / divider);
		L_arm1_cover->transform->Position = D3DXVECTOR3(-0.201f / divider, 0.0f, 0.469f / divider);
		L_arm2_cover->transform->Position = D3DXVECTOR3(-1.507f / divider, 0.0f, 0.987f / divider);
		L_arm3_cover->transform->Position = D3DXVECTOR3(-2.156f / divider, 0.0f, 0.0f / divider);

		L_joint1->transform->Rotation = D3DXVECTOR3(180.0f, 37.867f, 0.0f);
		L_joint2->transform->Rotation = D3DXVECTOR3(0.0f, 23.368f, 0.0f);
		L_joint3->transform->Rotation = D3DXVECTOR3(0.0f, -62.098f, 0.0f);
		//L_arm1->transform->Rotation = D3DXVECTOR3(90.0f, -26.071f, 0.0f);
		//L_arm2->transform->Rotation = D3DXVECTOR3(90.0f, -55.573f, 0.0f);
		//L_arm3->transform->Rotation = D3DXVECTOR3(90.0f, -88.989f, 0.0f);
		L_hand->transform->Rotation = D3DXVECTOR3(0.0f, -1.071f, 0.0f);
		L_fist->transform->Rotation = D3DXVECTOR3(-1.5f, -108.0f, -97.5f);
		L_arm1_cover->transform->Rotation = D3DXVECTOR3(90.0f, -26.071f, 0.0f);
		L_arm2_cover->transform->Rotation = D3DXVECTOR3(90.0f, -55.573f, 0.0f);
		L_arm3_cover->transform->Rotation = D3DXVECTOR3(90.0f, -88.989f, 0.0f);

		L_fist->AddComponent<SphereCollider>()->SetCollisionSize(1.3f);
		L_fist->AddComponent<PlayerAttack>();

		parts.push_back(L_joint1);
		parts.push_back(L_joint2);
		parts.push_back(L_joint3);
		//parts.push_back(L_arm1);
		//parts.push_back(L_arm2);
		//parts.push_back(L_arm3);
		parts.push_back(L_hand);
		parts.push_back(L_fist);
		parts.push_back(L_arm1_cover);
		parts.push_back(L_arm2_cover);
		parts.push_back(L_arm3_cover);
	}
	//右腕
	{
		//R_arm1 = scene->AddGameObject<EMPTYOBJECT>();
		//R_arm2 = scene->AddGameObject<EMPTYOBJECT>();
		//R_arm3 = scene->AddGameObject<EMPTYOBJECT>();
		R_joint1 = scene->AddGameObject<EMPTYOBJECT>();
		R_joint2 = scene->AddGameObject<EMPTYOBJECT>();
		R_joint3 = scene->AddGameObject<EMPTYOBJECT>();
		R_hand = scene->AddGameObject<EMPTYOBJECT>();
		R_fist = scene->AddGameObject<EMPTYOBJECT>();
		R_arm1_cover = scene->AddGameObject<EMPTYOBJECT>();
		R_arm2_cover = scene->AddGameObject<EMPTYOBJECT>();
		R_arm3_cover = scene->AddGameObject<EMPTYOBJECT>();

		R_joint1->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\joint.obj");
		R_joint2->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\joint.obj");
		R_joint3->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\joint.obj");
		//R_arm1->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm.obj");
		//R_arm2->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm.obj");
		//R_arm3->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm.obj");
		R_hand->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\hand.obj");
		R_fist->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\fist.obj");
		R_arm1_cover->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm1_cover.obj");
		R_arm2_cover->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm2_cover.obj");
		R_arm3_cover->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Character\\arm3_cover.obj");

		R_joint1->SetParent(body);
		R_joint2->SetParent(R_joint1);
		R_joint3->SetParent(R_joint2);
		//R_arm1->SetParent(R_joint1);
		//R_arm2->SetParent(R_joint2);
		//R_arm3->SetParent(R_joint3);
		R_hand->SetParent(R_joint3);
		R_fist->SetParent(R_hand);
		R_arm1_cover->SetParent(R_joint1);
		R_arm2_cover->SetParent(R_joint2);
		R_arm3_cover->SetParent(R_joint3);

		R_joint1->transform->Position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		R_joint2->transform->Position = D3DXVECTOR3(-1.235f / divider, 0.0f, 2.679f / divider);
		R_joint3->transform->Position = D3DXVECTOR3(-3.262f / divider, 0.0f, 2.133f / divider);
		//R_arm1->transform->Position = D3DXVECTOR3(-0.369f / divider, 0.0f, 0.811f / divider);
		//R_arm2->transform->Position = D3DXVECTOR3(-1.507f / divider, 0.0f, 0.987f / divider);
		//R_arm3->transform->Position = D3DXVECTOR3(-2.156f / divider, 0.0f, -0.006f / divider);
		R_hand->transform->Position = D3DXVECTOR3(-5.086f / divider, 0.0f, 0.0f);
		R_fist->transform->Position = D3DXVECTOR3(-2.489f / divider, 0.0f, -0.594f / divider);
		R_arm1_cover->transform->Position = D3DXVECTOR3(-0.201f / divider, 0.0f, 0.469f / divider);
		R_arm2_cover->transform->Position = D3DXVECTOR3(-1.507f / divider, 0.0f, 0.987f / divider);
		R_arm3_cover->transform->Position = D3DXVECTOR3(-2.156f / divider, 0.0f, 0.0f / divider);

		R_joint1->transform->Rotation = D3DXVECTOR3(0.0f, 142.133f, 0.0f);
		R_joint2->transform->Rotation = D3DXVECTOR3(0.0f, 23.368f, 0.0f);
		R_joint3->transform->Rotation = D3DXVECTOR3(0.0f, -62.098f, 0.0f);
		//R_arm1->transform->Rotation = D3DXVECTOR3(90.0f, -26.071f, 0.0f);
		//R_arm2->transform->Rotation = D3DXVECTOR3(90.0f, -55.573f, 0.0f);
		//R_arm3->transform->Rotation = D3DXVECTOR3(90.0f, -88.989f, 0.0f);
		R_hand->transform->Rotation = D3DXVECTOR3(0.0f, -1.071f, 0.0f);
		R_fist->transform->Rotation = D3DXVECTOR3(-1.5f, -108.0f, -97.5f);
		R_arm1_cover->transform->Rotation = D3DXVECTOR3(90.0f, -26.071f, 0.0f);
		R_arm2_cover->transform->Rotation = D3DXVECTOR3(90.0f, -55.573f, 0.0f);
		R_arm3_cover->transform->Rotation = D3DXVECTOR3(90.0f, -88.989f, 0.0f);

		R_fist->AddComponent<SphereCollider>()->SetCollisionSize(10.0f);
		R_fist->AddComponent<PlayerAttack>();

		parts.push_back(R_joint1);
		parts.push_back(R_joint2);
		parts.push_back(R_joint3);
		//parts.push_back(R_arm1);
		//parts.push_back(R_arm2);
		//parts.push_back(R_arm3);
		parts.push_back(R_hand);
		parts.push_back(R_fist);
		parts.push_back(R_arm1_cover);
		parts.push_back(R_arm2_cover);
		parts.push_back(R_arm3_cover);
	}


	animator = AddComponent<Animator>();
	animatorRoll = AddComponent<Animator>();
	rightHand = AddComponent<Animator>();
	leftHand = AddComponent<Animator>();

	animatorRoll->AddAnimation(AddComponent<CharacterMove>(), ROLL);
	animatorRoll->AddAnimation(AddComponent<CharacterDash>(), DASH);

	animator->AddAnimation(AddComponent<CharacterRetract>(), RETRACT);
	animator->AddAnimation(AddComponent<CharacterExtend>(), EXTEND);

	animator->AddAnimation(AddComponent<CharacterJump>(), JUMP, Animation::END);
	animator->AddAnimation(AddComponent<CharacterGuard>(), GUARD);
	animator->AddAnimation(AddComponent<CharacterParry>(), PARRY);
	animator->AddAnimation(AddComponent<CharacterStun>(), STUN);
	animator->AddAnimation(AddComponent<CharacterDeath>(), DEATH);

	rightHand->AddAnimation(AddComponent<CharacterPunchLaunchRight>(), PUNCH_LAUNCH_R);
	leftHand->AddAnimation(AddComponent<CharacterPunchLaunchLeft>(), PUNCH_LAUNCH_L);

	pressed = false;
	dash = false;
	dashCooler = false;
	rollstart = false;
	guard = false;
	stance = false;
	guardCooler = false;
	punch = false;
	disable = false;

	dashCooldown = 0;
	dashCounter = 0;
	guardCooldown = 0;
}

void CHARACTER::Update()
{
	//Trash
	/*
	|------------------------------TRASH----------------------------
	|if (Input::GetKeyTrigger('I') && animationChange1 == false)
	|{
	|	Animation::ANIMATION_STATUS stat = animator->GetAnimationState(EXTEND);
	|	Animation::ANIMATION_STATUS jump1 = animator->GetAnimationState(JUMP);
	|	if (jump1 == Animation::END)
	|	{
	|		if (stat == Animation::PLAYBACK) { animator->AnimationTransition(RETRACT, EXTEND); }
	|		else if (stat == Animation::END || stat == Animation::STANDBY) { animator->PlayAnimation(RETRACT); }
	|		animationChange1 = true;
	|		animationChange3 = false;
	|	}
	|}
	|if (animator->GetAnimationState(RETRACT) == Animation::END && animationChange2 == false && pressed == true)
	|{
	|	//animatorRoll->PlayAnimation(ROLL, Animation::LOOP);
	|	animationChange2 = true;
	|}
	|
	|
	|Animation::ANIMATION_STATUS jump1 = animator->GetAnimationState(JUMP);
	|if (jump1 == Animation::END)
	|{
	|	if (animationChange3 == false)
	|	{
	|		Animation::ANIMATION_STATUS stat = animator->GetAnimationState(RETRACT);
	|
	|		if (stat == Animation::PLAYBACK)
	|		{
	|			animator->AnimationTransition(EXTEND, RETRACT);
	|			animationChange3 = true;
	|		}
	|		else if (stat == Animation::END)
	|		{
	|			//animatorRoll->StopAnimation(ROLL);
	|			rollstart = false;
	|			animator->PlayAnimation(EXTEND);
	|			animationChange3 = true;
	|		}
	|	}
	|	animationChange1 = false;
	|	animationChange2 = false;
	|}
	|---------------------------------------------------------------
	*/

	PLAYER* player = Manager::GetScene()->GetPlayer();

#ifdef DEBUG
	if (Input::GetKeyPress('Z'))
	{
		//animator->PlayAnimation(DEATH);
		//disable = true;
	}
#endif

	if (disable == false)
	{
		//Punch | Guard | Parry
		{
			if (Input::GetKeyPress('L') && guardCooler == false)
			{
				if (rightHand->GetAnimationState(PUNCH_LAUNCH_R) != Animation::PLAYBACK && leftHand->GetAnimationState(PUNCH_LAUNCH_L) != Animation::PLAYBACK && animator->GetAnimationState(PARRY) != Animation::PLAYBACK)
				{
					guard = true;
				}
			}
			else
			{
				if (guard == true)
				{
					guard = false;
					stance = false;
					guardCooler = true;
					animator->PlayAnimation(PARRY);
				}

				if (Input::GetKeyTrigger('K')) { rightHand->PlayAnimation(PUNCH_LAUNCH_R);	punch = true; SoundReader::PlayMaster("asset\\sound\\use\\punch.wav", 0.2f);}
				if (Input::GetKeyTrigger('J')) { leftHand->PlayAnimation(PUNCH_LAUNCH_L);	punch = true; SoundReader::PlayMaster("asset\\sound\\use\\punch.wav", 0.2f);}
			}

			if (guard == true && stance == false)
			{
				stance = true;
				animator->PlayAnimation(GUARD);
				SoundReader::PlayMaster("asset\\sound\\use\\punch.wav", 0.2f);
			}

			if (guardCooler == true)
			{
				if (guardCooldown < 8) { guardCooldown++; }
				else { guardCooldown = 0; guardCooler = false; }
			}

			if (rightHand->GetAnimationState(PUNCH_LAUNCH_R) != Animation::PLAYBACK && leftHand->GetAnimationState(PUNCH_LAUNCH_L) != Animation::PLAYBACK) { punch = false; }
		}
		//Dash
		{
			if (Input::GetKeyTrigger('I') && dashCooler == false)
			{
				dash = true;
				dashCooler = true;
				D3DXVECTOR3 dir = GetForwardDirection();
				D3DXVec3Normalize(&dir, &dir);
				player->rigidbody->Speed = dir * 0.5f;
				animatorRoll->PlayAnimation(DASH);
				SoundReader::GetReadSound(SoundReader::DASH)->Play(false, 0.1f);
			}

			if (dash == true)
			{
				if (dashCounter < 10) { dashCounter++; }
				else { dashCounter = 0; dash = false; }
			}

			if (dashCooler == true)
			{
				if (dashCooldown < 60) { dashCooldown++; }
				else { dashCooldown = 0; dashCooler = false; }
			}
		}

		if (guard == false && punch == false)
		{
			player->posture->Recover(0.08f);
		}

		//Input
		if (
			Input::GetKeyPress('W') ||
			Input::GetKeyPress('A') ||
			Input::GetKeyPress('S') ||
			Input::GetKeyPress('D')
			) {
			pressed = true; rollstart = true;
		}
		else { pressed = false; }


		if (rollstart == true) { innerbody->transform->Rotation.x += 6.0f; }
		if (pressed == false) { rollstart = false; }

	}

	if (animator->GetAnimationState(STUN) != Animation::PLAYBACK && disable == true && player->dead == false)
	{
		disable = false;
	}

	//if (Input::GetKeyPress('1')) { L_fist->transform->Rotation.x += 0.5f; }
	//if (Input::GetKeyPress('2')) { L_fist->transform->Rotation.x -= 0.5f; }
	//if (Input::GetKeyPress('3')) { L_fist->transform->Rotation.y += 0.5f; }
	//if (Input::GetKeyPress('4')) { L_fist->transform->Rotation.y -= 0.5f; }
	//if (Input::GetKeyPress('5')) { L_fist->transform->Rotation.z += 0.5f; }
	//if (Input::GetKeyPress('6')) { L_fist->transform->Rotation.z -= 0.5f; }

#ifdef DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], " | X : %.2f, Y : %.2f, Z : %.2f", L_fist->transform->Rotation.x, L_fist->transform->Rotation.y, L_fist->transform->Rotation.z);
#endif
}