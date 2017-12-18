#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "vector"
struct dot
{
   double x;
   double y;

};
struct vect_2d
{
   double x;
   double y;

};

struct elemets
{
  dot point;
  double value;
  unsigned int partition;
};

struct obstacle{

     dot position ;
     double radius;
     double gain;

};



typedef elemets q;
typedef dot position;
typedef vect_2d velocity;

struct agent_state{
    position pos;
    velocity vel;
    velocity att; // attractive term
    velocity rep; // repulsive term
   //std::vector<obstacle> obstacle_detect;
    double radius;
    double gain;  // 0<k<1
};

class geometry
{
public:
    geometry();
};

#endif // GEOMETRY_H
