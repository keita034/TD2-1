#include"Mesh.h"

Mesh* Mesh::mesh = nullptr;

#pragma region �p�u���b�N

//����`�悷��
void Mesh::DrawLine(float x1, float y1, float x2, float y2, EngineMathF::Vector4 color)
{
	assert(lineCount < lineMaxCount);

	// ���_�f�[�^
	std::vector <PosColor > vertices = {
	  {{x1, y1, 0.0f}, {color.x, color.y, color.z, color.w}},
	  {{x2, y2, 0.0f}, {color.x, color.y, color.z, color.w}},
	};

	UINT indxcount = lineCount * lineVertexCount;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	copy(vertices.begin(), vertices.end(), &lineBuff->vertMap[indxcount]);

	// �p�C�v���C���X�e�[�g�̐ݒ�
	directX12Core->GetCommandList()->SetPipelineState(linePipelineSet[blendMode]->pipelineState.Get());

	// ���[�g�V�O�l�`���̐ݒ�
	directX12Core->GetCommandList()->SetGraphicsRootSignature(linePipelineSet[blendMode]->rootSignature.Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST); //�O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetVertexBuffers(0, 1, &lineBuff->vbView);

	//�萔�o�b�t�@�r���[
	directX12Core->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetGPUVirtualAddress());

	// �`��R�}���h
	directX12Core->GetCommandList()->DrawInstanced(lineVertexCount, 1, indxcount, 0);

	lineCount++;
}

//�O�p�`��`�悷��
void Mesh::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, EngineMathF::Vector4 color, int fillFlag)
{
	if (fillFlag)
	{
		DrawTriangleFill(x1, y1, x2, y2, x3, y3, color);
	}
	else
	{
		DrawLine(x1, y1, x2, y2, color);
		DrawLine(x2, y2, x3, y3, color);
		DrawLine(x3, y3, x1, y1, color);

	}
}

//�l�p�`��`�悷��
void Mesh::DrawBox(float x, float y, float radiusX, float radiusY, float angle, EngineMathF::Vector4 color, int fillFlag)
{
	if (fillFlag)
	{
		DrawBoxFill(x, y, radiusX, radiusY, angle, color);

	}
	else
	{

		DrawLine(x - radiusX, y - radiusY , x + radiusX, y - radiusY, color);//���ォ��E��
		DrawLine(x - radiusX, y - radiusY , x - radiusX, y + radiusY, color);//���ォ�獶��
		DrawLine(x + radiusX, y - radiusY , x + radiusX, y + radiusY, color);//�E�ォ��E��
		DrawLine(x - radiusX, y + radiusY , x + radiusX, y + radiusY, color);//��������E��
	}
}

//�ȉ~��`�悷��
void Mesh::DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, EngineMathF::Vector4 color, int fillMode)
{
	constexpr UINT NumDiv = 64; // ������
	float RadianPerDivision = EngineMathF::AX_2PI / float(NumDiv); // ����1�P�ʂ̊p�x

	//�����_���������1�������Ă�����1�����悤�ɂ���
	std::array<float, NumDiv + 1> pointsX{};
	std::array<float, NumDiv + 1> pointsY{};
	float angleCos = cos(angle);
	float angleSin = sin(angle);
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseX = cos(RadianPerDivision * static_cast<float>(i)) * radiusX;
		float baseY = sin(RadianPerDivision * static_cast<float>(i)) * radiusY;
		pointsX[i] = float(baseX * angleCos - baseY * angleSin + x);
		pointsY[i] = float(baseY * angleCos + baseX * angleSin + y);
	}

	//�Ō�ƍŏ��͈ꏏ
	(*pointsX.rbegin()) = (*pointsX.begin());
	(*pointsY.rbegin()) = (*pointsY.begin());

	if (fillMode)
	{
		for (size_t index = 0; index < NumDiv; ++index)
		{
			DrawTriangleFill(x, y, pointsX[index], pointsY[index], pointsX[index + 1], pointsY[index + 1], color);
		}
	}
	else
	{
		for (size_t index = 0; index < NumDiv; ++index)
		{
			DrawLine(pointsX[index], pointsY[index], pointsX[index + 1], pointsY[index + 1], color);
		}
	}
}

