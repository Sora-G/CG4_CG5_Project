#include "Effect.h"
#include <algorithm>

using namespace KamataEngine;

void Effect::Initialize(Model* model, Vector3 scale, Vector3 rotate, Vector3 position,Vector4 color) {
	// NULLポインタチェック
	assert(model);
	// 引数で受け取ったデータをメンバ変数に代入
	model_ = model;
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = rotate;
	worldTransform_.translation_ = position;
	
	//色の設定
	objectColor_.Initialize();
	color_ = color;

	//ワールド変換データの初期化
	worldTransform_.Initialize();
}

void Effect::Update() {
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();

	//worldTransform_.translation_.x += 1.0f;
	//worldTransform_.translation_.y -= 0.5f;
	worldTransform_.rotation_.z += 1.57f;

	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	//終了なら何もしない
	if (isFinished_) {
		return;
	}

	//カウンターを進める
	counter_ += 1.0f / 60.0f;

	//存続時間の上限に達したら
	if (counter_ >= kDuration_) {
		counter_ = kDuration_;
		//終了扱いにする
		isFinished_ = true;
	}

	//フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration_, 0.0f, 1.0f);

	worldTransform_.scale_.x = std::clamp(1.0f - counter_ / kDuration_, 0.0f, 0.2f);
}

void Effect::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera, &objectColor_);
}
