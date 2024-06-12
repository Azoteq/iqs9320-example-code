/*
* This file contains all the necessary settings for the IQS9320 and this file can
* be changed from the GUI or edited here
* File:   IQS9320_init.h
* Author: Azoteq
*/

#ifndef IQS9320_INIT_H
#define IQS9320_INIT_H

/* Change the Version Info */
/* Memory Map Position 0x0000 - 0x00 */
#define PROD_0                                   0x16
#define PROD_1                                   0x07

/* Change the Device Configuration */
/* Memory Map Position 0x2000 - 0x2008 */
#define SYSTEM_CONTROL_0                         0x00
#define SYSTEM_CONTROL_1                         0x00
#define SYSTEM_CONFIG_0                          0x0B
#define SYSTEM_CONFIG_1                          0x5E
#define NP_SAMPLING_INTERVAL_0                   0x00
#define NP_SAMPLING_INTERVAL_1                   0x00
#define NP_TIMEOUT_0                             0x88
#define NP_TIMEOUT_1                             0x13
#define LP_SAMPLING_INTERVAL_0                   0x28
#define LP_SAMPLING_INTERVAL_1                   0x00
#define LP_TIMEOUT_0                             0x88
#define LP_TIMEOUT_1                             0x13
#define ULP_SAMPLING_INTERVAL_0                  0x50
#define ULP_SAMPLING_INTERVAL_1                  0x00
#define ULP_TIMEOUT_0                            0x00
#define ULP_TIMEOUT_1                            0x00
#define DEFAULT_READ_LOCATION_0                  0x0A
#define DEFAULT_READ_LOCATION_1                  0x10

/* Change the Multipliers and Dividers A */
/* Memory Map Position 0x3000 - 0x3009 */
#define MIRROR_SEL_CH0_0                         0x21
#define MIRROR_SEL_CH0_1                         0x4D
#define MIRROR_SEL_CH1_0                         0x21
#define MIRROR_SEL_CH1_1                         0x4D
#define MIRROR_SEL_CH2_0                         0x21
#define MIRROR_SEL_CH2_1                         0x49
#define MIRROR_SEL_CH3_0                         0x21
#define MIRROR_SEL_CH3_1                         0x4D
#define MIRROR_SEL_CH4_0                         0xC1
#define MIRROR_SEL_CH4_1                         0x58
#define MIRROR_SEL_CH5_0                         0xC1
#define MIRROR_SEL_CH5_1                         0x56
#define MIRROR_SEL_CH6_0                         0xC1
#define MIRROR_SEL_CH6_1                         0x58
#define MIRROR_SEL_CH7_0                         0xC1
#define MIRROR_SEL_CH7_1                         0x58
#define MIRROR_SEL_CH8_0                         0x21
#define MIRROR_SEL_CH8_1                         0x4B
#define MIRROR_SEL_CH9_0                         0x21
#define MIRROR_SEL_CH9_1                         0x49

/* Change the Multipliers and Dividers B */
/* Memory Map Position 0x3014 - 0x301D */
#define MIRROR_SEL_CH10_0                        0x21
#define MIRROR_SEL_CH10_1                        0x4B
#define MIRROR_SEL_CH11_0                        0x21
#define MIRROR_SEL_CH11_1                        0x47
#define MIRROR_SEL_CH12_0                        0xC1
#define MIRROR_SEL_CH12_1                        0x56
#define MIRROR_SEL_CH13_0                        0xC1
#define MIRROR_SEL_CH13_1                        0x58
#define MIRROR_SEL_CH14_0                        0xC1
#define MIRROR_SEL_CH14_1                        0x56
#define MIRROR_SEL_CH15_0                        0x61
#define MIRROR_SEL_CH15_1                        0x4E
#define MIRROR_SEL_CH16_0                        0xC1
#define MIRROR_SEL_CH16_1                        0x58
#define MIRROR_SEL_CH17_0                        0x61
#define MIRROR_SEL_CH17_1                        0x4E
#define MIRROR_SEL_CH18_0                        0xC1
#define MIRROR_SEL_CH18_1                        0x58
#define MIRROR_SEL_CH19_0                        0x21
#define MIRROR_SEL_CH19_1                        0x4B

/* Change the Effective Max Delta A */
/* Memory Map Position 0x3050 - 0x3059 */
#define MAX_DELTA_E_0_0                          0x10
#define MAX_DELTA_E_0_1                          0x27
#define MAX_DELTA_E_1_0                          0x10
#define MAX_DELTA_E_1_1                          0x27
#define MAX_DELTA_E_2_0                          0x10
#define MAX_DELTA_E_2_1                          0x27
#define MAX_DELTA_E_3_0                          0x10
#define MAX_DELTA_E_3_1                          0x27
#define MAX_DELTA_E_4_0                          0x10
#define MAX_DELTA_E_4_1                          0x27
#define MAX_DELTA_E_5_0                          0x10
#define MAX_DELTA_E_5_1                          0x27
#define MAX_DELTA_E_6_0                          0x10
#define MAX_DELTA_E_6_1                          0x27
#define MAX_DELTA_E_7_0                          0x10
#define MAX_DELTA_E_7_1                          0x27
#define MAX_DELTA_E_8_0                          0x10
#define MAX_DELTA_E_8_1                          0x27
#define MAX_DELTA_E_9_0                          0x10
#define MAX_DELTA_E_9_1                          0x27

