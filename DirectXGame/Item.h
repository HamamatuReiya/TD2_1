#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Item {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	//燃料
	int Energy;
	//星
	//int Star;
	//加速
	//int acceleration;
};
