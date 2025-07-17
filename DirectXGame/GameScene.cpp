#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete stage_;
	delete model_;
}

void GameScene::Init() {
	//初期化処理
	worldTransform_.Initialize();
	camera_.translation_ = {0.0f, 0.0f, -20.0f};
	camera_.Initialize();

	stage_ = new Stage();
	stage_->Init();

	model_ = Model::CreateSphere();
}

void GameScene::Update() {
	//更新処理
	worldTransform_.TransferMatrix();
	camera_.UpdateMatrix();
	camera_.TransferMatrix();
	stage_->Update();
}

void GameScene::DrawBackGroundSprite() {
	//スプライトの描画処理
	stage_->Draw();
}

void GameScene::DrawModel() {
	//モデルの描画処理
	model_->Draw(worldTransform_, camera_);
}