//�J�E���g������
void Mesh::DrawReset()
{
	triangleCount = 0;
	lineCount = 0;
	boxCount = 0;
}

//�u�����h���[�h��ݒ肷��
void Mesh::SetBlendMode(BlendMode mode)
{
	blendMode = (UINT)mode;
}

//�F�R�[�h���擾����
EngineMathF::Vector4 Mesh::GetColor(int red, int blue, int green, int alpha)
{
	EngineMathF::Vector4 color{};

	color.x = static_cast<float>(red) / 255.0f;
	color.y = static_cast<float>(blue) / 255.0f;
	color.z = static_cast<float>(green) / 255.0f;
	color.w = static_cast<float>(alpha) / 255.0f;

	return color;
}

EngineMathF::Vector4 Mesh::GetColor(EngineMathF::Vector4 color)
{
	EngineMathF::Vector4 result{};

	result.x = static_cast<float>(color.x) / 255.0f;
	result.y = static_cast<float>(color.y) / 255.0f;
	result.z = static_cast<float>(color.z) / 255.0f;
	result.w = static_cast<float>(color.w) / 255.0f;

	return result;
}


//�R���X�g���N�^
Mesh::Mesh()
{
	directX12Core = DirectX12Core::GetInstance();

	//�e��p�C�v���C������
	CreatArryPipeline();

	//�O�p�`�o�b�t�@
	UINT vertexCount = triangleVertexCount * triangleMaxCount;
	UINT indexCount = triangleIndexCount * triangleMaxCount;
	triangleBuff = CreateBuff(vertexCount, indexCount);

	//���o�b�t�@
	vertexCount = lineVertexCount * lineMaxCount;
	indexCount = lineIndexCount * lineMaxCount;
	lineBuff = CreateBuff(vertexCount, indexCount);

	//�l�p�`�o�b�t�@
	vertexCount = boxVertexCount * boxMaxCount;
	indexCount = boxIndexCount * boxMaxCount;
	boxBuff = CreateBuff(vertexCount, indexCount);

	CreatConstBuff();

}

#pragma endregion

#pragma region �v���C�x�[�g

Mesh* Mesh::GetInstance()
{
	if (mesh == nullptr)
	{
		mesh = new Mesh();
	}

	return mesh;
}

void Mesh::Destroy()
{
	delete mesh;
}

//�O�p�`��`�悷��(���g�h��Ԃ�)
void Mesh::DrawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, EngineMathF::Vector4 color)
{
	assert(triangleCount < triangleMaxCount);

	// ���_�f�[�^
	std::vector <PosColor > vertices = {
	  {{x1, y1, 0.0f}, {color.x, color.y, color.z, color.w}},
	  {{x2, y2, 0.0f}, {color.x, color.y, color.z, color.w}},
	  {{x3, y3, 0.0f}, {color.x, color.y, color.z, color.w}},
	};

	UINT vertexCount = triangleCount * triangleVertexCount;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	copy(vertices.begin(), vertices.end(), &triangleBuff->vertMap[vertexCount]);

	// �p�C�v���C���X�e�[�g�̐ݒ�
	directX12Core->GetCommandList()->SetPipelineState(trianglePipelineSet[blendMode]->pipelineState.Get());

	// ���[�g�V�O�l�`���̐ݒ�
	directX12Core->GetCommandList()->SetGraphicsRootSignature(trianglePipelineSet[blendMode]->rootSignature.Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //�O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetVertexBuffers(0, 1, &triangleBuff->vbView);

	//�萔�o�b�t�@�r���[
	directX12Core->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetGPUVirtualAddress());

	// �`��R�}���h
	directX12Core->GetCommandList()->DrawInstanced(triangleVertexCount, 1, vertexCount, 0);

	// �g�p�J�E���g�㏸
	triangleCount++;
}

