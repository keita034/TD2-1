#include "Sprite2D.h"

void Sprite2D::Initialize()
{
	SpriteInitialize();

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWindowWidth());
	float height = static_cast<float>(WindowsApp::GetInstance()->GetWindowHeight());

	EngineMathF::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);

	CreatVertexIndexBuffer();
}

//�`��
void Sprite2D::Draw(TextureData& textureData, Transform& transform, Material* material)
{
		//�摜�̔����̃T�C�Y
	float halfW = static_cast<float>(textureData.width) * 0.5f;
	float halfH = static_cast<float>(textureData.height) * 0.5f;

	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, -halfH, 0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-halfW, halfH, 0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{halfW, -halfH, 0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{halfW, halfH, 0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
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

	EngineMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//���s�ړ��s��
	mTrans.MakeTranslation(transform.translation);
	//��]�s��
	mRot.MakeRotation(transform.rotation);
	//�X�P�[���s��
	mScale.MakeScaling(transform.scale);
	//���[���h�s��
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;

	SpriteDraw(textureData, transform, material);
}

void Sprite2D::AnimationDraw(TextureData& textureData, Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Material* material)
{
	size_t animeFrame = static_cast<size_t>(frame / frameDiv);

	size_t width = static_cast<size_t>(radiusX) * 2;
	size_t height = static_cast<size_t>(radiusY) * 2;

	float widthU = static_cast<float>(width / textureData.width);

	//�摜�̔����̃T�C�Y
	float halfW = static_cast<float>(width);
	float halfH = static_cast<float>(height);

	if (textureData.width/ width <animeFrame+1)
	{
		frame = 0;
	}

	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, -halfH, 0.0f},{widthU * static_cast<float>(animeFrame),0.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-halfW, halfH, 0.0f},{widthU * static_cast<float>(animeFrame),1.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{halfW, -halfH, 0.0f},{widthU * static_cast<float>((animeFrame+1)),0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{halfW, halfH, 0.0f},{widthU * static_cast<float>((animeFrame+1)),1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
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

	EngineMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//���s�ړ��s��
	mTrans.MakeTranslation(transform.translation);
	//��]�s��
	mRot.MakeRotation(transform.rotation);
	//�X�P�[���s��
	mScale.MakeScaling(transform.scale);
	//���[���h�s��
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;

	SpriteDraw(textureData, transform, material);
}
