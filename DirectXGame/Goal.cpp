#include "Goal.h"

void Goal::Initialize(Model* model, Vector3 position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {position};
}

void Goal::Update() { worldTransform_.UpdateMatrix(); }

void Goal::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }
