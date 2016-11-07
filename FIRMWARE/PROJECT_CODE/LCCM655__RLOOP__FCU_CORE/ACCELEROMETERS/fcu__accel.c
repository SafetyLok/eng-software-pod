/**
 * @file		FCU__ACCEL.C
 * @brief		Accelerometer Subsystem
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__ACCELEROMETER
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_ACCEL__Init(void)
{


}


/***************************************************************************//**
 * @brief
 * Process any Throttle tasks
 * 
 */
void vFCU_ACCEL__Process(void)
{


}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

