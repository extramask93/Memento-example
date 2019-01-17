#pragma once
#include <memory>
#include <vector>

enum class Interpolation
{
    LINEAR,CIRCULAR
};
enum class Grip {
    OPENED,CLOSED,NOT_CHANGE,
};
struct Vectorf {
    float x;
    float y;
    float z;
};
class ArmMemento {
    ArmMemento(Vectorf pos, float speed, Grip grip) :pos_m(pos), speed_m(speed), grip_m(grip) {}
    float speed_m;
    Grip grip_m;
    Vectorf pos_m;
    friend class Arm;
};

using MementoContainer = std::vector<std::shared_ptr<ArmMemento>>;
using Memento = std::shared_ptr<ArmMemento>;

class Arm {
public:
    Memento move(Vectorf pos);
    Memento drawStraight(Vectorf distance);
    Memento setSpeed(float speed);
    Memento gripOpen();
    Memento gripClose();
    void undo();
    void redo();
    friend std::ostream& operator << (std::ostream &o,const Arm &arm)
    {
        o<<"On position: "<<arm.position.x<<','<<arm.position.y<<','<<arm.position.z<<'\n';
        o<<"With speed : "<<arm.speed<<'\n';
        o<<"Grip : "<<static_cast<int>(arm.gripState)<<'\n';
        return o;
    }
private:
    float speed = 0;
    int lastOpindex = 0;
    Vectorf position = {0.f,0.f,0.f};
    Grip gripState = Grip::OPENED;
    MementoContainer history = {};
    void restore(const Memento &memento);
};