#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete model_;
}

void GameScene::Initialize() {
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();

	model_ = Model::Create();
}

void GameScene::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());
	//--ここから3Dモデルの描画処理を書く--

	model_->Draw(worldTransform_, camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}
