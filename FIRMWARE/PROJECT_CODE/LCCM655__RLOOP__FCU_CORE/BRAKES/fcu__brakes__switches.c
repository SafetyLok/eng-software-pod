/**
 * @file		FCU__BRAKES__SWITCHES.C
 * @brief		Switch interface for the brakes.
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
 * @addtogroup FCU__BRAKES__SWITCHES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init the brake switches modules
 * 
 * @st_funcMD5		BADA00E37708032B41CF323DF1117D6D
 * @st_funcID		LCCM655R0.FILE.008.FUNC.001
 */
void vFCU_BRAKES_SW__Init(void)
{
	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 0U;
	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 0U;
	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 0U;
	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 0U;
	sFCU.sBrakes[FCU_BRAKE__LEFT].u8BrakeSWErr = 0U;
	sFCU.sBrakes[FCU_BRAKE__RIGHT].u8BrakeSWErr = 0U;

	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].eSwitchState = SW_STATE__UNKNOWN;
	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].eSwitchState = SW_STATE__UNKNOWN;
	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].eSwitchState = SW_STATE__UNKNOWN;
	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].eSwitchState = SW_STATE__UNKNOWN;

	#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
		sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeenCnt = 0U;
		sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeenCnt = 0U;
		sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeenCnt = 0U;
		sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeenCnt = 0U;
	#endif

	//TODO: set flag if interrupt was seen
}

/***************************************************************************//**
 * @brief
 * Process the brake swtich tasks
 * 
 * @st_funcMD5		24FC7CAFDEFC3718FA50379B661CA39A
 * @st_funcID		LCCM655R0.FILE.008.FUNC.002
 */
void vFCU_BRAKES_SW__Process(void)
{

	Luint8 u8Brake;
	Luint8 u8Switch;

	for(u8Brake = 0U; u8Brake < (Luint8)FCU_BRAKE__MAX_BRAKES; u8Brake++)
	{
		for(u8Switch = 0U; u8Switch < (Luint8)BRAKE_SW__MAX_SWITCHES; u8Switch++)
		{
			if(sFCU.sBrakes[(Luint8)u8Brake].sLimits[(Luint8)u8Switch].u8EdgeSeen == 1U)
			{
				//read and save the switch status
				sFCU.sBrakes[(Luint8)u8Brake].sLimits[(Luint8)u8Switch].eSwitchState = eFCU_BRAKES_SW__Get_Switch((E_FCU__BRAKE_INDEX_T)u8Brake, (E_FCU__BRAKE_LIMSW_INDEX_T)u8Switch);

				//clear the flag
				sFCU.sBrakes[(Luint8)u8Brake].sLimits[(Luint8)u8Switch].u8EdgeSeen = 0U;

			}

		}
		//if both switches is closed, then flag fault
		if (sFCU.sBrakes[(Luint8)u8Brake].sLimits[(Luint8)BRAKE_SW__EXTEND].eSwitchState == SW_STATE__CLOSED && sFCU.sBrakes[(Luint8)u8Brake].sLimits[BRAKE_SW__RETRACT].eSwitchState == SW_STATE__CLOSED)
		{
			//set fault flag
			sFCU.sBrakes[(Luint8)u8Brake].u8BrakeSWErr = 1U;
		}
	}

	//if an edge has occurred, sample the switches and save the switch state.

}

/***************************************************************************//**
 * @brief
 * Gets the fault flag of a brake limit switches
 *
 * @param[in]		eBrake					The brake index
 * @return				0 = normal, 1 = fault
 * @st_funcMD5		4D64D7EE0EA87E2F031F6F1E830B0400
 * @st_funcID		LCCM655R0.FILE.008.FUNC.003
 */
Luint8 u8FCU_BRAKES_SW__Get_FaultFlag(E_FCU__BRAKE_INDEX_T eBrake)
{
	return sFCU.sBrakes[(Luint8)eBrake].u8BrakeSWErr;
}

/***************************************************************************//**
 * @brief
 * Gets the state of a brake limit swtich
 *
 * @param[in] 			eBrake			The brake, left or right
 * @param[in]			eSwitch			The extend or retract switch
 * @return				Open, Closed or Unknown
 * @st_funcMD5		6DCC43E5255CBEDF8C3D98FEDD691FE3
 * @st_funcID		LCCM655R0.FILE.008.FUNC.004
 */
