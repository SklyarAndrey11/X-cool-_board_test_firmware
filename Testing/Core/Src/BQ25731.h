/*
 * BQ25731.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Andrey
 
 */

#ifndef INC_BQ25731_H_
#define INC_BQ25731_H_

#define CHARGE_OPTION_0_REG                0x00 /*Charge Option 0*/
#define CHARGE_CURRENT_REG                 0x02 /*7-bit charge current setting LSB 128 mA, Range 0 mA – 16256 mA (RSR=5mΩ)*/
#define CHARGE_VOLTAGE_REG                 0x04 /*12-bit charge voltage setting LSB 8 mV, Default: 1S-4200mV, 2S-8400mV, 3S-12600mV, 4S-16800mV, 5S-21000mV*/
#define OTG_VOLTAGE_REG                    0x06 /*12-bit OTG voltage setting LSB 8 mV, Range: 3000 mV – 24000 mV*/
#define OTG_VOLTAGE_CURRENT_REG            0x08 /*7-bit OTG output current setting LSB 100 mA, Range: 0 A – 12700 mA(RAC=5mΩ)*/
#define INPUT_VOLTAGE_REG                  0x0A /*8-bit input voltage setting LSB 64 mV, Range: 3200 mV – 19520 mV*/
#define INPUT_CURRENT_LIMIT_HOST_REG       0x0E /*6-bit Input current limit set by hostLSB: 100-mA, Range: 100 mA - 10000 mA with 100 mA offset (RAC=5mΩ)*/
#define CHARGE_STATUS_REG                  0x20 /*Charger Status*/
#define PROCHOT_STATUS_REG                 0x22 /*Prochot status*/
#define INPUT_CURRENT_LIMIT_USE_REG        0x24 /*7-bit input current limit in use LSB: 50 mA, Range: 100 mA - 10000 mA (RAC=5mΩ) */
#define ADC_VBUS_PSYS_REG                  0x26 /*8-bit digital output of input voltage, 8-bit digital output of system power PSYS: Full range: 3.06 V, LSB: 12 mV VBUS: Full range: 0 V - 24.48 V, LSB 96 mV*/
#define ADC_BAT_CHARGE_DISCHARGE_CURRENT_REG  0x28 /*7-bit digital output of battery charge current, 7-bit digital output of battery discharge current ICHG: Full range 16.256 A, LSB 128 mA
                                                   IDCHG: Full range: 65.024 A, LSB: 512 mA (RSR=5mΩ)*/
#define ADC_INPUT_CURRENT_CMPIN_VOLTAGE_REG   0x2A	/* 8-bit digital output of input current, 8-bit digital output of CMPIN voltage
                                                    POR State - IIN: Full range: 25.5 A, LSB 100 mA (RAC=5mΩ) CMPIN: Full range 3.06 V, LSB: 12 mV*/
#define ADC_SY_SAND_BAT_VOLTAGE_REG           0x2C /*8-bit digital output of system voltage, 8-bit digital output of battery voltage VSYS: Full range: 2.88 V - 19.2 V, LSB: 64 mV (1S-4S)
                                                   VSYS: Full range: 8.16 V - 24.48 V, LSB: 64 mV (5S) VBAT: Full range : 2.88 V - 19.2 V, LSB 64 mV (1S-4S) VBAT: Full range : 8.16 V - 24.48 V, LSB 64 mV (5S)*/
#define MANUFATURER_ID_REG                    0x2E /*Manufacturer ID - 0x0040H*/
#define DEVICE_ID_REG                         0x2F /*Device ID*/
#define CHARGE_OPTION_1_REG                   0x30 /*Charge Option 1*/
#define CHARGE_OPTION_2_REG                   0x32 /*Charge Option 2*/
#define CHARGE_OPTION_3_REG                   0x34 /*Charge Option 3*/
#define PROCHOT_OPTION_0_REG                  0x36 /*PROCHOT Option 0*/
#define PROCHOT_OPTION_1_REG                  0x38 /*PROCHOT Option 1*/
#define ADC_OPTION_REG                        0x3A /*ADC Option*/
#define ADC_OPTION_4_REG                      0x3C /*ADC Option 4*/
#define VMIN_ACTIVE_PROTECT_REG               0x3E /*Vmin Active Protection */


