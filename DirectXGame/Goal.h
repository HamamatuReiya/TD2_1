#pragma once
#include "Model.h"
#include "MyMath.h"
#include "WorldTransform.h"
#include <Sprite.h>

class Goal {
public:
	void Initialize(Model* model, Vector3 position);
	void Update();
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
};
