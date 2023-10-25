#include "Obstacle2.h"
#include "MyMath.h"
#include <cassert>

void Obstacle2::Initialize(Model* model, uint32_t obstacle) {

	model_ = model;
	building_ = obstacle;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f,15.0f, 100.0f};

	worldTransform_.UpdateMatrix();
};

Vector3 Obstacle2::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Obstacle2::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, building_);
};

void Obstacle2::OnCollision() { isDead_ = true; };
