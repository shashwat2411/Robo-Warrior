#include "script.h"
#include "prefab.h"
#include "manager.h"
#include "scene.h"
#include "soundReader.h"

void Posture::Start()
{
	posture = 0.0f;
	maxPosture = 100.0f;

	invincible = false;
	invincibilityCounter = 0;
	noDamage = false;
	barController = nullptr;
}

void Posture::Update()
{
	if (barController != nullptr) { *barController = posture; }
	if (posture >= maxPosture && noDamage == false)
	{
		HitPoints* hp = gameObject->GetComponent<HitPoints>();
		CHARACTER* character = Manager::GetScene()->FindGameObject<CHARACTER>();
		if (hp != nullptr)
		{
			hp->Damage(15.0f);
			posture = 0.0f;
			D3DXVECTOR3 dir = -character->GetForwardDirection();
			D3DXVec3Normalize(&dir, &dir);
			gameObject->rigidbody->Speed = dir * 0.4f;
			character->disable = true;
			character->animator->PlayAnimation(CHARACTER::STUN);
			SoundReader::GetReadSound(SoundReader::STUN)->Play(false, 0.2f);
			//rotate animation
		}
	}

	if (invincible == true)
	{
		if (invincibilityCounter < COLLIDE_COUNTDOWN) { invincibilityCounter++; }
		else { invincibilityCounter = 0; invincible = false; }
	}
}