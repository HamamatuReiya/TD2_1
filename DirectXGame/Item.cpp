#include "Item.h"
#include "GameScene.h"

Item::~Item() {

}
void Item::Initialize(Model* model,Vector3& position) {
	model_ = model;
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();
}
void Item::Update() { worldTransform_.UpdateMatrix(); }
void Item::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}

void Item::OnCollision() { isItem_ = true; }



Vector3 Item::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}