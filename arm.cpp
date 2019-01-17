#include "arm.hpp"
#include <iostream>
    Memento Arm::drawStraight(Vectorf distance)
    {
        ArmMemento memento{position,speed,gripState};
        history.push_back(std::make_shared<ArmMemento>(memento));
        lastOpindex++;
        std::cout<<"Moving specified distance with linear interpolation\n";
        position.x += distance.x;
        position.y += distance.y;
        position.z += distance.z;
        return history.back();
    }
    Memento Arm::setSpeed(float spd)
    {
        ArmMemento memento{position,speed,gripState};
        lastOpindex++;
        history.push_back(std::make_shared<ArmMemento>(memento));
        std::cout<<"Setting speed to : "<<spd<<"\n";
        speed = spd; 
        return history.back();
    }
    Memento Arm::gripOpen()
    {
        ArmMemento memento{position,speed,gripState};
        lastOpindex++;
        history.push_back(std::make_shared<ArmMemento>(memento));
        std::cout<<"Opening the grip\n";
        gripState = Grip::OPENED;
        return history.back();
    }
    Memento Arm::gripClose() {
        ArmMemento memento{position,speed,gripState};
        lastOpindex++;
        history.push_back(std::make_shared<ArmMemento>(memento));
        std::cout<<"Closing the grip\n";
        gripState = Grip::CLOSED;
        return history.back();
    }
    Memento Arm::move(Vectorf pos) {
        ArmMemento memento{position,speed,gripState};
        lastOpindex++;
        history.push_back(std::make_shared<ArmMemento>(memento));
        std::cout<<"Moving to a position with linear interpolation\n";
        position = pos;
        return history.back();
    }
    void Arm::restore(const Memento &memento) {
            position = history[lastOpindex]->pos_m;
            speed = history[lastOpindex]->speed_m;
            gripState = history[lastOpindex]->grip_m;
    }
    void Arm::undo() {
        if(lastOpindex >0) {
            lastOpindex--;
            restore(history[lastOpindex]);
        }
    }
    void Arm::redo(){
        if(lastOpindex < history.size()-1) {
            lastOpindex++;
            restore(history[lastOpindex]);
        }

    }


