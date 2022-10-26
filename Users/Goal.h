#pragma once
#include "Transform.h"
#include "Camera.h"
#include "objModel.h"
#include "EngineMathUtility.h"
#include <memory>

class Goal
{
public:
	// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(Camera* camera);

private:
	std::unique_ptr<objModel> model_;
	std::unique_ptr<Transform> worldTransform_;
};