#pragma once
#include "CSheep.h"


class CSheep_YesTER : public CSheep
{
private:
	bool hairless;

public:
	CSheep_YesTER(glm::vec3 Position);
	virtual ~CSheep_YesTER();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual void Render() override;		// �� ���� ��, �� ���� ��
};
