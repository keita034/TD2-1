#include "ModelCone.h"
#include"TextureManager.h"

ModelCone::ModelCone()
{
}

ModelCone::~ModelCone()
{
}

void ModelCone::Create(bool smoothing)
{
	static_cast<void>(smoothing);

	//���_�o�b�t�@�E�C���f�b�N�X����
	CreatVertexIndexBuffer();

	//�萔�o�b�t�@����(�}�e���A��)
	DirectX12Core::GetInstance()->CreateConstBuff(constMapMaterial, constBuffMaterial);
	constMapMaterial->ambient = modelMaterial.ambient;
	constMapMaterial->diffuse = modelMaterial.diffuse;
	constMapMaterial->specular = modelMaterial.specular;
	constMapMaterial->alpha = modelMaterial.alpha;

	// ���_�f�[�^
	constexpr UINT NumDiv = 32; // ������
	float RadianPerDivision = EngineMathF::AX_2PI / float(NumDiv); // ����1�P�ʂ̊p�x

	//�����_���������1�������Ă�����1�����悤�ɂ���
	std::array<float, NumDiv + 1> pointsZ{};
	std::array<float, NumDiv + 1> pointsX{};
	std::array<float, NumDiv + 1> pointsU{};
	std::array<float, NumDiv + 1> pointsV{};

	//�㑤�̌v�Z
	//���_���W�̌v�Z
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseZ = cos(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		float baseX = sin(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		pointsZ[i] = baseZ * -1.0f;
		pointsX[i] = baseX;
	}

	//UV���W�̌v�Z
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.25f;
		pointsV[i] = baseV + 0.5f;
	}

	//�Ō�ƍŏ��͈ꏏ
	(*pointsZ.rbegin()) = (*pointsZ.begin());
	(*pointsX.rbegin()) = (*pointsX.begin());
	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	PosNormalUv tmp{};
	//�v�Z�����l����
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1.0f); i++)
	{
		tmp = {{ pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i]}};
		vertices.push_back(tmp);
	}

	tmp = {{ 0.0f,1.0f,0.0f },{},{ 0.25f,0.5f } };
	vertices.push_back(tmp);

	//�����̌v�Z
	//UV���W�̌v�Z
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.75f;
		pointsV[i] = baseV + 0.5f;
	}

	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	//�v�Z�����l����
	for (size_t i = 1; i < static_cast<size_t>(NumDiv + 1.0f); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i]} };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,-1.0f,0.0f },{},{ 0.75f,0.5 } };
	vertices.push_back(tmp);

	// �C���f�b�N�X�f�[�^
	uint8_t count = 0;
	uint16_t indexData = 0;

	//�C���f�b�N�X�f�[�^�̌v�Z�㑤
	for (uint16_t i = 0; i < 96; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(33);
			break;
		case 2:
			indexData++;
			indices.push_back(indexData);
			break;
		}

		count++;
	}

	count = 0;
	indexData = 35;
	//�C���f�b�N�X�f�[�^�̌v��
	for (size_t i = 96; i < maxIndex; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(65);
			break;
		case 2:
			indices.push_back(indexData - static_cast<unsigned>(1));
			indexData++;
			break;
		}

		count++;
	}

	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short Index0 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i * 3 + 0)];
		unsigned short Index1 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i * 3 + 1)];
		unsigned short Index2 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i * 3 + 2)];
		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		EngineMathF::Vector3 p0 = vertices[Index0].pos;
		EngineMathF::Vector3 p1 = vertices[Index1].pos;
		EngineMathF::Vector3 p2 = vertices[Index2].pos;
		//p0->p1�x�N�g���Ap0->p2�x�N�g�����v�Z(�x�N�g���̌��Z)
		EngineMathF::Vector3 v1 = p1 - p0;
		EngineMathF::Vector3 v2 = p2 - p0;
		//�O�ς͗������琂���ȃx�N�g��
		EngineMathF::Vector3 normal = v1.cross(v2);
		//���K������
		normal.normal();
		vertices[Index0].normal = normal;
		vertices[Index1].normal = normal;
		vertices[Index2].normal = normal;
	}

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	for (size_t i = 0; i < indices.size(); i++)
	{
		indexMap[i] = indices[i];   // �C���f�b�N�X���R�s�[
	}

	//���[���h���W
	matWorld = EngineMathF::MakeIdentity();
}

void ModelCone::Draw(Transform* transform, Material* material)
{
	ModelDraw(transform,material);
}

void ModelCone::Create(const char* filePath, bool smoothing)
{
	static_cast<void>(filePath);
	static_cast<void>(smoothing);
}

void ModelCone::Initialize()
{
	ModelInitialize();

	maxIndex = coneMaxIndex;
	maxVert = coneMaxVert;

	Create();
}
