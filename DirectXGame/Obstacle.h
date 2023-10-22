#pragma once
#include "Input.h"
#include "Model.h"
#include "MyMath.h"
#include "WorldTransform.h"
#include <Sprite.h>
#include <list>

class Obstacle {

public:
	
	void Initialize(Model* model, uint32_t obstacle, Vector3& obstaclePosition);
	void Draw(ViewProjection& viewProjection);
	void OnCollision();
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	uint32_t building_ = 0u;
	Obstacle* obstacle_ = nullptr;
	bool isDead_ = false;
	Vector3 obstaclePosition_;
};
