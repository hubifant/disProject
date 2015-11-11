#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <webots/robot.h>
#include <webots/emitter.h>
#include <webots/supervisor.h>

#define FORMATION_SIZE		4	// Number of robots in formation
#define TIME_STEP		64	// [ms] Length of time step

WbNodeRef  robs[FORMATION_SIZE];		// Robots nodes
WbFieldRef robs_trans[FORMATION_SIZE];		// Robots translation fields
WbFieldRef robs_rotation[FORMATION_SIZE];	// Robots rotation fields
WbDeviceTag emitter;				// Single emitter

float loc[FORMATION_SIZE][3];			// Location of everybody in the formation



//You can add the rest of the required variables in a similar fashion and initialize them similar to the robots in the simplest case!

/*----------------- for the goal and obstacles you might also need to ask the supervisor depending on the approach you take:
 1) absolute positions 2) relative distances based on the perception of the robot 
 approach 2 is more realistic and preferred. However approach 1 also exists incase you run into problems with implementing local perception
 most of the codes that you need for both approaches can be found in the labs (lab4 is particularly useful) 

Think about the obstacles, do you need to know their exact position? 
how can you differentiate between a robot and an obstacle if you use local perception? in one of your labs you had communication between robots where the distance 
between a pair of robots could be found
if you decide to use the absolute positions of all the obstacles through the supervisor,how can you make it more realistic? e.g define a region around the robot where you include the obstacles? 

The more realistic and less dependent on the supervisor you are, the better.

goal is the red cylinder which can be moved around between different trials of your code
*/




/*
 * Initialize robot positions and devices
 */
void reset(void) {
	
	wb_robot_init();
	emitter = wb_robot_get_device("emitter");
	if (emitter==0) printf("missing emitter\n");
	
	char rob[5] = "rob0";
	int i;
	for (i=0;i<FORMATION_SIZE;i++) {
		sprintf(rob,"rob%d",i);
		robs[i] = wb_supervisor_node_get_from_def(rob);
		robs_trans[i] = wb_supervisor_node_get_field(robs[i],"translation");
		robs_rotation[i] = wb_supervisor_node_get_field(robs[i],"rotation");
	}
}

/*
* this is sending the robots information only, for the obstacles and the goal you should complete this function
if you decide to go with absolute positions, however you can think about the relative distances which are more
realistic and try to use that data (you can find the codes for doing this in lab4)
*/

void send_init_poses(void)
{
        char buffer[255];	// Buffer for sending data
        int i;
         
        for (i=0;i<FORMATION_SIZE;i++) {
		// Get data
		loc[i][0] = wb_supervisor_field_get_sf_vec3f(robs_trans[i])[0]; // X
		loc[i][1] = wb_supervisor_field_get_sf_vec3f(robs_trans[i])[2]; // Z
		loc[i][2] = wb_supervisor_field_get_sf_rotation(robs_rotation[i])[3]; // THETA
		// Send it out
		sprintf(buffer,"%1d#%f#%f#%f",i,loc[i][0],loc[i][1],loc[i][2]);
		//printf("%1d#%f#%f#%f\n",i,loc[i][0],loc[i][1],loc[i][2]);
		wb_emitter_send(emitter,buffer,strlen(buffer));

		// Run one step
		wb_robot_step(TIME_STEP);
	}
}


/*
 * Main function.
 you need to compelet the code
 */
 
int main(int argc, char *args[]) {
	
	

	reset();     
	
	send_init_poses(); //this function is here as an example for communication using the supervisor
	
	
	for(;;) {
	
	  //-------------- you need to complete the code 
	
  	  wb_robot_step(TIME_STEP);
		
	}

}
