#include "Player.h"

using namespace KamataEngine;

Player::~Player() {
	//解放処理
	delete model_;
}

void Player::Init() {
	//初期化処理
	worldTransform_.translation_.y = 0.0f;
	worldTransform_.Initialize();
	model_ = Model::Create();
}

void Player::Update() {
	//更新処理
	Vector3 move = {};
	float speed = 0.1f;

	Input* input_ = nullptr;
	input_ = Input::GetInstance();

	if (input_->PushKey(DIK_W)) {
		move.y += speed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y -= speed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += speed;
	}
	if (input_->PushKey(DIK_A)) {
		move.x -= speed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera &camera) {
	//描画処理
	model_->Draw(worldTransform_, camera);
}
