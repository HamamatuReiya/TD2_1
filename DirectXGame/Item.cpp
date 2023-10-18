#include "Item.h"

Item::~Item() {

}
void Item::Initialize(Model* model, uint32_t textureHandle) {
	model_ = model;
	textureHandle_ = textureHandle;
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
//Vector3 Item::GetWorldPosition() {
//
//}