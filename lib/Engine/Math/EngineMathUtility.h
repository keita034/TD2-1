#pragma once
#include"EngineMathF.h"
#include"EngineMath.h"

namespace EngineMathUtility
{
	/// <summary>
	/// �f�B���N�g������t�@�C�����ꗗ������
	/// </summary>
	/// <param name="folderPath">�f�B���N�g���p�X</param>
	/// <returns>�t�@�C�����ꗗ</returns>
	std::vector<std::string> getFileNames(std::string folderPath);

#pragma region ��Βl�̌v�Z

	//��Βl�̌v�Z
	int Abs(int abs);

	//��Βl�̌v�Z
	long AbsL(long abs);

	//��Βl�̌v�Z
	long long AbsLL(long long abs);

#pragma endregion ��Βl�̌v�Z

#pragma region ��r�֐�

	/// <summary>
	/// �l���傫������Ԃ�
	/// </summary>
	template<typename T>
	T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	/// <summary>
	/// �l���傫���z��Ԃ�(vector)
	/// </summary>
	template<typename T>
	T Max(std::vector<T> values)
	{
		int num = values.size() - 1;

		if (num == 0)
		{
			return static_cast<T>(0);
		}

		float num2 = values[0];

		for (int i = 1; i < num; i++)
		{
			if (values[i] > num2)
			{
				num2 = values[i];
			}
		}

		return num2;
	}

	/// <summary>
	/// �l������������Ԃ�
	/// </summary>
	template<typename T>
	T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	/// <summary>
	/// �l���������z��Ԃ�(vector)
	/// </summary>
	template<typename T>
	T Min(std::vector<T> values)
	{
		int num = values.size() - 1;

		if (num == 0)
		{
			return static_cast<T>(0);
		}

		float num2 = values[0];

		for (int i = 1; i < num; i++)
		{
			if (values[i] < num2)
			{
				num2 = values[i];
			}
		}

		return num2;
	}

#pragma endregion ��r�֐�
};

//���W�ϊ��s��
struct ConstBufferDataTransform
{
	EngineMathF::Matrix4 mat;//3D�ϊ��s��
};


struct PosColor
{
	EngineMathF::Vector3 pos;//���W
	EngineMathF::Vector4 color;//�J���[
};

struct PosNormalUv
{
	EngineMathF::Vector3 pos;//���W
	EngineMathF::Vector3 normal;//�@���x�N�g��
	EngineMathF::Vector2 uv;//uv���W
};

//���W�EUV�E�J���[
struct PosUvColor
{
	EngineMathF::Vector3 pos;//���W
	EngineMathF::Vector2 uv;//uv���W
	EngineMathF::Vector4 color;//�J���[
};

typedef struct
{
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//�f�X�N�v���^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	//�X�v���C�g��
	UINT nextIndex;
}ModelShareVaria;

//�p�C�v���C���E���[�g�V�O�l�`���Z�b�g
struct PipelineSet
{
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};

struct worldViewpojCamera
{
	//���[���h�s��
	EngineMathF::Matrix4 world;
	//���[���h���W
	EngineMathF::Matrix4 matWorld;
	//�J�������W(���[���h���W)
	EngineMathF::Vector3 cameraPos;
};

//�}�e���A��
struct ModelMaterial
{
	//�}�e���A����
	std::string name;
	//�A���r�G���g�e���x
	EngineMathF::Vector3 ambient = { 0.06f, 0.06f, 0.06f };
	//�f�B�t���[�Y�e���x
	EngineMathF::Vector3 diffuse = { 0.0f,0.0f,0.0f };
	//�X�y�L�����[�e���x
	EngineMathF::Vector3 specular = { 0.0f,0.0f,0.0f };
	//�A���t�@
	float alpha = 1.0f;
	//�e�N�X�`���t�@�C����
	std::string textureFiename;
};

//�}�e���A���悤�萔�o�b�t�@�\����
struct ConstBuffDataMaterial
{
	//�A���r�G���g�W��
	EngineMathF::Vector3 ambient;
	//�p�f�B���O
	float pad1;
	//�f�B�t���[�Y�W��
	EngineMathF::Vector3 diffuse;
	//�p�f�B���O
	float pad2;
	//�X�y�L�����[�W��
	EngineMathF::Vector3 specular;
	//�A���t�@
	float alpha;
};

//�o�b�t�@�֘A
struct Buff
{
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//���_�}�b�v
	PosColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
};

//�u�����h���[�h
enum class BlendMode
{
	AX_BLENDMODE_NOBLEND,//�m�[�u�����h�i�f�t�H���g�j
	AX_BLENDMODE_ALPHA,//���u�����h
	AX_BLENDMODE_ADD,//���Z�u�����h
	AX_BLENDMODE_SUB,//���Z�u�����h
	AX_BLENDMODE_MULA,//��Z�u�����h
	AX_BLENDMODE_INVSRC,//���]�u�����h

	AX_BLENDMODE_MAX//�u�����h��ސ�
};

struct TextureData
{
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> srvHeap;

	//GPU�f�X�N�v���^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	//�f�X�N�v���^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	char PADDING[4]{};
	//����
	size_t width = 0;
	//�c��
	size_t height = 0;
	
	//�J���[
	EngineMathF::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
};