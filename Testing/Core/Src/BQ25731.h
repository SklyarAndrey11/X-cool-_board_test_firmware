/*
 * BQ25731.h
 *
 *  Created on: Nov 14, 2023
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

/*ChargerStatus Register (I2C address = 20h)*/
#define FAULT_ACOV_BIT                        7 /*default 0b ChargerStatus Register (I
2C address = 20h)*/
#define FAULT_BATOC_BIT                       6 /*default 0b The status is latched if triggered until a read from host. Fault
indicator for BATOC only during normal operation. However, in PTM
mode when EN_BATOC=1b, this status bit is fault indicator for both
BATOVP and BATOC; when EN_BATOC=0b, this status bit is not
effective.
0b: No fault
1b: BATOC is triggered*/
#define FAULT_ACOC_BIT                       5 /*default 0b The status is latched if triggered until a read from host.
0b: No fault
1b: ACOC*/
#define FAULT_SYSOVP_BIT                     4 /*default 0b SYSOVP Status and Clear. SYSOVP fault is latched until a clear
from host by writing this bit to 0.
When the SYSOVP occurs, this bit is HIGH. During the SYSOVP, the
converter is disabled.
After the SYSOVP is removed, the user must write a 0 to this bit
or unplug the adapter to clear the SYSOVP condition to enable the
converter again.
0b: Not in SYSOVP <default at POR>
1b: In SYSOVP. When SYSOVP is removed, write 0 to clear the
SYSOVP latch*/
#define FAULT_VSYS_UVP_BIT                   3 /*default 0b VSYS_UVP fault status and clear. VSYS_UVP fault is latched until a
clear from host by writing this bit to 0.
0b: No fault <default at POR>
1b: When system voltage is lower than VSYS_UVP, then 7 times
restart tries are failed.
*/
#define FAULT_FORCE_CONVERTER_OFF_BIT       2 /*defaut 0bThe status is latched if triggered until a read from host.
0b: No fault
1b: Force converter off triggered (when FORCE_CONV_OFF
(REG0x30[3])=1b)*/
#define FAULT_OTG_OVP                       1 /*default 0b The status is latched if triggered until a read from host.
0b: No fault
1b: OTG OVP fault is triggered*/
#define FAULT_OTG_UVP                       0 /*default 0b The status is latched if triggered until a read from host.
0b: No fault
1b: OTG UVP fault is triggered*/
/*ProchotStatus Register (I2C address = 23/22h)*/
/*. ProchotStatus Register (I2C address = 23h)*/
#define EN_PROCHOT_EXT_BIT                 6 /*default 0b PROCHOT Pulse Extension Enable. When pulse extension is
enabled, keep the PROCHOT pin voltage LOW until host writes
PROCHOT _CLEAR = 0b.
0b: Disable pulse extension <default at POR>
1b: Enable pulse extension*/
#define PROCHOT_WIDTH_BIT                  5 /*default 0b PROCHOT Pulse Width Minimum PROCHOT pulse width when
EN_PROCHOT _EXT = 0b
00b: 100 us
01b: 1 ms
10b: 5 ms
11b: 10 ms <default at POR>*/
#define PROCHOT_CLEAR_BIT                  3 /*default 0b PROCHOT Pulse Clear.
Clear PROCHOT pulse when EN_PROCHOT _EXT = 1b.
0b: Clear PROCHOT pulse and drive PROCHOT pin HIGH
1b: Idle <default at POR>*/
#define TSHUT_BIT                          2 /*default 0b TSHUT trigger:
0b: TSHUT is not triggered
1b: TSHUT is triggered*/
#define STAT_VAP_FAIL_BIT                  1 /*default 0b This status bit reports a failure to load VBUS 7 consecutive times
in VAP mode, which indicates the battery voltage might be not
high enough to enter VAP mode, or the VAP loading current
settings are too high.
0b: Not is VAP failure <default at POR>
1b: In VAP failure, the charger exits VAP mode, and latches off
until the host writes this bit to 0.*/
#define STAT_EXIT_VAP_BIT                  0 /*default 0b When the charger is operated in VAP mode, it can exit VAP
by either being disabled through host, or there are ACOV/ACOC/
SYSOVP/BATOVP/VSYS_UVP faults.
0b: PROCHOT_EXIT_VAP is not active <default at POR>
1b: PROCHOT_EXIT_VAP is active, PROCHOT pin is low until
host writes this status bit to 0.*/
/*ProchotStatus Register (I2C address = 22h)*/

