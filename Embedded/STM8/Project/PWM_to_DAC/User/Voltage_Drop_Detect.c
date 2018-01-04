/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "Voltage_Drop_Detect.h"

#define outMax 160
#define outMin 0 
  
static float prevInput;
static float error;
static float derivative;
static float integral = 0.0;
static int sampleTime = 100;  //10 ms
static unsigned long lastTime, now;
static double *setpoint;
static int *timeTick;
static float *input;
static float *output;
static float Kp, Ki, Kd;


void VDD_Init(float* Input, int* time){
  input = Input;
  timeTick = time;
}
	
bool VDD_Run(void){
  now = *timeTick;
  if((now-lastTime) > sampleTime){
    lastTime = now;
    
    error = prevInput - *input;
    prevInput = *input;
    if(error > 500) return false;
    else return true;
  }
	
}




