#pragma once
#include"ErrorException.h"
#include"EngineMathUtility.h"

class TextureManager
{
private:

	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> srvHeap;
	//�f�X�N�v���^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	char PADDING[4];

	Microsoft::WRL::ComPtr<ID3D12Device> device;

	static TextureManager* textureManager;

	//�e�N�X�`����
	UINT nextTexture;

	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};


public:

	/// <summary>
	/// �e�N�X�`�������[�h���܂�
	/// </summary>
	/// <param name="filepath">�e�N�X�`���̃t�@�C���p�X</param>
	/// <returns>�e�N�X�`���n���h��</returns>
	TextureData LoadTexture(const wchar_t* filepath);

	/// <summary>
	/// �e�N�X�`�������[�h���܂�(�|�C���^)
	/// </summary>
	/// <param name="filepath">�e�N�X�`���̃t�@�C���p�X</param>
	/// <returns>�e�N�X�`���n���h��</returns>
	void LoadTexturePtr(const wchar_t* filepath, TextureData* tex);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �C���X�^���X������
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static TextureManager* GetInstance();

	/// <summary>
	/// �C���X�^���X�����
	/// </summary>
	void Destroy();

private:

	TextureManager() = default;
	~TextureManager() = default;


	Microsoft::WRL::ComPtr<ID3D12Resource>CreateTexBuff(DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg);

	D3D12_GPU_DESCRIPTOR_HANDLE CreateShaderResourceView(ID3D12Resource* texBuff, DirectX::TexMetadata& metadata);
};