/* Change the Effective Max Delta B */
/* Memory Map Position 0x3064 - 0x306D */
#define MAX_DELTA_E_10_0                         0x10
#define MAX_DELTA_E_10_1                         0x27
#define MAX_DELTA_E_11_0                         0x10
#define MAX_DELTA_E_11_1                         0x27
#define MAX_DELTA_E_12_0                         0x10
#define MAX_DELTA_E_12_1                         0x27
#define MAX_DELTA_E_13_0                         0x10
#define MAX_DELTA_E_13_1                         0x27
#define MAX_DELTA_E_14_0                         0x10
#define MAX_DELTA_E_14_1                         0x27
#define MAX_DELTA_E_15_0                         0x10
#define MAX_DELTA_E_15_1                         0x27
#define MAX_DELTA_E_16_0                         0x10
#define MAX_DELTA_E_16_1                         0x27
#define MAX_DELTA_E_17_0                         0x10
#define MAX_DELTA_E_17_1                         0x27
#define MAX_DELTA_E_18_0                         0x10
#define MAX_DELTA_E_18_1                         0x27
#define MAX_DELTA_E_19_0                         0x10
#define MAX_DELTA_E_19_1                         0x27

/* Change the Sampled Max Delta A */
/* Memory Map Position 0x3078 - 0x3081 */
#define MAX_DELTA_S_0_0                          0x00
#define MAX_DELTA_S_0_1                          0x00
#define MAX_DELTA_S_1_0                          0x00
#define MAX_DELTA_S_1_1                          0x00
#define MAX_DELTA_S_2_0                          0x00
#define MAX_DELTA_S_2_1                          0x00
#define MAX_DELTA_S_3_0                          0x00
#define MAX_DELTA_S_3_1                          0x00
#define MAX_DELTA_S_4_0                          0x00
#define MAX_DELTA_S_4_1                          0x00
#define MAX_DELTA_S_5_0                          0x00
#define MAX_DELTA_S_5_1                          0x00
#define MAX_DELTA_S_6_0                          0x00
#define MAX_DELTA_S_6_1                          0x00
#define MAX_DELTA_S_7_0                          0x00
#define MAX_DELTA_S_7_1                          0x00
#define MAX_DELTA_S_8_0                          0x00
#define MAX_DELTA_S_8_1                          0x00
#define MAX_DELTA_S_9_0                          0x00
#define MAX_DELTA_S_9_1                          0x00

/* Change the Sampled Max Delta B */
/* Memory Map Position 0x308C - 0x3095 */
#define MAX_DELTA_S_10_0                         0x00
#define MAX_DELTA_S_10_1                         0x00
#define MAX_DELTA_S_11_0                         0x00
#define MAX_DELTA_S_11_1                         0x00
#define MAX_DELTA_S_12_0                         0x00
#define MAX_DELTA_S_12_1                         0x00
#define MAX_DELTA_S_13_0                         0x00
#define MAX_DELTA_S_13_1                         0x00
#define MAX_DELTA_S_14_0                         0x00
#define MAX_DELTA_S_14_1                         0x00
#define MAX_DELTA_S_15_0                         0x00
#define MAX_DELTA_S_15_1                         0x00
#define MAX_DELTA_S_16_0                         0x00
#define MAX_DELTA_S_16_1                         0x00
#define MAX_DELTA_S_17_0                         0x00
#define MAX_DELTA_S_17_1                         0x00
#define MAX_DELTA_S_18_0                         0x00
#define MAX_DELTA_S_18_1                         0x00
#define MAX_DELTA_S_19_0                         0x00
#define MAX_DELTA_S_19_1                         0x00

/* Change the Individual Thresholds */
/* Memory Map Position 0x30F0 - 0x30F9 */
#define INDIVIDUAL_THRESHOLDS_0                  0x28
#define INDIVIDUAL_THRESHOLDS_1                  0x28
#define INDIVIDUAL_THRESHOLDS_2                  0x28
#define INDIVIDUAL_THRESHOLDS_3                  0x28
#define INDIVIDUAL_THRESHOLDS_4                  0x28
#define INDIVIDUAL_THRESHOLDS_5                  0x28
#define INDIVIDUAL_THRESHOLDS_6                  0x28
#define INDIVIDUAL_THRESHOLDS_7                  0x28
#define INDIVIDUAL_THRESHOLDS_8                  0x28
#define INDIVIDUAL_THRESHOLDS_9                  0x28
#define INDIVIDUAL_THRESHOLDS_10                 0x28
#define INDIVIDUAL_THRESHOLDS_11                 0x28
#define INDIVIDUAL_THRESHOLDS_12                 0x28
#define INDIVIDUAL_THRESHOLDS_13                 0x28
#define INDIVIDUAL_THRESHOLDS_14                 0x28
#define INDIVIDUAL_THRESHOLDS_15                 0x28
#define INDIVIDUAL_THRESHOLDS_16                 0x28
#define INDIVIDUAL_THRESHOLDS_17                 0x28
#define INDIVIDUAL_THRESHOLDS_18                 0x28
#define INDIVIDUAL_THRESHOLDS_19                 0x28

