#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete model_;
	Model2::StaticFinalize();
}

void GameScene::Initialize() {
	//Model2の初期化
	Model2::StaticInitialize();
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	camera_.translation_.z = -10;
	//カメラの初期化
	camera_.Initialize();

	model_ = Model2::CreateSquare();

	textureHandle_ = TextureManager::Load("uvChecker.png");
}

void GameScene::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	//カメラの更新
	camera_.UpdateMatrix();
	//行列を定数バッファに転送
	camera_.TransferMatrix();
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//3Dモデル描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());
	//--ここから3Dモデルの描画処理を書く--

	model_->Draw(worldTransform_, camera_, textureHandle_);

	// 3Dモデル描画後処理
	Model2::PostDraw();
}
