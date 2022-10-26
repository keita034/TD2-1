#include"player.h"

void Player::Complement(float& x1, float x2, float flame)//�ړ��⊮
{
	float distanceX = x2 - x1;//�������o��
	float dividedDistanceX = distanceX / flame;//������flame�Ŋ������l

	x1 += dividedDistanceX;//������flame�Ŋ������l�𑫂�
}

Player::Player()
{
}

Player::~Player()
{
}

AABB& Player::GetCollider()
{
	return collider_;
}
void Player::SetTransform(EngineMathF::Vector3 translation)
{
	worldTransform_.translation = translation;
}
void Player::OnCollision()
{
	crashFlag = true;
	crashTime = 70;
	oldRot.y = worldTransform_.rotation.y;
	AudioManager::GetInstance()->PlayWave(confusionHandle);
}

bool Player::GetCrashFlag()
{
	return crashFlag;
}

void Player::Initialize(Transform* worldTransform)
{
	model_ = std::make_unique<objModel>();
	model_->Initialize();
	model_->Create("Resources/tire", true);
	worldTransform_.parent = worldTransform;
	worldTransform_.translation = { 0.0f, -2.0f, 10.0f };
	worldTransform_.Initialize();

	collider_.center = EngineMathF::GetWorldPosition(worldTransform_);

	confusionHandle = AudioManager::GetInstance()->LoadAudio("Resources/musics/confusion.mp3");

	//�����蔻��̑傫��
	collider_.size = {
		0.3f * worldTransform_.scale.x,
		0.5f * worldTransform_.scale.y,
		0.5f * worldTransform_.scale.z };
}

void Player::Update()
{
	if (!crashFlag)
	{
		if (!rollStopFlag)
		{
			worldTransform_.rotation += {0.2f, 0.0f, 0.0f};
		}

		//�ړ�
		Move();
		//����
		Rotate();

		if (Input::GetInstance()->TriggerPush(DIK_SPACE) && jumpFlag == 0 && !squatFlag)
		{
			jumpFlag = 1;
		}
	}
	else
	{
		if (jumpFlag == 1)
		{
			jumpFlag = 2;
		}

		worldTransform_.rotation += {0.0f, 0.4f, 0.0f};

		crashTime--;

		if (crashTime == 0)
		{
			crashFlag = false;
			worldTransform_.rotation.y = oldRotY;
			crashTime = 70;
		}
	}

	//�W�����v
	Jump();
}

void Player::titleUpdate()
{

	if (!rollStopFlag)
	{
		worldTransform_.rotation += {0.2f, 0.0f, 0.0f};
	}

}

void Player::Draw(Camera* camera)
{
	//�s��v�Z
	worldTransform_.TransUpdate(camera);

	collider_.center = EngineMathF::GetWorldPosition(worldTransform_);

	model_->Draw(&worldTransform_);
}

Transform& Player::GetWorldTransform()
{
	return worldTransform_;
}

void Player::Move()
{
	if (Input::GetInstance()->KeepPush(DIK_A) || Input::GetInstance()->KeepPush(DIK_LEFT))
	{
		worldTransform_.translation += {-0.03f, 0.0f, 0.0f};
	}
	else if (Input::GetInstance()->KeepPush(DIK_D) || Input::GetInstance()->KeepPush(DIK_RIGHT))
	{
		worldTransform_.translation += {0.03f, 0.0f, 0.0f};
	}

	//�ړ�����
	{
		const float moveLimitX = 4.5;

		worldTransform_.translation.x = EngineMathUtility::Max(worldTransform_.translation.x, -moveLimitX);
		worldTransform_.translation.x = EngineMathUtility::Min(worldTransform_.translation.x, moveLimitX);
	}
}

void Player::Rotate()
{

	if (Input::GetInstance()->KeepPush(DIK_A) || Input::GetInstance()->KeepPush(DIK_LEFT))
	{
		Complement(worldTransform_.rotation.y, -40.0f * EngineMathF::Deg2Rad, 10);//��

	}
	else if (Input::GetInstance()->KeepPush(DIK_D) || Input::GetInstance()->KeepPush(DIK_RIGHT))
	{
		Complement(worldTransform_.rotation.y, 40.0f * EngineMathF::Deg2Rad, 10);//��
	}
	else
	{
		Complement(worldTransform_.rotation.y, 0.0f, 10);//��
	}
}

void Player::Jump()
{
	if (jumpFlag == 1)
	{
		worldTransform_.translation.y += gravitySpeed;
		gravitySpeed -= 0.05f;

		if (gravitySpeed <= 0)
		{
			jumpFlag = 2;
		}
	}

	//������
	if (jumpFlag == 2)
	{
		worldTransform_.translation.y -= gravitySpeed;
		gravitySpeed += 0.04f;

		if (gravitySpeed >= defGravitySpeed)
		{
			jumpFlag = 0;
			gravitySpeed = defGravitySpeed;
			worldTransform_.translation.y = -2.0f;
		}
	}
}

void Player::Squat()
{
	if (Input::GetInstance()->TriggerPush(DIK_DOWN) && !jumpFlag && !squatFlag ||
		Input::GetInstance()->TriggerPush(DIK_S) && !jumpFlag && !squatFlag)
	{
		squatFlag = true;
		rollStopFlag = true;
		oldRot = worldTransform_.rotation;
		worldTransform_.rotation = { 0.0f,0.0f,0.0f };
		worldTransform_.rotation.z = 80.0f * EngineMathF::Deg2Rad;

		collider_.size = {
		0.5f * worldTransform_.scale.x,
		0.3f * worldTransform_.scale.y,
		0.5f * worldTransform_.scale.z };

	}

	if (squatFlag)
	{
		worldTransform_.rotation.y = -90.0f * EngineMathF::Deg2Rad;

		squatTime--;

		if (squatTime == 0)
		{
			squatTime = 60 * 2;
			squatFlag = false;
			rollStopFlag = false;
			worldTransform_.rotation = oldRot;

			//�����蔻��̑傫��
			collider_.size = {
				0.3f * worldTransform_.scale.x,
				0.5f * worldTransform_.scale.y,
				0.5f * worldTransform_.scale.z };
		}
	}
}

void Player::EndGameReset()
{
	worldTransform_.rotation = EngineMathF::Vector3(0.0f, 0.0f, 0.0f);

	worldTransform_.translation = EngineMathF::Vector3(0.0f, 0.0f, 10.0f);

	jumpFlag = 0;
	gravitySpeed = defGravitySpeed;
	worldTransform_.translation.y = -2.0f;
}

void Player::jumpReset()
{
	jumpFlag = 0;
	gravitySpeed = defGravitySpeed;
	worldTransform_.translation.y = -2.0f;
}