#define STAT_VINDPM_BIT                    7 /*default 0b PROCHOT Profile VINDPM status bit
0b: Not triggered
1b: Triggered, PROCHOT pin is low until host writes this status bit
to 0 when PP_VINDPM = 1b*/
#define STAT_COMP_BIT                      6 /*default 0b PROCHOT Profile CMPOUT status bit. The status is latched until
a read from host.
0b: Not triggered
1b: Triggered*/
#define STAT_ICRIT_BIT                     5 /*default 0b PROCHOT Profile ICRIT status bit. The status is latched until a
read from host.
0b: Not triggered
1b: Triggered*/
#define STAT_INOM_BIT                      4 /*default 0b PROCHOT Profile INOM status bit. The status is latched until a
read from host.
0b: Not triggered
1b: Triggered*/
#define STAT_IDCHG1_BIT                    3 /*default 0b PROCHOT Profile IDCHG1 status bit. The status is latched until a
read from host.
0b: Not triggered
1b: Triggered*/
#define STAT_VSYS_BIT                      2 /*default 0b PROCHOT Profile VSYS status bit. The status is latched until a
read from host.
0b: Not triggered
1b: Triggered*/
#define STAT_BATTERY_REMOVAL_BIT           1 /*default 0b PROCHOT Profile Battery Removal status bit. The status is
latched until a read from host.
0b: Not triggered
1b: Triggered*/
#define STAT_ADAPTER_REMOVAL_BIT           0 /*default 0b PROCHOT Profile Adapter Removal status bit. The status is
latched until a read from host.
0b: Not triggered
1b: Triggered*/

/*ChargeOption1 Register (I2C address = 31/30h) [reset = 3300h]*/

#define EN_IBAT_BIT                       7 /*default 0b IBAT Enable
Enable the IBAT output buffer. In low power mode (EN_LWPWR=1b), IBAT
buffer is always disabled regardless of this bit value.
0b Turn off IBAT buffer to minimize Iq <default at POR>
1b: Turn on IBAT buffer*/
#define EN_PROCHOT_LPWR_BIT               6 /*default 0b Enable PROCHOT during battery only low power mode
With battery only, enable VSYS in PROCHOT with low power consumption. Do
not enable this function with adapter present. Refer to Section 9.3.20.1 for more
details.
0b: Disable Independent Comparator low power PROCHOT <default at POR>
1b: Enable Independent Comparator low power PROCHOT*/
#define PSYS_CONFIG_BIT                   5 /*default 11b PSYS Enable and Definition Register
Enable PSYS sensing circuit and output buffer (whole PSYS circuit). In low
power mode (EN_LWPWR=1b), PSYS sensing and buffer are always disabled
regardless of this bit value.
00b: PSYS=PBUS+PBAT
01b: PSYS=PBUS
10b: Reserved
11b: Turn off PSYS buffer to minimize Iq<default at POR>*/
#define RSNS_RAC_BIT                     3 /*default 1b Input sense resistor RAC
0b: 10 mΩ
1b: 5 mΩ <default at POR>*/
#define RSNS_RSR_BIT                     2 /*default 1b Charge sense resistor RSR
0b: 10 mΩ
1b: 5 mΩ <default at POR>*/
#define PSYS_RATIO_BIT                   1 /*default 1b PSYS Gain
Ratio of PSYS output current vs total system power
0b: 0.25 µA/W
1b: 1 µA/W <default at POR>*/
#define EN_FAST_5MOHM_BIT                0 /*default 1b Enable fast compensation to increase bandwidth under 5 mΩ RAC
(RSNS_RAC=1b) for input current up to 6.4-A application (the fast
compensation will only work when IADPT pin is configured less than 160 kΩ)
0b: Turn off bandwidth promotion under RSNS_RAC=1b
(Note when this bit configured as 0b, IIN_HOST DAC can be extended up to
10 A, writing IIN_HOST value higher than 10 A will be neglected, the ICHG
regulation loop will be slower to guarantee stability under 6.4-A to 10-A input
current range)
1b: Turn on bandwidth promotion under RSNS_RAC=1b <default at POR>
(Note when this bit configured as 1b, IIN_HOST DAC is clamped at 6.4 A,
writing IIN_HOST value higher than 6.4 A will be neglected, the ICHG regulation
loop will be faster within 6.4-A input current range)*/


