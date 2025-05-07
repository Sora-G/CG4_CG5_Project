#include <KamataEngine.h>

using namespace KamataEngine;
using namespace MathUtility;

void WorldTransform::UpdateMatrix() {
	// スケーリング行列の作成
	Matrix4x4 matScale = MakeScaleMatrix(scale_);

	// 回転行列の生成
	Matrix4x4 matRotX = MakeRotateXMatrix(rotation_.x);
	Matrix4x4 matRotY = MakeRotateXMatrix(rotation_.y);
	Matrix4x4 matRotZ = MakeRotateXMatrix(rotation_.z);
	Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	// 平行移動行列の生成
	Matrix4x4 matTrans = MakeTranslateMatrix(translation_);

	// スケーリング、回転、移動の合成
	matWorld_ = matScale * matRot * matTrans;

	// 定数バッファに転送
	TransferMatrix();
}