#pragma once
#include "component.h"

class SoundReader
{
public:

	enum READ_SOUND
	{
		//SE
		GUARD,
		PARRY,
		ATTACK,
		ATTACK_LAND,
		DASH,
		HIT_WHILE_GUARD,
		HIT,
		ENEMY_LOCK_ON,
		DASH_ENEMY_ATTACK,
		ZIGZAG_ENEMY_ATTACK,
		STUN,
		PAUSE_IN,
		PAUSE_OUT,
		BUTTON,
		OPTION_CHANGE,
		GAME_START,
		DEATH,
		ENEMY_KILL,
		COUNTDOWN,
		GAME_OVER,

		//BGM
		TITLE,
		GAME,
		RESULT,

		READ_SOUND_MAX
	};

private:
	static Audio Audios[SoundReader::READ_SOUND_MAX];

public:

	static void ReadSound()
	{
		//SE
		Audios[GUARD].Load					("asset\\sound\\use\\punch.wav");
		Audios[PARRY].Load					("asset\\sound\\use\\parry.wav");
		Audios[ATTACK].Load					("asset\\sound\\use\\punch.wav");
		Audios[ATTACK_LAND].Load			("asset\\sound\\use\\attack_land.wav");
		Audios[DASH].Load					("asset\\sound\\use\\dash.wav");
		Audios[HIT_WHILE_GUARD].Load		("asset\\sound\\use\\hit_while_guarding.wav");
		Audios[HIT].Load					("asset\\sound\\use\\lifeLose.wav");
		Audios[ENEMY_LOCK_ON].Load			("asset\\sound\\use\\lockon.wav");
		Audios[DASH_ENEMY_ATTACK].Load		("asset\\sound\\use\\dashEnemyAttack.wav");
		Audios[ZIGZAG_ENEMY_ATTACK].Load	("asset\\sound\\use\\dashEnemyAttack.wav");
		Audios[STUN].Load					("asset\\sound\\use\\stun.wav");
		Audios[PAUSE_IN].Load				("asset\\sound\\use\\pause_in.wav");
		Audios[PAUSE_OUT].Load				("asset\\sound\\use\\pause_out.wav");
		Audios[BUTTON].Load					("asset\\sound\\use\\button.wav");
		Audios[OPTION_CHANGE].Load			("asset\\sound\\use\\selectChange.wav");
		Audios[DEATH].Load					("asset\\sound\\use\\playerDeath.wav");
		Audios[ENEMY_KILL].Load				("asset\\sound\\use\\enemyDeath.wav");
		Audios[COUNTDOWN].Load				("asset\\sound\\use\\countdown.wav");
		Audios[GAME_OVER].Load				("asset\\sound\\use\\gameOver.wav");

		//BGM
		Audios[TITLE].Load					("asset\\sound\\use\\TitleBGM.wav");
		Audios[GAME].Load					("asset\\sound\\use\\GameBGM.wav");
		Audios[RESULT].Load					("asset\\sound\\use\\ResultBGM.wav");
	}

	static Audio* GetReadSound(READ_SOUND value)
	{
		return &Audios[value];
	}

	static void StopAllSound()
	{
		for (int i = 0; i < READ_SOUND_MAX; i++)
		{
			Audios[i].Stop();
		}
	}

	static void PlayMaster(const char* value, float volume, float loop = false)
	{
		Audio* audio = Manager::GetScene()->AddGameObject<SOUND>(GAMEOBJECT_LAYER)->audio;
		audio->Load(value);
		audio->Play(loop, volume);
	}
};