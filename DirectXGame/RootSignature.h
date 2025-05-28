#pragma once

#include <d3dx12.h>//ID3D12RootSignature
#include <Windows.h>

class RootSignature {
public:
	//生成
	void Create();

	ID3D12RootSignature* Get();

	RootSignature();
	~RootSignature();

private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;

};
