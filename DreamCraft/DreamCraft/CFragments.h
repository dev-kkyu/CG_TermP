#include "CBlock.h"

class CFragments : public CBlock
{
private:

	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 color;

	int object;

public:
	CFragments(glm::vec3 Position,int object);
	virtual ~CFragments();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��

};
