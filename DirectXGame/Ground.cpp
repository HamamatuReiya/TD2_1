#include "Ground.h"

void Ground::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Ground::Update() {
	const float kSpeed = 0.15f;
	Vector3 move = {0.0f, 0.0f, kSpeed};

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }