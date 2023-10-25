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
	delete item_;
	delete meterSprite_;
	delete meterFlameSprite_;
	delete titleTextSprite_;
	delete titleBackSprite_;
	delete pressSpaceSprite_;
	delete stage1Sprite_;
	delete stage1SelectSprite_;
	delete stage2Sprite_;
	delete stage2SelectSprite_;
	delete explanationSprite_;
	delete gameOverSprite_;
	delete gameClearSprite_;
	delete goal_;
	delete goal2_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// scene = Title;

	/////////////
	titleTextTexture_ = TextureManager::Load("TitleText.png");
	titleTextSprite_ = Sprite::Create(titleTextTexture_, {0, 0});

	titleBackTexture_ = TextureManager::Load("TitleBack.png");
	titleBackSprite_ = Sprite::Create(titleBackTexture_, {0, 0});

	pressSpaceTexture_ = TextureManager::Load("PRESSSPACE.png");
	pressSpaceSprite_ = Sprite::Create(pressSpaceTexture_, {0, 0});
	spaceKeyBlinking_ = 0;
	isSpaceKeyBlinking_ = true;

	stage1Texture_ = TextureManager::Load("STAGE1.png");
	stage1Sprite_ = Sprite::Create(stage1Texture_, {0, 0});

	stage1SelectTexture_ = TextureManager::Load("STAGE1SELECT.png");
	stage1SelectSprite_ = Sprite::Create(stage1SelectTexture_, {0, 0});

	stage2Texture_ = TextureManager::Load("STAGE2.png");
	stage2Sprite_ = Sprite::Create(stage2Texture_, {0, 0});
	stage2SelectTexture_ = TextureManager::Load("STAGE2SELECT.png");
	stage2SelectSprite_ = Sprite::Create(stage2SelectTexture_, {0, 0});
	if (isStage1Clear_ == true) {
		stage2Color_ = {1, 1, 1, 1};
	}
	stage2Sprite_->SetColor(stage2Color_);

	/////////////////

	////////////////
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	isStagePushSpace_ = false;
	isStageUpdate_ = true;
	isPlayerPosY_ = false;

	//プレイヤーの初期位置
	worldPos.y = 50.0f;
	railCamera_ = new RailCamera();
	railCamera_->Initialize(worldPos, rotation);

	player_ = new Player();
	playerModel_ = Model::CreateFromOBJ("Player", true);
	Vector3 playerPosition(0, -2.0f, 30.0f);
	player_->Initialize(playerModel_, playerPosition);
	player_->SetParent(&railCamera_->GetWorldTransform());

	//障害物1
	obstacle_ = new Obstacle();
	building_ = TextureManager::Load("black.png");
	obstacleModel_ = Model::Create();
	obstacle_->Initialize(obstacleModel_, building_);
	//障害物2
	obstacle2_ = new Obstacle2();
	obstacle2_->Initialize(obstacleModel_, building_);

	debugCamera_ = new DebugCamera(1280, 720);

	skydome_ = new Skydome();
	skydomeModel_ = Model::CreateFromOBJ("skydome", true);
	skydome_->Initialize(skydomeModel_);

	ground_ = std::make_unique<Ground>();
	groundModel_.reset(Model::CreateFromOBJ("Ground", true));
	ground_->Initialize(groundModel_.get());

	item_ = new Item();
	itemModel_ = Model::CreateFromOBJ("item", true);

	meterTextur_ = TextureManager::Load("Meter.png");
	meterSprite_ = Sprite::Create(meterTextur_, {100, 600});
	meter = -500.0f;

	meterFlameTexture_ = TextureManager::Load("MeterFlame.png");
	meterFlameSprite_ = Sprite::Create(meterFlameTexture_, {97, 97});

	explanationTexture_ = TextureManager::Load("explanation.png");
	explanationSprite_ = Sprite::Create(explanationTexture_, {0, 0});

	gameOverTexture_ = TextureManager::Load("GameOver.png");
	gameOverSprite_ = Sprite::Create(gameOverTexture_, {0, 0});

	gameClearTexture_ = TextureManager::Load("GameClear.png");
	gameClearSprite_ = Sprite::Create(gameClearTexture_, {0, 0});
	isGameClear_ = false;

	goal_ = new Goal();
	goalModel_ = Model::CreateFromOBJ("Goal", true);
	goal_->Initialize(goalModel_,goalPos_);

	goal2_ = new Goal();
	goalModel2_ = Model::CreateFromOBJ("Goal", true);
	goal2_->Initialize(goalModel2_, goalPos2_);

	itemPos_ = {0, 30, 100};
	item_->Initialize(itemModel_,itemPos_);


	////////////////

}

