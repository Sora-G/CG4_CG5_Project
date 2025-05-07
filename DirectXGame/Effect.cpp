#include "Effect.h"

void Effect::Initialize(KamataEngine::Model* model) {
	// NULLポインタチェック
	assert(model);
	// 引数で受け取ったデータをメンバ変数に代入
	model_ = model;

	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.Initialize();
}

void Effect::Update() {
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera);
}
