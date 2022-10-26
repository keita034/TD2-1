#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"EngineMathUtility.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"
#include "Camera.h"
#include"Sprite.h"
#include"DefaultMaterial.h"

//pragma comment



//using namespace


class Sprite3D : public Sprite
{
private:

public:

	Sprite3D() = default;
	~Sprite3D() = default;

	//������
	virtual void Initialize()override;

	///<summary>
	///�`��
	///</summary>
	virtual void Draw(TextureData& textureData, Transform& transform, Material* material = &DEFAULT_SPRITE3D_MATERIAL);
	
	virtual void Draw(TextureData& textureData, Transform& transform,Camera* camera, BillboardFlag flag = NonBillboard, Material* material = &DEFAULT_SPRITE3D_MATERIAL);

	virtual void AnimationDraw(TextureData& textureData, Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Material* material = &DEFAULT_SPRITE3D_MATERIAL);

private:



	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite3D& operator=(const Sprite3D&) = delete;
	Sprite3D(const Sprite3D&) = delete;
};

