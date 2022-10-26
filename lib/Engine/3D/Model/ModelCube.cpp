#include "ModelCube.h"
#include"DirectX12Core.h"
#include"TextureManager.h"

ModelCube::ModelCube()
{
}

ModelCube::~ModelCube()
{
}

void ModelCube::Create(bool smoothing)
{
	static_cast<void>(smoothing);
	//���_�o�b�t�@�E�C���f�b�N�X����
	CreatVertexIndexBuffer();

	//�萔�o�b�t�@����(�}�e���A��)
	DirectX12Core::GetInstance()->CreateConstBuff(constMapMaterial, constBuffMaterial);
	EngineMathF::Vector3 one = { 0.8f,0.8f,0.8f };
	constMapMaterial->ambient = one;
	constMapMaterial->diffuse = one;
	constMapMaterial->specular = one;
	constMapMaterial->alpha = modelMaterial.alpha;

	// ���_�f�[�^
	//����
	PosNormalUv tmp = { { -1.0f, -1.0f, -1.0f }, {}, { 0.0f, 1.0f } };//����C���f�b�N�X0
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f} };//�����C���f�b�N�X1
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f} };//�E��C���f�b�N�X2
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f} };//�E���C���f�b�N�X3
	vertices.push_back(tmp);

	//�E
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 0.0f, 1.0f} };//����C���f�b�N�X4
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f} };//�����C���f�b�N�X5
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f} };//�E��C���f�b�N�X6
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f} };//�E���C���f�b�N�X7
	vertices.push_back(tmp);

	//��
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f} };//����C���f�b�N�X8
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f} };//�����C���f�b�N�X9
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f} };//�E��C���f�b�N�X10
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f} };//�E���C���f�b�N�X11
	vertices.push_back(tmp);
	
	//��
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f} };//����C���f�b�N�X12
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f} };//�����C���f�b�N�X13
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f} };//�E��C���f�b�N�X14
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f} };//�E���C���f�b�N�X15
	vertices.push_back(tmp);

	//��
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 1.0f} };//����C���f�b�N�X16
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f} };//�����C���f�b�N�X17
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 1.0f} };//�E��C���f�b�N�X18
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f} };//�E���C���f�b�N�X19
	vertices.push_back(tmp);

	//��
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f} };//����C���f�b�N�X20
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 0.0f, 0.0f} };//�����C���f�b�N�X21
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f} };//�E��C���f�b�N�X22
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 0.0f} };//�E���C���f�b�N�X23
	vertices.push_back(tmp);

// �C���f�b�N�X�f�[�^

	//����
	indices.push_back(0), indices.push_back(1), indices.push_back(3);//0
	indices.push_back(3), indices.push_back(2), indices.push_back(0);//1

	//�E
	indices.push_back(4), indices.push_back(5), indices.push_back(7);//2
	indices.push_back(7), indices.push_back(6), indices.push_back(4);//3

	//��
	indices.push_back(8), indices.push_back(9), indices.push_back(11);//4
	indices.push_back(11), indices.push_back(10), indices.push_back(8);//5

	//��
	indices.push_back(12), indices.push_back(13), indices.push_back(15);//6
	indices.push_back(15), indices.push_back(14), indices.push_back(12);//7

	//��
	indices.push_back(16), indices.push_back(17), indices.push_back(19);//8
	indices.push_back(19), indices.push_back(18), indices.push_back(16);//9

	//��
	indices.push_back(20), indices.push_back(21), indices.push_back(23);//10
	indices.push_back(23), indices.push_back(22), indices.push_back(20);//11

	for (size_t i = 0; i < cubeMaxIndex / 3; i++)
	{
		//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short Index0 = indices[i * 3 + 0];
		unsigned short Index1 = indices[i * 3 + 1];
		unsigned short Index2 = indices[i * 3 + 2];
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

	matWorld = EngineMathF::MakeIdentity();
}

void ModelCube::Draw(Transform* transform, Material* material)
{
	ModelDraw(transform,material);
}

void ModelCube::Create(const char* filePath, bool smoothing)
{
	static_cast<void>(filePath);
	static_cast<void>(smoothing);
}

void ModelCube::Initialize()
{
	ModelInitialize();

	maxIndex = cubeMaxIndex;
	maxVert = cubeMaxVert;

	Create();

}
