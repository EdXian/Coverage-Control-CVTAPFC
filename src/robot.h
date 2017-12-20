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
        obstacle_list obstacles;

        void detect_obstacle(obstacle_list& obstacles);
        void clear_obstacle();
        potential *p;
    private:
        void dynamics();


};

#endif // ROBOT_H
