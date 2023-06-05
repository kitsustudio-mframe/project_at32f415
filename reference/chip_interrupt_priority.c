/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "at32f415/chip_arm.h"
/* ****************************************************************************************
 * Macro
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"

/* ****************************************************************************************
 * Type/Structure
 */ 
typedef struct _nvic_priority_level_t{
  IRQn_Type irq;
  uint8_t priority;
}nvic_priority_level_t;

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Public
 */

/* ****************************************************************************************
 * Private
 */
const static nvic_priority_level_t nvic_priority_level[] = {
  {WWDT_IRQn,               15},
  {PVM_IRQn,                15},
  {TAMP_STAMP_IRQn,         15},
  {ERTC_WKUP_IRQn,          15},
  {FLASH_IRQn,              15},
  {CRM_IRQn,                15},
  {EXINT0_IRQn,             15},
  {EXINT1_IRQn,             15},
  {EXINT2_IRQn,             15},
  {EXINT3_IRQn,             15},
  {EXINT4_IRQn,             15},
  {DMA1_Channel1_IRQn,      15},
  {DMA1_Channel2_IRQn,      15},
  {DMA1_Channel3_IRQn,      15},
  {DMA1_Channel4_IRQn,      15},
  {DMA1_Channel5_IRQn,      15},
  {DMA1_Channel6_IRQn,      15},
  {DMA1_Channel7_IRQn,      15},
  {ADC1_IRQn,               15},
  {CAN1_TX_IRQn,            15},
  {CAN1_RX0_IRQn,           15},
  {CAN1_RX1_IRQn,           15},
  {CAN1_SE_IRQn,            15},
  {EXINT9_5_IRQn,           15},
  {TMR1_BRK_TMR9_IRQn,      15},
  {TMR1_OVF_TMR10_IRQn,     15},
  {TMR1_TRG_HALL_TMR11_IRQn,15},
  {TMR1_CH_IRQn,            15},
  {TMR2_GLOBAL_IRQn,        15},
  {TMR3_GLOBAL_IRQn,        15},
  {TMR4_GLOBAL_IRQn,        15},
  {I2C1_EVT_IRQn,           15},
  {I2C1_ERR_IRQn,           15},
  {I2C2_EVT_IRQn,           15},
  {I2C2_ERR_IRQn,           15},
  {SPI1_IRQn,               15},
  {SPI2_IRQn,               15},
  {USART1_IRQn,             15},
  {USART2_IRQn,             15},
  {USART3_IRQn,             15},
  {EXINT15_10_IRQn,         15},
  {ERTCAlarm_IRQn,          15},
  {OTGFS1_WKUP_IRQn,        15},
  {SDIO1_IRQn,              15},
  {TMR5_GLOBAL_IRQn,        15},
  {UART4_IRQn,              15},
  {UART5_IRQn,              15},
  {DMA2_Channel1_IRQn,      15},
  {DMA2_Channel2_IRQn,      15},
  {DMA2_Channel3_IRQn,      15},
  {DMA2_Channel4_5_IRQn,    15},
  {OTGFS1_IRQn,             15},
  {CMP1_IRQn,               15},
  {CMP2_IRQn,               15},
  {DMA2_Channel6_7_IRQn,    15},
};
/* ****************************************************************************************
 * Inline Function
 */
 
/* ****************************************************************************************
 * Private Function
 */ 
 
/* ****************************************************************************************
 * Public Function
 */

/**
 *
 */
void core_at32f415_interrupt_priority(void){
	int i;
	int count = (sizeof(nvic_priority_level) / sizeof(nvic_priority_level_t));
	
	for(i=0; i<count; i++){
		NVIC_SetPriority(nvic_priority_level[i].irq, nvic_priority_level[i].priority);
	}
}

#pragma clang diagnostic pop

/* *****************************************************************************************
 *    End of file
 */
