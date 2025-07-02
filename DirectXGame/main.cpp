#include <Windows.h>
#include <d3dcompiler.h>
#include "KamataEngine.h"
#include "Shader.h"
#include "RootSignature.h"
#include "PipelineState.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace KamataEngine;

//関数プロトタイプ宣言
void SetupPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps);
//RenderTextureResourceの生成
ID3D12Resource* CreateRenderTextureResource(ID3D12Device* device, uint32_t width, uint32_t height, DXGI_FORMAT format, const FLOAT* clearColor);
//DepthStencilTextureResourceの生成
ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3C_12_スズキ_ソラ");

	// DirectXCommonのインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//DirectXCommonクラスのが管理している、ウィンドウの幅と高さの取得
	int32_t w = dxCommon->GetBackBufferWidth();
	int32_t h = dxCommon->GetBackBufferHeight();
	DebugText::GetInstance()->ConsolePrintf(std::format("width: {}, height: {}\n", w, h).c_str());

	//DirectXCommonクラスが管理している、コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();


	//RootSignature作成----------
	RootSignature rs;
	rs.Create();

	//VertexShaderをCompileする----------
	//コンパイル済みのShader、エラー情報の格納場所の用意
	//頂点シェーダーの読み込みとコンパイル
	Shader vs;
	vs.LoadDxc(L"Resources/shaders/TestVS.hlsl", L"vs_6_0");
	assert(vs.GetDxcBlob() != nullptr);
	//ピクセルシェーダーの読み込みとコンパイル
	Shader ps;
	ps.LoadDxc(L"Resources/shaders/TestPS.hlsl", L"ps_6_0");
	assert(ps.GetDxcBlob() != nullptr);
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;//エラーオブジェクト

	//PipelineStateの生成
	PipelineState pipelineState;
	SetupPipelineState(pipelineState, rs, vs, ps);

	//リソースの確保を含め、頂点情報を柔軟に対応できるようにVertexData構造体を新たに作成する
	//Vertex4->VertexDataに変更して利用する
	struct VertexData {
		Vector4 position;
		Vector2 texcoord;
	};

	//頂点データの準備
	VertexData vertices[] = {
	    {{1.0f, 1.0f, 0.0f, 1.0f},   {1.0f, 0.0f}},//右上
        {{-1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},//左下
        {{1.0f, -1.0f, 0.0f, 1.0f},  {1.0f, 1.0f}},//右下
        {{-1.0f, 1.0f, 0.0f, 1.0f},  {0.0f, 0.0f}}//左上
    };

	//VertexBufferの生成
	VertexBuffer vb;
	vb.Create(sizeof(vertices), sizeof(vertices[0]));

	//頂点リソースにデータを書き込む
	VertexData* pGpuVertices = nullptr;
	vb.Get()->Map(0, nullptr, reinterpret_cast<void**>(&pGpuVertices));

	for (int i = 0; i < _countof(vertices); ++i) {
		pGpuVertices[i] = vertices[i];
	}

	//頂点インデックスデータの準備
	uint16_t indices[] = {0, 2, 1, 1, 3, 0};

	//IndexBuffer(IndexResource,IndexResourceView)の生成
	IndexBuffer ib;
	ib.Create(sizeof(indices), sizeof(indices[0]));

	//頂点インデックスリソースにデータを書き込む
	uint16_t* pGpuIndices = nullptr;
	ib.Get()->Map(0, nullptr, reinterpret_cast<void**>(&pGpuIndices));

	for (int i = 0; i < _countof(indices); ++i) {
		pGpuIndices[i] = indices[i];
	}

	//Resource生成、Heap生成、View生成　で再利用される変数の準備
	ID3D12Device* device = dxCommon->GetDevice();
	HRESULT hr;


	//RenderTexture関係
	//0.RenderTextureResourceの作成
	//画面クリア色
	const FLOAT kRenderTargetClearColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};

	ID3D12Resource* renderTextureResource = CreateRenderTextureResource(
		device, WinApp::kWindowWidth, WinApp::kWindowHeight, 
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, kRenderTargetClearColor);

	//1.RTV用のDescriptorHeapを作成する
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;

	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc{};
	rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescriptorHeapDesc.NumDescriptors = 1;

	hr = device->CreateDescriptorHeap(&rtvDescriptorHeapDesc, IID_PPV_ARGS(&rtvDescriptorHeap));
	assert(SUCCEEDED(hr));

	//CPU側からみたHANDLEを取得しておく
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandleCPU = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	//2.RTV用のViewの生成
	device->CreateRenderTargetView(renderTextureResource, nullptr, rtvHandleCPU);


	//DepthStencilTexture関係
	//0.DepthStencilTextureResourceの作成
	ID3D12Resource* depthStencilResource = CreateDepthStencilTextureResource(
		device, WinApp::kWindowWidth, WinApp::kWindowHeight);

	//1.DSV用のDescroptorHeapの作成
	ID3D12DescriptorHeap* dsvDescriptorHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC dsvDescriptorHeapDesc{};
	dsvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//HeapType
	dsvDescriptorHeapDesc.NumDescriptors = 1;//HeapTypeの個数
	dsvDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//DSVはShaderで触らないとする

	hr = device->CreateDescriptorHeap(&dsvDescriptorHeapDesc, IID_PPV_ARGS(&dsvDescriptorHeap));
	assert(SUCCEEDED(hr));

	//CPU側からみたHANDLEを取得しておく
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandleCPU = dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	//2.DSV用のViewの生成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//基本的にResourceに合わせる
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;//2DTexture

	//DSVHeapの先頭にDSVを作る
	device->CreateDepthStencilView(depthStencilResource, &dsvDesc, dsvHandleCPU);


	//SRV(Shader Resource Desc)を準備する
	//1.SRV用の DescriptorHeapの作成
	ID3D12DescriptorHeap* srvDescriptorHeap = nullptr;

	D3D12_DESCRIPTOR_HEAP_DESC srvDescriptorHeapDesc = {};
	srvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//SRV
	srvDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//PixelShaderから見える
	srvDescriptorHeapDesc.NumDescriptors = 1;

	hr = device->CreateDescriptorHeap(&srvDescriptorHeapDesc, IID_PPV_ARGS(&srvDescriptorHeap));
	assert(SUCCEEDED(hr));

	//CPU側から見たHANDLE、GPU側からみたHANDLEを取得しておく
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandleCPU = srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE srvHandleGPU = srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();

	//2.SRV(Shader Resource View)の作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;//RenderTargetResourceと同じにする
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//RGBA値をそのままShaderに対応させる
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;//MipLevelは1しかない

	device->CreateShaderResourceView(
		renderTextureResource,//Viewと関連付けたいリソース 
		&srvDesc, //SRVの詳細情報(Desc:Description、構成内容の記述)
		srvHandleCPU//SRV用デスクリプタヒープのCPUHandle
	);



	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		//TranslationBarrierをSRV=>RTVに設定する
		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;//TranslationBarrierの設定
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;//フラグはNoneにして奥
		barrier.Transition.pResource = renderTextureResource;//バリアを張る対象のリソース
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;//遷移前
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//遷移後
		commandList->ResourceBarrier(1, &barrier);//バリアを張る

		//描画先のRTVとDSVを設定する
		commandList->OMSetRenderTargets(1, &rtvHandleCPU, false, &dsvHandleCPU);

		//ViewPortの設定
		D3D12_VIEWPORT viewPort{};
		viewPort.Width = WinApp::kWindowWidth;
		viewPort.Height = WinApp::kWindowHeight;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.MinDepth = 0.0f;//深度の最小値
		viewPort.MaxDepth = 1.0f;//深度の最大値

		commandList->RSSetViewports(1, &viewPort);

		//Scissorの設定
		D3D12_RECT scissorRect{};
		//基本的にビューポートと同じ短径が描画されるようにする
		scissorRect.left = 0;
		scissorRect.right = WinApp::kWindowWidth;
		scissorRect.top = 0;
		scissorRect.bottom = WinApp::kWindowHeight;

		commandList->RSSetScissorRects(1, &scissorRect);

		//全画面クリア
		commandList->ClearRenderTargetView(rtvHandleCPU, kRenderTargetClearColor, 0, nullptr);
		//指定した深度で画面全体をクリアする
		commandList->ClearDepthStencilView(dsvHandleCPU, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		//描画



		//TranslationBarrierを基に戻し、PixelShaderが扱えるようにする
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                       // TranslationBarrierの設定
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                            // フラグはNoneにして奥
		barrier.Transition.pResource = renderTextureResource;                        // バリアを張る対象のリソース
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;// 遷移前
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;// 遷移後
		commandList->ResourceBarrier(1, &barrier);//バリアを張る


		// 描画開始
		dxCommon->PreDraw();
		// 描画処理はここから

		//コマンドを積む
		commandList->SetGraphicsRootSignature(rs.Get());
		commandList->SetPipelineState(pipelineState.Get());
		commandList->IASetVertexBuffers(0, 1, vb.GetView());
		commandList->IASetIndexBuffer(ib.GetView());
		//トポロジの設定
		commandList->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//使用するデスクリプタヒープの設定
		commandList->SetDescriptorHeaps(srvDescriptorHeap->GetDesc().NumDescriptors, &srvDescriptorHeap);

		//SRVのDescriptorDableの先頭を設定
		commandList->SetGraphicsRootDescriptorTable(0, srvHandleGPU);

		//頂点数、インデックス数、インデックスの開始位置、インデックスのオフセット
		//commandList->DrawInstanced(3, 1, 0, 0);
		commandList->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);

		// 描画終了
		dxCommon->PostDraw();
	}

	//解放
	renderTextureResource->Release();
	srvDescriptorHeap->Release();
	rtvDescriptorHeap->Release();

	depthStencilResource->Release();
	dsvDescriptorHeap->Release();

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

