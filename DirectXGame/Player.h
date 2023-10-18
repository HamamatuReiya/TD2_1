#pragma once
#include "Input.h"
#include "Model.h"
#include "MyMath.h"
#include "WorldTransform.h"
#include <Sprite.h>
#include <list>

class Player {
public:
	//~Player();
	void Initialize(Model* model, uint32_t textureHandle, Vector3 playerPosition);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void SetParent(const WorldTransform* parent);
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	Vector3 GetWorldPosition();
	void OnCollision();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;
	Input* input_ = nullptr;
	bool isDead_ = false;
};
