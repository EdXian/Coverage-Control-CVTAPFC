#ifndef ROBOT_H
#define ROBOT_H
#include "geometry.h"
#include "potential.h"
#include "vector"

class robot
{
    public:
        robot();
        agent_state robot_state;
        std::vector<obstacle> obstacle_list;
        void detect_obstacle();
        //potential *p;
    private:
        void dynamics();


};

#endif // ROBOT_H
