#include "Particle.h"

using namespace KamataEngine;

void Particle::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);
	//引数で受け取ったデータをメンバ変数に代入
	model_ = model;

	worldTransform_.Initialize();
}

void Particle::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Particle::Draw(Camera& camera) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, camera);
}
