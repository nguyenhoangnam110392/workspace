#ifndef __VOLTAGE_DROP_DETECT_H
#define __VOLTAGE_DROP_DETECT_H

// 
// C Binding for C++ Compilers
// 
#ifdef __cplusplus
extern "C"
{
#endif

void VDD_Init(float* Input, float* Output, double* Setpoint, int* time);
void VDD_Run(void);



#ifdef __cplusplus
}
#endif

#endif /* __FILTER_H */

