////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
// This file contains the definitions related to the motorschema 'move_to_goal'.                  //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef MS_MOVE_TO_GOAL
#define MS_MOVE_TO_GOAL


#include "robot_state.h"
#include "utils.h"

// definitions

#define GOAL_REACHED_DISTANCE 0.1

// methods

void get_move_to_goal_vector(float* direction);



#endif
