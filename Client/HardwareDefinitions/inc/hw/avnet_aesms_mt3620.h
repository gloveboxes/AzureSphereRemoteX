/* Copyright (c) Microsoft Corporation. All rights reserved.
   Licensed under the MIT License. */

// This header lists the available peripherals for the Avnet AES-MS-MT3620
// and provides the header definition and application manifest values required to use them.

// This file is autogenerated from ../../avnet_aesms_mt3620.json.  Do not edit it directly.

#pragma once
#include "hw/mt3620.h"

// AES-MS-MT3620 pin 5 exposes GPIO 0. Pin shared with ADC Controller 0.
#define AVNET_AESMS_PIN5_GPIO0 MT3620_GPIO0

// AES-MS-MT3620 pin 6 exposes GPIO 1. Pin shared with ADC Controller 0.
#define AVNET_AESMS_PIN6_GPIO1 MT3620_GPIO1

// AES-MS-MT3620 pin 7 exposes GPIO 2. Pin shared with ADC Controller 0.
#define AVNET_AESMS_PIN7_GPIO2 MT3620_GPIO2

// AES-MS-MT3620 pin 8 exposes GPIO 4. Pin shared with ADC Controller 1.
#define AVNET_AESMS_PIN8_GPIO4 MT3620_GPIO4

// AES-MS-MT3620 pin 9 exposes GPIO 5. Pin shared with ADC Controller 1.
#define AVNET_AESMS_PIN9_GPIO5 MT3620_GPIO5

// AES-MS-MT3620 pin 10 exposes GPIO 6. Pin shared with ADC Controller 1.
#define AVNET_AESMS_PIN10_GPIO6 MT3620_GPIO6

// AES-MS-MT3620 pin 11 exposes GPIO 8. Pin shared with ADC Controller 2.
#define AVNET_AESMS_PIN11_GPIO8 MT3620_GPIO8

// AES-MS-MT3620 pin 12 exposes GPIO 9. Pin shared with ADC Controller 2.
#define AVNET_AESMS_PIN12_GPIO9 MT3620_GPIO9

// AES-MS-MT3620 pin 13 exposes GPIO 10. Pin shared with ADC Controller 2.
#define AVNET_AESMS_PIN13_GPIO10 MT3620_GPIO10

// AES-MS-MT3620 pin 14 exposes GPIO 12.
#define AVNET_AESMS_PIN14_GPIO12 MT3620_GPIO12

// AES-MS-MT3620 pin 15 exposes GPIO 13.
#define AVNET_AESMS_PIN15_GPIO13 MT3620_GPIO13

// AES-MS-MT3620 pin 16 exposes GPIO 16.
#define AVNET_AESMS_PIN16_GPIO16 MT3620_GPIO16

// AES-MS-MT3620 pin 17 exposes GPIO 17.
#define AVNET_AESMS_PIN17_GPIO17 MT3620_GPIO17

// AES-MS-MT3620 pin 18 exposes GPIO 26. Pin shared with SPI0 and UART0.
#define AVNET_AESMS_PIN18_GPIO26 MT3620_GPIO26

// AES-MS-MT3620 pin 19 exposes GPIO 27. Pin shared with ISU0.
#define AVNET_AESMS_PIN19_GPIO27 MT3620_GPIO27

// AES-MS-MT3620 pin 20 exposes GPIO 28. Pin shared with ISU0.
#define AVNET_AESMS_PIN20_GPIO28 MT3620_GPIO28

// AES-MS-MT3620 pin 21 exposes GPIO 29. Pin shared with UART0 and SPI0.
#define AVNET_AESMS_PIN21_GPIO29 MT3620_GPIO29

// AES-MS-MT3620 pin 22 exposes GPIO 31. Pin shared with SPI1 and UART1.
#define AVNET_AESMS_PIN22_GPIO31 MT3620_GPIO31

// AES-MS-MT3620 pin 23 exposes GPIO 32. Pin shared with ISU1.
#define AVNET_AESMS_PIN23_GPIO32 MT3620_GPIO32

// AES-MS-MT3620 pin 24 exposes GPIO 33. Pin shared with ISU1.
#define AVNET_AESMS_PIN24_GPIO33 MT3620_GPIO33

// AES-MS-MT3620 pin 25 exposes GPIO 34. Pin shared with SPI1 and UART1.
#define AVNET_AESMS_PIN25_GPIO34 MT3620_GPIO34

// AES-MS-MT3620 pin 26 exposes GPIO 35. Pin shared with SPI1.
#define AVNET_AESMS_PIN26_GPIO35 MT3620_GPIO35