//インプットレイアウト、ブレンドステート、ラスタライザステート
//引数として、空のpipelineState、RootSignature、頂点シェーダーvs、ピクセルシェーダーpsを参照で受け取る
void SetupPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps) {
	//InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;


	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//BlendState
	D3D12_BLEND_DESC blendDesc{};
	//全ての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//RasterizerStateの設定を行う
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	//裏面(反時計回り)をカリングする
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	//塗りつぶしモードをソリッドにする(ワイヤーフレームなら　D3D12_FILL_MODE_WIREFRAME)
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	//PSO(PiplineStateObject)の生成
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	graphicsPipelineStateDesc.pRootSignature = rs.Get();                                                    // RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;                                                // InputLayout
	graphicsPipelineStateDesc.VS = {vs.GetDxcBlob()->GetBufferPointer(), vs.GetDxcBlob()->GetBufferSize()}; // VertexShader
	graphicsPipelineStateDesc.PS = {ps.GetDxcBlob()->GetBufferPointer(), ps.GetDxcBlob()->GetBufferSize()}; // PixelShader
	graphicsPipelineStateDesc.BlendState = blendDesc;                                                       // BlendDesc
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;                                             // Rasterizer
	//書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1; // １つのRTVに書き込む
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//利用するトポロジ(形状)のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//どのように画面に色を打ち込むかの設定
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	//PSOを生成する
	pipelineState.Create(graphicsPipelineStateDesc);
}

