#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete modelEffect_;
	delete effect_;
}

void GameScene::Initialize() {
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();

	// 3Dモデルデータの生成
	modelEffect_ = Model::CreateFromOBJ("plane");
	// エフェクトの生成＆初期化
	effect_ = new Effect();
	effect_->Initialize(modelEffect_);
}

void GameScene::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//パーティクルの更新
	effect_->Update(); 
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());
	//--ここから3Dモデルの描画処理を書く--

	// パーティクルの描画
	effect_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}
