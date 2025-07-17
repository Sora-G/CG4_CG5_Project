#pragma once

#include "KamataEngine.h"

// Vector3同士の加算
KamataEngine::Vector3& operator+=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);

// Vector3同士の減算
KamataEngine::Vector3& operator-=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);

// Vector3同士の加算
KamataEngine::Vector3& operator*=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);

KamataEngine::Vector3& operator*(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);

KamataEngine::Matrix4x4& operator*=(KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

// 4x4行列の乗算
KamataEngine::Matrix4x4 MatrixMultply(KamataEngine::Matrix4x4& m1, KamataEngine::Matrix4x4& m2);

// アフィン変換行列
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rot, const KamataEngine::Vector3& translate);

// ベクトル変換
KamataEngine::Vector3 TransformNormal(const KamataEngine::Vector3& v, const KamataEngine::Matrix4x4& m);

// 逆行列
KamataEngine::Matrix4x4 Inverse(const KamataEngine::Matrix4x4& matrix);
