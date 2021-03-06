/**
 * @file		POWER_CORE__FAULTS.C
 * @brief		Fault handing subsystem
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__FAULTS
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

extern struct _strPWRNODE sPWRNODE;


/***************************************************************************//**
 * @brief
 * Init the faults
 * 
 * @st_funcMD5		CBEED90EEFF7D81B70D366D76617977B
 * @st_funcID		LCCM653R0.FILE.020.FUNC.001
 */
void vPWRNODE_FAULTS__Init(void)
{
	//init the top level fault tree
	vFAULTTREE__Init(&sPWRNODE.sFaults.sTopLevel);

}


/***************************************************************************//**
 * @brief
 * Process any faults
 * 
 * @st_funcMD5		19F51A99163A0836D41AACBEED64BD7F
 * @st_funcID		LCCM653R0.FILE.020.FUNC.002
 */
void vPWRNODE_FAULTS__Process(void)
{
	//check our guarding of the main structure
	if(sPWRNODE.u32Guard1 != 0xABCD9876U)
	{
		//fault
		vFAULTTREE__Set_Flag(&sPWRNODE.sFaults.sTopLevel, C_LCCM653__CORE__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sPWRNODE.sFaults.sTopLevel, C_LCCM653__CORE__FAULT_INDEX__01);
	}
	if(sPWRNODE.u32Guard2 != 0x12983465U)
	{
		//fault
		vFAULTTREE__Set_Flag(&sPWRNODE.sFaults.sTopLevel, C_LCCM653__CORE__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sPWRNODE.sFaults.sTopLevel, C_LCCM653__CORE__FAULT_INDEX__01);
	}
}

#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

