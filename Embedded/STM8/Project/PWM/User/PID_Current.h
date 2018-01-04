#ifndef __PID_Current_H
#define __PID_Current_H

// 
// C Binding for C++ Compilers
// 
#ifdef __cplusplus
extern "C"
{
#endif

void PID_Current_Init(float* Input, float* Output, double* Setpoint, int* time);
void PID_Current_Run(void);



#ifdef __cplusplus
}
#endif

#endif /* __FILTER_H */

