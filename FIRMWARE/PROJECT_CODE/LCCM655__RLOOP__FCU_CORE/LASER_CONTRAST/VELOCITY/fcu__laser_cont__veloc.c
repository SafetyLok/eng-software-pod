/**
 * @file		FCU__LASER_CONT__VELOC.C
 * @brief		Velocity Calculator based on laser contrast sensor distance.
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
 * @addtogroup FCU__LASER_CONTRAST__VELOC
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;


void vFCU_LASERCONT_VELOC__Init(void)
{

	//sFCU.sContrast.sVeloc.u32CurrentVeloc_mms = 0U;;

}



void vFCU_LASERCONT_VELOC__Process(void)
{
	//do nothing.

}

//get the result of the computation
Luint32 u32FCU_LASERCONT_VELOC__Get_CurrentVeloc_mms(void)
{
	return 0; //sFCU.sContrast.sVeloc.u32CurrentVeloc_mms;
}

//compute the veloc
Luint32 u32FCU_LASERCONT_VELOC__Compute(Luint32 u32Distance, Luint64 u64TimeDelta)
{
	Luint64 u64Temp;
	Luint64 u64Temp2;
	//Velocity = Distance * time
	//Distance is in mm
	//Time is in 20ns increments

	u64Temp = (Luint64)u32Distance;
	//make very large so as the math and div works out nice.
	u64Temp *= 1000000000U;

	//compute the time
	u64Temp2 = u64TimeDelta;

	//safety
	#if C_LOCALDEF__LCCM124__RTI_CLK_FREQ != 50U
		#error
	#else
		//convert to ns
		//todo: we could technically shift to div by 2 here and reduce the size of the numerator
		u64Temp2 *= 20U;
	#endif

	//divide
	//math safety
	if (u64Temp2 == 0U)
	{
		u64Temp = 0U;
	}
	else
	{
		u64Temp /= u64Temp2;
	}

	return (Luint32)u64Temp;

}


#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif
