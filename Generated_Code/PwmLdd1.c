/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : PwmLdd1.c
**     Project     : ServoMotor
**     Processor   : MKL46Z256VLL4
**     Component   : PWM_LDD
**     Version     : Component 01.014, Driver 01.03, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-25, 11:10, # CodeGen: 5
**     Abstract    :
**          This component implements a pulse-width modulation generator
**          that generates signal with variable duty and fixed cycle.
**          This PWM component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
**     Settings    :
**          Component name                                 : PwmLdd1
**          Period device                                  : TPM0_MOD
**          Duty device                                    : TPM0_C4V
**          Output pin                                     : LCD_P44/PTD4/LLWU_P14/SPI1_PCS0/UART2_RX/TPM0_CH4
**          Output pin signal                              : 
**          Counter                                        : TPM0_CNT
**          Interrupt service/event                        : Disabled
**          Period                                         : 20 ms
**          Starting pulse width                           : 1.5 ms
**          Initial polarity                               : low
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnEnd                                      : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**          Referenced components                          : 
**            Linked component                             : SERVO1_TimerUnit
**     Contents    :
**         Init       - LDD_TDeviceData* PwmLdd1_Init(LDD_TUserData *UserDataPtr);
**         Enable     - LDD_TError PwmLdd1_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable    - LDD_TError PwmLdd1_Disable(LDD_TDeviceData *DeviceDataPtr);
**         SetRatio16 - LDD_TError PwmLdd1_SetRatio16(LDD_TDeviceData *DeviceDataPtr, uint16_t Ratio);
**         SetDutyUS  - LDD_TError PwmLdd1_SetDutyUS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);
**         SetDutyMS  - LDD_TError PwmLdd1_SetDutyMS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file PwmLdd1.c
** @version 01.03
** @brief
**          This component implements a pulse-width modulation generator
**          that generates signal with variable duty and fixed cycle.
**          This PWM component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
*/         
/*!
**  @addtogroup PwmLdd1_module PwmLdd1 module documentation
**  @{
*/         

/* MODULE PwmLdd1. */

#include "PwmLdd1.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TDeviceData *LinkedDeviceDataPtr;
  bool EnUser;                         /* Enable/Disable device */
  bool EnMode;                         /* Enable/Disable device in clock configuration */
  uint16_t RatioStore;                 /* Ratio of L-level to H-level */
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} PwmLdd1_TDeviceData;

typedef PwmLdd1_TDeviceData *PwmLdd1_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static PwmLdd1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;

