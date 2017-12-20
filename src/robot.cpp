#include "robot.h"

robot::robot()
{
    robot_state.gain = 0.8; //1<k<0
    p = new potential(robot_state.gain);
}


void robot::dynamics(){

}

//detect neighbors and obstacles
void robot::detect_obstacle(obstacle_list& obstacles){

    for(obstacle_list::iterator it = obstacles.begin() ; it != obstacles.end() ; it++){
        //obstacle &obs = *(it);
        this->obstacles.push_back(*(it));
    }

}

void robot::clear_obstacle(){

    this->obstacles.clear();

}
