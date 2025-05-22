#include "GameScene.h"
#include <random>

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

using namespace KamataEngine;
using namespace MathUtility;

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
	camera_.translation_.z = -100;
	//カメラの初期化
	camera_.Initialize();
	//3Dモデルデータの生成
	modelParticle_ = Model::CreateSphere(4, 4);
	
	for (int i = 0; i < 150; i++) {
		//生成
		Particle* particle = new Particle();
		//位置
		Vector3 position = {0.0f, 0.0f, 0.0f};
		//速度
		Vector3 velocity = {distribution(randomEngine), distribution(randomEngine), 0.0f};
		Normalize(velocity);
		velocity *= distribution(randomEngine);
		velocity *= 0.1f;
		//パーティクルの生成＆初期化
		particle->Initialize(modelParticle_, position, velocity);
		//リストに追加
		particles_.push_back(particle);
	}
	
}

void GameScene::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

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
