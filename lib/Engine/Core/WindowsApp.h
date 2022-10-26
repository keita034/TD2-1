#pragma once
#include"ErrorException.h"

class WindowsApp
{
private:
	WNDCLASSEX wndclassex{};
	HWND hwnd;
	MSG massege{};//���b�Z�[�W
	int windowWidth = 1280;//����
	int windowHeight = 720;//�c��



public:
	//�V���O���g���C���X�^���X�̎擾
	static WindowsApp* GetInstance();

	/// <summary>
	/// �E�B���h�E����
	/// </summary>
	/// <param name="title">�^�C�g��(���C�h����)</param>
	/// <param name="width">�E�B���h�E����</param>
	/// <param name="height">�E�B���h�E����</param>
	void CreatWindow(const wchar_t* title = L"DirectXGame", int width = 1280, int height = 720);
	bool MessageWindow();
	void Break();

	//�Z�b�^�[
	void SetW(WNDCLASSEX W);
	void SetHwnd(HWND Hwnd);

	//�Q�b�^�[
	WNDCLASSEX GetW();
	HWND GetHwnd();
	int GetWindowHeight();
	int GetWindowWidth();

private:
	//�R���X�g���N�^�E�f�X�g���N�^
	WindowsApp() = default;
	~WindowsApp() = default;
};