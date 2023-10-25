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
#include "Item.h"
#include "Ground.h"
#include "Obstacle.h"
#include "Obstacle2.h"
#include "Obstacle3.h"
#include "Obstacle4.h"
#include "Obstacle5.h"
#include "Obstacle6.h"
#include "Obstacle7.h"
#include "Obstacle8.h"
#include "Obstacle9.h"
#include "Obstacle10.h"
#include "Obstacle11.h"
#include "Obstacle12.h"
#include "Obstacle13.h"
#include "Breezeway.h"
#include "Breezeway2.h"
#include "Breezeway3.h"
#include "Breezeway4.h"
#include "Breezeway5.h"
#include "Breezeway6.h"
#include <sstream>

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

	void checkAllCollisions();

	void AddItem(Vector3 position);

	void LoadItemStage1PopData();

	void UpdateItemPopCommands();

	void ItemDelete();

private: // メンバ変数

	enum Scene {
		Title,
		Stage1,
		Stage2,
		GameOver,
	};

	enum Scene scene;

	enum TitleScene {
		Start,
		Select,
	};

	enum TitleScene titleScene;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;
	Model* playerModel_ = nullptr;
	bool isPlayerPosY_;

	Vector3 worldPos;
	Vector3 rotation;
	RailCamera* railCamera_ = nullptr;

	DebugCamera* debugCamera_ = nullptr;
	int isDebugCameraActive_;

	Skydome* skydome_ = nullptr;
	Model* skydomeModel_ = nullptr;

	std::unique_ptr<Ground> ground_;
	std::unique_ptr<Model> groundModel_;

	Item* item_ = nullptr;
	Model* itemModel_ = nullptr;
	Vector3 itemPos_;
	std::list<Item*> items_;
	std::stringstream itemPopCommands;

	//障害物の複数化
	/*Obstacle* obstacle_ = nullptr;
	Model* obstacleModel_ = nullptr;
	Vector3 obstaclePos_;
	std::list<Obstacle*> obstacles_;*/

	int standFlag = false;
	int standTime = 0;

	uint32_t meterTextur_ = 0;
	Sprite* meterSprite_ = nullptr;
	float meter;
	Vector2 size;

	uint32_t meterFlameTexture_ = 0;
	Sprite* meterFlameSprite_ = nullptr;

	uint32_t titleTextTexture_ = 0;
	Sprite* titleTextSprite_ = nullptr;

	uint32_t titleBackTexture_ = 0;
	Sprite* titleBackSprite_ = nullptr;

	uint32_t pressSpaceTexture_ = 0;
	Sprite* pressSpaceSprite_ = nullptr;
	int spaceKeyBlinking_;
	bool isSpaceKeyBlinking_;

	bool isStageUpdate_;

	uint32_t stage1Texture_ = 0;
	Sprite* stage1Sprite_ = nullptr;
	uint32_t stage1SelectTexture_ = 0;
	Sprite* stage1SelectSprite_ = nullptr;
	bool isSelectStage1=true;
	bool isStage1Clear_=false;
	bool isStagePushSpace_ = false;

	uint32_t stage2Texture_ = 0;
	Sprite* stage2Sprite_ = nullptr;
	uint32_t stage2SelectTexture_ = 0;
	Sprite* stage2SelectSprite_ = nullptr;
	Vector4 stage2Color_ = {0.5,0.5,0.5,1};

	uint32_t explanationTexture_ = 0;
	Sprite* explanationSprite_ = nullptr;

	uint32_t gameOverTexture_ = 0;
	Sprite* gameOverSprite_ = nullptr;

	uint32_t gameClearTexture_ = 0;
	Sprite* gameClearSprite_ = nullptr;
	bool isGameClear_;

	Goal* goal_ = nullptr;
	Model* goalModel_ = nullptr;
	Vector3 goalPos_ = {0, 50, 400};

	Goal* goal2_ = nullptr;
	Vector3 goal2Pos_ = {0, 50, 800};

	// 障害物3Dモデル
	Model* obstacleModel_ = nullptr;
	Model* breezewayModel_ = nullptr;
	// 障害物
	Obstacle* obstacle_ = nullptr;
	Obstacle2* obstacle2_ = nullptr;
	Obstacle3* obstacle3_ = nullptr;
	Obstacle4* obstacle4_ = nullptr;
	Obstacle5* obstacle5_ = nullptr;
	Obstacle6* obstacle6_ = nullptr;
	Obstacle7* obstacle7_ = nullptr;
	Obstacle8* obstacle8_ = nullptr;
	Obstacle9* obstacle9_ = nullptr;
	Obstacle10* obstacle10_ = nullptr;
	Obstacle11* obstacle11_ = nullptr;
	Obstacle12* obstacle12_ = nullptr;
	Obstacle13* obstacle13_ = nullptr;
	Breezeway* breezeway_ = nullptr;
	Breezeway2* breezeway2_ = nullptr;
	Breezeway3* breezeway3_ = nullptr;
	Breezeway4* breezeway4_ = nullptr;
	Breezeway5* breezeway5_ = nullptr;
	Breezeway6* breezeway6_ = nullptr;
	// 障害物テクスチャハンドル
	uint32_t building_ = 0;
	uint32_t building2_ = 0;

	//サウンド
	uint32_t bgmHandle_ = 0;
	uint32_t bgmLoop_ = 0;
	bool isBgm_ = false;

	uint32_t soundHandle_ = 0;

	uint32_t pushSoundHandle_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
