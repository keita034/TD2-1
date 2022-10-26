#include "Sprite3D.h"


void Sprite3D::Initialize()
{
	SpriteInitialize();

	CreatVertexIndexBuffer();
}

void Sprite3D::Draw(TextureData& textureData, Transform& transform, Camera* camera, BillboardFlag flag, Material* material)
{
	EngineMathF::Matrix4 mTrans, mRot, mScale;

	//���s�ړ��s��
	mTrans.MakeTranslation(transform.translation);
	//��]�s��
	mRot.MakeRotation(transform.rotation);
	//�X�P�[���s��
	mScale.MakeScaling(transform.scale);

	switch (flag)
	{
	case NonBillboard:
		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	case AllBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[1][0] = 0;
		mat.m[1][1] = 1;
		mat.m[1][2] = 0;
		mat.m[1][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case YBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[0][0] = 1;
		mat.m[0][1] = 0;
		mat.m[0][2] = 0;
		mat.m[0][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;


		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XYBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[2][0] = 0;
		mat.m[2][1] = 0;
		mat.m[2][2] = 1;
		mat.m[2][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	default:
		assert(0);
		break;
	}

	Draw(textureData, transform, material);
}

void Sprite3D::AnimationDraw(TextureData& textureData, Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Material* material)
{
	size_t animeFrame = static_cast<size_t>(frame / frameDiv);

	size_t width = static_cast<size_t>(radiusX) * 2;
	size_t height = static_cast<size_t>(radiusY) * 2;

	float widthU = static_cast<float>(width) / static_cast<float>(textureData.width);

	//�摜�̔����̃T�C�Y
	float halfW = static_cast<float>(width) / 10;
	float halfH = static_cast<float>(height) / 10;

	if (textureData.width / width < animeFrame + 1)
	{
		frame = 0;
	}

	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, halfH, 0.0f},{widthU * static_cast<float>((animeFrame)),0.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-halfW, -halfH, 0.0f},{widthU * static_cast<float>((animeFrame)),1.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{halfW, halfH, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{halfW, -halfH, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
	};

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1, 0, 3, // �O�p�`1��
		2, 3, 0, // �O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   // �C���f�b�N�X���R�s�[
	}

	SpriteDraw(textureData, transform, material);
}

//�`��
void Sprite3D::Draw(TextureData& textureData, Transform& transform, Material* material)
{

	//�摜�̔����̃T�C�Y
	float halfW = static_cast<float>(textureData.width) * 0.0625f;
	float halfH = static_cast<float>(textureData.height) * 0.0625f;

	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, halfH, 0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-halfW, -halfH, 0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{halfW, halfH, 0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{halfW, -halfH, 0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
	};

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1, 0, 3, // �O�p�`1��
		2, 3, 0, // �O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   // �C���f�b�N�X���R�s�[
	}

	SpriteDraw(textureData, transform, material);
}

