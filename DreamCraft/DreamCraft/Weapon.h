#pragma once
#include "RobotParts.h"
class Weapon : public RobotParts
{
private:
    int i;
    float rotate;
    bool isrotDirec;
public:
    Weapon();
    Weapon(int i);    //i�� ����

    ~Weapon();

    void Update() override;
    void change(glm::vec3 weaponColor);
};
