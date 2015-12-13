#include <stdio.h>
#include <math.h>
#include <string.h>

#include "ms_move_to_goal.h"





////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
// This file contains everything related to the motorschema 'move_to_goal'.                       //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////





void get_move_to_goal_vector(float * direction) {
	int j;
	for (j=0;j<2;j++) {
		direction[j] = (migr[j]-unit_center[j]);
	}
	float direction_norm = norm(direction,2);
	
	// direction_norm > MAX_THRESHOLD
	if (direction_norm > move_to_goal_max_threshold) {
		normalize(direction,direction,2);

	// direction_norm < MIN_THRESHOLD
	} else if (direction_norm < move_to_goal_min_threshold) {
		direction[0]=0;
		direction[1]=0;

	// direction_norm in the middle
	} else {
	    normalize(direction,direction,2);
	    float multiplier_factor=(direction_norm-move_to_goal_min_threshold)/(move_to_goal_max_threshold-move_to_goal_min_threshold);
	    multiply_vector_by(direction,2,multiplier_factor);
        }
    
	
	return;
}

