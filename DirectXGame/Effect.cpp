#include "Effect.h"

using namespace KamataEngine;

void Effect::Initialize(Model* model, Vector3 scale, Vector3 rotate, Vector3 position) {
	// NULLポインタチェック
	assert(model);
	// 引数で受け取ったデータをメンバ変数に代入
	model_ = model;
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = rotate;
	worldTransform_.translation_ = position;
	
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
