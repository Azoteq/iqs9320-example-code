/******************************************************************************
*                                                                             *
*                                 Copyright by                                *
*                                                                             *
*                               Azoteq (Pty) Ltd                              *
*                           Republic of South Africa                          *
*                                                                             *
*                            Tel: +27(0)21 863 0033                           *
*                                 www.azoteq.com                              *
*                                                                             *
*******************************************************************************
* Refer to IQS9320 datasheet for more information, available here:             *
* - https://www.azoteq.com/design/datasheets/                                 *
*******************************************************************************
*                       IQS9320 - Registers & Memory Map                       *
*******************************************************************************/

#ifndef __IQS9320_ADDRESSES_H
#define __IQS9320_ADDRESSES_H

#include "../IQS9320.h"

/* Device Information - Read Only */

/* VERSION DETAILS: 0x0000 - 0x000A */
#define IQS9320_MM_PROD_NUM                     0x0000
#define IQS9320_MM_MAJOR_VERSION_NUM            0x0002
#define IQS9320_MM_MINOR_VERSION_NUM            0x0004

/* DEVICE DATA: 0x1000 - 0x10B4 */
#define IQS9320_MM_SYSTEM_STATUS		        0x1000

/* DEVICE CONFIGURATION: 0x2000 - 0x2010 */
#define IQS9320_MM_SYSTEM_CONTROL               0x2000
#define IQS9320_MM_SYSTEM_CONFIGURATION         0x2002
#define IQS9320_MM_DEFAULT_READ_LOCATION        0x2010
#define IQS9320_MM_NORMAL_POWER_TIMEOUT         0x2006
#define IQS9320_MM_LOW_POWER_TIMEOUT            0x200A

/* CHANNEL CONFIGURATION: 0x3000 - 0x3120 */
#define IQS9320_MM_MIRROR_SELECTION_CH0         0x3000
#define IQS9320_MM_MIRROR_SELECTION_CH10        0x3014
#define IQS9320_MM_CALIBRATION_PARAMETERS_CH0   0x3028
#define IQS9320_MM_CALIBRATION_PARAMETERS_CH10  0x3042
#define IQS9320_MM_EFFECTIVE_MAX_DELTA_CH0      0x3050
#define IQS9320_MM_EFFECTIVE_MAX_DELTA_CH10     0x3064


#endif /* __IQS9320_ADDRESSES_H */