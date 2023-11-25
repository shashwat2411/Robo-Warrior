#include "component.h"
#include "input.h"

void Animator::Start()
{
	//data.push_back(AnimationData(0, Data(0.0f, &gameObject->transform->Rotation.x)));
	//data.push_back(AnimationData(20, Data(50.0f, &gameObject->transform->Rotation.x)));
	//data.push_back(AnimationData(40, Data(-120.0f, &gameObject->transform->Rotation.x)));
	//data.push_back(AnimationData(60, Data(30.0f, &gameObject->transform->Rotation.x)));
	//data.push_back(AnimationData(80, Data(-70.0f, &gameObject->transform->Rotation.x)));

	//data[0].angle.push_back(Data(0.0f, &gameObject->transform->Rotation.y));
	//data[1].angle.push_back(Data(50.0f, &gameObject->transform->Rotation.y));
	//data[2].angle.push_back(Data(-120.0f, &gameObject->transform->Rotation.y));
	//data[3].angle.push_back(Data(60.0f, &gameObject->transform->Rotation.y));
	//data[4].angle.push_back(Data(-20.0f, &gameObject->transform->Rotation.y));
	multiple = true;

}

void Animator::End()
{
	animation.clear();
}

void Animator::Update()
{
	if (animation[animIndex]->status == Animation::PLAYBACK || animation[animIndex]->status == Animation::LOOP)
	{
		float dt, dangle;
		float timer = animation[animIndex]->timer;
		float frame1 = animation[animIndex]->data[animation[animIndex]->index].frame;
		float frame2 = animation[animIndex]->data[animation[animIndex]->index + 1].frame;

		dt = (float)(timer - frame1) / (float)(frame2 - frame1);
		for (int i = 0; i < animation[animIndex]->data[animation[animIndex]->index].angle.size(); i++)
		{
			float angle1 = animation[animIndex]->data[animation[animIndex]->index].angle[i].move;
			float angle2 = animation[animIndex]->data[animation[animIndex]->index + 1].angle[i].move;
			dangle = (angle2 - angle1);

			*animation[animIndex]->data[animation[animIndex]->index].angle[i].pointer = angle1 + (dt * dangle);
		}
		animation[animIndex]->timer++;
		if (animation[animIndex]->timer > frame2)
		{
			animation[animIndex]->index++;
			if (animation[animIndex]->index >= animation[animIndex]->data.size() - 1)
			{
				if (animation[animIndex]->status != Animation::LOOP)
				{
					InitAnimation(Animation::END);
				}
				else
				{
					InitAnimation(Animation::LOOP);
				}
			}
		}
	}
}

void Animator::Draw()
{

}