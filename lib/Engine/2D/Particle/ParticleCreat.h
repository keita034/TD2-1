#pragma once
#include"Particle.h"
#include"EngineMathUtility.h"
#include"DirectX12Core.h"

class ParticleCreat
{
private:

	static ModelShareVaria modelShareVaria;

public:
	static Particle* CreateParticle(const wchar_t* filePath);

private:
	//�p�C�v���C���̐���
	static void CreatPipeline();
	//�f�X�N�v���^�q�[�v�̐���
	static void CreateDescriptorHeap();
	//�f�X�N�v���^�����W�̐���
	static void CreateDescriptorRange();
};