/*CChargeOption1 Register (I2C address = 30h)*/
#define CMP_REF_BIT                      7 /*default 0b Independent Comparator internal Reference
0b: 2.3 V <default at POR>
1b: 1.2 V*/
#define CMP_POL_BIT                      6 /*default 0b Independent Comparator output Polarity
0b: When CMPIN is above internal threshold, CMPOUT is LOW (internal
hysteresis) <default at POR>
1b: When CMPIN is below internal threshold, CMPOUT is LOW (external
hysteresis)*/
#define CMP_DEG_BIT                     5 /*default 00b Independent comparator deglitch time, only applied to the falling edge of
CMPOUT (HIGH → LOW).
00b: Independent comparator is enabled with output deglitch time 5 µs <default
at POR>
01b: Independent comparator is enabled with output deglitch time of 2 ms
10b: Independent comparator is enabled with output deglitch time of 20 ms
11b: Independent comparator is enabled with output deglitch time of 5 sec*/
#define FORCE_CONV_OFF_BIT             3 /*default 0b Force Converter Off function
When independent comparator triggers, (CMPOUT pin pulled down) converter
latches off, at the same time, CHRG_OK signal goes LOW to notify the system.
Charge current is also set to zero internally, but charge current register setting
keeps the same. To get out of converter latches off, firstly the CMPOUT should
be released to high and secondly FORCE_CONV_OFF bit should be cleared
(=0b).
0b: Disable this function <default at POR>
1b: Enable this function*/
#define EN_PTM_BIT                     2 /*default 0b PTM enable register bit, it will automatically reset to zero
0b: disable PTM. <default at POR>
1b: enable PTM.*/
#define EN_SHIP_DCHG_BIT               1 /*default 0b Discharge SRN for Shipping Mode. Used to discharge VBAT pin capacitor
voltage which is necessary for battery gauge device shipping mode.
When this bit is 1, discharge SRN pin down in 140 ms 20 mA. When 140 ms is
over, this bit is reset to 0b automatically. If this bit is written to 0b by host before
140 ms expires, VSYS should stop discharging immediately. Note if after 140-ms
SRN voltage is still not low enough for battery gauge device entering ship mode,
the host may need to start a new 140-ms discharge cycle.
0b: Disable shipping mode <default at POR>
1b: Enable shipping mode
*/
#define AUTO_WAKEUP_EN_BIT             0 /*default 0b Auto Wakeup Enable
When this bit is HIGH, if the battery is below VSYS_MIN , the device should
automatically enable 128-mA charging current for 30 mins. When the battery is
charged up above minimum system voltage, charge will terminate and the bit is
reset to LOW. The charger will also exit auto wake up if host write a new charge
current value to charge current register Reg0x14().
0b: Disable <default at POR>
1b: Enable*/

/*ChargeOption2 Register (I2C address = 33h) */

#define PKPWR_TOVLD_DEG_BIT            7 /*default 00b Input Overload time in Peak Power Mode
00b: 1 ms <default at POR>
01b: 2 ms
10b: 5 ms
11b: 10 ms*/
#define EN_PKPWR_IIN_DPM_BIT           5 /*default 0b Enable Peak Power Mode triggered by input current overshoot
If REG0x33[5:4] are 00b, peak power mode is disabled. Upon adapter
removal, the bits are reset to 00b.
0b: Disable peak power mode triggered by input current overshoot
<default at POR>
1b: Enable peak power mode triggered by input current overshoot.*/
#define EN_PKPWR_VSYS_BIT              4 /*default 0b Enable Peak Power Mode triggered by system voltage under-shoot
If REG0x33[5:4] are 00b, peak power mode is disabled. Upon adapter
removal, the bits are reset to 00b.
0b: Disable peak power mode triggered by system voltage under-shoot
<default at POR>
1b: Enable peak power mode triggered by system voltage under-shoot.*/
#define STAT_PKPWR_OVLD_BIT            3 /*default 0b Indicator that the device is in overloading cycle. Write 0 to get out of
overloading cycle.
0b: Not in peak power mode. <default at POR>
1b: In peak power mode.*/
#define STAT_PKPWR_RELAX_BIT           2 /*default 0b Indicator that the device is in relaxation cycle. Write 0 to get out of
relaxation cycle.
0b: Not in relaxation cycle. <default at POR>
1b: In relaxation mode.*/
#define PKPWR_TMAX_BIT                 1 /*default 00b Peak power mode overload and relax cycle time.
00b: 20 ms <default at POR>
01b: 40 ms
10b: 80 ms
11b: 1 sec*/

