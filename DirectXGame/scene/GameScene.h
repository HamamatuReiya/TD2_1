#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "RailCamera.h"
#include "Skydome.h"
#include "Ground.h"
#include "Obstacle.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;
	uint32_t playerTexture_ = 0;
	Model* playerModel_ = nullptr;

	Vector3 worldPos;
	Vector3 rotation;
	RailCamera* railCamera_ = nullptr;

	DebugCamera* debugCamera_ = nullptr;
	int isDebugCameraActive_;

	Skydome* skydome_ = nullptr;
	Model* skydomeModel_ = nullptr;

	std::unique_ptr<Ground> ground_;
	std::unique_ptr<Model> groundModel_;

	Obstacle* obstacle_ = nullptr;
	uint32_t building_ = 0;
	Model* obstacleModel_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
