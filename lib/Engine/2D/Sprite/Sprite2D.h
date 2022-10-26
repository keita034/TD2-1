#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"EngineMathUtility.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"
#include"Sprite.h"
#include"DefaultMaterial.h"
//pragma comment



//using namespace

class Sprite2D : public Sprite
{
private:


public:

	Sprite2D() = default;
	~Sprite2D() = default;

	//������
	virtual void Initialize()override;

	///<summary>
	///�`��
	///</summary>
	virtual void Draw(TextureData& textureData, Transform& transform, Material* material = &DEFAULT_SPRITE2D_MATERIAL)override;

	virtual void AnimationDraw(TextureData& textureData, Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Material* material = &DEFAULT_SPRITE2D_MATERIAL);

private:


	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite2D& operator=(const Sprite2D&) = delete;
	Sprite2D(const Sprite2D&) = delete;

};