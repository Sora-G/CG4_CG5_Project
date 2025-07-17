#pragma once
#include "KamataEngine.h"
class Player {
public:
	~Player();//解放処理
	void Init();//初期化処理
	void Update();//更新処理
	void Draw(KamataEngine::Camera& camera); // 描画処理

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
};