#define CHANNEL 0x00U
/* Internal method prototypes */
static void SetRatio(LDD_TDeviceData *DeviceDataPtr);
/*
** ===================================================================
**     Method      :  PwmLdd1_Init (component PWM_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* PwmLdd1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  PwmLdd1_TDeviceData *DeviceDataPrv;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  DeviceDataPrv->EnUser = TRUE;        /* Set the flag "device enabled" */
  DeviceDataPrv->RatioStore = 0x1333U; /* Ratio after initialization */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_PwmLdd1_ID,DeviceDataPrv);
  DeviceDataPrv->LinkedDeviceDataPtr = SERVO1_TimerUnit_Init((LDD_TUserData *)NULL);
  if (DeviceDataPrv->LinkedDeviceDataPtr == NULL) { /* Is initialization of TimerUnit unsuccessful? */
    /* Unregistration of the device structure */
    PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_PwmLdd1_ID);
    /* Deallocation of the device structure */
    /* {Default RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
    return NULL;                       /* If so, then the PWM initialization is also unsuccessful */
  }
  PwmLdd1_SetClockConfiguration(DeviceDataPrv, Cpu_GetClockConfiguration()); /* Set Initial according clock configuration */
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  PwmLdd1_Enable (component PWM_LDD)
*/
/*!
**     @brief
**         Enables the component - it starts the signal generation.
**         Events may be generated (see SetEventMask).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd1_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  PwmLdd1_TDeviceData *DeviceDataPrv = (PwmLdd1_TDeviceData *)DeviceDataPtr;

  /* Clock configuration test - this test can be disabled by setting the "Ignore clock configuration test"
     property to the "yes" value in the "Configuration inspector" */
  if (!DeviceDataPrv->EnMode) {        /* Is the device disabled in the actual clock configuration? */
    return ERR_SPEED;                  /* If yes then error */
  }
  if (!DeviceDataPrv->EnUser) {        /* Is the device disabled by user? */
    DeviceDataPrv->EnUser = TRUE;      /* If yes then set the flag "device enabled" */
    (void)SERVO1_TimerUnit_Enable(DeviceDataPrv->LinkedDeviceDataPtr); /* Enable TimerUnit */
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  PwmLdd1_Disable (component PWM_LDD)
*/
/*!
**     @brief
**         Disables the component - it stops signal generation and
**         events calling.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd1_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  PwmLdd1_TDeviceData *DeviceDataPrv = (PwmLdd1_TDeviceData *)DeviceDataPtr;

  /* Clock configuration test - this test can be disabled by setting the "Ignore clock configuration test"
     property to the "yes" value in the "Configuration inspector" */
  if (!DeviceDataPrv->EnMode) {        /* Is the device disabled in the actual clock configuration? */
    return ERR_SPEED;                  /* If yes then error */
  }
  if (DeviceDataPrv->EnUser) {         /* Is the device enabled by user? */
    DeviceDataPrv->EnUser = FALSE;     /* If yes then set the flag "device enabled" */
   (void)SERVO1_TimerUnit_Disable(DeviceDataPrv->LinkedDeviceDataPtr); /* Disable TimerUnit component */
   (void)SERVO1_TimerUnit_ResetCounter(DeviceDataPrv->LinkedDeviceDataPtr); /* Reset counter */
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  PwmLdd1_SetRatio16 (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as a 16-bit unsigned integer number. 0 - FFFF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         [Starting pulse width] property. 
**         Note: Calculated duty depends on the timer possibilities and
**         on the selected period.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Ratio           - Ratio to set. 0 - 65535 value is
**                           proportional to ratio 0 - 100%
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd1_SetRatio16(LDD_TDeviceData *DeviceDataPtr, uint16_t Ratio)
{
  PwmLdd1_TDeviceData *DeviceDataPrv = (PwmLdd1_TDeviceData *)DeviceDataPtr;

  /* Clock configuration test - this test can be disabled by setting the "Ignore clock configuration test"
     property to the "yes" value in the "Configuration inspector" */
  if (!DeviceDataPrv->EnMode) {        /* Is the device disabled in the actual clock configuration? */
    return ERR_SPEED;                  /* If yes then error */
  }
  DeviceDataPrv->RatioStore = Ratio;   /* Store new value of the ratio */
  SetRatio(DeviceDataPtr);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  PwmLdd1_SetDutyUS (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets the new duty value of the output signal.
**         The duty is expressed in microseconds as a 16-bit unsigned
**         integer number. The method is available only if it is not
**         selected list of predefined values in [Starting pulse width]
**         property.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Time            - Duty to set [in microseconds]
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_MATH - Overflow during evaluation
**                           ERR_PARAM_RANGE - Parameter out of range
*/
/* ===================================================================*/
LDD_TError PwmLdd1_SetDutyUS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time)
{
  PwmLdd1_TDeviceData *DeviceDataPrv = (PwmLdd1_TDeviceData *)DeviceDataPtr;
  LDD_TimerUnit_Tfloat rtval;          /* Result of multiplication */

  /* Clock configuration test - this test can be disabled by setting the "Ignore clock configuration test"
     property to the "yes" value in the "Configuration inspector" */
  if (!DeviceDataPrv->EnMode) {        /* Is the device disabled in the actual clock configuration? */
    return ERR_SPEED;                  /* If yes then error */
  }
  /* Time test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Time > 0x4E20U) {                /* Is the given value out of range? */
    return ERR_PARAM_RANGE;            /* If yes then error */
  }
  rtval = Time * 3.2768F;              /* Multiply given value and actual clock configuration coefficient */
  if (rtval > 0xFFFFUL) {              /* Is the result greater than 65535 ? */
    DeviceDataPrv->RatioStore = 0xFFFFU; /* If yes then use maximal possible value */
  }
  else {
    DeviceDataPrv->RatioStore = (uint16_t)rtval;
  }
  SetRatio(DeviceDataPtr);             /* Calculate and set up new appropriate values of the duty register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PwmLdd1_SetDutyMS (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets the new duty value of the output signal.
**         The duty is expressed in milliseconds as a 16-bit unsigned
**         integer number. The method is available only if it is not
**         selected list of predefined values in [Starting pulse width]
**         property.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Time            - Duty to set [in milliseconds]
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_MATH - Overflow during evaluation
**                           ERR_PARAM_RANGE - Parameter out of range
*/
/* ===================================================================*/
LDD_TError PwmLdd1_SetDutyMS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time)
{
  PwmLdd1_TDeviceData *DeviceDataPrv = (PwmLdd1_TDeviceData *)DeviceDataPtr;
  LDD_TimerUnit_Tfloat rtval;          /* Result of multiplication */

  /* Clock configuration test - this test can be disabled by setting the "Ignore clock configuration test"
     property to the "yes" value in the "Configuration inspector" */
  if (!DeviceDataPrv->EnMode) {        /* Is the device disabled in the actual clock configuration? */
    return ERR_SPEED;                  /* If yes then error */
  }
  /* Time test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Time > 0x14U) {                  /* Is the given value out of range? */
    return ERR_PARAM_RANGE;            /* If yes then error */
  }
  rtval = Time * 3276.8F;              /* Multiply given value and actual clock configuration coefficient */
  if (rtval > 0xFFFFUL) {              /* Is the result greater than 65535 ? */
    DeviceDataPrv->RatioStore = 0xFFFFU; /* If yes then use maximal possible value */
  }
  else {
    DeviceDataPrv->RatioStore = (uint16_t)rtval;
  }
  SetRatio(DeviceDataPtr);             /* Calculate and set up new appropriate values of the duty register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SetRatio (component PWM_LDD)
**
**     Description :
**         This method calculates new value of duty compare register from 
**         variable RatioStore.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetRatio(LDD_TDeviceData *DeviceDataPtr)
{
  PwmLdd1_TDeviceData *DeviceDataPrv = (PwmLdd1_TDeviceData*)DeviceDataPtr;
  uint16_t Period;
  uint16_t Duty;

  (void)SERVO1_TimerUnit_GetPeriodTicks(DeviceDataPrv->LinkedDeviceDataPtr, &Period);
  if (Period == 0U) {
    Duty = DeviceDataPrv->RatioStore;
  }
  else {
    Duty = (uint16_t)((((uint32_t)(Period) * DeviceDataPrv->RatioStore) + 0x8000) >> 0x10);
  }
  (void)SERVO1_TimerUnit_SetOffsetTicks(DeviceDataPrv->LinkedDeviceDataPtr, CHANNEL, Duty);
}
/*
** ===================================================================
**     Method      :  PwmLdd1_SetClockConfiguration (component PWM_LDD)
**
**     Description :
**         This method changes the clock configuration. During a clock 
**         configuration change the component changes it's setting 
**         immediately upon a request.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PwmLdd1_SetClockConfiguration(LDD_TDeviceData *DeviceDataPtr, LDD_TClockConfiguration ClockConfiguration)
{
  PwmLdd1_TDeviceData *DeviceDataPrv = (PwmLdd1_TDeviceData *)DeviceDataPtr;

  switch (ClockConfiguration) {
    case CPU_CLOCK_CONFIG_0:
      DeviceDataPrv->EnMode = TRUE;    /* Set the flag "device enabled" in the actual clock configuration */
      break;
    default:
      DeviceDataPrv->EnMode = FALSE;   /* Set the flag "device disabled" in the actual clock configuration */
      break;
  }
}

/* END PwmLdd1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