/*ChargeOption0 Register (I2C address = 01/00h) [reset = E70Eh]*/
/*ChargeOption0 Register (I2C address = 01h) */
#define EN_LPWR_BIT                          7 /*defautlt 1b Low Power Mode Enable, under low power mode lowest quiescent current is
achieved when only battery exist. It is not recommended to enable low power
mode when adapter present.
0b: Disable Low Power Mode. Device in performance mode with battery only.
The PROCHOT, current/power monitor buffer and comparator follow register
setting.
1b: Enable Low Power Mode. Device in low power mode with battery only
for lowest quiescent current. The REGN is off. The PROCHOT, discharge
current monitor buffer, power monitor buffer and independent comparator are
disabled. ADC is not available in Low Power Mode. Independent comparator
and its low power mode PROCHOT profile can be enabled by setting
EN_PROCHOT_LPWR bit to 1b. <default at POR> */
#define WDTMR_ADJ_BIT                        6/*default: 11b WATCHDOG Timer Adjust
Set maximum delay between consecutive Host write of charge voltage or
charge current command.
If device does not receive a write on the REG0x15() or the REG0x14()
within the watchdog time period, the charger will be suspended by setting
the REG0x14() to 0 mA 256 mA (BQ25731).
After expiration, the timer will resume upon the write of REG0x14(),
REG0x15() or REG0x12[14:13].
00b: Disable Watchdog Timer
01b: Enabled, 5 sec
10b: Enabled, 88 sec
11b: Enable Watchdog Timer, 175 sec <default at POR*/
#define IIN_DPM_AUTO_DISABLE_BIT             4 /*default 0b IIN_DPM Auto Disable
When CELL_BATPRESZ pin is LOW, the charger automatically disables the
IIN_DPM function by setting EN_IIN_DPM (REG0x12[1]) to 0. The host can
enable IIN_DPM function later by writing EN_IIN_DPM bit (REG0x12[1]) to 1.
0b: Disable this function. IIN_DPM is not disabled when CELL_BATPRESZ
goes LOW. <default at POR>
1b: Enable this function. IIN_DPM is disabled when CELL_BATPRESZ goes
LOW.*/
#define OTG_ON_CHRGOK_BIT                    3 /*default: 0b Add OTG to CHRG_OK
Drive CHRG_OK to HIGH when the device is in OTG mode.
0b: Disable <default at POR>
1b: Enable*/
#define EN_OOA_BIT                           2 /*default 1b Out-of-Audio Enable
In both forward mode and OTG mode, switching frequency reduces with
diminishing load, under extreme light load condition the switching frequency
could be lower than 25 kHz which is already in audible frequency range. By
configuring EN_OOA=1b, the minimum PFM burst frequency is clamped at
around 25 kHz to avoid any audible noise.
0b: No limit of PFM burst frequency
1b: Set minimum PFM burst frequency to above 25 kHz to avoid audio noise
<default at POR>
*/
#define PWM_FREQBIT                          1 /*default 1b Switching Frequency Selection: Recommend 800 kHz with 2.2 µH, and 400
kHz with 4.7 µH.
0b: 800kHz
1b: 400 kHz<default at POR>*/
#define LOW_PTM_RIPPLE_BIT                   0 /*default 1b PTM mode input voltage and current ripple reduction
0b: Disable
1b: Enable <default at POR>*/

/*. ChargeOption0 Register (I2C address = 00h)*/

#define EN_CMP_LATCH_BIT                    7 /*default 0 The EN_CMP_LATCH bit, will latch the independent comparator output after
it is triggered at low state. If enabled in PROCHOT profile REG34H[6]=1 ,
STAT_COMP bit REG0x21[6] keep 1b after triggered until read by host and
clear
0b: Independent comparator output will not latch when it is low<default at
POR>
1b: Independent comparator output will latch when it is low, host can clear
CMPOUT pin by toggling this REG0x12[7] bit*/
#define VSYS_UVP_ENZ_BIT                   6 /*default 0b To disable system under voltage protection.
0b: VSYS under voltage protection is enabled <default at POR>
1b: VSYS under voltage protection is disabled*/
#define EN_LEARN_BIT                       5 /*default 0b LEARN mode allows the battery to discharge and converter to shut off while
the adapter is present . It calibrates the battery gas gauge over a complete
discharge/charge cycle. When the host determines the battery voltage is
below battery depletion threshold, the host switch the system back to adapter
input by writing this bit back to 0b.
0b: Disable LEARN Mode <default at POR>
1b: Enable LEARN Mode*/
#define IADPT_GAIN_BIT                     4 /*default 0b IADPT Amplifier Ratio
The ratio of voltage on IADPT and voltage across ACP and ACN.
0b: 20× <default at POR>
1b: 40× */
#define IBAT_GAIN_BIT                      3 /*default 1b IBAT Amplifier Ratio
The ratio of voltage on IBAT and voltage across SRP and SRN
0b: 8×
1b: 16× <default at POR>*/
#define EN_IIN_DPM_BIT                     1 /*default 1b IIN_DPM Enable
Host writes this bit to enable IIN_DPM regulation loop. When the IIN_DPM
is disabled by the charger (refer to IIN_DPM_AUTO_DISABLE), this bit goes
LOW.
0b: IIN_DPM disabled
1b: IIN_DPM enabled <default at POR>*/
#define CHRG_INHIBIT_BIT                   0 /*default 0b Charge Inhibit
When this bit is 0, battery charging will start with valid values in the
ChargeVoltage() register and the ChargeCurrent register.
0b: Enable Charge <default at POR>
1b: Inhibit Charge*/

