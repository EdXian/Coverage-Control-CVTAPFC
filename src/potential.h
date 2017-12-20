#ifndef POTENTIAL_H
#define POTENTIAL_H
#include "geometry.h"
#include "math.h"
//#include "robot.h"
#include "stdio.h"
#include "iostream"

typedef std::vector<obstacle> obstacle_list;

class potential
{
    public:

        potential(double gain);
        void gradient_phi(agent_state& robot,obstacle_list obstacles ,position target);
        double k_gain;

         double distance(position a,position b);
    private:


        double gamma(agent_state robot , dot target);


        double beta(agent_state robot,obstacle_list obstacles);


        double sigmod(agent_state robot,obstacle obs);
        double zigma(agent_state robot ,obstacle o);
        double phi(double x ,double y,agent_state robot, dot target);

};

#endif // POTENTIAL_H
