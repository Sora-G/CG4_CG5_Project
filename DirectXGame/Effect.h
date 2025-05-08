#pragma once

#include "KamataEngine.h"

class Effect {
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 scale, KamataEngine::Vector3 rotate, KamataEngine::Vector3 position, KamataEngine::Vector4 color);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(KamataEngine::Camera& camera);

	bool IsFinished() { return isFinished_; }

private:                                          // メンバ変数
	KamataEngine::WorldTransform worldTransform_; // ワールド変換データ
	KamataEngine::Model* model_ = nullptr;        // モデル
	KamataEngine::ObjectColor objectColor_;       // 色変更オブジェクト
	KamataEngine::Vector4 color_;                 // 色の数値
	bool isFinished_ = false;//終了フラグ
	float counter_ = 0.0f;//経過時間カウント
	const float kDuration_ = 1.0f;//存続時間
};
