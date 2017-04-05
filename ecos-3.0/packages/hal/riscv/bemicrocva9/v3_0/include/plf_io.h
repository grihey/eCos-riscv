/// Syntacore SCR* framework
///
/// @copyright (C) Syntacore 2015-2016. All rights reserved.
/// @author mn-sc
///
/// @brief platform specific configurations
//

//#include "plf_c5_sdk.h"

#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H


#ifndef PLF_UART_BAUDRATE
#define PLF_UART_BAUDRATE 115200
#endif

#define PLF_UART0_16550
#define PLF_UART0_BASE   0x7fff1200

// RTC timebase: 1 MHZ
#define PLF_RTC_TIMEBASE 1000000
// sys clk freq, 25 MHz
#define PLF_SYS_FREQ     20000000
// cpu clk freq
#define PLF_CPU_FREQ     PLF_SYS_FREQ

#endif // PLATFORM_CONFIG_H
