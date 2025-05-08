#include "GameScene.h"
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> dist(-1.0f, 1.0f);//-1.0~1.0
std::uniform_real_distribution<float> distScale(0.5f, 1.5f); //0.5~1.0
std::uniform_real_distribution<float> distColor(0.7f, 1.0f); //0.0~1.0


using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete modelEffect_;
	for (Effect* effect : effects_) {
		delete effect;
	}
}

void GameScene::Initialize() {
	srand((unsigned)time(NULL));
	//ワールド変換データの初期化
	worldTransform_.Initialize();
	camera_.translation_.z = -100.0f;
	//カメラの初期化
	camera_.Initialize();

	// 3Dモデルデータの生成
	modelEffect_ = Model::CreateFromOBJ("plane");
}

void GameScene::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	
	if (rand() % 6 == 0) {
		//発生源
		Vector3 effectPosition = {dist(randomEngine) * 110.0f, dist(randomEngine) * 40.0f, 0.0f};
		//エフェクトの発生
		EffectBorn(effectPosition);
	}

	for (Effect* effect : effects_) {
		//パーティクルの更新
		effect->Update();
	}

	effects_.remove_if([](Effect* effect) {
		if (effect->IsFinished() == true) {
			delete effect;
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

	for (Effect* effect : effects_) {
		// パーティクルの描画
		effect->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
}

void GameScene::EffectBorn(Vector3 position) {
	// エフェクトの生成＆初期化
	for (int i = 0; i < 1; i++) {
		Vector3 effectScale = {distScale(randomEngine), distScale(randomEngine) * 5.0f, 1.0f};
		Vector3 effectRotate = {0.0f, 0.0f, dist(randomEngine) * (float(M_PI) * 2.0f)};
		Vector4 effectColor = {distColor(randomEngine), distColor(randomEngine), 0.3f, 1.0f};
		//生成
		Effect* effect = new Effect();
		//初期化
		effect->Initialize(modelEffect_, effectScale, effectRotate, position, effectColor);
		//リストに追加
		effects_.push_back(effect);
	}
}
