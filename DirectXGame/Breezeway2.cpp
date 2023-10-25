#include "Breezeway2.h"
#include "MyMath.h"
#include <cassert>

void Breezeway2::Initialize(Model* model, uint32_t breezeway) {

	model_ = model;
	building2_ = breezeway;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {6.0f, 60.0f, 170.0f};

	worldTransform_.UpdateMatrix();
};

Vector3 Breezeway2::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Breezeway2::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, building2_);
};

void Breezeway2::OnCollision() { isDead_ = true; };
