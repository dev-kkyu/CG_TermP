#include "CSound.h"

CSound::CSound()
{
}

void CSound::Move()
{
	PlaySound(L"Sound/�ȱ�.wav", 0, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
}

void CSound::Attack()
{
	PlaySound(L"Sound/����.wav", 0, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
}

void CSound::Init()
{
	PlaySound(L"Sound/����.wav", 0, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
}
