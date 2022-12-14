#include "TextureManager.h"
#include"DirectX12Core.h"

TextureManager* TextureManager::textureManager = nullptr;

TextureData TextureManager::LoadTexture(const wchar_t* filepath)
{
	if (nextTexture > 2024)
	{
		assert(0);
	}

	TextureData tmp{};

	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	tmp.srvHeap = srvHeap;
	tmp.descriptorRange = descriptorRange;

	// WICテクスチャのロード
	HRESULT result = LoadFromWICFile(
		filepath,
		DirectX::WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	//ミップマップ生成
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャをSRGBとして扱う
	metadata.format = DirectX::MakeSRGB(metadata.format);

	tmp.texBuff = CreateTexBuff(metadata, scratchImg);

	tmp.gpuHandle = CreateShaderResourceView(tmp.texBuff.Get(), metadata);

	tmp.width = metadata.width;
	tmp.height = metadata.height;

	nextTexture++;
	return tmp;
}

void TextureManager::LoadTexturePtr(const wchar_t* filepath, TextureData* tex)
{
	if (nextTexture > 2024)
	{
		assert(0);
	}

	TextureData tmp{};

	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	tmp.srvHeap = srvHeap;
	tmp.descriptorRange = descriptorRange;

	// WICテクスチャのロード
	HRESULT result = LoadFromWICFile(
		filepath,
		DirectX::WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	//ミップマップ生成
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャをSRGBとして扱う
	metadata.format = DirectX::MakeSRGB(metadata.format);

	tmp.texBuff = CreateTexBuff(metadata, scratchImg);

	tmp.gpuHandle = CreateShaderResourceView(tmp.texBuff.Get(), metadata);

	tmp.width = metadata.width;
	tmp.height = metadata.height;

	nextTexture++;

	tex = &tmp;
}

void TextureManager::Initialize()
{
	HRESULT result;
	device = DirectX12Core::GetInstance()->GetDevice();
	//SRVの最大個数
	const size_t kMaxSRVCount = 2042;

	descriptorRange.NumDescriptors = 1;//1度の描画に使うテクスチャが一枚なので
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;//テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	// 設定を元にSRV用デスクリプタヒープを生成
	result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(srvHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	// ヒープ設定
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
}

TextureManager* TextureManager::GetInstance()
{
	if (!textureManager)
	{
		textureManager = new TextureManager();
	}

	return textureManager;
}

void TextureManager::Destroy()
{
	delete textureManager;
}

Microsoft::WRL::ComPtr<ID3D12Resource> TextureManager::CreateTexBuff(DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> tmp;
	// リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;//幅
	textureResourceDesc.Height = (UINT)metadata.height;//高さ
	textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	// テクスチャバッファの生成
	HRESULT result = device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(tmp.ReleaseAndGetAddressOf()));

	//テクスチャバッファにデータ転送
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// ミップマップレベルを指定してイメージを取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		result = tmp->WriteToSubresource(
			(UINT)i,
			nullptr,              // 全領域へコピー
			img->pixels,          // 元データアドレス
			(UINT)img->rowPitch,  // 1ラインサイズ
			(UINT)img->slicePitch // 1枚サイズ
		);
		assert(SUCCEEDED(result));
	}

	return tmp;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::CreateShaderResourceView(ID3D12Resource* texBuff, DirectX::TexMetadata& metadata)
{
	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//ハンドルのポインタずらし
	cpuHandle.ptr += static_cast<UINT64>(nextTexture) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64>(nextTexture) * incrementSize;

	// シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = static_cast<UINT>(metadata.mipLevels);

	// ハンドルの指す位置にシェーダーリソースビュー作成
	device->CreateShaderResourceView(texBuff, &srvDesc, cpuHandle);

	return gpuHandle;
}
