#include "potential.h"

potential::potential(double gain)
{
    k_gain =gain;
}




double potential::distance(position a, position b){

return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );

}

double potential::gamma(agent_state robot , dot target){
    return (robot.pos.x - target.x)*(robot.pos.x - target.x) + (robot.pos.y - target.y) * (robot.pos.y - target.y);
}

double potential::sigmod(agent_state robot,obstacle obs){
    double value=0.0;
    double dist ;
    dist = distance(robot.pos , obs.position);
    value = 1 + exp(-1*(dist - (obs.radius/2))*(obs.gain)) ; //     radius = obs.radius  ,  gain = 5
    value = 1/value;
    return value;
}

double potential::beta(agent_state robot, obstacle_list obstacles){
    double beta_i = 1.0, beta_il;
    if(obstacles.size()>1){
        for(unsigned int i=0;i<obstacles.size();i++){

            beta_il = sigmod(robot,obstacles[i]);
            beta_i = beta_i * beta_il;
        }
    }
    if(obstacles.size()==1){
      beta_i = sigmod( robot ,obstacles[0]);
     // std::cout << "beta_i"  <<  beta_i<<std::endl;
    }
    return beta_i;
}

//compute navigation function
void potential::gradient_phi(agent_state& robot,obstacle_list obstacles ,position target){

       double gamma_ , beta_=1.0 , alpha;
       double  beta_l=1.0;
       vect_2d rep_sum,rep;
       double h;

       rep.x = 1.0;
       rep.y = 1.0;
       gamma_ = this->gamma( robot , target);
       beta_ = this ->beta(robot ,obstacles );

       alpha = pow( gamma_ , robot.gain )+beta_;
       alpha = 1/pow( alpha , (1/robot.gain + 1));

       robot.att.x = beta_ * 2* ( robot.pos.x - target.x) ;
       robot.att.y = beta_ * 2* ( robot.pos.y - target.y) ;

    //    std::cout<< "-------------" <<std::endl;
    //    std::cout <<"k = " << robot.gain  <<std::endl;
    //    std::cout <<"alpha = " << alpha  <<std::endl;
    //    std::cout <<"gamma_ = " << gamma_  <<std::endl;
    //    std::cout <<"beta = " << beta_<<std::endl;
    //    std::cout << "attx = " <<  robot.att.x
    //              << "  atty = " <<   robot.att.y<<std::endl;


       if(obstacles.size()>1){
           for(unsigned int i=0;obstacles.size();i++){
               beta_l =1.0;
               h = zigma(robot ,obstacles[i]);
               rep.x =  h*gamma_ * robot.gain * (robot.pos.x-obstacles[i].position.x);
               rep.y =  h*gamma_ * robot.gain * (robot.pos.y-obstacles[i].position.y);

               for(unsigned int j =0 ; j < obstacles.size() ; j++){
                   if(j!=i){

                       beta_l  *=  sigmod(robot , obstacles[j]);

                   }

               }
               rep_sum.x += rep.x * beta_l;
               rep_sum.y += rep.y * beta_l;
           }
           robot.rep.x = rep_sum.x;
           robot.rep.y = rep_sum.y;

       }else if(obstacles.size()==1){

           h = zigma(robot ,obstacles[0]);
           rep.x =  h*gamma_  * (robot.pos.x-obstacles[0].position.x);
           rep.y =  h*gamma_  * (robot.pos.y-obstacles[0].position.y);
           robot.rep.x = rep.x * beta_l;
           robot.rep.y = rep.y * beta_l;
       }

      robot.vel.x = -1*alpha * (robot.att.x - robot.rep.x) ;
      robot.vel.y = -1*alpha * (robot.att.y - robot.rep.y) ;
}

double potential::zigma(agent_state robot ,obstacle obs){
    double  value1 ,value2 ,value3;
    double h ;
    h = ((obs.radius/2.0)-distance(robot.pos ,obs.position )); //12/robot.radius)
    value1 = 1/((1+exp(h))*(1+exp(h)));
    value2 = exp(h)/obs.radius;
    value3 = 1/ distance(robot.pos , obs.position);
    return value1 * value2 * value3;
}


//double potential::phi(double x ,double y,agent_state robot , dot target){
//    double dist ,dist2,value,beta_,k;
//    dot data;
//    data.x =x;
//    data.y =y;
//    k = robot.gain;
//    dist = distance(data , target);
//    dist2 = dist*dist;
//    beta_ = this->beta(robot);
//    value = pow(dist2,k)+beta_;
//    value = dist2/pow(value,1/k);
//    return value;
//}
