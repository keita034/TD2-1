#pragma once
#include"Material.h"
#include"TextureManager.h"

//�f�t�H���g�̃e�N�X�`��(���F)�����ς��Ȃ�����
extern TextureData DEFAULT_TEXTURE;

//�f�t�H���g�̃}�e���A�������ς��Ȃ�����
extern Material DEFAULT_TEXTURE_MATERIAL;

//�f�t�H���g�̃����o�[�g�}�e���A�������ς��Ȃ�����
extern Material DEFAULT_LAMBERT_MATERIAL;

//�f�t�H���g�̃t�H���O�}�e���A�������ς��Ȃ�����
extern Material DEFAULT_PHONG_MATERIAL;

//�f�t�H���g�̃X�v���C�g2D�}�e���A�������ς��Ȃ�����
extern Material DEFAULT_SPRITE2D_MATERIAL;

//�f�t�H���g�̃X�v���C�g3D�}�e���A�������ς��Ȃ�����
extern Material DEFAULT_SPRITE3D_MATERIAL;

void DefaultMaterialInitialize();
