#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete player_; 
    delete railCamera_;
	delete debugCamera_;
    delete skydome_;
	delete titleSprite_;
	delete meterSprite_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	scene = Title;
	/////////////
	titleTexture_ = TextureManager::Load("TitleTexture.png");
	titleSprite_ = Sprite::Create(titleTexture_, {0, 0});
	/////////////////

	////////////////
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

	debugCamera_ = new DebugCamera(1280, 720);

	skydome_ = new Skydome();
	skydomeModel_ = Model::CreateFromOBJ("skydome", true);
	skydome_->Initialize(skydomeModel_);

	ground_ = std::make_unique<Ground>();
	groundModel_.reset(Model::CreateFromOBJ("Ground", true));
	ground_->Initialize(groundModel_.get());

	meterTextur_ = TextureManager::Load("Meter.png");
	meterSprite_ = Sprite::Create(meterTextur_, {100, 100});
	Meter = 100.0f;
	////////////////

}

void GameScene::Update() { 

	switch (scene) {
	case Title:
		//Qを押してシーンの切り替え
		if (input_->TriggerKey(DIK_Q)) {
			scene = Game;
		}

		break;
	case Game:
		if (input_->TriggerKey(DIK_Q)) {
			scene = GameOver;
		}
		debugCamera_->Update();
		player_->Update();
		railCamera_->Update();
		checkAllCollisions();
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
		break;
		case GameOver:
		if (input_->TriggerKey(DIK_Q)) {
			scene = Title;
		}
		break;
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

	switch (scene) {
	case Title:
		titleSprite_->Draw();
		break;
	}

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

	switch (scene) {
	case Title:

		break;
	case Game:
		player_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);

		break;
	case GameOver:

		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (scene) {
	case Game:
		meterSprite_->Draw();
		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::checkAllCollisions() {
	Vector3 playerPos;
	playerPos = player_->GetWorldPosition();
	if (playerPos.z > 200.0f) {
		scene = GameOver;
	}
}
