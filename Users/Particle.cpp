#include "Particle.h"

Hexagon num;

void SceneParticle::Initialize()
{
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::GetInstance()->LoadTexture(L"Resources/Hexagon.png");
	textureBox_ = TextureManager::GetInstance()->LoadTexture(L"Resources/white1x1.png");

	input_ = Input::GetInstance();

	sprite_ = std::make_unique<Sprite2D>();
	sprite_->Initialize();

	spriteBox_ = std::make_unique<Sprite2D>();
	spriteBox_->Initialize();

	Reset();

	spriteBoxTransform.translation = { 1280 /2, 320 ,0.0f };
	spriteBoxTransform.Initialize();
}

void SceneParticle::Reset()
{
	pos.x = 0;
	pos.y = -48;

	pos2.x = 150;
	pos2.y = -48;

	bottom.y = static_cast<float>(-1020) / 2;

	num.timer = 120;
}

void SceneParticle::EyeCatchInitialize()
{
	Hexagon tmp;
	Hexagon tmp2;

	tmp.transform.translation = { pos.x,pos.y ,0.0f };
	tmp2.transform.translation = { pos2.x,pos2.y,0.0f };

	tmp.transform.Initialize();
	tmp2.transform.Initialize();

	//tmp.sprite_.reset(Sprite::Create(textureHandle_, { pos.x,pos.y }));
	//tmp2.sprite_.reset(Sprite::Create(textureHandle_, { pos2.x,pos2.y }));
	//spriteBox_.reset(Sprite::Create(textureBox_, { 0, 320 }));

	hexagon_.push_back(std::move(tmp));
	hexagon2_.push_back(std::move(tmp2));

	hexagon_.remove_if([](Hexagon& hexagon)
		{
			return hexagon.timer <= 0;
		});
	hexagon2_.remove_if([](Hexagon& hexagon)
		{
			return hexagon.timer <= 0;
		});
}

void SceneParticle::EyeCatchDraw()
{
	for (Hexagon& i : hexagon_)
	{
		sprite_->Draw(textureHandle_,i.transform);
		i.timer--;
	}

	for (Hexagon& i : hexagon2_)
	{
		sprite_->Draw(textureHandle_, i.transform);
		i.timer--;
	}
}

void SceneParticle::state()
{
	flag = true;
}

void SceneParticle::EyeCatch()
{
	if (input_->TriggerPush(DIK_P))
	{
		flag = true;
	}

	// ウィンドウサイズを超えたら一段ずらす
	if (pos.x > 1400)
	{
		if (flag2 == true)
		{
			pos.x = 0;
			pos.y += 48;
			flag2 = false;
		}
		else
		{
			pos.x = -75;
			pos.y += 48;
			flag2 = true;
		}
	}
	if (pos2.x > 1400)
	{
		if (flag3 == true)
		{
			pos2.x = 150;
			pos2.y += 48;
			flag3 = false;
		}
		else
		{
			pos2.x = 75;
			pos2.y += 48;
			flag3 = true;
		}
	}

	if (flag == true)
	{
		EyeCatchInitialize();

		//spriteBox_->SetSize({ 1280.0f, 980.0f });
		textureBox_.width = static_cast<size_t>(1280);
		textureBox_.height = static_cast<size_t>(980);
		bottom.y += 8.5f;
		spriteBoxTransform.translation = { 1280 / 2,bottom.y,0.0f };
		spriteBox_->Draw(textureBox_, spriteBoxTransform);

		EyeCatchDraw();
		
		pos.x += 300;
		pos2.x += 300;
		num.timer++;
	}

	if (num.timer > 330)
	{
		flag = false;
		if (flag == false)
		{
			Reset();
		}
	}
}

void SceneParticle::Draw()
{
	EyeCatch();
}

float SceneParticle::GetNumTimer()
{
	return num.timer;
}