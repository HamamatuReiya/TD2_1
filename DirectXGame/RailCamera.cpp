﻿#include "RailCamera.h"
#include "ImGuiManager.h"
#include "MyMath.h"

void RailCamera::Initialize(Vector3& worldPos, Vector3& rotation) {
	isFall = true;
	isMeter_ = true;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.translation_ = worldPos;
	worldTransform_.rotation_ = rotation;
	//worldTransform_.rotation_ = Add(worldTransform_.rotation_, {0.0f, -0.0f, 0.0f});
	viewProjection_.Initialize();
}

void RailCamera::Update() {

	isFall = true;
	if (isMeter_ == true) {

		if (input_->PushKey(DIK_SPACE)) {
			isFall = false;
			// 上昇速度
			fallY += 0.0075f;

			if (fallY < 0) {
				fallY += 0.025f;
			}
		}
	}

	// 上昇速度制限
	if (fallY > 1.5) {
		fallY = 1.5;
	}

	// 落下速度制限
	if (fallY < -1.5) {
		fallY = -1.5;
	}

	if (isFall == true){
		// 落下速度
		fallY -= 0.0075f;

		if (fallY > 0) {
			fallY -= 0.025f;
		}
    }

	//地面
	if (worldTransform_.translation_.y < 3.0f) {
		worldTransform_.translation_.y = 3.0f;
		fallY = 0.0f;
	}

	//上昇制限
	if (worldTransform_.translation_.y > 150.0f) {
		worldTransform_.translation_.y = 150.0f;
		fallY = 0.0f;
	}

	Vector3 move = {0.0f, fallY, 0.3f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	Vector3 rotate = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, rotate);

	worldTransform_.UpdateMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	/*ImGui::Begin("Camera");
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -300.0f, 300.0f);
	ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();*/
}

Vector3 RailCamera::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}