// AES-MS-MT3620 pin 27 exposes GPIO 37. Pin shared with I2C2.
#define AVNET_AESMS_PIN27_GPIO37 MT3620_GPIO37

// AES-MS-MT3620 pin 28 exposes GPIO 38. Pin shared with I2C2.
#define AVNET_AESMS_PIN28_GPIO38 MT3620_GPIO38

// AES-MS-MT3620 pin 29 exposes GPIO 41. Pin shared with ADC Controller 0.
#define AVNET_AESMS_PIN29_GPIO41 MT3620_GPIO41

// AES-MS-MT3620 pin 30 exposes GPIO 42. Pin shared with ADC Controller 0.
#define AVNET_AESMS_PIN30_GPIO42 MT3620_GPIO42

// AES-MS-MT3620 pin 31 exposes GPIO 43. Pin shared with ADC Controller 0.
#define AVNET_AESMS_PIN31_GPIO43 MT3620_GPIO43

// AES-MS-MT3620 PWM CONTROLLER 0: channel 0 on pin 5, channel 1 on pin 6, channel 2 on pin 7. Pins for this controller are shared with AVNET_AESMS_PIN5_GPIO0, AVNET_AESMS_PIN6_GPIO1, and AVNET_AESMS_PIN7_GPIO2. If this PWM controller is requested, none of these GPIOs can be used.
#define AVNET_AESMS_PWM_CONTROLLER0 MT3620_PWM_CONTROLLER0

// AES-MS-MT3620 PWM CONTROLLER 1: channel 0 on pin 8, channel 1 on pin 9, channel 2 on pin 10. Pins for this controller are shared with AVNET_AESMS_PIN8_GPIO4, AVNET_AESMS_PIN9_GPIO5, AVNET_AESMS_PIN10_GPIO6. If this PWM controller is requested, none of these GPIOs can be used.
#define AVNET_AESMS_PWM_CONTROLLER1 MT3620_PWM_CONTROLLER1

// AES-MS-MT3620 PWM CONTROLLER 2: channel 0 on pin 11, channel 1 on pin 12, channel 2 on pin 13. Pins for this controller are shared with AVNET_AESMS_PIN11_GPIO8, AVNET_AESMS_PIN12_GPIO9, and AVNET_AESMS_PIN13_GPIO10. If this PWM controller is requested, none of these GPIOs can be used.
#define AVNET_AESMS_PWM_CONTROLLER2 MT3620_PWM_CONTROLLER2

// AES-MS-MT3620 ADC CONTROLLER 0: channel 0 on pin 29, channel 1 on pin 30, channel 2 on pin 31. Pins for this controller are shared with AVNET_AESMS_PIN29_GPIO41, AVNET_AESMS_PIN30_GPIO42, and AVNET_AESMS_PIN31_GPIO43. If this ADC controller is requested, none of these GPIOs can be used.
#define AVNET_AESMS_ADC_CONTROLLER0 MT3620_ADC_CONTROLLER0

// AES-MS-MT3620 ISU 0 configured as UART, pin 20 (RX), pin 18 (TX), pin 21 (CTS), pin 19 (RTS).
#define AVNET_AESMS_ISU0_UART MT3620_ISU0_UART

// AES-MS-MT3620 ISU 0 configured as SPI, pin 20 (MISO), pin 18 (SCLK), pin 21 (CSA), pin 19 (MOSI).
#define AVNET_AESMS_ISU0_SPI MT3620_ISU0_SPI

// AES-MS-MT3620 ISU 0 configured as I2C,  pin 20 (SDA) and pin 18 (SCL).
#define AVNET_AESMS_ISU0_I2C MT3620_ISU0_I2C

// AES-MS-MT3620 ISU 1 configured as UART, pin 24 (RX), pin 22 (TX), pin 25 (CTS), pin 23 (RTS).
#define AVNET_AESMS_ISU1_UART MT3620_ISU1_UART

// AES-MS-MT3620 ISU 1 configured as SPI, pin 24 (MISO), pin 22 (SCLK), pin 25 (CSA), pin 23 (MOSI) and pin 26 (CSB).
#define AVNET_AESMS_ISU1_SPI MT3620_ISU1_SPI

// AES-MS-MT3620 ISU 1 configured as I2C,  pin 24 (SDA) and pin 23 (SCL).
#define AVNET_AESMS_ISU1_I2C MT3620_ISU1_I2C

// AES-MS-MT3620 ISU 2 configured as I2C,  pin 28 (SDA) and pin 27 (SCL).
#define AVNET_AESMS_ISU2_I2C MT3620_ISU2_I2C

