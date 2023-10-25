﻿#include "Obstacle8.h"
#include "MyMath.h"
#include <cassert>

void Obstacle8::Initialize(Model* model, uint32_t obstacle) {

	model_ = model;
	building_ = obstacle;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {10.0f, 10.0f, 10.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {-19.0f, 30.0f, 170.0f};

	worldTransform_.UpdateMatrix();
};

Vector3 Obstacle8::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Obstacle8::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, building_);
};

void Obstacle8::OnCollision() { isDead_ = true; };
