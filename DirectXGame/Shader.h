#pragma once

#include <string>	//wstring,string
#include <d3d12.h>	//ID3DBlob

#include <d3dcompiler.h>//dxcapi.hが依存している
#include <dxcapi.h>//IDxcBlobを利用するため

class Shader {
public:
	//シェーダファイルを読み込み、コンパイル済みデータを生成する
	void Load(const std::wstring& filePath, const std::wstring& shaderModel);
	void LoadDxc(const std::wstring& filePath, const std::wstring& shaderModel);

	//生成したコンパイル済みデータを取得する
	ID3DBlob* GetBlob();
	IDxcBlob* GetDxcBlob();

	//コンストラクタ
	Shader();
	//デストラクタ
	~Shader();

private:
	ID3DBlob* blob_ = nullptr;	//コンストラクタで初期化しない
	IDxcBlob* dxcBlob_ = nullptr;//コンパイル済みのシェーダーデータ
};
