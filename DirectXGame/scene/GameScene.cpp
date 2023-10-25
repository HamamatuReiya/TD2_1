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
	for (Item* item : items_) {
		delete item;
	}
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
	/*for (Obstacle* obstacle : obstacles_) {
		delete obstacle;
	}*/
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
	//障害物3
	obstacle3_ = new Obstacle3();
	obstacle3_->Initialize(obstacleModel_, building_);
	//障害物4
	obstacle4_ = new Obstacle4();
	obstacle4_->Initialize(obstacleModel_, building_);
	// 障害物5
	obstacle5_ = new Obstacle5();
	obstacle5_->Initialize(obstacleModel_, building_);
	//障害物6
	obstacle6_ = new Obstacle6();
	obstacle6_->Initialize(obstacleModel_, building_);
	// 障害物7
	obstacle7_ = new Obstacle7();
	obstacle7_->Initialize(obstacleModel_, building_);
	// 障害物8
	obstacle8_ = new Obstacle8();
	obstacle8_->Initialize(obstacleModel_, building_);
	// 障害物9
	obstacle9_ = new Obstacle9();
	obstacle9_->Initialize(obstacleModel_, building_);
	// 障害物10
	obstacle10_ = new Obstacle10();
	obstacle10_->Initialize(obstacleModel_, building_);
	// 障害物11
	obstacle11_ = new Obstacle11();
	obstacle11_->Initialize(obstacleModel_, building_);
	// 障害物11
	obstacle12_ = new Obstacle12();
	obstacle12_->Initialize(obstacleModel_, building_);
	// 障害物11
	obstacle13_ = new Obstacle13();
	obstacle13_->Initialize(obstacleModel_, building_);
	//渡り廊下1リソース
	breezeway_ = new Breezeway();
	building2_ = TextureManager::Load("breezeway.png");
	breezewayModel_ = Model::Create();
	breezeway_->Initialize(breezewayModel_, building2_);
	//渡り廊下2
	breezeway2_ = new Breezeway2();
	breezeway2_->Initialize(breezewayModel_, building2_);
	//渡り廊下3
	breezeway3_ = new Breezeway3();
	breezeway3_->Initialize(breezewayModel_, building2_);
	// 渡り廊下4
	breezeway4_ = new Breezeway4();
	breezeway4_->Initialize(breezewayModel_, building2_);
	// 渡り廊下5
	breezeway5_ = new Breezeway5();
	breezeway5_->Initialize(breezewayModel_, building2_);
	// 渡り廊下6
	breezeway6_ = new Breezeway6();
	breezeway6_->Initialize(breezewayModel_, building2_);

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

	//サウンド読み込み
	bgmHandle_ = audio_->LoadWave("bgm.wav");

	soundHandle_ = audio_->LoadWave("energy.wav");

	pushSoundHandle_ = audio_->LoadWave("push.wav");

	////////////////

}

