#pragma once
#include"ErrorException.h"
#include"EngineMathUtility.h"
#include"Camera.h"
#include"ModelPipeLine.h"
#include"DirectX12Core.h"
#include"Light.h"
#include"Transform.h"
#include"Material.h"

enum class ModelShape
{
	Cube,//������
	Sphere,//��
	Capsule,//�J�v�Z��
	Cylinder,//�~��
	Cone,//�~��
};

enum ShaderType
{
	Default,
	Flat,
	Gouraud,
	Lambert,
	Phong,

};

class Model
{
protected:

	TextureData textureData;

	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;

	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//���_�}�b�v
	PosNormalUv* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	char PADDING1[4];
	//�C���f�b�N�X�̐�
	UINT maxIndex;
	char PADDING2[4];
	//���_�̐�
	UINT maxVert;
	//���[���h�s��
	EngineMathF::Matrix4 matWorld;
	//���_�f�[�^
	std::vector<PosNormalUv>vertices;
	//���_�C���f�b�N�X
	std::vector<uint16_t> indices;
	//���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<uint16_t, std::vector<uint16_t>>smoothData;
	//���C�g
	static Light* light;
	//�}�e���A��
	ModelMaterial modelMaterial{};
	//�萔�o�b�t�@�}�e���A��
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	//�萔�o�b�t�@�}�e���A���̃}�b�s���O�p�|�C���^
	ConstBuffDataMaterial* constMapMaterial = nullptr;


public:

	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	virtual EngineMathF::Matrix4& GetMatWorld();

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	/// <returns>���_���W�z��</returns>
	virtual const std::vector<PosNormalUv>GetVertices();

	/// <summary>
	/// �C���f�b�N�X���擾
	/// </summary>
	/// <returns>�C���f�b�N�X���W�z��</returns>
	virtual const std::vector<uint16_t>GetIndices();

	/// <summary>
	/// ���C�g�̃Z�b�g
	/// </summary>
	/// <param name="light">���C�g</param>
	static void SetLight(Light* light_);

	Model() = default;
	virtual ~Model()= default;

	virtual void Initialize() = 0;

	virtual void Draw(Transform* transform,Material* material) = 0;

protected:

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create(bool smoothing) = 0;

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="filePath">�I�u�W�F�N�g�܂ł̃t�@�C���p�X</param>
	virtual void Create(const char* filePath, bool smoothing) = 0;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	virtual void ModelDraw(Transform* transform, Material* material);

	//������
	virtual void ModelInitialize();


	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Model& operator=(const Model&) = delete;
	Model(const Model&) = delete;
};