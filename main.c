/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"

/* Global variables **********************************************************/
int speed = 0;
volatile int rpm = 0;
volatile int rpm_step = -250;
volatile bool engine_running = false;
volatile bool blink_on = false;

void can_send_engine_on(void)
{

	/* TO-DO: your task implementations **************************************/

	// set payload bytes, if necessary
	// CAN_0.BUF[...].DATA.B[...] = ...;

	// write the correct CODE value to this register to instruct the CAN controller to transmit the CAN message
	CAN_0.BUF[8].CS.B.CODE = 0xCU;
	LED_Tx = !LED_Tx;
}

void can_send_speed(int value)
{
	/* TO-DO: your task implementations **************************************/
	CAN_0.BUF[9].DATA.B[0] = value;
	CAN_0.BUF[9].CS.B.CODE = 0xCU;
}

void can_send_rpm(int value)
{
	/* TO-DO: your task implementations **************************************/
	CAN_0.BUF[10].DATA.B[0] = value & 0xFF;
	CAN_0.BUF[10].DATA.B[1] = (value >> 8) & 0xFF;
	CAN_0.BUF[10].CS.B.CODE = 0xCU;
}

void can_send_lights(void)
{
	uint8_t lights = 0;
	if (blink_on)
	{

		if (SW2)
		{
			lights = lights | 0x01; /* Left indicator */
		}

		if (SW1)
		{
			lights = lights | 0x02; /* Right indicator */
		}
	}

	LED_U1 = (lights & 0x01) != 0;
	LED_U3 = (lights & 0x02) != 0;
	/* Both switches have now been checked. */
	CAN_0.BUF[11].DATA.B[0] = lights;
	CAN_0.BUF[11].CS.B.CODE = 0xCU;
}

void can_send(void)
{

	/* TO-DO: your task implementations **************************************/

	/*************************************************************************/
}

/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void)
{
	/* peripherals initialization */
	peripheralsInit();

	/* TO-DO: your task implementations **************************************/

	/* Configure and start timer channels */
	/* PIT timer channel 1, period = 1000 ms */
	PIT_ConfigureTimer(2, 100); /* Channel 2, period 100 ms */
	PIT_StartTimer(2);			/* Enable the timer */
	/*************************************************************************/

	/* main program */
	while (1)
	{
		/* System function */
		systemFunction();

		/* TO-DO: your task implementations **********************************/

		can_send();

		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}

/*
 * @brief	CAN receive interrupt
 *
 * @param   CANDriver   canp	The CAN controller which received a message
 * @param	CANRxFrame	crfp	The message which was received
 * @retval	void
 */
void can_receive(CANRxFrame crfp)
{
	LED_Rx = !LED_Rx;
	if (crfp.IDE == CAN_IDE_STD) // a standard message frame has been received
	{
		/* TO-DO: your task implementations ******************************/
		if (crfp.SID == 0x11)
		{
			LED_U1 = !LED_U1;

			if (!engine_running)
			{
				rpm = 8000;
				rpm_step = -250;
				engine_running = true;

				PIT_ConfigureTimer(1, 1000);
				PIT_StartTimer(1);

				blink_on = true;

				PIT_ConfigureTimer(3, 500);
				PIT_StartTimer(3);
			}

			LED_P = 1;
		}
		else if (crfp.SID == 0x10)
		{
			LED_P = 0;
			engine_running = false;
			PIT_StopTimer(1);

			PIT_StopTimer(3);
			blink_on = false;

			LED_U1 = 0;
			LED_U3 = 0;
		}
	}
}

/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_1(void)
{
	/* TO-DO: your task implementations **************************************/
	PIT.CHANNEL[1].TFLG.R = 1U;

	if (engine_running)
	{
		rpm += rpm_step;

		if (rpm == 0)
		{
			rpm_step = 250;
		}
		else if (rpm == 8000)
		{
			rpm_step = -250;
		}
	}
}

/*
 * @brief	PIT timer channel 2 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_2(void)
{
	/* TO-DO: your task implementations **************************************/
	PIT.CHANNEL[2].TFLG.R = 1U; /* Acknowledge the timer event */
	if (engine_running)
	{
		speed = (POT * 240) / 4095;

		can_send_engine_on();
		can_send_speed(speed);
		can_send_rpm(rpm);
		can_send_lights();
	}
}

/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void)
{
	/* TO-DO: your task implementations **************************************/
	PIT.CHANNEL[3].TFLG.R = 1U;

	if (engine_running)
	{
		blink_on = !blink_on;
	}
}
