﻿#include "Breezeway5.h"
#include "MyMath.h"
#include <cassert>

void Breezeway5::Initialize(Model* model, uint32_t breezeway) {

	model_ = model;
	building2_ = breezeway;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {-6.0f, 30.0f, 290.0f};

	worldTransform_.UpdateMatrix();
};

Vector3 Breezeway5::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Breezeway5::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, building2_);
};

void Breezeway5::OnCollision() { isDead_ = true; };
