#pragma once
#include "model.h"

class ModelReader
{
public:

	enum READ_MODEL
	{
		DASH_ENEMY_M,
		ZIGZAG_ENEMY_M,

		READ_MODEL_MAX
	};

private:
	static Model Models[ModelReader::READ_MODEL_MAX];

public:
	static void ReadModel()
	{
		Models[DASH_ENEMY_M].Load("asset\\model\\dashEnemy.obj");
		Models[ZIGZAG_ENEMY_M].Load("asset\\model\\zigzagEnemy.obj");
	}

	static void UnReadModel()
	{
		for (int i = 0; i < READ_MODEL::READ_MODEL_MAX; i++)
		{
			Models[i].Unload();
		}
	}
	static Model* GetReadModel(READ_MODEL value)
	{
		return &Models[value];
	}
};