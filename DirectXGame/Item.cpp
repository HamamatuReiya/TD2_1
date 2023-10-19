#include "Item.h"

Item::~Item() {

}
void Item::Initialize(Model* model) {
	model_ = model;
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 50.0f, 100.0f};
	worldTransform_.Initialize();
}
void Item::Update() {

}
//void Item::Draw(ViewProjection& viewProjection) {
//
//}

void Item::OnCollision() {

}
Vector3 Item::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}