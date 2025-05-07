#pragma once

#include "KamataEngine.h"

class Effect {
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 scale, KamataEngine::Vector3 rotate, KamataEngine::Vector3 position);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(KamataEngine::Camera& camera);

private:                                          // メンバ変数
	KamataEngine::WorldTransform worldTransform_; // ワールド変換データ
	KamataEngine::Model* model_ = nullptr;        // モデル
};
