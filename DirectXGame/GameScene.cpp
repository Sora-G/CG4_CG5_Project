#include "GameScene.h"
#include "MathUtilityForText.h"
#include <time.h>

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
	srand(static_cast<unsigned int>(time(NULL)));
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();
	camera_.translation_ = {0.0f, 0.0f, -100.0f};
	//3Dモデルデータの生成
	modelParticle_ = Model::CreateSphere(4, 4);
}

void GameScene::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	//行列の更新
	camera_.UpdateMatrix();
	//行列の転送
	camera_.TransferMatrix();

	for (Particle* particle : particles_) {
		// パーティクルの更新
		particle->Update();
	}

	// 終了フラグの立ったパーティクルの削除
	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished()) {
			delete particle;
			return true;
		}
		return false;
	});
	
	if (rand() % 30 == 0) {
		// 発生位置は乱数
		Vector3 position = {RandomFloat() * 30.0f, RandomFloat() * 20.0f, 0.0f};
		// パーティクルの生成
		ParticleBorn(position);
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

void GameScene::ParticleBorn(Vector3 position) {
	for (int i = 0; i < 150; i++) {
		//生成
		Particle* particle = new Particle();
		//パーティクルの生成＆初期化
		particle->Initialize(modelParticle_, position);
		//リストに追加
		particles_.push_back(particle);
	}
}
