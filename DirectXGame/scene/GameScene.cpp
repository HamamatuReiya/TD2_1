#include "GameScene.h"
#include "TextureManager.h"
#include <fstream>
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete player_; 
    delete railCamera_;
	delete debugCamera_;
    delete skydome_;
	delete titleSprite_;
	delete item_;
	for (Item* item : items_) {
		delete item;
	}
	delete meterSprite_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//scene = Title;

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

	item_ = new Item();
	itemModel_ = Model::CreateFromOBJ("item", true);

	LoadItemStage1PopData();

	meterTextur_ = TextureManager::Load("Meter.png");
	meterSprite_ = Sprite::Create(meterTextur_, {100, 600});
	meter = -500.0f;
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
		UpdateItemPopCommands();
		for (Item* item : items_) {
			item->Update();
		}
		items_.remove_if([](Item* item) {
			if (item->IsDead()) {
				delete item;
				return true;
			}
			return false;
		});

		Vector2 size = meterSprite_->GetSize();
		size.y = meter;
		if (input_->PushKey(DIK_SPACE) && meter < 0.0f) {
			meter += 2.0f;
		}
		meterSprite_->SetSize(size);

		if (meter < 0) {
			railCamera_->SetisMeter(true);
		} else {
			railCamera_->SetisMeter(false);
		}


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
		Initialize();
		if (input_->TriggerKey(DIK_Q)) {
			scene = Title;
		}
		ItemDelete();
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
		for (Item* item : items_) {
			item->Draw(viewProjection_);
		}
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
	if (playerPos.z > 400.0f) {
		scene = GameOver;
	}

	const float PLAYER_R = 1.0f;
	const float ITEM_R = 1.0f;
	Vector3 posA, posB;
	
	for (Item* item : items_) {
		posA = item->GetWorldPosition();
		posB = player_->GetWorldPosition();
		float P = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		          (posB.z - posA.z) * (posB.z - posA.z);
		float R = (PLAYER_R + ITEM_R) * (PLAYER_R + ITEM_R);
		if (P <= R) {
			item->OnCollision();
		}
	}
	

}

void GameScene::ItemDelete() { 
	/*for (Item* item : items_) {
		delete item;
	}*/
	LoadItemStage1PopData();
}

void GameScene::AddItem(Vector3 position) { 
	Item* item = new Item(); 
	item->Initialize(itemModel_, position);
	item->SetGameScene(this);
	items_.push_back(item);
}

void GameScene::LoadItemStage1PopData() { 
	std::ifstream file; 
    file.open("Resources/stage1ItemPop.csv");
	assert(file.is_open());
	itemPopCommands << file.rdbuf();
	file.close();
}

void GameScene::UpdateItemPopCommands() {
	if (standFlag) {
		standTime--;
		if (standTime <= 0) {
			standFlag = false;
		}
		return;
	}
	std::string line;
	while (getline(itemPopCommands, line)) {
		std::istringstream line_stream(line);
		std::string word;
		getline(line_stream, word, ',');
		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			AddItem(Vector3(x, y, z));
		} else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');
			int32_t waitTime = atoi(word.c_str());
			standFlag = true;
			standTime = waitTime;
			break;
		}
	}
}