//�l�p�`��`�悷��(���g�h��Ԃ�)
void Mesh::DrawBoxFill(float x, float y, float radiusX, float radiusY, float angle, EngineMathF::Vector4 color)
{
	assert(boxCount < boxMaxCount);

	float left = -radiusX;
	float top = -radiusY;
	float right = radiusX;
	float bottom = radiusY;

	// ���_�f�[�^
	std::vector <PosColor > vertices = {
	  {{left, bottom, 0.0f},{color.x, color.y, color.z, color.w}},//����
	  {{left, top, 0.0f},{color.x, color.y, color.z, color.w}},//����
	  {{right, top, 0.0f},{color.x, color.y, color.z, color.w}},//�E��
	  {{right, bottom, 0.0f},{color.x, color.y, color.z, color.w}},//�E��
	};

	//�C���f�b�N�X
	std::vector<uint16_t> indices = { 0, 1, 2, 2, 3, 0 };

	//��]
	for (auto& vertex : vertices)
	{
		//��]
		vertex.pos = {
		  vertex.pos.x * cosf(angle) + vertex.pos.y * -sinf(angle),
		  vertex.pos.x * sinf(angle) + vertex.pos.y * cosf(angle), vertex.pos.z };

		//���s�ړ�
		vertex.pos.x += x;
		vertex.pos.y += y;
	}

	UINT vertexCount = boxCount * boxVertexCount;
	UINT indxCount = boxCount * boxIndexCount;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	std::copy(vertices.begin(), vertices.end(), &boxBuff->vertMap[vertexCount]);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	std::copy(indices.begin(), indices.end(), &boxBuff->indexMap[indxCount]);

	//�p�C�v���C���X�e�[�g�̐ݒ�
	directX12Core->GetCommandList()->SetPipelineState(trianglePipelineSet[blendMode]->pipelineState.Get());

	//���[�g�V�O�l�`���̐ݒ�
	directX12Core->GetCommandList()->SetGraphicsRootSignature(trianglePipelineSet[blendMode]->rootSignature.Get());

	//�v���~�e�B�u�`��̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //�O�p�`���X�g

	//���_�o�b�t�@�̐ݒ�
	directX12Core->GetCommandList()->IASetVertexBuffers(0, 1, &boxBuff->vbView);

	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	directX12Core->GetCommandList()->IASetIndexBuffer(&boxBuff->ibView);

	//�萔�o�b�t�@�r���[
	directX12Core->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetGPUVirtualAddress());

	//�`��R�}���h
	directX12Core->GetCommandList()->DrawIndexedInstanced(boxIndexCount, 1, static_cast<UINT>(indxCount), static_cast<INT>(vertexCount), 0);

	//�g�p�J�E���g�㏸
	boxCount++;
}

//�e��p�C�v���C���Z�b�g����
void Mesh::CreatArryPipeline()
{
	//�O�p�`�`��p�p�C�v���C���Z�b�g
	trianglePipelineSet[(UINT)BlendMode::AX_BLENDMODE_NOBLEND] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_NOBLEND);
	trianglePipelineSet[(UINT)BlendMode::AX_BLENDMODE_ALPHA] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_ALPHA);
	trianglePipelineSet[(UINT)BlendMode::AX_BLENDMODE_ADD] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_ADD);
	trianglePipelineSet[(UINT)BlendMode::AX_BLENDMODE_SUB] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_SUB);
	trianglePipelineSet[(UINT)BlendMode::AX_BLENDMODE_MULA] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_MULA);
	trianglePipelineSet[(UINT)BlendMode::AX_BLENDMODE_INVSRC] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_INVSRC);

	//���C���`��p�p�C�v���C���Z�b�g
	linePipelineSet[(UINT)BlendMode::AX_BLENDMODE_NOBLEND] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_NOBLEND);
	linePipelineSet[(UINT)BlendMode::AX_BLENDMODE_ALPHA] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_ALPHA);
	linePipelineSet[(UINT)BlendMode::AX_BLENDMODE_ADD] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_ADD);
	linePipelineSet[(UINT)BlendMode::AX_BLENDMODE_SUB] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_SUB);
	linePipelineSet[(UINT)BlendMode::AX_BLENDMODE_MULA] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_MULA);
	linePipelineSet[(UINT)BlendMode::AX_BLENDMODE_INVSRC] = CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_INVSRC);
}

