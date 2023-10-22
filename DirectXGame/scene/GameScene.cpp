#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { delete player_; 
delete railCamera_;
	delete debugCamera_;
delete skydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	worldPos.y = 30.0f;
	railCamera_ = new RailCamera();
	railCamera_->Initialize(worldPos, rotation);

	player_ = new Player();
	playerTexture_ = TextureManager::Load("W.jpg");
	playerModel_ = Model::Create();
	Vector3 playerPosition(0, -2.0f, 30.0f);
	player_->Initialize(playerModel_, playerTexture_, playerPosition);
	player_->SetParent(&railCamera_->GetWorldTransform());

	/*obstacle_ = new Obstacle();
	building_ = TextureManager::Load("black.png");
	obstacleModel_ = Model::Create();
	Vector3 obstaclePosition(0.0f, 10.0f, 50.0f);
	obstacle_->Initialize(obstacleModel_, building_, obstaclePosition);*/
	obstacle_ = new Obstacle();
	Vector3 obstaclePosition(0.0f, 10.0f, 50.0f);
	building_ = TextureManager::Load("black.png");
	obstacle_->Initialize(obstacleModel_, building_, obstaclePosition);


	debugCamera_ = new DebugCamera(1280, 720);

	skydome_ = new Skydome();
	skydomeModel_ = Model::CreateFromOBJ("skydome", true);
	skydome_->Initialize(skydomeModel_);

	ground_ = std::make_unique<Ground>();
	groundModel_.reset(Model::CreateFromOBJ("Ground", true));
	ground_->Initialize(groundModel_.get());
}

void GameScene::Update() { 
	debugCamera_->Update();
	player_->Update();
	railCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_BACKSPACE)) {
		isDebugCameraActive_ = false;
	}
#endif
	if (isDebugCameraActive_) {
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	obstacle_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions(){
	//判定対象AとBの座標
	Vector3 posA, posB;
	#pragma region 自キャラと障害物の当たり判定
	//自キャラの座標
	posA = player_->GetWorldPosition();

	//障害物の座標
	posB = obstacle_->GetWorldPosition();

	float a = posB.x - posA.x;
	float b = posB.y - posA.y;
	float c = posB.z - posA.z;

	float d = sqrtf(a * a + b * b + c * c);

	if (d <= 6.0f) {
		// 自キャラの衝突時コールバックを呼び出す
		player_->OnCollision();
		// 障害物の衝突時コールバックを呼び出す
		obstacle_->OnCollision();
	}

	#pragma endregion
};
