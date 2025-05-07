#include "GameScene.h"
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> dist1(-1.0f, 1.0f);//-1.0~1.0
std::uniform_real_distribution<float> dist2(0.5f, 1.0f); //0.0~1.0



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


	Vector3 effectScale = {0.2f, dist2(randomEngine) * 10.0f, 1.0f};
	Vector3 effectRotate = {0.0f, 0.0f, dist1(randomEngine) * (float(M_PI) * 2.0f)};
	Vector3 effectPosition = {0.0f, 0.0f, 0.0f};
	// エフェクトの生成＆初期化
	effect_ = new Effect();
	effect_->Initialize(modelEffect_, effectScale, effectRotate, effectPosition);
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