//�萔�o�b�t�@����(2D���W�ϊ��s��)
void Mesh::CreatConstBuff()
{
	//�萔�o�b�t�@����
	directX12Core->CreateConstBuff(constMapTransform, constBuffTransform);

	EngineMathF::MakeOrthogonalL(
		0.0f, static_cast<float>(WindowsApp::GetInstance()->GetWindowWidth()),
		static_cast<float>(WindowsApp::GetInstance()->GetWindowHeight()), 0.0f,
		0.0f, 1.0f, constMapTransform->mat);

}

///<summary>
///�p�C�v���C���쐬
///</summary>
///<param name="type">�v���~�e�B�u�`��</param>
///<param name="mode">�u�����h���[�h��</param>
///<returns>�p�C�v���C��</returns>
std::unique_ptr<PipelineSet> Mesh::CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode mode)
{
	HRESULT result;

	std::unique_ptr< PipelineSet>set = std::make_unique<PipelineSet>();

	ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g

	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};


	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/Shaders/2D/MeshVS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);

	// �G���[�Ȃ�
	if (FAILED(result))
	{
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/Shaders/2D/MeshPS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&psBlob, &errorBlob);

	// �G���[�Ȃ�
	if (FAILED(result))
	{
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		//���W
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//uv���W 
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};


	// �V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �J�����O���Ȃ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	// �u�����h�X�e�[�g
	//���ʐݒ�(�A���t�@�l)
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;//���Z
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;//�\�[�X�̒l��100%�g��
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;//�e�X�g�̒l��0%�g��

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		blenddesc.BlendEnable = false;// �u�����h��L��

		break;

	case BlendMode::AX_BLENDMODE_ALPHA:

		blenddesc.BlendEnable = true;// �u�����h��L��
		// ����������
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;// ���Z
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
		blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;;// 1.0f-�\�[�X�̃A���t�@�l

		break;

	case BlendMode::AX_BLENDMODE_ADD:

		blenddesc.BlendEnable = true;// �u�����h��L��
		// ���Z����
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;// ���Z
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		blenddesc.DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��

		break;

	case BlendMode::AX_BLENDMODE_SUB:

		//���ʐݒ�(�A���t�@�l)
		blenddesc.BlendEnable = true;// �u�����h��L��
		// ���Z����
		blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// �f�X�g����\�[�X�����Z
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		blenddesc.DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��

		break;

	case BlendMode::AX_BLENDMODE_MULA:

		//���ʐݒ�(�A���t�@�l)
		blenddesc.BlendEnable = true;// �u�����h��L��
		//��Z
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlend = D3D12_BLEND_ZERO;
		blenddesc.DestBlend = D3D12_BLEND_SRC_COLOR;

		break;

	case BlendMode::AX_BLENDMODE_INVSRC:

		//���ʐݒ�(�A���t�@�l)
		blenddesc.BlendEnable = true;// �u�����h��L��
		// �F���]
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;// ���Z
		blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-�f�X�g�J���[�̒l
		blenddesc.DestBlend = D3D12_BLEND_ZERO;// �g��Ȃ�

		break;

	case BlendMode::AX_BLENDMODE_MAX:
		assert(0);
		break;
	}

	pipelineDesc.BlendState.RenderTarget[0] = blenddesc;

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = type;
	//D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE
	//D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams = {};
	//�萔�o�b�t�@0��
	rootParams.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//���
	rootParams.Descriptor.ShaderRegister = 0;//�萔�o�b�t�@�o�b�t�@�ԍ�
	rootParams.Descriptor.RegisterSpace = 0;//�f�t�H���g�l
	rootParams.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�S�ẴV�F�[�_�[���猩����

	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = &rootParams; //���[�g�p�����[�^�̐擪�A�h���X
	rootSignatureDesc.NumParameters = 1;        //���[�g�p�����[�^��

	// ���[�g�V�O�l�`���̃V���A���C�Y
	ID3DBlob* rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	result = directX12Core->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(set->rootSignature.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
	rootSigBlob->Release();
	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = set->rootSignature.Get();

	// �p�C�v�����X�e�[�g�̐���
	result = directX12Core->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(set->pipelineState.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	return set;
}

///<summary>
///�o�b�t�@�쐬
///</summary>
///<param name="vertexCount">���_��</param>
///<param name="indexCount">�C���f�b�N�X��</param>
///<returns>�o�b�t�@</returns>
std::unique_ptr <Buff> Mesh::CreateBuff(UINT vertexCount, UINT indexCount)
{
	HRESULT result;
	std::unique_ptr <Buff> buff = std::make_unique<Buff>();

	if (vertexCount > 0)
	{
		// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
		UINT sizeVB = static_cast<UINT>(sizeof(PosColor) * vertexCount);

		// ���_�o�b�t�@�̐ݒ�
		D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
		// ���\�[�X�ݒ�
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		// ���_�o�b�t�@�̐���
		result = directX12Core->GetDevice()->CreateCommittedResource(
			&heapProp, // �q�[�v�ݒ�
			D3D12_HEAP_FLAG_NONE,
			&resDesc, // ���\�[�X�ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(buff->vertBuff.ReleaseAndGetAddressOf()));
		assert(SUCCEEDED(result));

		// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
		result = buff->vertBuff->Map(0, nullptr, (void**)&buff->vertMap);
		assert(SUCCEEDED(result));

		// ���_�o�b�t�@�r���[�̍쐬
		// GPU���z�A�h���X
		buff->vbView.BufferLocation = buff->vertBuff->GetGPUVirtualAddress();
		// ���_�o�b�t�@�̃T�C�Y
		buff->vbView.SizeInBytes = sizeVB;
		// ���_�P���̃f�[�^�T�C�Y
		buff->vbView.StrideInBytes = sizeof(PosColor);
	}

	if (indexCount > 0)
	{
		// �C���f�b�N�X�f�[�^�̃T�C�Y
		UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * indexCount);
		// ���_�o�b�t�@�̐ݒ�
		D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
		//���\�[�X�ݒ�
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Width = sizeIB;//�C���f�b�N�X��񂪓��镪�̃T�C�Y
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		//�C���f�b�N�X�o�b�t�@�̐���
		result = directX12Core->GetDevice()->CreateCommittedResource(
			&heapProp,//�q�[�v�ݒ�
			D3D12_HEAP_FLAG_NONE,
			&resDesc,//���\�[�X�ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(buff->indexBuff.ReleaseAndGetAddressOf()));

		//�C���f�b�N�X�o�b�t�@���}�b�s���O
		result = buff->indexBuff->Map(0, nullptr, (void**)&buff->indexMap);
		//�}�b�s���O����
		buff->indexBuff->Unmap(0, nullptr);

		//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
		buff->ibView.BufferLocation = buff->indexBuff->GetGPUVirtualAddress();
		buff->ibView.Format = DXGI_FORMAT_R16_UINT;
		buff->ibView.SizeInBytes = sizeIB;
		assert(SUCCEEDED(result));
	}

	return buff;
}

#pragma endregion
