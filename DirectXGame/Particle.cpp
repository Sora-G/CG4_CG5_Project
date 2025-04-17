#include "Particle.h"
#include "MathUtilityForText.h"
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

void Particle::Initialize(Model* model,Vector3 position) {
	//NULLポインタチェック
	assert(model);
	//引数で受け取ったデータをメンバ変数に代入
	model_ = model;
	worldTransform_.translation_ = position;
	//色の設定
	objectColor_.Initialize();
	color_ = {1.0f, 1.0f, 0.0f, 1.0f};
	//移動速度
	speed_ = {RandomFloat(), RandomFloat(), 0.0f};
	//ワールド変換データの初期化
	worldTransform_.Initialize();
}

void Particle::Update() {
	//終了なら何もしない
	if (isFinished_) {
		return;
	}

	//カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	//存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		//終了扱いにする
		isFinished_ = true;
	}
	
	//行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
	
	//移動
	worldTransform_.translation_ += speed_;
	
	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);
	
	//フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
}

void Particle::Draw(Camera& camera) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, camera, &objectColor_);
}
