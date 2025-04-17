#pragma once

#include <KamataEngine.h>

class Particle 
{
public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model,KamataEngine::Vector3 position);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(KamataEngine::Camera& camera);

	//デスフラグのゲッター
	bool IsFinished() { return isFinished_; }

	//float型のランダム関数(-1.0f~1.0f)
	float RandomFloat() { return static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f; }

private: // メンバ変数
	KamataEngine::WorldTransform worldTransform_;//ワールド変換データ
	KamataEngine::Model* model_ = nullptr;//モデル
	KamataEngine::ObjectColor objectColor_;//色変更オブジェクト
	KamataEngine::Vector4 color_;//色の数値
	KamataEngine::Vector3 speed_;//移動速度
	bool isFinished_ = false;//終了フラグ
	float counter_ = 0.0f;//経過時間カウント
	const float kDuration = 1.0f;//存続時間(消滅までの時間)<秒/s>
};