/*ChargeCurrent Register (I2C address = 03/02h) [reset = 0000h] */
/*0 = Adds 0 mA of charger current.
1 = Adds x mA of charger current.*/
/*Charge Current Register with 5-mΩ Sense Resistor (I2C address = 03h)*/
#define CHARGE_CURRENT_8192_MA_BIT             4
#define CHARGE_CURRENT_4096_MA_BIT             3
#define CHARGE_CURRENT_2048_MA_BIT             2
#define CHARGE_CURRENT_1024_MA_BIT             1
#define CHARGE_CURRENT_500_MA_BIT              0
/*. Charge Current Register with 5-mΩ Sense Resistor (I2C address = 02h)*/
#define CHARGE_CURRENT_256_MA_BIT              7
#define CHARGE_CURRENT_128_MA_BIT              6

/*ChargeVoltage Register (I2C address = 05/04h) [reset value based on CELL_BATPRESZ pin setting] */
/*ChargeVoltage Register (I2C address = 05h)*/
/*0 = Adds 0 mV of charger voltage.
1 = Adds x mV of charger voltage.*/
#define CHARGE_VOLTAGE_16384_MV_BIT            6
#define CHARGE_VOLTAGE_8192_MV_BIT             5
#define CHARGE_VOLTAGE_4096_MV_BIT             4
#define CHARGE_VOLTAGE_2048_MV_BIT             3
#define CHARGE_VOLTAGE_1024_MV_BIT             2
#define CHARGE_VOLTAGE_512_MV_BIT              1
#define CHARGE_VOLTAGE_256_MV_BIT              0
/*ChargeVoltage Register (I2C address = 04h)*/
#define CHARGE_VOLTAGE_128_MV_BIT              7
#define CHARGE_VOLTAGE_64_MV_BIT               6
#define CHARGE_VOLTAGE_32_MV_BIT               5
#define CHARGE_VOLTAGE_16_MV_BIT               4
#define CHARGE_VOLTAGE_8_MV_BIT                3

/*ChargerStatus Register (I2C address = 21/20h) [reset = 0000h]*/
/*ChargerStatus Register (I2C address = 21h)*/
#define STAT_AC_BIT                            7 /*default 0 Input source status. STAT_AC is valid as long as VBUS go within
3.5-V to 26-V range. It is different from CHRG_OK bit, When
CHRG_OK is valid, STAT_AC must be valid, but if STAT_AC is valid,
it is not necessary CHRG_OK is valid. There are Force converter
off, ACOC, TSHUT , SYSOVP, VSYS_UVP, BATOVP can pull low
CHRG_OK.
0b: Input not present
1b: Input is present */
#define ICO_DONE_BIT                          6/*default 0 After the ICO routine is successfully executed, the bit goes 1.
0b: ICO is not complete
1b: ICO is complete*/
#define IN_VAP_BIT                            5/*default 0b 0b: Charger is not operated in VAP mode
1b: Charger is operated in VAP mode
Digital status bit indicates VAP has enabled(1) or disabled(0). The
enable of VAP mode only follows the host command, which is not
blocked by any status of /PROCHOT. The exit of VAP mode also
follows the host command, except that any faults will exit VAP mode
automatically. STAT_EXIT_VAP (REG0x21[8]) becomes 1 which will
pull low /PROCHOT until host clear.
The host can enable VAP by setting OTG/VAP/FRS pin high and
0x32[5]=0, disable VAP by setting either OTG/VAP/FRS pin low
or 0x32[5]=1. Any faults in VAP When IN_VAP bit goes 0->1,
charger should disable VINDPM, IIN_DPM, ICRIT, ILIM pin, disable
PP_ACOK if it is enabled, enable PP_VSYS if it is disabled. When
IN_VAP bit goes 1->0, charger should enable VINDPM, IIN_DPM,
ICRIT, ILIM pin function.
*/
#define IN_VINDMP_BIT                         4 /*default 0b: Charger is not in VINDPM during forward mode, or voltage
regulation during OTG mode
1b: Charger is in VINDPM during forward mode, or voltage
regulation during OTG mode
*/
#define IN_IIN_DPM_BIT                        3 /*default 0b: Charger is not in IIN_DPM during forward mode.
1b: Charger is not in IIN_DPM during forward mode.*/
#define IN_FCHRG                              2 /*default 0b: Charger is not in fast charge
1b: Charger is in fast charger*/
#define IN_OTG_BIT                            0 /*default 0b: Charger is not in OTG
1b: Charge is in OTG*/
