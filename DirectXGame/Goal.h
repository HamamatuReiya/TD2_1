#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Goal {
public:
	void Initialize(Model* model, Vector3 position);
	void Update();
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};