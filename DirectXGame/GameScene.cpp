#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete modelParticle_;
	delete particle_;
}

void GameScene::Initialize() {
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();
	//3Dモデルデータの生成
	modelParticle_ = Model::CreateSphere(4, 4);
	//パーティクルの生成＆初期化
	particle_ = new Particle();
	particle_->Initialize(modelParticle_);
}

void GameScene::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//パーティクルの更新
	particle_->Update(); 
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());
	//--ここから3Dモデルの描画処理を書く--

	// パーティクルの描画
	particle_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}
