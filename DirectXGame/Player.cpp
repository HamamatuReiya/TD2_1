#include "Player.h"
#include "MyMath.h"
#include <cassert>

void Player::Initialize(Model* model, Vector3 playerPosition) {
	assert(model);
	model_ = model;
	isDead_ = false;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, playerPosition);
}

void Player::Update() {
	const float kCharacterSpeed = 0.0f;
	Vector3 move = {0.0f, 0.0f, kCharacterSpeed};

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::OnCollision() { isDead_ = true; }

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }



