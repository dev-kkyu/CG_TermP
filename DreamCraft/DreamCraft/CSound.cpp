#include "CSound.h"

#include <Windows.h>
#include <mmsystem.h>					//����
#pragma comment (lib, "winmm.lib")		//����

CSound::CSound()
{
}

void CSound::Move()
{
	PlaySound(L"Resource/Sound/�ȱ�.wav", 0, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
}

void CSound::Attack()
{
	PlaySound(L"Resource/Sound/����.wav", 0, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
}

void CSound::Init()
{
	PlaySound(L"Resource/Sound/����.wav", 0, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
}
