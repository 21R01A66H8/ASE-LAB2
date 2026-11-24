/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: can.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "can.h"
#include "xpc56el.h"

/*
 * @brief	CAN0 initialization function
 *
 * @param	void
 * @retval	void
 */
void CAN_Init(void)
{
	can_lld_start(&CAND1, &can_config_cfg0);

	/* Buffer 8: Engine On */
	CAN_0.BUF[8].MSG_CS.R = 0;
	CAN_0.BUF[8].MSG_ID.R = 0;

	CAN_0.BUF[8].MSG_CS.B.CODE = 0x8;
	CAN_0.BUF[8].MSG_CS.B.IDE = 1;	  /* Extended */
	CAN_0.BUF[8].MSG_CS.B.SRR = 1;	  /* Required for extended */
	CAN_0.BUF[8].MSG_CS.B.RTR = 0;	  /* Data frame */
	CAN_0.BUF[8].MSG_CS.B.LENGTH = 0; /* No payload */
	CAN_0.BUF[8].MSG_ID.B.EXT_ID = 0xDA0;

	/* Buffer 9: Speed */
	CAN_0.BUF[9].MSG_CS.R = 0;
	CAN_0.BUF[9].MSG_ID.R = 0;

	CAN_0.BUF[9].MSG_CS.B.CODE = 0x8;
	CAN_0.BUF[9].MSG_CS.B.IDE = 0; /* Standard */
	CAN_0.BUF[9].MSG_CS.B.SRR = 0;
	CAN_0.BUF[9].MSG_CS.B.RTR = 0;	  /* Data frame */
	CAN_0.BUF[9].MSG_CS.B.LENGTH = 1; /* One payload byte */
	CAN_0.BUF[9].MSG_ID.B.STD_ID = 0x5A0;

	CAN_0.BUF[10].MSG_CS.R = 0;
	CAN_0.BUF[10].MSG_ID.R = 0;

	CAN_0.BUF[10].MSG_CS.B.CODE = 0x8;
	CAN_0.BUF[10].MSG_CS.B.IDE = 0; /* Standard */
	CAN_0.BUF[10].MSG_CS.B.SRR = 0;
	CAN_0.BUF[10].MSG_CS.B.RTR = 0;	  /* Data frame */
	CAN_0.BUF[10].MSG_CS.B.LENGTH = 2; /* Two payload byte */
	CAN_0.BUF[10].MSG_ID.B.STD_ID = 0x280;

	CAN_0.BUF[11].MSG_CS.R = 0;
	CAN_0.BUF[11].MSG_ID.R = 0;

	CAN_0.BUF[11].MSG_CS.B.CODE = 0x8;
	CAN_0.BUF[11].MSG_CS.B.IDE = 0; /* Standard */
	CAN_0.BUF[11].MSG_CS.B.SRR = 0;
	CAN_0.BUF[11].MSG_CS.B.RTR = 0;	  /* Data frame */
	CAN_0.BUF[11].MSG_CS.B.LENGTH = 1; /* One payload byte */
	CAN_0.BUF[11].MSG_ID.B.STD_ID = 0x470;
}

/*
 * @brief	CAN message transmit function
 *
 * @param	CANTxFrame	txMsg
 * @param	canmbx_t	mbx
 * @retval	void
 */
void CAN_TxMessage(CANTxFrame txMsg, canmbx_t mbx)
{
	// nop
}
