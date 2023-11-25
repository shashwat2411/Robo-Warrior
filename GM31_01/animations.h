#pragma once
#include "component.h"
#include "prefab.h"

//player
class PlayerAnimation : public Animation
{
public:

	void Start() override
	{
		data.push_back(AnimationData(0, Data(0.0f, &gameObject->transform->Position.z)));
		data.push_back(AnimationData(3, Data(1.0f, &gameObject->transform->Position.z)));
		data.push_back(AnimationData(6, Data(0.0f, &gameObject->transform->Position.z)));

		//data[0].angle.push_back(Data(0.0f, &gameObject->transform->Rotation.y));
		//data[1].angle.push_back(Data(50.0f, &gameObject->transform->Rotation.y));
		//data[2].angle.push_back(Data(-120.0f, &gameObject->transform->Rotation.y));
		//data[3].angle.push_back(Data(60.0f, &gameObject->transform->Rotation.y));
		//data[4].angle.push_back(Data(-20.0f, &gameObject->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 6;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class CharacterRetract : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		float divider = 6.0f;

		//¶˜r
		data.push_back(AnimationData(0,		Data(-1.0f, &character->L_joint1->transform->Position.x)));
		data[0].angle.push_back(            Data(71.196f, &character->L_joint1->transform->Rotation.y));
		data[0].angle.push_back(            Data(0.0f, &character->L_joint2->transform->Rotation.y));
		data[0].angle.push_back(            Data(0.0f, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(10,	Data(-1.0f, &character->L_joint1->transform->Position.x)));
		data[1].angle.push_back(            Data(63.853f, &character->L_joint1->transform->Rotation.y));
		data[1].angle.push_back(            Data(26.738f, &character->L_joint2->transform->Rotation.y));
		data[1].angle.push_back(            Data(29.903, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(30,	Data(0.809f, &character->L_joint1->transform->Position.x)));
		data[2].angle.push_back(            Data(63.853f, &character->L_joint1->transform->Rotation.y));
		data[2].angle.push_back(            Data(26.738f, &character->L_joint2->transform->Rotation.y));
		data[2].angle.push_back(            Data(29.903f, &character->L_joint3->transform->Rotation.y));

		//‰E˜r
		data[0].angle.push_back(            Data(1.0f, &character->R_joint1->transform->Position.x));
		data[0].angle.push_back(            Data(108.804f, &character->R_joint1->transform->Rotation.y));
		data[0].angle.push_back(            Data(0.0f, &character->R_joint2->transform->Rotation.y));
		data[0].angle.push_back(            Data(0.0f, &character->R_joint3->transform->Rotation.y));

		data[1].angle.push_back(            Data(1.0f, &character->R_joint1->transform->Position.x));
		data[1].angle.push_back(            Data(116.147, &character->R_joint1->transform->Rotation.y));
		data[1].angle.push_back(            Data(26.738f, &character->R_joint2->transform->Rotation.y));
		data[1].angle.push_back(            Data(29.903, &character->R_joint3->transform->Rotation.y));

		data[2].angle.push_back(            Data(-0.809f, &character->R_joint1->transform->Position.x));
		data[2].angle.push_back(            Data(116.147, &character->R_joint1->transform->Rotation.y));
		data[2].angle.push_back(            Data(26.738f, &character->R_joint2->transform->Rotation.y));
		data[2].angle.push_back(            Data(29.903f, &character->R_joint3->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 30;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class CharacterMove : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		data.push_back(AnimationData(0,		Data(0.0f, &character->innerbody->transform->Rotation.x)));
		data.push_back(AnimationData(60,	Data(-359.0f, &character->innerbody->transform->Rotation.x)));

		index = 0;
		timer = 0;
		animationSize = 60;
		keyframes = 2;
		status = Animation::STANDBY;
	}
};
class CharacterExtend : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		float divider = 6.0f;

		//¶˜r
		data.push_back(AnimationData(0,		Data(0.809f, &character->L_joint1->transform->Position.x)));
		data[0].angle.push_back(            Data(63.853f, &character->L_joint1->transform->Rotation.y));
		data[0].angle.push_back(            Data(26.738f, &character->L_joint2->transform->Rotation.y));
		data[0].angle.push_back(            Data(29.903, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(20,	Data(-1.0f, &character->L_joint1->transform->Position.x)));
		data[1].angle.push_back(            Data(63.853f, &character->L_joint1->transform->Rotation.y));
		data[1].angle.push_back(            Data(26.738f, &character->L_joint2->transform->Rotation.y));
		data[1].angle.push_back(            Data(29.903, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(30,	Data(-1.0f, &character->L_joint1->transform->Position.x)));
		data[2].angle.push_back(            Data(71.196f, &character->L_joint1->transform->Rotation.y));
		data[2].angle.push_back(            Data(0.0f, &character->L_joint2->transform->Rotation.y));
		data[2].angle.push_back(            Data(0.0f, &character->L_joint3->transform->Rotation.y));

		//‰E˜r
		data[0].angle.push_back(            Data(-0.809f, &character->R_joint1->transform->Position.x));
		data[0].angle.push_back(            Data(116.147, &character->R_joint1->transform->Rotation.y));
		data[0].angle.push_back(            Data(26.738f, &character->R_joint2->transform->Rotation.y));
		data[0].angle.push_back(            Data(29.903, &character->R_joint3->transform->Rotation.y));

		data[1].angle.push_back(            Data(1.0f, &character->R_joint1->transform->Position.x));
		data[1].angle.push_back(            Data(116.147, &character->R_joint1->transform->Rotation.y));
		data[1].angle.push_back(            Data(26.738f, &character->R_joint2->transform->Rotation.y));
		data[1].angle.push_back(            Data(29.903, &character->R_joint3->transform->Rotation.y));

		data[2].angle.push_back(            Data(1.0f, &character->R_joint1->transform->Position.x));
		data[2].angle.push_back(            Data(108.804f, &character->R_joint1->transform->Rotation.y));
		data[2].angle.push_back(            Data(0.0f, &character->R_joint2->transform->Rotation.y));
		data[2].angle.push_back(            Data(0.0f, &character->R_joint3->transform->Rotation.y));


		index = 0;
		timer = 0;
		animationSize = 30;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};

class CharacterJump : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		//¶˜r
		data.push_back(AnimationData(0,     Data(180.0f,    &character->L_joint1->transform->Rotation.x)));
		data[0].angle.push_back(		    Data(0.0f,      &character->L_joint1->transform->Rotation.z));
		data[0].angle.push_back(            Data(0.0f,      &character->L_joint2->transform->Rotation.y));
		data[0].angle.push_back(            Data(0.0f,      &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(10,    Data(180.0f,    &character->L_joint1->transform->Rotation.x)));
		data[1].angle.push_back(            Data(44.598f,   &character->L_joint1->transform->Rotation.z));
		data[1].angle.push_back(            Data(0.0f,      &character->L_joint2->transform->Rotation.y));
		data[1].angle.push_back(            Data(0.0f,      &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(30,    Data(156.019f,  &character->L_joint1->transform->Rotation.x)));
		data[2].angle.push_back(            Data(-76.513f,  &character->L_joint1->transform->Rotation.z));
		data[2].angle.push_back(            Data(20.829f,   &character->L_joint2->transform->Rotation.y));
		data[2].angle.push_back(            Data(27.948f,   &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(50,    Data(180.0f,    &character->L_joint1->transform->Rotation.x)));
		data[3].angle.push_back(            Data(49.328f,   &character->L_joint1->transform->Rotation.z));
		data[3].angle.push_back(            Data(0.0f,      &character->L_joint2->transform->Rotation.y));
		data[3].angle.push_back(            Data(0.0f,      &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(60,    Data(180.0f,    &character->L_joint1->transform->Rotation.x)));
		data[4].angle.push_back(            Data(0.0f,      &character->L_joint1->transform->Rotation.z));
		data[4].angle.push_back(            Data(0.0f,      &character->L_joint2->transform->Rotation.y));
		data[4].angle.push_back(            Data(0.0f,      &character->L_joint3->transform->Rotation.y));

		//‰E˜r
		data[0].angle.push_back(            Data(0.0f,      &character->R_joint1->transform->Rotation.x));
		data[0].angle.push_back(            Data(0.0f,      &character->R_joint1->transform->Rotation.z));
		data[0].angle.push_back(            Data(0.0f,      &character->R_joint2->transform->Rotation.y));
		data[0].angle.push_back(            Data(0.0f,      &character->R_joint3->transform->Rotation.y));

		data[1].angle.push_back(            Data(0.0f,      &character->R_joint1->transform->Rotation.x));
		data[1].angle.push_back(            Data(-44.598f,  &character->R_joint1->transform->Rotation.z));
		data[1].angle.push_back(            Data(0.0f,      &character->R_joint2->transform->Rotation.y));
		data[1].angle.push_back(            Data(0.0f,      &character->R_joint3->transform->Rotation.y));

		data[2].angle.push_back(            Data(23.981f,   &character->R_joint1->transform->Rotation.x));
		data[2].angle.push_back(            Data(76.513f,   &character->R_joint1->transform->Rotation.z));
		data[2].angle.push_back(            Data(20.829f,   &character->R_joint2->transform->Rotation.y));
		data[2].angle.push_back(            Data(27.948f,   &character->R_joint3->transform->Rotation.y));
														    
		data[3].angle.push_back(            Data(0.0f,      &character->R_joint1->transform->Rotation.x));
		data[3].angle.push_back(            Data(-49.328f,  &character->R_joint1->transform->Rotation.z));
		data[3].angle.push_back(            Data(0.0f,      &character->R_joint2->transform->Rotation.y));
		data[3].angle.push_back(            Data(0.0f,      &character->R_joint3->transform->Rotation.y));
														    
		data[4].angle.push_back(            Data(0.0f,      &character->R_joint1->transform->Rotation.x));
		data[4].angle.push_back(            Data(0.0f,      &character->R_joint1->transform->Rotation.z));
		data[4].angle.push_back(            Data(0.0f,      &character->R_joint2->transform->Rotation.y));
		data[4].angle.push_back(            Data(0.0f,      &character->R_joint3->transform->Rotation.y));

		data[0].angle.push_back(            Data(0.0f,      &character->transform->Position.y));
		data[1].angle.push_back(            Data(0.0f,      &character->transform->Position.y));
		data[2].angle.push_back(            Data(3.0f,      &character->transform->Position.y));
		data[3].angle.push_back(            Data(0.0f,      &character->transform->Position.y));
		data[4].angle.push_back(            Data(0.0f,      &character->transform->Position.y));

		index = 0;
		timer = 0;
		animationSize = 60;
		keyframes = 5;
		status = Animation::STANDBY;
	}
};
class CharacterPunchLaunchRight : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		//‰E˜r
		data.push_back(AnimationData(0,		Data(142.133f, &character->R_joint1->transform->Rotation.y)));
		data[0].angle.push_back(			Data(23.368f, &character->R_joint2->transform->Rotation.y));
		data[0].angle.push_back(			Data(-62.098f, &character->R_joint3->transform->Rotation.y));

		data.push_back(AnimationData(3,	Data(81.664f, &character->R_joint1->transform->Rotation.y)));
		data[1].angle.push_back(			Data(-0.857f, &character->R_joint2->transform->Rotation.y));
		data[1].angle.push_back(			Data(13.871f, &character->R_joint3->transform->Rotation.y));

		data.push_back(AnimationData(6,	Data(142.133f, &character->R_joint1->transform->Rotation.y)));
		data[2].angle.push_back(			Data(23.368f, &character->R_joint2->transform->Rotation.y));
		data[2].angle.push_back(			Data(-62.098f, &character->R_joint3->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 6;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class CharacterPunchLaunchLeft : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		//‰E˜r
		data.push_back(AnimationData(0, Data(37.867f, &character->L_joint1->transform->Rotation.y)));
		data[0].angle.push_back(Data(23.368f, &character->L_joint2->transform->Rotation.y));
		data[0].angle.push_back(Data(-62.098f, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(3, Data(98.336f, &character->L_joint1->transform->Rotation.y)));
		data[1].angle.push_back(Data(-0.857f, &character->L_joint2->transform->Rotation.y));
		data[1].angle.push_back(Data(13.871f, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(6, Data(37.867f, &character->L_joint1->transform->Rotation.y)));
		data[2].angle.push_back(Data(23.368f, &character->L_joint2->transform->Rotation.y));
		data[2].angle.push_back(Data(-62.098f, &character->L_joint3->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 6;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class CharacterGuard : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		//‰E˜r
		data.push_back(AnimationData(0, Data(37.867f, &character->L_joint1->transform->Rotation.y)));
		data[0].angle.push_back(Data(142.133f, &character->R_joint1->transform->Rotation.y));

		data.push_back(AnimationData(6, Data(101.087f, &character->L_joint1->transform->Rotation.y)));
		data[1].angle.push_back(Data(78.971f, &character->R_joint1->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 6;
		keyframes = 2;
		status = Animation::STANDBY;
	}
};
class CharacterParry : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		//¶˜r
		data.push_back(AnimationData(0, Data(101.087f, &character->L_joint1->transform->Rotation.y)));
		data[0].angle.push_back(Data(-62.098f, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(2, Data(71.625f, &character->L_joint1->transform->Rotation.y)));
		data[1].angle.push_back(Data(7.7f, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(10, Data(71.625f, &character->L_joint1->transform->Rotation.y)));
		data[2].angle.push_back(Data(7.7f, &character->L_joint3->transform->Rotation.y));

		data.push_back(AnimationData(16, Data(37.867f, &character->L_joint1->transform->Rotation.y)));
		data[3].angle.push_back(Data(-62.098f, &character->L_joint3->transform->Rotation.y));


		//‰E˜r
		data[0].angle.push_back(Data(78.971f, &character->R_joint1->transform->Rotation.y));
		data[0].angle.push_back(Data(-62.098f, &character->R_joint3->transform->Rotation.y));

		data[1].angle.push_back(Data(107.837f, &character->R_joint1->transform->Rotation.y));
		data[1].angle.push_back(Data(7.7f, &character->R_joint3->transform->Rotation.y));

		data[2].angle.push_back(Data(107.837f, &character->R_joint1->transform->Rotation.y));
		data[2].angle.push_back(Data(7.7f, &character->R_joint3->transform->Rotation.y));

		data[3].angle.push_back(Data(142.133f, &character->R_joint1->transform->Rotation.y));
		data[3].angle.push_back(Data(-62.098, &character->R_joint3->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 15;
		keyframes = 4;
		status = Animation::STANDBY;
	}
};
class CharacterStun : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		//¶˜r
		//L_joint1
		data.push_back(AnimationData(0, Data(180.0f,	&character->L_joint1->transform->Rotation.x)));
		data.push_back(AnimationData(6, Data(180.0f,	&character->L_joint1->transform->Rotation.x)));
		data.push_back(AnimationData(40, Data(149.723f,	&character->L_joint1->transform->Rotation.x)));
		data.push_back(AnimationData(70, Data(149.723f,	&character->L_joint1->transform->Rotation.x)));
		data.push_back(AnimationData(90, Data(180.0f,	&character->L_joint1->transform->Rotation.x)));

		data[0].angle.push_back(Data(101.087f,	&character->L_joint1->transform->Rotation.y));
		data[1].angle.push_back(Data(0.0f,		&character->L_joint1->transform->Rotation.y));
		data[2].angle.push_back(Data(0.0f,		&character->L_joint1->transform->Rotation.y));
		data[3].angle.push_back(Data(0.0f,		&character->L_joint1->transform->Rotation.y));
		data[4].angle.push_back(Data(37.867f,	&character->L_joint1->transform->Rotation.y));

		//L_joint3

		data[0].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[1].angle.push_back(Data(31.62f,	&character->L_joint3->transform->Rotation.y));
		data[2].angle.push_back(Data(31.62f,	&character->L_joint3->transform->Rotation.y));
		data[3].angle.push_back(Data(31.62f,	&character->L_joint3->transform->Rotation.y));
		data[4].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		
		
		
		
		

		//‰E˜r
		//R_joint1
		data[0].angle.push_back(Data(0.0f,	&character->R_joint1->transform->Rotation.x));
		data[1].angle.push_back(Data(0.0f,	&character->R_joint1->transform->Rotation.x));
		data[2].angle.push_back(Data(31.4f,	&character->R_joint1->transform->Rotation.x));
		data[3].angle.push_back(Data(31.4,	&character->R_joint1->transform->Rotation.x));
		data[4].angle.push_back(Data(0.0f,	&character->R_joint1->transform->Rotation.x));
		
		data[0].angle.push_back(Data(78.971f,	&character->R_joint1->transform->Rotation.y));
		data[1].angle.push_back(Data(180.0f,	&character->R_joint1->transform->Rotation.y));
		data[2].angle.push_back(Data(180.0f,	&character->R_joint1->transform->Rotation.y));
		data[3].angle.push_back(Data(180.0f,	&character->R_joint1->transform->Rotation.y));
		data[4].angle.push_back(Data(142.133f,	&character->R_joint1->transform->Rotation.y));

		//R_joint3
		
		data[0].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[1].angle.push_back(Data(31.62f,	&character->R_joint3->transform->Rotation.y));
		data[2].angle.push_back(Data(31.62f,	&character->R_joint3->transform->Rotation.y));
		data[3].angle.push_back(Data(31.62f,	&character->R_joint3->transform->Rotation.y));
		data[4].angle.push_back(Data(-62.098,	&character->R_joint3->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 90;
		keyframes = 5;
		status = Animation::STANDBY;
	}
};
class CharacterDash : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		//‰E˜r
		data.push_back(AnimationData(0, Data(0.0f,  &character->body->transform->Position.y)));
		data.push_back(AnimationData(5, Data(0.5f, &character->body->transform->Position.y)));
		data.push_back(AnimationData(30, Data(0.0f, &character->body->transform->Position.y)));

		index = 0;
		timer = 0;
		animationSize = 30;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class CharacterDeath : public Animation
{
public:

	void Start() override
	{
		CHARACTER* character = (CHARACTER*)gameObject;

		int multiplier = 4;
		float displace = 0.85f;

		data.push_back(AnimationData(0 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(1 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(2 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(3 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(4 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(5 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(6 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(7 * multiplier, Data(0.0f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(9 * multiplier, Data(15.878f, &character->body->transform->Rotation.x)));
		data.push_back(AnimationData(9 * multiplier + 45, Data(15.878f, &character->body->transform->Rotation.x)));

		//¶˜r
		data[0].angle.push_back(Data(-1.0f,	 &character->L_joint1->transform->Position.x));
		data[1].angle.push_back(Data(-displace, &character->L_joint1->transform->Position.x));
		data[2].angle.push_back(Data(-1.0f,	 &character->L_joint1->transform->Position.x));
		data[3].angle.push_back(Data(-displace, &character->L_joint1->transform->Position.x));
		data[4].angle.push_back(Data(-1.0f,	 &character->L_joint1->transform->Position.x));
		data[5].angle.push_back(Data(-displace, &character->L_joint1->transform->Position.x));
		data[6].angle.push_back(Data(-1.0f,	 &character->L_joint1->transform->Position.x));
		data[7].angle.push_back(Data(-displace, &character->L_joint1->transform->Position.x));
		data[8].angle.push_back(Data(-1.72f, &character->L_joint1->transform->Position.x));
		data[9].angle.push_back(Data(-1.72f, &character->L_joint1->transform->Position.x));

		data[0].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[1].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[2].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[3].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[4].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[5].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[6].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[7].angle.push_back(Data(-62.098f,	&character->L_joint3->transform->Rotation.y));
		data[8].angle.push_back(Data(-2.684f,	&character->L_joint3->transform->Rotation.y));
		data[9].angle.push_back(Data(-2.684f,	&character->L_joint3->transform->Rotation.y));

		//‰E˜r
		data[0].angle.push_back(Data(1.0f,	&character->R_joint1->transform->Position.x));
		data[1].angle.push_back(Data(displace, &character->R_joint1->transform->Position.x));
		data[2].angle.push_back(Data(1.0f,	&character->R_joint1->transform->Position.x));
		data[3].angle.push_back(Data(displace,	&character->R_joint1->transform->Position.x));
		data[4].angle.push_back(Data(1.0f,	&character->R_joint1->transform->Position.x));
		data[5].angle.push_back(Data(displace,	&character->R_joint1->transform->Position.x));
		data[6].angle.push_back(Data(1.0f,	&character->R_joint1->transform->Position.x));
		data[7].angle.push_back(Data(displace,	&character->R_joint1->transform->Position.x));
		data[8].angle.push_back(Data(1.72f,	&character->R_joint1->transform->Position.x));
		data[9].angle.push_back(Data(1.72f,	&character->R_joint1->transform->Position.x));

		data[0].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[1].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[2].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[3].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[4].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[5].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[6].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[7].angle.push_back(Data(-62.098f,	&character->R_joint3->transform->Rotation.y));
		data[8].angle.push_back(Data(-2.684f,	&character->R_joint3->transform->Rotation.y));
		data[9].angle.push_back(Data(-2.684f,	&character->R_joint3->transform->Rotation.y));

		index = 0;
		timer = 0;
		animationSize = 9 * multiplier + 45;
		keyframes = 10;
		status = Animation::STANDBY;
	}
};

//Enemy
class EnemyLockOn : public Animation
{
public:

	void Start() override
	{
		DASH_ENEMY* enemy = (DASH_ENEMY*)gameObject;

		data.push_back(AnimationData(0, Data(0.0f, &enemy->transform->Rotation.x)));
		data.push_back(AnimationData(30, Data(-10.0f, &enemy->transform->Rotation.x)));
		data.push_back(AnimationData(50, Data(-10.0f, &enemy->transform->Rotation.x)));

		index = 0;
		timer = 0;
		animationSize = 50;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class EnemyLockOnReverse : public Animation
{
public:

	void Start() override
	{
		DASH_ENEMY* enemy = (DASH_ENEMY*)gameObject;

		data.push_back(AnimationData(0, Data(450.0f, &enemy->transform->Rotation.x)));
		data.push_back(AnimationData(15, Data(450.0f, &enemy->transform->Rotation.x)));
		data.push_back(AnimationData(25, Data(370.0f, &enemy->transform->Rotation.x)));

		index = 0;
		timer = 0;
		animationSize = 25;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class EnemySpawner : public Animation
{
public:

	void Start() override
	{

		data.push_back(AnimationData(0,		Data(-2.0f,	&gameObject->transform->Position.y)));
		data.push_back(AnimationData(20,	Data(2.0f,	&gameObject->transform->Position.y)));

		index = 0;
		timer = 0;
		animationSize = 20;
		keyframes = 2;
		status = Animation::STANDBY;
	}
};

//Dash Enemy
class DashEnemyAttack : public Animation
{
public:

	void Start() override
	{
		DASH_ENEMY* enemy = (DASH_ENEMY*)gameObject;

		data.push_back(AnimationData(0, Data(-10.0f, &enemy->transform->Rotation.x)));
		data.push_back(AnimationData(30, Data(400.0f, &enemy->transform->Rotation.x)));
		data.push_back(AnimationData(45, Data(450.0f, &enemy->transform->Rotation.x)));

		index = 0;
		timer = 0;
		animationSize = 45;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class DashEnemyMove : public Animation
{
public:

	void Start() override
	{
		DASH_ENEMY* enemy = (DASH_ENEMY*)gameObject;

		data.push_back(AnimationData(0, Data(0.0f, &enemy->transform->Rotation.x)));
		data.push_back(AnimationData(60, Data(359.0f, &enemy->transform->Rotation.x)));

		index = 0;
		timer = 0;
		animationSize = 60;
		keyframes = 2;
		status = Animation::STANDBY;
	}
};

//Enemy2
class ZigzagEnemyMove : public Animation
{
public:

	void Start() override
	{
		ZIGZAG_ENEMY* enemy = (ZIGZAG_ENEMY*)gameObject;


		data.push_back(AnimationData(0.0f,		Data(0.0f, &enemy->body->transform->Position.y)));
		data.push_back(AnimationData(20.0f,		Data(0.4f, &enemy->body->transform->Position.y)));
		data.push_back(AnimationData(40.0f,		Data(0.0f, &enemy->body->transform->Position.y)));

		index = 0;
		timer = 0;
		animationSize = 40;
		keyframes = 3;
		status = Animation::STANDBY;
	}
};
class ZigzagEnemyAttack : public Animation
{
public:

	void Start() override
	{
		ZIGZAG_ENEMY* enemy = (ZIGZAG_ENEMY*)gameObject;

		float zigzag = 1.0f;

		data.push_back(AnimationData(0, Data(0.0f,  &enemy->body->transform->Position.x)));
		data.push_back(AnimationData(5, Data(zigzag, &enemy->body->transform->Position.x)));
		data.push_back(AnimationData(14, Data(-zigzag, &enemy->body->transform->Position.x)));
		data.push_back(AnimationData(23, Data(zigzag, &enemy->body->transform->Position.x)));
		data.push_back(AnimationData(31, Data(-zigzag, &enemy->body->transform->Position.x)));
		data.push_back(AnimationData(36, Data(0.0f, &enemy->body->transform->Position.x)));

		data[0].angle.push_back(Data(0.0f, &enemy->body->transform->Rotation.z));
		data[1].angle.push_back(Data(-10.0f, &enemy->body->transform->Rotation.z));
		data[2].angle.push_back(Data(10.0f, &enemy->body->transform->Rotation.z));
		data[3].angle.push_back(Data(-10.0f, &enemy->body->transform->Rotation.z));
		data[4].angle.push_back(Data(10.0f, &enemy->body->transform->Rotation.z));
		data[5].angle.push_back(Data(0.0f, &enemy->body->transform->Rotation.z));

		index = 0;
		timer = 0;
		animationSize = 36;
		keyframes = 7;
		status = Animation::STANDBY;
	}
};