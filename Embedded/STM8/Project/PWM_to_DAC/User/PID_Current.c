/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "PID_Current.h"

#define outMax 160
#define outMin 0 
  
static float prevInput;
static float error;
static float derivative;
static float integral = 0.0;
static int sampleTime = 2;
static unsigned long lastTime, now;
static double *setpoint;
static int *timeTick;
static float *input;
static float *output;
static float Kp, Ki, Kd;


void PID_Current_Init(float* Input, float* Output, double* Setpoint, int* time){
  input = Input;
  output = Output;
  setpoint = Setpoint;
  timeTick = time;
}
	
void PID_Current_Run(void){
  now = *timeTick;
  if((now-lastTime) > sampleTime){
    lastTime = now;
    
    //Kp = 0.00004;
    //Ki = 0.000000;
    //Kd = 0.00010;
    //sampleTime = 2;
    //vol = 13.0
    
    Kp = 0.000035;
    Ki = 0.000000;
    Kd = 0.00010;
    
    error = *setpoint- *input;
    integral = integral + error;
    derivative = *input- prevInput;
    *output += Kp * error + Ki * integral + Kd * derivative;
    prevInput = *input;
    
    if(*output > outMax) *output = outMax;
    if(*output < outMin) *output = outMin;
  }
	
}




