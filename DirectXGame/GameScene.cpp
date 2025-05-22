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
	//乱数の初期化
	srand((unsigned)time(NULL));
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();
	//3Dモデルデータの生成
	modelParticle_ = Model::CreateSphere(4, 4);

}

void GameScene::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	if (rand() % 20 == 0) {
		Vector3 position = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0.0f};
		ParticleBorn(position);
	}

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

void GameScene::ParticleBorn(Vector3 position) {	
	for (int i = 0; i < 150; i++) {
		//生成
		Particle* particle = new Particle();
		//位置
		Vector3 position_ = position;
		//速度
		Vector3 velocity_ = {distribution(randomEngine), distribution(randomEngine), 0.0f};
		Normalize(velocity_);
		velocity_ *= distribution(randomEngine);
		velocity_ *= 0.1f;
		//パーティクルの生成＆初期化
		particle->Initialize(modelParticle_, position_, velocity_);
		//リストに追加
		particles_.push_back(particle);
	}
}
