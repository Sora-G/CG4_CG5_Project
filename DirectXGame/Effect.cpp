#include "Effect.h"

void Effect::Initialize(KamataEngine::Model* model) {
	// NULLポインタチェック
	assert(model);
	// 引数で受け取ったデータをメンバ変数に代入
	model_ = model;

	worldTransform_.Initialize();
}

void Effect::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera);
}