ID3D12Resource* CreateRenderTextureResource(ID3D12Device* device, uint32_t width, uint32_t height, DXGI_FORMAT clearFormat, const FLOAT* clearColor) {
	//1.生成するRenderTextureのDesc生成
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(width);//RenderTextureの幅
	resourceDesc.Height = UINT(height);//Textureの高さ
	resourceDesc.MipLevels = 1;//mipmapの数
	resourceDesc.DepthOrArraySize = 1;//奥行or配列Textureの配列数
	resourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;//TextureのFormat
	resourceDesc.SampleDesc.Count = 1;//サンプリングカウント
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;//Textureの次元数。普段使っているのは2次元
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;//RenderTargetとして使う通知

	//2.利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;//VRAM上に作

	//3.ClearValueの用意
	D3D12_CLEAR_VALUE clearValue{};
	clearValue.Format = clearFormat;
	clearValue.Color[0] = clearColor[0];
	clearValue.Color[1] = clearColor[1];
	clearValue.Color[2] = clearColor[2];
	clearValue.Color[3] = clearColor[3];

	//4.RenderTextureResourceの生成
	ID3D12Resource* resource = nullptr;
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties, 
		D3D12_HEAP_FLAG_NONE, 
		&resourceDesc, 
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 
		&clearValue, 
		IID_PPV_ARGS(&resource)
	);
	assert(SUCCEEDED(hr));

	return resource;
}

ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height) { 
	//1.生成するDepthStencilTextureのDesc設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = width;
	resourceDesc.Height = height;
	resourceDesc.MipLevels = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.Format = DXGI_FORMAT_D32_FLOAT;

	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	//2.利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	//深度値のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	//3.Resourceの生成
	ID3D12Resource* resource = nullptr;
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties, 
		D3D12_HEAP_FLAG_NONE, 
		&resourceDesc, 
		D3D12_RESOURCE_STATE_DEPTH_WRITE, 
		&depthClearValue, 
		IID_PPV_ARGS(&resource)
	);
	assert(SUCCEEDED(hr));

	return resource;
}