/*ChargeOption2 Register (I2C address = 32h)*/

#define EN_EXTILIM_BIT                7 /*default 1b Enable ILIM_HIZ pin to set input current limit
0b: Input current limit is set by IIN_DPM register..
1b: Input current limit is set by the lower value of ILIM_HIZ pin and
IIN_DPM register.. <default at POR>*/
#define EN_ICHG_IDCHG_BIT             6 /*default 0b: IBAT pin as discharge current. <default at POR>
1b: IBAT pin as charge current.*/

#define Q2_OCP_BIT                    5 /*default 1b Q2 OCP threshold by sensing Q2 VDS
0b: 210 mV
1b: 150 mV <default at POR>*/
#define ACX_OCP_BIT                   4 /*default 1b Fixed Input current OCP threshold by sensing ACP-ACN, converter
is disabled immediately when triggered non latch protection resume
switching automatically after ACX comparator release.
0b: 280 mV(RSNS_RAC=0b)/200 mV(RSNS_RAC=1b)
1b: 150 mV(RSNS_RAC=0b)/100 mV(RSNS_RAC=1b) <default at
POR>
*/
#define EN_ACOC_BIT                   3 /*default 0b ACOC Enable
Configurable Input overcurrent (ACOC) protection by sensing the
voltage across ACP and ACN. Upon ACOC (after 250-μs blank-out
time), converter is disabled. Non latch fault, after 250-ms falling edge
de-glitch time converter starts switching automatically.
0b: Disable ACOC <default at POR>
1b: ACOC threshold 133% or 200% ILIM2*/
#define ACOC_VTH_BIT                 2 /*default 1b ACOC Limit
Set MOSFET OCP threshold as percentage of IIN_DPM with current
sensed from RAC.
0b: 133% of ILIM2
1b: 200% of ILIM2 <default at POR>*/
#define EN_BATOC_BIT                 1 /*default 1b BATOC
Battery discharge overcurrent (BATOC) protection by sensing the
voltage across SRN and SRP. Upon BATOC, converter is disabled.
0b: Disable BATOC
1b: Enable BATOC threshold 133% or 200% PROCHOT IDCHG_TH2
<default at POR>*/
#define BATOC_VTH_BIT                0 /*default 1b Set battery discharge overcurrent threshold as percentage of
PROCHOT battery discharge current limit. Note when SRN and SRP
common voltage is low for 1S application, the BATOC threshold could
be derating.
0b: 133% of PROCHOT IDCHG_TH2
1b: 200% of PROCHOT IDCHG _TH2<default at POR>*/
/*ChargeOption3 Register (I2C address = 35/34h) [reset = 0434h]*/

#define EN_HIZ_BIT                   7 /*default 0b Device HIZ Mode Enable
When the charger is in HIZ mode, the device draws minimal quiescent
current. With VBUS above UVLO. REGN LDO stays on, and system
powers from battery.
0b: Device not in HIZ mode <default at POR>
1b: Device in HIZ mode*/

#define RESET_REG_BIT               6 /*default 0b Reset Registers
All the registers are reset to POR default setting except the VINDPM
register.
0b: Idle <default at POR>
1b: Reset all the registers to default values. After reset, this bit goes back
to 0.*/
#define RESET_VINDPM_BIT            5 /*default 0b Reset VINDPM Threshold
0b: Idle
1b: Converter is disabled to measure VINDPM threshold. After VINDPM
measurement is done, this bit goes back to 0 and converter starts*/
#define EN_OTG_BIT                  4 /*default 0b OTG Mode Enable
Enable device in OTG mode when OTG/VAP/FRS pin is HIGH.
0b: Disable OTG <default at POR>
1b: Enable OTG mode to supply VBUS from battery*/
#define EN_ICO_MODE_BIT             3 /* default 0b Enable ICO Algorithm
0b: Disable ICO algorithm. <default at POR>
1b: Enable ICO algorithm.*/
#define EN_OTG_BIGCAP_BIT           0 /*default 0b Enable OTG compensation for VBUS effective capacitance larger than 33
μF
0b: Disable OTG large VBUS capacitance compensation (Recommended
for VBUS effective capacitance smaller than 33 μF) <default at POR>
1b: Enable OTG large VBUS capacitance compensation (Recommended
for VBUS effective capacitance larger than 33 μF)*/
