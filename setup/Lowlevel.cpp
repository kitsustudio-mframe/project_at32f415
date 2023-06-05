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
#include "lang/package-info.h"
#include "hal/package-info.h"
#include "at32f415/package-info.h"
#include "cmsisrtos/package-info.h"
#include "ctrl/package-info.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Using
 */  

//-----------------------------------------------------------------------------------------
using namespace lang;
using namespace hal;
using namespace at32f415;
using namespace at32f415::core;
//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Extern
 */
extern "C" void core_at32f415_interrupt_priority(void);

/* ****************************************************************************************
 * Variable
 */
static cmsisrtos::CmsisrtosConfigDefault *systemCmsisrtosConfigDefault;
static cmsisrtos::CmsisrtosKernel *systemCmsisrtosKernel;
static hal::usart::USART* coreUsart;
static ctrl::SerialPort* coreSerialPort;

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
  coreUsart = new at32f415::core::CoreUSART(at32f415::usart::UART5);
  coreSerialPort = new ctrl::SerialPort(*coreUsart);
  coreSerialPort->open();
  coreSerialPort->setBaudrate(256000);
}

void lowlevel_kernel(void){
  systemCmsisrtosConfigDefault = new cmsisrtos::CmsisrtosConfigDefault();
  systemCmsisrtosConfigDefault->setInputStream(&coreSerialPort->getInputStream());
  systemCmsisrtosConfigDefault->setOutputStream(&coreSerialPort->getOutputStream());
  systemCmsisrtosConfigDefault->setClock(Core::getSystemCoreClock());
  
  systemCmsisrtosKernel = new cmsisrtos::CmsisrtosKernel(*systemCmsisrtosConfigDefault);
  
  System::setup(*systemCmsisrtosKernel);
}

/**
 * @brief 
 * 
 */
void lowlevel(void){
  lowlevel_basicInit();
  lowlevel_consloe();
  lowlevel_kernel();
  core_at32f415_interrupt_priority();
}


 
/* ****************************************************************************************
 * End of file
 */ 
