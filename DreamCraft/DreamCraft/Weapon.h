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
    Weapon(int i);    //i´Â ¹æÇâ

    ~Weapon();

    void Update() override;
    void FixedUpdate();
    void change(glm::vec3 weaponColor);
};
