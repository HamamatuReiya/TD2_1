#include "Breezeway6.h"
#include "MyMath.h"
#include <cassert>

void Breezeway6::Initialize(Model* model, uint32_t breezeway) {

	model_ = model;
	building2_ = breezeway;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {6.0f, 30.0f, 290.0f};

	worldTransform_.UpdateMatrix();
};

Vector3 Breezeway6::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Breezeway6::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, building2_);
};

void Breezeway6::OnCollision() { isDead_ = true; };
