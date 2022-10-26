#pragma once
#include"ErrorException.h"
#include"EngineMathUtility.h"
#include"Camera.h"

struct VerPosColScaRot
{
	EngineMathF::Vector3 pos;//���W
	EngineMathF::Vector4 color;//�J���[
	float scale;//�X�P�[��
	float rotation;//��]�p
};

struct ParticleConstBuffData
{
	EngineMathF::Matrix4 mat;
	EngineMathF::Matrix4 matBillboard;
};

//�p�[�e�B�N���f�[�^
struct ParticleData
{
	//���W
	EngineMathF::Vector3 position = {};
	//���x
	EngineMathF::Vector3 velocity = {};
	//�����x
	EngineMathF::Vector3 accel = {};

	//���݃t���[��
	UINT frame = 0;
	//�I���t���[��
	UINT numFrame = 0;

	//�X�P�[��
	float scale = 1.0f;
	//�����l
	float sScale = 1.0f;
	//�ŏI�l
	float eScale = 0.0f;

	//��]�p
	float rotation = 0.0f;
	//�����l
	float sRotation = 0.0f;
	//�ŏI�l
	float eRotation = 0.0f;

	//�J���[
	EngineMathF::Vector4 color = {1.0f,1.0f,1.0f,1.0f};
	//�����l
	EngineMathF::Vector4 sColor = { 1.0f,1.0f,1.0f,1.0f };
	//�ŏI�l
	EngineMathF::Vector4 eColor = { 1.0f,1.0f,1.0f,1.0f };
};

class Particle
{
protected:
	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> cmdList = nullptr;
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr <ID3D12RootSignature> rootSignature;
	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> srvHeap;
	//�f�X�N�v���^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	//�X�v���C�g��
	UINT nextIndex;
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//���_�}�b�v
	VerPosColScaRot* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr <ID3D12Resource> texBuff = nullptr;
	//GPU�f�X�N�v���^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	//CPU�f�X�N�v���^�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	ParticleConstBuffData* constMapTransform = nullptr;
	//�v���W�F�N�V�����s��
	EngineMathF::Matrix4 matProjection;
	//���_��
	const uint32_t vertexCount = 1024;
	char PADING[4];
	//�p�[�e�B�N���z��
	std::forward_list<ParticleData>particleDatas;
public:

	Particle()= default;

	virtual ~Particle() = default;

	//������
	virtual void Initialize(ModelShareVaria& modelShareVaria) = 0;


	///<summary>
	///�ǂݍ���
	///</summary>
	///<param name="filePath">�t�@�C���p�X</param>
	virtual void Load(const wchar_t* filePath) = 0;

	///<summary>
	///�X�V
	///</summary>
	virtual void Update() = 0;

	///<summary>
	///�`��
	///</summary>
	virtual void Draw(Camera* camera) = 0;

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name="life">��������</param>
	/// <param name="position">�������W</param>
	/// <param name="velocity">���x</param>
	/// <param name="accel">�����x</param>
	/// <param name="scale">{�J�n���X�P�[��,�I�����X�P�[��}</param>
	/// <param name="rotation">{�J�n����]�p,�I������]�p}</param>
	/// <param name="sColor">�J�n�J���[</param>
	/// <param name="eColor">�I���J���[</param>
	virtual void Add(
		UINT life, EngineMathF::Vector3& position, EngineMathF::Vector3& velocity,
		EngineMathF::Vector3& accel,EngineMathF::Vector2& scale, EngineMathF::Vector2& rotation
		,EngineMathF::Vector4& sColor, EngineMathF::Vector4& eColor) = 0;

protected:
	//�V�F�[�_�|���\�[�X�r���[����
	virtual void CreateShaderResourceView() = 0;
	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	virtual void CreatConstBuff() = 0;
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer() = 0;
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer() = 0;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Particle& operator=(const Particle&) = delete;
	Particle(const Particle&) = delete;
};