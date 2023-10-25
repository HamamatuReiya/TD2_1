#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MyMath.h"

class Skydome {
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};