/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "AutoPID.h"

#define outMax 1000
#define outMin 0 
 
static bool *startPID;
static bool set_ADC_min = false;
static bool set_cycle = false;
static bool warm_up = false;
static float ADC_max, ADC_min;
static float absMax, absMin;
static float lastADC = 0;
static float delta = 0;
static float beta = 0;
static float oscillateRatio = 0.8;
static float stableRatio = 0.1;
static float Ku, Tu;
static int cycleCount = 0;
static int cycleOK = 0;
static int Step = 1;
static int lastPeak, currentPeak;
static double time;

static float prevInput;
static float error;
static float derivative;
static float integral = 0.0;
static int sampleTime = 1;
static unsigned long lastTime, now;
static double *setpoint;
static int *timeTick;
static float *input;
static float *output;
static float Kp, Ki, Kd;


void PID_Init(float* mInput, float* mOutput, double* mSetpoint, int* mTime, bool *mstartPID){
  input = mInput;
  output = mOutput;
  setpoint = mSetpoint;
  timeTick = mTime;
  startPID = mstartPID;
  
  ADC_max = *setpoint;
  ADC_min = *setpoint;
  
  Kp = 0.001;
  Ki = 0.00000001;
  Kd = 0.002;
}
	
void PID_Run(void){
  now = *timeTick;
  if((now-lastTime) > sampleTime){
    lastTime = now;  
    error = *setpoint- *input;
    integral = integral + error;
    derivative = *input- prevInput;
    *output += Kp * error + Ki * integral + Kd * derivative;
    prevInput = *input;
    
    if(*output > outMax)  *output = outMax;     //Limit max output
    if(*output < outMin)  *output = outMin;     //Limit min output  
    
    AutoTune();
    
    time++;
  }
	
}

void AutoTune(void){
  if(*input >= *setpoint) warm_up = true;     //Startup

  if(*input > ADC_max && warm_up){            //Set peak top 
    ADC_max = *input;  
    lastPeak = currentPeak;                   //Set time for peak
    currentPeak = now;
    set_ADC_min = true;                       //flag set_min
  }
  if((*input < ADC_min) && set_ADC_min){      //Set peak bottom
    ADC_min = *input;
    set_cycle = true;                         //flag set_cycle
  }
  
  if(*input >= *setpoint && set_cycle){       //If ADC value go up, set peak top and bottom 
    delta = ADC_max - ADC_min;                //Get different between 2 value
    absMax = ADC_max;
    absMin = ADC_min;
    ADC_max = *setpoint;                      //Reset ADC max to default value
    ADC_min = *setpoint;                      //Reset ADC min to defaule value
    set_ADC_min = false;                      //Reset flag set_min
    set_cycle = false;                        //Reset flag set_cycle
    
    if(delta*100/(*setpoint) >= oscillateRatio)   
      cycleCount++;                                  //If the different > 0.5% (ratio = 0.5), count the peak
    else
      if(cycleCount > 0)        cycleCount--;       //If output ok, decrease peak count
    
  }
  
  if(cycleCount >= 3){                              //If 3 cycle have peak > 0.5% than setpoint
    Ku = 4*(2*Step)/((absMax-absMin)*3.14159);
    Tu = (double)(currentPeak-lastPeak) / 1000;
    Kp = 0.6 * Ku;
    //Ki = 1.2 * Ku/Tu;
    Kd = 0.6 * Ku * Tu / 8;
    cycleCount = 0;
    //*startPID = true;
  }
  
  if(time==1000){
    beta = (lastADC-(*input))*100/(lastADC);
    beta = abs(beta);
    if(beta <= stableRatio)    
      cycleOK++;
    else                       
      if(cycleOK > 0)          cycleOK--; 
    
    lastADC = *input;
    time = 0;
  }
  
  if(cycleOK >= 30){
    *startPID = true;
    cycleOK = 0;
  }
}

float abs(float number){
  if(number < 0)        number = -number;
  return number;
}
int getTime(void){
  return *timeTick;
}




