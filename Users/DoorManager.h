#pragma once
#include "door.h"
#include"Sprite2D.h"

class DoorManager
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(EngineMathF::Vector3 vector);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(int frequencyInvocationDoor);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

	/// <summary>
/// �X�v���C�g�p�`��
/// </summary>
	void SpriteDraw();

	void  Reset();

	bool GetMashFlag(int frequencyInvocationDoor);

private:
	std::unique_ptr<door> door_[4]={};
	
	EngineMathF::Vector3 vector_;

	EngineMathF::Vector3 moveVector_;

	TextureData textureHandle_;
	Transform transform_;
	std::unique_ptr<Sprite2D> sprite_;
};

