#include "Player.h"

using namespace KamataEngine;

Player::~Player() {
	//解放処理
	delete model_;
}

void Player::Init() {
	//初期化処理
	worldTransform_.Initialize();
	model_ = Model::CreateSphere();
}

void Player::Update() {
	//更新処理
	worldTransform_.TransferMatrix();
}

void Player::Draw(Camera &camera) {
	//描画処理
	model_->Draw(worldTransform_, camera);
}
