#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

void vLCCM655R0_TS_002_TCASE_001(void);


//Function to call the tests for this test specification
void vLCCM655R0_TS_002(void)
{

	//Call the test cases
	vLCCM655R0_TS_002_TCASE_001();

}

//Individual Test Cases can be found below
/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.002.TCASE.001
 * @st_test_desc
 * Todo
 * 
*/
void vLCCM655R0_TS_002_TCASE_001(void)
{
	DEBUG_PRINT("START:LCCM655R0.TS.002.TCASE.001\r\n");

	//Call the target function
	E_FCU__LASER_CONT_INDEX_T eLaser = LASER_CONT__FWD;
	vFCU_LASERCONT_TRKDB__Inc_Marker(eLaser);


	//todo: USER TO ADD
	if(1)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.002.TCASE.001\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.002.TCASE.001\r\n");
	}
	DEBUG_PRINT("END:LCCM655R0.TS.002.TCASE.001\r\n");

}


#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif

