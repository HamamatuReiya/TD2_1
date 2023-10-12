#include "RailCamera.h"
#include "ImGuiManager.h"
#include "MyMath.h"

void RailCamera::Initialize(Vector3& worldPos, Vector3& rotation) {
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.translation_ = worldPos;
	worldTransform_.rotation_ = rotation;
	viewProjection_.Initialize();
}

void RailCamera::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {
		//fallY =0.0f;
	}

	if (input_->PushKey(DIK_SPACE)) {
		fallY+=0.005f;
	}

	Vector3 move = {0.0f, fallY, 0.05f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	//落下速度
	fallY -= 0.0025f;

	if (fallY < -1) {
		fallY = -1;
	}

	//地面
	if (worldTransform_.translation_.y < 3.0f) {
		worldTransform_.translation_.y = 3.0f;
		fallY = 0.0f;
	}

	Vector3 rotate = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, rotate);

	worldTransform_.UpdateMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();
}