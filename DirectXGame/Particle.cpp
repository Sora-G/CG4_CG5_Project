#include "Particle.h"

using namespace KamataEngine;
using namespace MathUtility;

void Particle::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);
	//引数で受け取ったデータをメンバ変数に代入
	model_ = model;
	//色の設定
	objectColor_.Initialize();
	color_ = {1.0f, 1.0f, 0.0f, 1.0f};
	//ワールド変換データの初期化
	worldTransform_.Initialize();
}

void Particle::Update() {
	//移動
	worldTransform_.translation_ += {0.0f, 1.0f, 0.0f};
	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);
	//行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(Camera& camera) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, camera, &objectColor_);
}
