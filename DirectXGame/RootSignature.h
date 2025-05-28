#pragma once

#include <d3dx12.h>//ID3D12RootSignature

class RootSignature {
public:
	//生成
	void Create();

	ID3D12RootSignature* Get();

	RootSignature();
	~RootSignature();

private:
	ID3D12RootSignature* rootSignature_ = nullptr;

};
