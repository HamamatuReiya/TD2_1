#pragma once
#include "Model.h"
#include "MyMath.h"
#include "WorldTransform.h"
#include <Sprite.h>
#include <list>

class Item {
public:
	~Item();
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();

	void Draw(ViewProjection& viewProjection);
	void OnCollision();
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	uint32_t textureHandle_ = 0u;
	Model* model_ =nullptr;
	Item* item_ = nullptr;
	bool isItem_ = false;
};
