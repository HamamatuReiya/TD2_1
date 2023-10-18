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
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}
void Item::Update() {

}
//void Item::Draw(ViewProjection& viewProjection) {
//
//}
void Item::OnCollision() {

void Item::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}
//Vector3 Item::GetWorldPosition() {
//
//}