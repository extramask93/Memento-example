#include <iostream>
#include "arm.hpp"


int main() {
    Arm arm_6_dof;
    arm_6_dof.move({1,2,3});
    arm_6_dof.gripClose();
    arm_6_dof.setSpeed(12.5);
    arm_6_dof.undo();
    std::cout<<arm_6_dof;
    return  0;
}