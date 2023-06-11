/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mframe.h"
#include "chip.h"
#include "rtos.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Using
 */  

//-----------------------------------------------------------------------------------------
using namespace mframe::lang;
using namespace mframe::hal;
using namespace chip;
using namespace chip::core;
//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Variable
 */
static cmsisrtos::CmsisrtosConfigDefault *systemCmsisrtosConfigDefault;
static cmsisrtos::CmsisrtosKernel *systemCmsisrtosKernel;
static mframe::hal::usart::USART* coreUsart;
static mframe::ctrl::SerialPort* coreSerialPort;

/* ****************************************************************************************
 * Method
 */


/**
 * @brief 
 * 
 */
void lowlevel_basicInit(void){
  Core::setSystemCoreClock(144);
  Core::iomux.init();
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::gpiod.init();
  Core::gpiof.init();
  Core::iomux.remapSWDIO(CoreIomux::MapSWDIO::JTAGDISABLE);
}

void lowlevel_consloe(void){
  Core::gpioc.setFunction(12, false);
  coreUsart = new CoreUSART(chip::usart::UART5);
  coreSerialPort = new mframe::ctrl::SerialPort(*coreUsart);
  coreSerialPort->open();
  coreSerialPort->setBaudrate(256000);
}

void lowlevel_kernel(void){
  systemCmsisrtosConfigDefault = new cmsisrtos::CmsisrtosConfigDefault();
  systemCmsisrtosConfigDefault->setInputStream(&coreSerialPort->getInputStream());
  systemCmsisrtosConfigDefault->setOutputStream(&coreSerialPort->getOutputStream());
  systemCmsisrtosConfigDefault->setClock(Core::getSystemCoreClock());
  
  systemCmsisrtosKernel = new cmsisrtos::CmsisrtosKernel(*systemCmsisrtosConfigDefault);
  
  System::setup(*systemCmsisrtosKernel, 1024, 6144);
}

/**
 * @brief 
 * 
 */
void lowlevel(void){
  lowlevel_basicInit();
  lowlevel_consloe();
  lowlevel_kernel();
}


 
/* ****************************************************************************************
 * End of file
 */ 
