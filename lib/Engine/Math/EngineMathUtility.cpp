#include "EngineMathUtility.h"

namespace EngineMathUtility
{
#pragma region ��Βl�̌v�Z

	//�l�𐮐���
	int Abs(int abs)
	{
		return 	std::abs(abs);
	}

	//�l�𐮐���
	long AbsL(long abs)
	{
		return 	std::labs(abs);
	}

	//�l�𐮐���
	long long AbsLL(long long abs)
	{
		return 	std::llabs(abs);
	}

#pragma endregion ��Βl�̌v�Z

	// �f�B���N�g������t�@�C�����ꗗ������
	std::vector<std::string> getFileNames(std::string folderPath)
	{
		{
			std::filesystem::directory_iterator iter(folderPath), end;
			std::error_code err;
			std::vector<std::string> file_names;

			for (; iter != end && !err; iter.increment(err))
			{
				const std::filesystem::directory_entry entry = *iter;

				file_names.push_back(entry.path().string());
			}

			return file_names;
		}
	}
}