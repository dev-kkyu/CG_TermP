#include "CSound.h"

CSound::CSound()
{
}

void CSound::Move()
{
	PlaySound(L"Sound/걷기.wav", 0, SND_FILENAME | SND_ASYNC); //일반 재생
}

void CSound::Attack()
{
	PlaySound(L"Sound/공격.wav", 0, SND_FILENAME | SND_ASYNC); //일반 재생
}

void CSound::Init()
{
	PlaySound(L"Sound/생성.wav", 0, SND_FILENAME | SND_ASYNC); //일반 재생
}
