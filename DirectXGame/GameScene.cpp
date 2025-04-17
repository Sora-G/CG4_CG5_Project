#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete modelParticle_;
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}

void GameScene::Initialize() {
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();
	//3Dモデルデータの生成
	modelParticle_ = Model::CreateSphere(4, 4);
	
	for (int i = 0; i < 150; i++) {
		//生成
		Particle* particle = new Particle();
		//位置
		Vector3 position = {0.5f * i, 0.0f, 0.0f};
		//パーティクルの生成＆初期化
		particle->Initialize(modelParticle_, position);
		//リストに追加
		particles_.push_back(particle);
	}
	
}

void GameScene::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	for (Particle* particle : particles_) {
		//パーティクルの更新
		particle->Update(); 
	}
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());
	//--ここから3Dモデルの描画処理を書く--

	for (Particle* particle : particles_) {
		// パーティクルの描画
		particle->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
}