void GameScene::Update() { 

	switch (scene) {
	case Title:

		switch (titleScene) {
		case Start:
			spaceKeyBlinking_++;
			if (spaceKeyBlinking_ >= 60) {
				spaceKeyBlinking_ = 0;
			}
			if (spaceKeyBlinking_ >= 30) {
				isSpaceKeyBlinking_ = false;
			} else {
				isSpaceKeyBlinking_ = true;
			}
			// SPACEを押してシーンの切り替え
			if (input_->TriggerKey(DIK_SPACE)) {
				titleScene = Select;
			}
			break;

			case Select:
			if (isStage1Clear_ == true) {
				if (input_->TriggerKey(DIK_LEFTARROW)) {
					isSelectStage1 = true;
				} else if (input_->TriggerKey(DIK_RIGHTARROW)) {
					isSelectStage1 = false;
				}
			}
			if (input_->TriggerKey(DIK_SPACE)) {
				//ステージの選択
				if (isSelectStage1 == true) {
					scene = Stage1;
					spaceKeyBlinking_ = 0;
					isSpaceKeyBlinking_ = true;
				}
				if (isSelectStage1 == false) {
					scene = Stage2;
					spaceKeyBlinking_ = 0;
					isSpaceKeyBlinking_ = true;
				}
			}
			break;
		}

		break;
		//////////ステージ1//////////////
	case Stage1:
		if (isGameClear_ == false) {

			if (input_->TriggerKey(DIK_SPACE)) {
				isStagePushSpace_ = true;
			}
			if (isStagePushSpace_ == true) {
				railCamera_->Update();
				player_->Update();
				if (input_->PushKey(DIK_SPACE) && meter < 0.0f) {
					meter += 2.0f;
				}
				isPlayerPosY_ = true;
			}
		}

		if (isGameClear_ == true) {
			if (input_->TriggerKey(DIK_SPACE)) {
				scene = Title;
				Initialize();
			}
		}

		goal_->Update();
		debugCamera_->Update();
			checkAllCollisions();
			
			item_->Update();

			size = meterSprite_->GetSize();
			size.y = meter;
			
			meterSprite_->SetSize(size);

			if (meter <= -500) {
				meter = -500;
			}

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
		///////////ステージ2////////////
	case Stage2:
		if (isGameClear_ == false) {

			    if (input_->TriggerKey(DIK_SPACE)) {
				isStagePushSpace_ = true;
			    }
			    if (isStagePushSpace_ == true) {
				railCamera_->Update();
				player_->Update();
				if (input_->PushKey(DIK_SPACE) && meter < 0.0f) {
					meter += 2.0f;
				}
				isPlayerPosY_ = true;
			    }
		}

		if (isGameClear_ == true) {
			    if (input_->TriggerKey(DIK_SPACE)) {
				scene = Title;
				Initialize();
			    }
		}
		goal2_->Update();
		debugCamera_->Update();
		checkAllCollisions();
		
		item_->Update();

		size = meterSprite_->GetSize();
		size.y = meter;
		
		meterSprite_->SetSize(size);

		if (meter <= -500) {
			meter = -500;
		}

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
		
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = Title;
			Initialize();
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
		titleBackSprite_->Draw();
		switch (titleScene) {
		case Start:
			titleTextSprite_->Draw();
			if (isSpaceKeyBlinking_ == true) {
				pressSpaceSprite_->Draw();
			}
			break;

			case Select:
			stage1Sprite_->Draw();
			stage2Sprite_->Draw();
			if (isSelectStage1 == true) {
				stage1SelectSprite_->Draw();
			} else {
				stage2SelectSprite_->Draw();
			}
			break;
		}
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
	case Stage1:
		player_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);
		obstacle_->Draw(viewProjection_);
		obstacle2_->Draw(viewProjection_);
		/*for (Obstacle* obstacle : obstacles_) {
			
		}*/
		for (Item* item : items_) {
			item->Draw(viewProjection_);
		}
		goal_->Draw(viewProjection_);
		item_->Draw(viewProjection_);
		break;
	case Stage2:
		player_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);
		obstacle_->Draw(viewProjection_);
		obstacle2_->Draw(viewProjection_);
		/*for (Obstacle* obstacle : obstacles_) {
			
		}*/
		for (Item* item : items_) {
			item->Draw(viewProjection_);
		}
		goal2_->Draw(viewProjection_);
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
	case Stage1:
		meterFlameSprite_->Draw();
		meterSprite_->Draw();
		if (isStagePushSpace_ == false) {
			explanationSprite_->Draw();
		}
		if (isGameClear_ == true) {
			gameClearSprite_->Draw();
		}
		break;
	case Stage2:
		meterFlameSprite_->Draw();
		meterSprite_->Draw();
		if (isStagePushSpace_ == false) {
			explanationSprite_->Draw();
		}
		if (isGameClear_ == true) {
			gameClearSprite_->Draw();
		}
		break;
	case GameOver:
		gameOverSprite_->Draw();
		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::checkAllCollisions() {
	if (isSelectStage1 == true) {
		playerHitPos = player_->GetWorldPosition();
		if (playerHitPos.z > 400.0f) {
			isGameClear_ = true;
			isStage1Clear_ = true;
		}
	}

	if (isSelectStage1 == false) {
		playerHitPos = player_->GetWorldPosition();
		if (playerHitPos.z > 800.0f) {
			isGameClear_ = true;
		}
	}

	if (isPlayerPosY_ == true) {
		if (playerHitPos.y <= 1.0f) {
			scene = GameOver;
		}
	}

	const float PLAYER_R = 1.0f;
	const float ITEM_R = 1.5f;
		posA = item_->GetWorldPosition();
		posB = player_->GetWorldPosition();
		float P = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		          (posB.z - posA.z) * (posB.z - posA.z);
		float R = (PLAYER_R + ITEM_R) * (PLAYER_R + ITEM_R);
		if (P <= R) {
			item_->OnCollision();
			meter -= 250;
		}
	}
	const float OBSTACLE_R = 5.0f;
	posA = obstacle_->GetWorldPosition();
	posB = player_->GetWorldPosition();
	float A = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
	          (posB.z - posA.z) * (posB.z - posA.z);
	float B = (PLAYER_R + OBSTACLE_R) * (PLAYER_R + OBSTACLE_R);
	if (A <= B) {
		scene = GameOver;
	}
	posA = obstacle2_->GetWorldPosition();
	posB = player_->GetWorldPosition();
	float C = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
	          (posB.z - posA.z) * (posB.z - posA.z);
	float D = (PLAYER_R + OBSTACLE_R) * (PLAYER_R + OBSTACLE_R);
	if (C <= D) {
		scene = GameOver;
	}
}

void GameScene::ItemDelete() { 
	/*for (Item* item : items_) {
		delete item;
	}*/
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

}
