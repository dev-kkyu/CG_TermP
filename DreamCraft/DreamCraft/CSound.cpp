#include "CSound.h"

#include <Windows.h>
#include <mmsystem.h>					//음악
#pragma comment (lib, "winmm.lib")		//음악

CSound::CSound()
{
}

void CSound::Move()
{
	PlaySound(L"Resource/Sound/걷기.wav", 0, SND_FILENAME | SND_ASYNC); //일반 재생
}

void CSound::Attack()
{
	PlaySound(L"Resource/Sound/공격.wav", 0, SND_FILENAME | SND_ASYNC); //일반 재생
}

void CSound::Init()
{
	PlaySound(L"Resource/Sound/생성.wav", 0, SND_FILENAME | SND_ASYNC); //일반 재생
}
