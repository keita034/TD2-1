#pragma once
#include"ErrorException.h"


class DirectX12Core
{
private:

	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;


	//�o�b�N�o�b�t�@
	std::vector< Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	//�o���A�[�f�X�N
	D3D12_RESOURCE_BARRIER barrierDesc{};

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	//�t�F���X�̐���
	UINT64 fenceVal = 0;

	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

	//�N���A�[�J���[
	FLOAT clearColor[4] = { 0.1f, 0.25f, 0.5f, 0.0f };

	//�r���[�|�[�g
	D3D12_VIEWPORT viewport{};

	//�V�U�[��`
	D3D12_RECT scissorRect{};

	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;

	//�[�x�r���[�p�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	static DirectX12Core* DirectX12Core_;

public:

	//�V���O���g���C���X�^���X�̎擾
	static DirectX12Core* GetInstance();

	//������
	void DirectXInitialize();

	//�`�揀��
	void BeginDraw();

	//�`���n��
	void EndDraw();

	//�R�}���h��n��
	void ExecuteCommand();

	void Destroy();
	//�Z�b�^�[

	//�w�i�̐F�ς�(RGBA)
	void SetBackScreenColor(float red, float green, float blue, float alpha);

	//�Q�b�^�[
	Microsoft::WRL::ComPtr<ID3D12Device> GetDevice();
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetRtvHeap();
	Microsoft::WRL::ComPtr<IDXGISwapChain4> GetSwapChain();
	D3D12_CPU_DESCRIPTOR_HANDLE GetRtvHandle();
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCmdAllocator();
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetCommandQueue();
	D3D12_DESCRIPTOR_HEAP_DESC GetRtvHeapDesc();
	Microsoft::WRL::ComPtr<IDXGIFactory7> GetDxgiFactory();
	Microsoft::WRL::ComPtr<ID3D12Fence> GetFence();
	UINT64 GetFenceVal();

#pragma region �e���v���[�g�֐�

	//�萔�o�b�t�@�쐬
	template<typename T>
	void CreateConstBuff(T*& buff, Microsoft::WRL::ComPtr<ID3D12Resource>& constBuff)
	{

		// ���_�o�b�t�@�̐ݒ�
		D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
		// ���\�[�X�ݒ�
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Width = (sizeof(T) + 0xff) & ~0xff; // ���_�f�[�^�S�̂̃T�C�Y
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		//�萔�o�b�t�@�̐���
		result = device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(constBuff.ReleaseAndGetAddressOf()));
		assert(SUCCEEDED(result));

		//�萔�o�b�t�@�̃}�b�s���O
		result = constBuff->Map(0, nullptr, (void**)&buff);//�}�b�s���O
		assert(SUCCEEDED(result));

	}

#pragma endregion

private:

	//DXGI�܂�菉����
	HRESULT InitializeDXGIDevice();

	//�ŏI�I�ȃ����_�[�^�[�Q�b�g�̐���
	HRESULT CreatFinalRenderTarget();

	//�X���b�v�`�F�C���̐���
	HRESULT CreateSwapChain();

	//�R�}���h�܂�菉����
	HRESULT InitializeCommand();

	//�t�F���X����
	HRESULT CreateFence();

	//�[�x�֌W����
	HRESULT CreatDepthBuffer();

	//�f�o�b�O���C���[��L���ɂ���
	void EnableDebugLayer();

	//�R���X�g���N�^�E�f�X�g���N�^
	DirectX12Core() = default;
	~DirectX12Core() = default;
};