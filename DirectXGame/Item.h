#pragma once
#include "Model.h"
#include "MyMath.h"
#include "WorldTransform.h"
#include <Sprite.h>
#include <list>

class GameScene;

class Item {
public:
	~Item();
	void Initialize(Model* model,Vector3& position);
	void Update();

	void Draw(ViewProjection& viewProjection);
	void OnCollision();
	Vector3 GetWorldPosition();
	bool IsDead() const { return isItem_; }
	void SetIsItem(bool isItem) { isItem_ = isItem; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	uint32_t textureHandle_ = 0u;
	Model* model_ =nullptr;
	Item* item_ = nullptr;
	bool isItem_ = false;
	GameScene* gameScene_ = nullptr;
};
