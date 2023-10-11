#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

class RailCamera {
public:
	void Initialize(Vector3& worldPos, Vector3& rotation);
	void Update();
	ViewProjection& GetViewProjection() { return viewProjection_; }
	WorldTransform& GetWorldTransform() { return worldTransform_; };

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	float fallY;
	Input* input_ = nullptr;
};