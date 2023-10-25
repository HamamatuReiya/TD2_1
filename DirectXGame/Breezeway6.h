﻿#pragma once
#include "Input.h"
#include "Model.h"
#include "MyMath.h"
#include "WorldTransform.h"
#include <Sprite.h>
#include <list>
class Breezeway6 {
public:
	void Initialize(Model* model, uint32_t breezeway);
	void Draw(ViewProjection& viewProjection);
	void OnCollision();
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t building2_ = 0u;
	Breezeway6* Breezeway6_ = nullptr;
	bool isDead_ = false;
};