/* Change the Channel Select and Disable */
/* Memory Map Position 0x3104 - 0x3105 */
#define CYCLE_0_SELECT                           0x0A
#define CYCLE_1_SELECT                           0x0A
#define CHANNEL_DISABLE_0                        0x00
#define CHANNEL_DISABLE_1                        0x00
#define CHANNEL_DISABLE_2                        0x00

/* Change the Rx Select */
/* Memory Map Position 0x310A - 0x3113 */
#define RX_SELECT_0                              0x1E   // 30
#define RX_SELECT_1                              0x1C   // 28
#define RX_SELECT_2                              0x19   // 25
#define RX_SELECT_3                              0x17   // 23
#define RX_SELECT_4                              0x12   // 18
#define RX_SELECT_5                              0x0D   // 13
#define RX_SELECT_6                              0x08   // 8
#define RX_SELECT_7                              0x05   // 5
#define RX_SELECT_8                              0x02   // 2
#define RX_SELECT_9                              0x00   // 0
#define RX_SELECT_10                             0x1F   // 31
#define RX_SELECT_11                             0x1D   // 29
#define RX_SELECT_12                             0x1A   // 26
#define RX_SELECT_13                             0x18   // 24
#define RX_SELECT_14                             0x13   // 19
#define RX_SELECT_15                             0x0E   // 14
#define RX_SELECT_16                             0x0B   // 11
#define RX_SELECT_17                             0x06   // 6
#define RX_SELECT_18                             0x03   // 3
#define RX_SELECT_19                             0x01   // 1

/* Change the Tx Select */
/* Memory Map Position 0x311E - 0x3127 */
#define TX_SELECT_0                              0x26   // 38
#define TX_SELECT_1                              0x28   // 40
#define TX_SELECT_2                              0x2A   // 42
#define TX_SELECT_3                              0x16   // 22
#define TX_SELECT_4                              0x11   // 17
#define TX_SELECT_5                              0x0C   // 12
#define TX_SELECT_6                              0x09   // 9
#define TX_SELECT_7                              0x04   // 4
#define TX_SELECT_8                              0x2B   // 43
#define TX_SELECT_9                              0x2D   // 45
#define TX_SELECT_10                             0x29   // 41
#define TX_SELECT_11                             0x27   // 39
#define TX_SELECT_12                             0x1B   // 27
#define TX_SELECT_13                             0x15   // 21
#define TX_SELECT_14                             0x14   // 20
#define TX_SELECT_15                             0x0F   // 15
#define TX_SELECT_16                             0x0A   // 10
#define TX_SELECT_17                             0x07   // 7
#define TX_SELECT_18                             0x10   // 16
#define TX_SELECT_19                             0x2C   // 44

/* Change the ATI Target and Band */
/* Memory Map Position 0x3132 - 0x3133 */
#define ATI_TARGET_0                             0xC8
#define ATI_TARGET_1                             0x00
#define ATI_BAND_0                               0x32
#define ATI_BAND_1                               0x00

/* Change the Thresholds */
/* Memory Map Position 0x3136 - 0x3137 */
#define ACTIVATION_THRESHOLD                     0x28
#define REFERENCE_HALT_THRESHOLD                 0x14
#define FAST_REF_THRESHOLD                       0x0A
#define MOVEMENT_THRESHOLD                       0x08

/* Change the Filter Values */
/* Memory Map Position 0x313A - 0x313D */
#define BETA_LTA_NP                              0x0A
#define BETA_LTA_LP                              0x06
#define BETA_LTA_ULP                             0x05
#define BETA_FAST_LTA_NP                         0x08
#define BETA_FAST_LTA_LP                         0x05
#define BETA_FAST_LTA_ULP                        0x04
#define BETA_COUNTS_NP                           0x03
#define BETA_COUNTS_LP                           0x01
#define BETA_COUNTS_ULP                          0x00

/* Change the Reference Halt Timeout */
/* Memory Map Position 0x3144 - 0x3143 */
#define REF_HALT_TIMEOUT_0                       0x27

/* Change the Activation Hysteresis */
/* Memory Map Position 0x3145 - 0x3144 */
#define ACTIVATION_HYSTERESIS_0                  0x05

/* Change the Timing Generator Settings */
/* Memory Map Position 0x3146 - 0x3146 */
#define TIMING_GENERATOR_0                       0x00
#define TIMING_GENERATOR_1                       0x00

/* Change the Hardware Settings */
/* Memory Map Position 0x3148 - 0x3148 */
#define HARDWARE_SETTINGS_0                      0x8C
#define HARDWARE_SETTINGS_1                      0x01

#endif	/* IQS9320_INIT_H */