void GameScene::Update() { 

	if (isBgm_ == false) {
		bgmLoop_ = audio_->PlayWave(bgmHandle_, true);
		isBgm_ = true;
	}

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
				audio_->PlayWave(pushSoundHandle_);
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
					LoadItemStage1PopData();
					scene = Stage1;
					spaceKeyBlinking_ = 0;
					isSpaceKeyBlinking_ = true;
					audio_->PlayWave(pushSoundHandle_);
				}
				if (isSelectStage1 == false) {
					scene = Stage2;
					spaceKeyBlinking_ = 0;
					isSpaceKeyBlinking_ = true;
					audio_->PlayWave(pushSoundHandle_);
				}
			}
			break;
		}

		break;
		//////////ステージ1//////////////
	case Stage1:
		if (isGameClear_ == false) {

			if (input_->TriggerKey(DIK_SPACE)) {
				if (isStagePushSpace_ == false) {
					audio_->PlayWave(pushSoundHandle_);
				}
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
				audio_->PlayWave(pushSoundHandle_);
				Initialize();
			}
		}

		debugCamera_->Update();
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
				if (isStagePushSpace_ == false) {
					audio_->PlayWave(pushSoundHandle_);
				}
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
				audio_->PlayWave(pushSoundHandle_);
				Initialize();
			    }
		}
		debugCamera_->Update();
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
			audio_->PlayWave(pushSoundHandle_);
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
		obstacle3_->Draw(viewProjection_);
		obstacle4_->Draw(viewProjection_);
		obstacle5_->Draw(viewProjection_);
		obstacle6_->Draw(viewProjection_);
		obstacle7_->Draw(viewProjection_);
		obstacle8_->Draw(viewProjection_);
		obstacle9_->Draw(viewProjection_);
		obstacle10_->Draw(viewProjection_);
		obstacle11_->Draw(viewProjection_);
		obstacle12_->Draw(viewProjection_);
		obstacle13_->Draw(viewProjection_);
		breezeway_->Draw(viewProjection_);
		breezeway2_->Draw(viewProjection_);
		breezeway3_->Draw(viewProjection_);
		breezeway4_->Draw(viewProjection_);
		breezeway5_->Draw(viewProjection_);
		breezeway6_->Draw(viewProjection_);
		/*for (Obstacle* obstacle : obstacles_) {
			
		}*/
		for (Item* item : items_) {
			item->Draw(viewProjection_);
		}
		break;
	case Stage2:
		player_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);
		obstacle_->Draw(viewProjection_);
		obstacle2_->Draw(viewProjection_);
		obstacle3_->Draw(viewProjection_);
		obstacle4_->Draw(viewProjection_);
		obstacle5_->Draw(viewProjection_);
		obstacle6_->Draw(viewProjection_);
		obstacle7_->Draw(viewProjection_);
		obstacle8_->Draw(viewProjection_);
		obstacle9_->Draw(viewProjection_);
		obstacle10_->Draw(viewProjection_);
		obstacle11_->Draw(viewProjection_);
		obstacle12_->Draw(viewProjection_);
		obstacle13_->Draw(viewProjection_);
		breezeway_->Draw(viewProjection_);
		breezeway2_->Draw(viewProjection_);
		breezeway3_->Draw(viewProjection_);
		breezeway4_->Draw(viewProjection_);
		breezeway5_->Draw(viewProjection_);
		breezeway6_->Draw(viewProjection_);

		/*for (Obstacle* obstacle : obstacles_) {
			
		}*/
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
	Vector3 playerPos;
	playerPos = player_->GetWorldPosition();
	if (playerPos.z > 400.0f) {
		isGameClear_ = true;
		isStage1Clear_ = true;
	}

	if (isPlayerPosY_ == true) {
		if (playerPos.y <= 1.0f) {
			scene = GameOver;
		}
	}

	const float PLAYER_R = 1.0f;
	const float ITEM_R = 1.5f;
	Vector3 posA, posB;
	
	for (Item* item : items_) {
		posA = item->GetWorldPosition();
		posB = player_->GetWorldPosition();
		float P = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		          (posB.z - posA.z) * (posB.z - posA.z);
		float R = (PLAYER_R + ITEM_R) * (PLAYER_R + ITEM_R);
		if (P <= R) {
			item->OnCollision();
			audio_->PlayWave(soundHandle_);
			meter -= 250;
		}
	}
	//ここから障害物の当たり判定
	const float OBSTACLE_R = 9.0f;
	posA = obstacle_->GetWorldPosition();
	posB = player_->GetWorldPosition();
	float A = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
	          (posB.z - posA.z) * (posB.z - posA.z);
	float B = (PLAYER_R + OBSTACLE_R) * (PLAYER_R + OBSTACLE_R);
	if (A <= B) {
		scene = GameOver;
	}
	const float BREEZEWAY_R = 2.5f;
	posA = breezeway_->GetWorldPosition();
	posB = player_->GetWorldPosition();
	float C = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
	          (posB.z - posA.z) * (posB.z - posA.z);
	float D = (PLAYER_R + BREEZEWAY_R) * (PLAYER_R + BREEZEWAY_R);
	if (C <= D) {
		scene = GameOver;
	}
	posA = breezeway4_->GetWorldPosition();
	posB = player_->GetWorldPosition();
	float E = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
	          (posB.z - posA.z) * (posB.z - posA.z);
	float F = (PLAYER_R + BREEZEWAY_R) * (PLAYER_R + BREEZEWAY_R);
	if (E <= F) {
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
