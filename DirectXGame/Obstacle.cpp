#include "Obstacle.h"
#include "MyMath.h"
#include <cassert>

void Obstacle::Initialize(Model* model, uint32_t obstacle, Vector3& obstaclePosition) {
	assert(model);

	model_ = model;
	building_ = obstacle;
	obstaclePosition_ = obstaclePosition;

	worldTransform_.scale_ = {1.0f, 5.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = obstaclePosition_;

	worldTransform_.Initialize();

};

Vector3 Obstacle::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Obstacle::Draw(ViewProjection& viewProjection){
	model_->Draw(worldTransform_, viewProjection, building_);
};

void Obstacle::OnCollision(){ 
	isDead_ = true; 
};

