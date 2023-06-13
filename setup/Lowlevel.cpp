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
#include "chip.h"
#include "mframe.h"
#include "rtos.h"

//-----------------------------------------------------------------------------------------
#include "stdio.h"
#include "stdlib.h"

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------
using namespace mframe::lang;
using namespace mframe::hal;
using namespace chip;
using namespace chip::core;
using chip::core::CoreHardwareInfo;
using cmsisrtos::CmsisrtosKernel;
using mframe::ctrl::SerialPort;
using mframe::hal::usart::USART;
using mframe::lang::managerment::Stacker;
using mframe::lang::managerment::SystemConfig;

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Variable
 */

//-----------------------------------------------------------------------------------------
struct LowlevelSystem {
  struct {
    uint32_t space[(sizeof(Stacker) + 3) / 4];
    uint32_t buffer[27 * 256];
    Stacker* object;
  } allocator;

  struct {
    uint32_t space[(sizeof(CmsisrtosKernel) + 3) / 4];
    CmsisrtosKernel* object;
  } kernel;

  struct {
    uint32_t space[(sizeof(CoreHardwareInfo) + 3) / 4];
    CoreHardwareInfo* object;
  } hardwareInfo;

} static lowlevelSystem;

//-----------------------------------------------------------------------------------------
struct LowlevelConsole {
  struct {
    uint32_t space[(sizeof(CoreUSART) + 3) / 4];
    CoreUSART* object;
  } usart;

  struct {
    uint32_t space[(sizeof(SerialPort) + 3) / 4];
    SerialPort* object;
  } serialPort;

} static lowlevelConsole;

/* ****************************************************************************************
 * Method
 */

//-----------------------------------------------------------------------------------------
static void lowlevelChipSetup(void) {
  Core::defaultSetup();
  return;
}

//-----------------------------------------------------------------------------------------
static void lowlevelSystemSetup(void) {
  lowlevelSystem.allocator.object = new (lowlevelSystem.allocator.space)
      Stacker(lowlevelSystem.allocator.buffer, sizeof(lowlevelSystem.allocator.buffer));

  lowlevelSystem.kernel.object = new (lowlevelSystem.kernel.space)
      cmsisrtos::CmsisrtosKernel(chip::misc::MISC::systemReset);

  lowlevelSystem.hardwareInfo.object = new (lowlevelSystem.hardwareInfo.space)
      CoreHardwareInfo();
  return;
}

//-----------------------------------------------------------------------------------------
static void lowlevelConsoleSetup(void) {
  Core::gpioc.setFunction(12, false);
  lowlevelConsole.usart.object = new (lowlevelConsole.usart.space)
      CoreUSART(chip::usart::UART5);

  lowlevelConsole.serialPort.object = new (lowlevelConsole.serialPort.space)
      mframe::ctrl::SerialPort(*lowlevelConsole.usart.object);
  
  lowlevelConsole.usart.object->init();
  lowlevelConsole.serialPort.object->open();
  lowlevelConsole.serialPort.object->setBaudrate(256000);
  return;
}

//-----------------------------------------------------------------------------------------

void lowlevel(void) {
  lowlevelChipSetup();
  lowlevelSystemSetup();
  lowlevelConsoleSetup();

  SystemConfig config;

  config.system.allocator = lowlevelSystem.allocator.object;
  config.system.hardwareInfo = lowlevelSystem.hardwareInfo.object;
  config.system.kernel = lowlevelSystem.kernel.object;

  config.svchost.stackSize = 1024;
  config.svchost.taskQuantity = 32;

  config.console.inputStream = &lowlevelConsole.serialPort.object->getInputStream();
  config.console.outputStream = &lowlevelConsole.serialPort.object->getOutputStream();
  config.console.sizeScanner = 64;
  config.console.sizePrintBiffer = 256;

  System::setup(config);
}

/* ****************************************************************************************
 * End of file
 */