E_FCU__SWITCH_STATE_T eFCU_BRAKES_SW__Get_Switch(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch)
{
	Luint32 u32Temp;
	Luint8 u8Temp;
	E_FCU__SWITCH_STATE_T eReturn;

	//init our return in place of default switch statements
	eReturn = SW_STATE__UNKNOWN;

	switch(eBrake)
	{
		case FCU_BRAKE__LEFT:

			switch(eSwitch)
			{
				case BRAKE_SW__EXTEND:
					// pin 1 (1U) is mapped to BRAKE_SW_EXTEND SWITCH
					// @TODO: Create a mapping of GIO PINS to respective LIMIT SWITCH
#ifndef WIN32
					u32Temp = u32RM4_GIO__Get_Bit(RM4_GIO__PORT_A, 1U);
#else
					u32Temp = 0U;
#endif
					if(u32Temp == 0U)
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					else
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					break;

				case BRAKE_SW__RETRACT:
					// pin 0 (0U) is mapped to BRAKE_SW_RETRACT SWITCH
					// @TODO: Create a mapping of GIO PINS to respective LIMIT SWITCH
#ifndef WIN32
					u32Temp = u32RM4_GIO__Get_Bit(RM4_GIO__PORT_A, 0U);
#else
					u32Temp = 0U;
#endif
					if(u32Temp == 0U)
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					else
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					break;

				default:
					//handled in init return
					break;
			}//switch(eSwitch)


			break;

		case FCU_BRAKE__RIGHT:
			switch(eSwitch)
			{
				case BRAKE_SW__EXTEND:
#ifndef WIN32
					u8Temp = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 9U);
#else
					u8Temp = 0U;
#endif
					if(u8Temp == 0U)
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					else
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					break;

				case BRAKE_SW__RETRACT:
#ifndef WIN32
					u8Temp = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 22U);
#else
					u8Temp = 0U;
#endif

					if(u8Temp == 0U)
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					else
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					break;

				default:
					//handled in return init
					break;
			}//switch(eSwitch)
			break;

		default:
			//handled in return init
			break;

	}//switch(eBrake)


	return eReturn;
}
#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES

/***************************************************************************//**
 * @brief
 * Brake 0 (Left) Retract switch interrupt handler
 * 
 * @st_funcMD5		A8CE24558C449D064B0F8DAE39F73A2B
 * @st_funcID		LCCM655R0.FILE.008.FUNC.005
 */
void vFCU_BRAKES_SW__Left_SwitchRetract_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
		vSTEPDRIVE_LIMIT__Limit_ISR(0U);

		sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 1U;
		#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
				sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeenCnt++;
		#endif
	#endif
}

/***************************************************************************//**
 * @brief
 * Brake 0 (Left) Extended switch interrupt handler
 * 
 * @st_funcMD5		52D447864E938FED83B81425C24A17E9
 * @st_funcID		LCCM655R0.FILE.008.FUNC.006
 */
void vFCU_BRAKES_SW__Left_SwitchExtend_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
		vSTEPDRIVE_LIMIT__Limit_ISR(0U);

		sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 1U;
		#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
				sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeenCnt++;
		#endif
	#endif
}


/***************************************************************************//**
 * @brief
 * Brake 1 (Right) Retract switch interrupt handler
 * 
 * @st_funcMD5		0F6BA6917B67273329EC9170E241988D
 * @st_funcID		LCCM655R0.FILE.008.FUNC.007
 */
void vFCU_BRAKES_SW__Right_SwitchRetract_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
		vSTEPDRIVE_LIMIT__Limit_ISR(1U);

		sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 1U;
		#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
				sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeenCnt++;
		#endif
	#endif
}

/***************************************************************************//**
 * @brief
 * Brake 1 (Right) Extended switch interrupt handler
 * 
 * @st_funcMD5		57473F00C9D72BDB4147318A86C69A46
 * @st_funcID		LCCM655R0.FILE.008.FUNC.008
 */
void vFCU_BRAKES_SW__Right_SwitchExtend_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
		vSTEPDRIVE_LIMIT__Limit_ISR(1U);

		sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 1U;
		#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
				sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeenCnt++;
		#endif
	#endif
}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

