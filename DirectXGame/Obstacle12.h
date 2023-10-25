#pragma once
#include "Input.h"
#include "Model.h"
#include "MyMath.h"
#include "WorldTransform.h"
#include <Sprite.h>
#include <list>
class Obstacle12 {
public:
	void Initialize(Model* model, uint32_t obstacle);
	void Draw(ViewProjection& viewProjection);
	void OnCollision();
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t building_ = 0u;
	Obstacle12* obstacle12_ = nullptr;
	bool isDead_ = false;
};
