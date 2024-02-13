/******************************************************************************
 *                                                                            *
 *                                Copyright by                                *
 *                                                                            *
 *                              Azoteq (Pty) Ltd                              *
 *                          Republic of South Africa                          *
 *                                                                            *
 *                           Tel: +27(0)21 863 0033                           *
 *                           E-mail: info@azoteq.com                          *
 *                                                                            *
 * ========================================================================== *
 * @file        IQS9320.cpp                                                   *
 * @brief       This file contains the constructors and methods which allow   *
 *              ease of use of an IQS9320 Integrated Circuit (IC). The        *
 *              IQS9320 is a 20 Channel inductive sensing device. This class  *
 *              provides an easy means of initializing and interacting with   *
 *              the IQS9320 device from an Arduino-based device.              *
 * @author      JN. Lochner - Azoteq PTY Ltd                                  *
 * @version     v0.0.0                                                        *
 * @date        2023                                                          *
 * ========================================================================== *
 * @attention  Makes use of the following standard Arduino libraries:         *
 * - Arduino.h -> Included in IQS9320.h, comes standard with Arduino          *
 * - azq_i2c.h -> Included in IQS9320.h, Azoteq wrapper for Arduino's 'Wire'  *
 *****************************************************************************/

/* Include Files */
#include "IQS9320.h"

/* Load the IQS9320 Settings */
#ifdef IQS9320_V0_7
#include "IQS9320_v0_7_init.h"
#endif

#ifdef IQS9320_V0_4
#include "IQS9320_v0_4_init.h"
#endif

/* Private Functions */


/*****************************************************************************/
/*                             CONSTRUCTORS                                  */
/*****************************************************************************/
IQS9320::IQS9320(){
}

/*****************************************************************************/
/*                            PUBLIC METHODS                                 */
/*****************************************************************************/

/**
  * @name   begin
  * @brief  A method to initialize the IQS9320 device with the I2C Bus,
  *         device address and ready pin specified by the user.
  * @param  i2c_bus       ->  Either 0 or 1 depending on the I2C bus used.
  * @param  deviceAddress ->  The address of the IQS9320 device.
  * @param  readyPin      ->  The Arduino pin which is connected to the ready
  *                           pin of the IQS9320 device.
  * @param  clk_speed     ->  I2C Clock speed. Will force I2C bus to run at
  *                           defined speed. Can break other devices.
  * @retval None.
  * @note   - Receiving a true return value does not mean that initialization
  *           was successful.
  *         - Receiving a true return value only means that the IQS device
  *           responded to the request for communication.
  *         - Receiving a false return value means that initialization did not
  *           take place at all.
  *         - If communication is successfully established then it is unlikely
  *           that initialization will fail.
*/
void IQS9320::begin(uint8_t deviceAddressIn, pin_size_t mclr_pin, uint8_t nChannels)
{
  // Initialize I2C communication here, since this library can't function without it.
  Wire.begin();
  Wire.setClock(400000);

  /* Initialize I2C communication here, since this library can't function
  without it. */
  _deviceAddress  = deviceAddressIn;
  _nChannels      = nChannels;
  _mclr_pin       = mclr_pin;
  _debug_en       = false;

  /* Set MCLR pins and pull HIGH */
  pinMode(_mclr_pin, OUTPUT);
  digitalWrite(_mclr_pin, HIGH);

  /* Float the other pins to prevent interference */
  pinMode(19, INPUT);
  pinMode(18, INPUT);
  pinMode(17, INPUT);
  pinMode(16, INPUT);
  pinMode(3, INPUT);

  /* Initialize "running" and "init" state machine variables. */
  iqs9320_state.state = IQS9320_STATE_START;
  iqs9320_state.init_state = IQS9320_INIT_VERIFY_PRODUCT;
}

/**
  * @name   init
  * @brief  A method that runs through a normal start-up routine to set up the
  *         IQS9320 with the desired settings from the IQS9320_init.h file.
  * @retval Returns true if the full start-up routine has been completed,
  *         returns false if not.
  * @note   - No false return will be given, the program will thus be stuck
  *           when one of the cases is not able to finish.
  *         - See serial communication to find the ERROR case
  */
bool IQS9320::init(void)
{
  uint16_t prod_num;
  uint8_t ver_maj, ver_min;

  switch (iqs9320_state.init_state)
  {
    /* Verifies product number to determine if the correct device is connected
    for this example */
    case IQS9320_INIT_VERIFY_PRODUCT:
      Serial.println("IQS9320_INIT_VERIFY_PRODUCT");
      prod_num = getProductNum(STOP);
      ver_maj = getmajorVersion(STOP);
      ver_min = getminorVersion(STOP);
      Serial.print("\t\tProduct number is: ");
      Serial.print(prod_num);
      Serial.print(" v");
      Serial.print(ver_maj);
      Serial.print(".");
      Serial.println(ver_min);
      if(prod_num == IQS9320_PRODUCT_NUM)
      {
        iqs9320_state.init_state = IQS9320_INIT_READ_RESET;
      }
      else
      {
        Serial.println("\t\tDevice is not a IQS9320!");
        iqs9320_state.init_state = IQS9320_INIT_NONE;
      }
    break;

    /* Verify if a reset has occurred */
    case IQS9320_INIT_READ_RESET:
      Serial.println("IQS9320_INIT_READ_RESET");
      updateInfoFlags(STOP);
      if (checkReset())
      {
        Serial.println("\t\tReset event occurred.");
        iqs9320_state.init_state = IQS9320_INIT_ACK_RESET;
      }
      else
      {
        Serial.println("\t\t No Reset Event Detected - Request SW Reset");
        iqs9320_state.init_state = IQS9320_INIT_CHIP_RESET;
      }
    break;

    /* Perform SW Reset */
    case IQS9320_INIT_CHIP_RESET:
       Serial.println("IQS9320_INIT_CHIP_RESET");

      //Perform SW Reset
      SW_Reset(STOP);
      Serial.println("\t\tSoftware Reset Bit Set.");
      delay(100);
      iqs9320_state.init_state = IQS9320_INIT_READ_RESET;
    break;

    /* Acknowledge that the device went through a reset */
    case IQS9320_INIT_ACK_RESET:
      Serial.println("IQS9320_INIT_ACK_RESET");
      acknowledgeReset(STOP);
      delay(10);
      iqs9320_state.init_state = IQS9320_INIT_UPDATE_SETTINGS;
      break;

    /* Write desired settings to the IQS9320 */
    case IQS9320_INIT_UPDATE_SETTINGS:
      Serial.println("IQS9320_INIT_UPDATE_SETTINGS");
      updateSettings(STOP);
      iqs9320_state.init_state = IQS9320_INIT_DEFAULT_READ_SYS_STATUS;
    break;

    /* Change the default read location to System Control */
    case IQS9320_INIT_DEFAULT_READ_SYS_STATUS:
      Serial.println("IQS9320_INIT_DEFAULT_READ_SYS_STATUS");
      changeDefaultRead(IQS9320_MM_SYSTEM_STATUS, STOP);
      iqs9320_state.init_state = IQS9320_INIT_RECONFIG_DEV;
    break;

    /* Write the reconfig bit and set up the device */
    case IQS9320_INIT_RECONFIG_DEV:
      Serial.println("IQS9320_INIT_RECONFIG_DEV");
      reconfigureDevice(STOP);
      delay(10);
      iqs9320_state.init_state = IQS9320_INIT_ATI;
    break;

    /* Run the ATI algorithm to recalibrate the device with newly added settings */
    case IQS9320_INIT_ATI:
      Serial.println("IQS9320_INIT_ATI");
      ReATI(STOP);
      iqs9320_state.init_state = IQS9320_INIT_WAIT_FOR_ATI;
      Serial.println("IQS9320_INIT_WAIT_FOR_ATI");
    break;

    /* Read the ATI Active bit to see if the rest of the program can continue */
    case IQS9320_INIT_WAIT_FOR_ATI:
      delay(10);
      if(!readATIactive())
      {
        Serial.println("\t\tDONE");
        iqs9320_state.init_state = IQS9320_INIT_RESEED;
      }
    break;

    /* Ressed the counts to match LTA after device is configured */
    case IQS9320_INIT_RESEED:
      Serial.println("IQS9320_INIT_RESEED");
      ReSeed(STOP);
      iqs9320_state.init_state = IQS9320_INIT_READ_DATA;
    break;

    /* Read the latest data from the iqs9320 */
    case IQS9320_INIT_READ_DATA:
      Serial.println("IQS9320_INIT_READ_DATA");
      queueValueUpdates();
      delay(10);
      queueValueUpdates();
      delay(10);
      iqs9320_state.init_state = IQS9320_INIT_DONE;
    break;

    /* If all operations have been completed correctly, the RDY pin can be set
     * up as an interrupt to indicate when new data is available */
    case IQS9320_INIT_DONE:
      Serial.println("IQS9320_INIT_DONE\n");
      Serial.print("\e[s");
      new_data_available = true;
      return true;
    break;

    default:
      break;
  }
  return false;
}

/**
  * @name   run
  * @brief  This method is called continuously during runtime, which serves as
  *         the main state machine.
  * @param  None.
  * @retval None.
  * @note   The state machine continuously checks for specific events and
  *         updates the state machine accordingly. A reset event will cause
  *         the state machine to re-initialize the device.
  *
  *         queueValueUpdates can be edited by the user if other data should be
  *         read every time a RDY window is received.
  */
void IQS9320::run(void)
{
  switch (iqs9320_state.state)
  {
    /* After a hardware reset, this is the starting position of the main
    state machine */
    case IQS9320_STATE_START:
      iqs9320_state.state = IQS9320_STATE_INIT;
    break;

    /* Perform the initialization routine on the IQS9320 */
    case IQS9320_STATE_INIT:
      if(init())
      {
        iqs9320_state.state = IQS9320_STATE_IDLE;
      }
    break;

    /* Send an I2C software reset in the next RDY window */
    case IQS9320_STATE_SW_RESET:
      SW_Reset(STOP);
      iqs9320_state.state = IQS9320_STATE_RUN;
    break;

    /* Continuous reset monitoring state, ensure no reset event has occurred
    for data to be valid */
    case IQS9320_STATE_CHECK_RESET:
      if(checkReset())
      {
        Serial.println("Reset Occurred!\n");
        new_data_available = false;
        iqs9320_state.state = IQS9320_STATE_START;
        iqs9320_state.init_state = IQS9320_INIT_VERIFY_PRODUCT;
      }

      /* A reset did not occur, move to the run state and wait for a new ready
      window */
      else
      {
        new_data_available = true; /* No reset, thus data is valid */
        iqs9320_state.state = IQS9320_STATE_IDLE;
      }
    break;

    /* If a RDY Window is open, read the latest values from the IQS9320 */
    case IQS9320_STATE_RUN:
      queueValueUpdates();
      new_data_available = false;
      iqs9320_state.state = IQS9320_STATE_CHECK_RESET;
    break;

    /* Idle State for the IQS9320, the user should request new data to promt
    the IQS9320 to change state */
    case IQS9320_STATE_IDLE:
    break;
  }
}

/**
  * @name   requestData
  * @brief  Request the IQS9320 to perform its main loop and return new
  *         infromation from the device.
  * @param  None.
  * @retval None..
*/
void IQS9320::requestData(void)
{
  iqs9320_state.state = IQS9320_STATE_RUN;
}

/**
  * @name   queueValueUpdates
  * @brief  All I2C read operations in the queueValueUpdates method will be
  *         performed each time the IQS9320 opens a RDY window.
  * @param  None.
  * @retval None.
  * @note   Any Address in the IQS9320 memory map can be read from here.
  */
void IQS9320::queueValueUpdates(void)
{
  uint8_t transferBytes[40];	// The array which will hold the bytes to be transferred.

  #ifdef IQS9320_V0_7
  uint8_t bytes_per_field = 4;  // Calculate how many bytes is required to fit all the channels
  uint8_t total_bytes = 2+(3*bytes_per_field); // Calculate the total bytes to read
  #endif
  #ifdef IQS9320_V0_4
  uint8_t bytes_per_field = _nChannels/8 + 1;  // Calculate how many bytes is required to fit all the channels
  uint8_t total_bytes = 2+(2*bytes_per_field); // Calculate the total bytes to read
  #endif

	/* Read the info flags. 2 System flags bytes for activation and filter halt */
  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_STATUS, total_bytes, transferBytes, STOP);
	// readOnly(_deviceAddress, 2+(2*bytes_per_field), transferBytes, STOP);

	/* Assign the System Status */
  IQSMemoryMap.SYSTEM_STATUS[0] =  transferBytes[0];
  IQSMemoryMap.SYSTEM_STATUS[1] =  transferBytes[1];

  for(uint8_t i = 0; i < bytes_per_field; i++)
  {
    #ifdef IQS9320_V0_7
      /* Assign the ATI Error Flags */
      IQSMemoryMap.ATI_ERROR[i] =  transferBytes[2+i];
      /* Assign the Filter Halt Flags */
      IQSMemoryMap.FILTER_HALT_FLAGS[i] =  transferBytes[2+bytes_per_field+i];
      /* Assign the Activation Flags */
      IQSMemoryMap.ACTIVATION_FLAGS[i] =  transferBytes[2+2*bytes_per_field+i];
    #endif
    #ifdef IQS9320_V0_4
        /* Assign the Activation Flags */
        IQSMemoryMap.ACTIVATION_FLAGS[i] =  transferBytes[2+i];
        /* Assign the Filter Halt Flags */
        IQSMemoryMap.FILTER_HALT_FLAGS[i] =  transferBytes[2+bytes_per_field+i];
    #endif
  }

  /* Stream delta when debug is enabled */
  if(_debug_en)
  {
    /* Calculate the start address for Normalized delta base on total active channels */
    uint16_t address = IQS9320_MM_ACTIVATION_FLAGS + 3*bytes_per_field;
    if((address & 0x0001) == 1)
    {
      address++;
    }

    readRandomBytes16(_deviceAddress, address, _nChannels, transferBytes, STOP);
    for(uint8_t i = 0; i < _nChannels; i++)
    {
      IQSMemoryMap.CH_NORM_DELTA[i] = transferBytes[i];
    }

    /* Calculate the start address for Movement base on total active channels */
    address = address + (_nChannels);

    readRandomBytes16(_deviceAddress, address, _nChannels, transferBytes, STOP);
    for(uint8_t i = 0; i < _nChannels; i++)
    {
      IQSMemoryMap.CH_MOVEMENT[i] = transferBytes[i];
    }

    /* Calculate the start address for Delta base on total active channels */
    address = address + (_nChannels);

    readRandomBytes16(_deviceAddress, address, _nChannels*2, transferBytes, STOP);
    for(uint8_t i = 0; i < _nChannels*2; i++)
    {
      IQSMemoryMap.CH_DELTA[i] = transferBytes[i];
    }
  }
}

/**
  * @name	  readATIactive
  * @brief  A method that checks if the ATI routine is still active
  * @param  None.
  * @retval Returns true if the ATI_ACTIVE_BIT is cleared, false if the
  *         ATI_ACTIVE_BIT is set.
  * @note   If the ATI routine is active the channel states (NONE, PROX, TOUCH)
  *         might exhibit unwanted behaviour. Thus it is advised to wait for
  *         the routine to complete before continuing.
  */
bool IQS9320::readATIactive(void)
{
  /* Read the Info flags */
  updateInfoFlags(STOP);

  /* Return the ATI Active status */
  return getBit(IQSMemoryMap.SYSTEM_STATUS[0], IQS9320_ATI_ACTIVE_BIT);
}

/**
  * @name	  checkReset
  * @brief  A method that checks if the device has reset and returns the reset
  *         status.
  * @param  None.
  * @retval Returns true if a reset has occurred, false if no reset has occurred.
  * @note   If a reset has occurred the device settings should be reloaded using
  *         the begin function. After new device settings have been reloaded
  *         the acknowledge reset function can be used to clear the reset flag.
  */
bool IQS9320::checkReset(void)
{
	/* Perform a bitwise AND operation with the SHOW_RESET_BIT to return the
  reset status */
  return getBit(IQSMemoryMap.SYSTEM_STATUS[0], IQS9320_SHOW_RESET_BIT);
}

/**
  * @name	  checkProductNum
  * @brief  A method that checks the device product number and compares the
  *         result to the defined value to return a boolean result.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *                           Use the STOP and RESTART definitions.
  * @retval Returns the product number as a unit16_t value.
  * @note   If the product is not correctly identified an appropriate messages
  *         should be displayed.
  */
uint16_t IQS9320::getProductNum(bool stopOrRestart)
{
	uint8_t transferBytes[2];	      // A temporary array to hold the byte to be transferred.
  uint8_t prodNumLow = 0;         // Temporary storage for the Counts low byte.
  uint8_t prodNumHigh = 0;        // Temporary storage for the Counts high byte.
  uint16_t prodNumReturn = 0;     // The 16bit return value.

	/* Read the Device info from the IQS9320. */
	readRandomBytes16(_deviceAddress, IQS9320_MM_PROD_NUM, 2, transferBytes, stopOrRestart);

  /* Construct the 16bit return value. */
  prodNumLow = transferBytes[0];
  prodNumHigh = transferBytes[1];
  prodNumReturn = (uint16_t)(prodNumLow);
  prodNumReturn |= (uint16_t)(prodNumHigh<<8);
  /* Return the Counts value. */
  return prodNumReturn;
}

/**
  * @name	getmajorVersion
  * @brief  A method that checks the device firmware version's major value.
  * @param  stopOrRestart -> Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *                          Use the STOP and RESTART definitions.
  * @retval Returns major version number as a uint8_t value.
  */
uint8_t IQS9320::getmajorVersion(bool stopOrRestart)
{
	uint8_t transferBytes[2];	// A temporary array to hold the byte to be transferred.
  uint8_t ver_maj = 0;      // Temporary storage for the firmware version major number.

	/* Read the Device info from the IQS9320. */
	readRandomBytes16(_deviceAddress, IQS9320_MM_MAJOR_VERSION_NUM, 2, transferBytes, stopOrRestart);

  /* Get major value from correct byte */
  ver_maj = transferBytes[0];
  /* Return the major firmware version number value. */
  return ver_maj;
}

/**
  * @name	getminorVersion
  * @brief  A method that checks the device firmware version's minor value.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *                           Use the STOP and RESTART definitions.
  * @retval Returns minor version number as a unit8_t value.
  */
uint8_t IQS9320::getminorVersion(bool stopOrRestart)
{
	uint8_t transferBytes[2];	// A temporary array to hold the byte to be transferred.
  uint8_t ver_min = 0;      // Temporary storage for the firmware version minor number.

	/* Read the Device info from the IQS9320. */
	readRandomBytes16(_deviceAddress, IQS9320_MM_MINOR_VERSION_NUM, 2, transferBytes, stopOrRestart);
  /* get major value from correct byte */
  ver_min = transferBytes[0];
  /* Return the minor firmware version number value. */
  return ver_min;
}

/**
  * @name	acknowledgeReset
  * @brief  A method that clears the Reset Event bit by writing it to a 0.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *                           Use the STOP and RESTART definitions.
  * @retval None.
  * @note   If a reset has occurred the device settings should be reloaded using
  *         the begin function. After new device settings have been reloaded
  *         this method should be used to clear the reset bit.
  */
void IQS9320::acknowledgeReset(bool stopOrRestart)
{
	uint8_t transferByte[2];	// A temporary array to hold the bytes to be transferred.
	/* Read the System Flags from the IQS9320, these must be read first in order
  not to change any settings. */
	readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, STOP);
	/* Set the the ACK_RESET_BIT in the SYSTEM_CONTROL register */
	transferByte[0] = setBit(transferByte[0], IQS9320_ACK_RESET_BIT);
	/* Write the new byte to the System Flags address. */
	writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, stopOrRestart);
}

/**
  * @name   ReATI
  * @brief  A method which sets the REDO_ATI_BIT in order to force the IQS9320
  *         device to run the Automatic Tuning Implementation (ATI) routine.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *                           Use the STOP and RESTART definitions.
  * @retval None.
  * @note   I2C communications are disabled for the duration of the ATI process.
  */
void IQS9320::ReATI(bool stopOrRestart)
{
  uint8_t transferByte[2]; // Array to store the bytes transferred.

  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONFIGURATION, 2, transferByte, STOP);
  transferByte[0] = setBit(transferByte[0], 3); /* Enable ATI */
  transferByte[0] = setBit(transferByte[0], 5); /* Enable ATI on Configure */
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONFIGURATION, 2, transferByte, STOP);

  /* Reconfigure device to enable ATI */
  reconfigureDevice(STOP);

  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, STOP);
  /* Set the the RE_ATI_BIT in the SYSTEM_CONTROL register */
  transferByte[0] = setBit(transferByte[0], IQS9320_RE_ATI_BIT);
  /* Write the new byte to the required device. */
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, stopOrRestart);
}

/**
  * @name   ReReSeedATI
  * @brief  A method which sets the IQS9320_RESEED_BIT in order to force the IQS9320
  *         device to reseed the counts.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *                           Use the STOP and RESTART definitions.
  * @retval None.
  * @note   I2C communications are disabled for the duration of the ATI process.
  */
void IQS9320::ReSeed(bool stopOrRestart)
{
  uint8_t transferByte[2]; // Array to store the bytes transferred.

  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, STOP);
  /* Set the the IQS9320_RESEED_BIT in the SYSTEM_CONTROL register */
  transferByte[0] = setBit(transferByte[0], IQS9320_RESEED_BIT);
  /* Write the new byte to the required device. */
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, stopOrRestart);
}

/**
  * @name   SW_Reset
  * @brief  A method that sets the SW RESET bit to force the IQS9320 device to
  *         do a software reset.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *                           Use the STOP and RESTART definitions.
  * @retval None.
  * @note   To perform SW Reset, bit IQS9320_SW_RESET_BIT in SYSTEM_CONTROL is set.
  */
void IQS9320::SW_Reset(bool stopOrRestart)
{
  uint8_t transferByte[2]; // Array to store the bytes transferred.

  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, STOP);
  /* Set the the SW_RESET_BIT in the SYSTEM_CONTROL register */
  transferByte[0] = setBit(transferByte[0], IQS9320_SW_RESET_BIT);
  /* Write the new byte to the required device. */
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, stopOrRestart);
}

/**
  * @name   updateInfoFlags
  * @brief  A method that reads the info flags from the IQS9320 and assigns
  *         it to the local SYSTEM_STATUS register.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *              			        Use the STOP and RESTART definitions.
  * @retval None.
  * @note   The local SYSTEM_STATUS register is altered with the new value of
  *         the info flags register, retrieved from the IQS9320.
  */
void IQS9320::updateInfoFlags(bool stopOrRestart)
{
	uint8_t transferBytes[2];	// The array which will hold the bytes to be transferred.

	/* Read the info flags. */
	readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_STATUS, 2, transferBytes, stopOrRestart);
	/* Assign the info flags to the local SYSTEM_STATUS register */
  IQSMemoryMap.SYSTEM_STATUS[0] =  transferBytes[0];
  IQSMemoryMap.SYSTEM_STATUS[1] =  transferBytes[1];
}

/**
  * @name   DebugOn
  * @brief  A method that turns on debug streaming that adds delta values to the
  *         streaming buffer.
  * @param  None
  * @retval None.
  */
void IQS9320::DebugOn(void)
{
  _debug_en = true;
}

/**
  * @name   DebugOff
  * @brief  A method that turns off debug streaming that adds delta values to the
  *         streaming buffer.
  * @param  None
  * @retval None.
  */
void IQS9320::DebugOff(void)
{
  _debug_en = false;
}

/**
  * @name   updateSettings
  * @brief  A method that writes in the settings to set up the device.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *              			        Use the STOP and RESTART definitions.
  * @retval None.
  * @note   The local IQSMemoryMap registers should be altered with new values
  *         before this function is called.
  */
void IQS9320::updateSettings(bool stopOrRestart)
{
  uint8_t transferBytes[30];

  /* Change the Device Configuration */
  /* Memory Map Position 0x2000 - 0x2007 */
  transferBytes[0]  = SYSTEM_CONTROL_0;
  transferBytes[1]  = SYSTEM_CONTROL_1;
  transferBytes[2]  = SYSTEM_CONFIG_0;
  transferBytes[3]  = SYSTEM_CONFIG_1;
  transferBytes[4]  = NP_SAMPLING_INTERVAL_0;
  transferBytes[5]  = NP_SAMPLING_INTERVAL_1;
  transferBytes[6]  = NP_TIMEOUT_0;
  transferBytes[7]  = NP_TIMEOUT_1;
  transferBytes[8]  = LP_SAMPLING_INTERVAL_0;
  transferBytes[9]  = LP_SAMPLING_INTERVAL_1;
  transferBytes[10]  = LP_TIMEOUT_0;
  transferBytes[11] = LP_TIMEOUT_1;
  transferBytes[12] = ULP_SAMPLING_INTERVAL_0;
  transferBytes[13] = ULP_SAMPLING_INTERVAL_1;
  transferBytes[14] = ULP_TIMEOUT_0;
  transferBytes[15] = ULP_TIMEOUT_1;
  transferBytes[16] = DEFAULT_READ_LOCATION_0;
  transferBytes[17] = DEFAULT_READ_LOCATION_1;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 18, transferBytes, STOP);
  Serial.println("\t\t1. Write Device Configuration");

  /* Change the Mirror Selection CH 0-9 */
  /* Memory Map Position 0x3000 - 0x3009 */
  transferBytes[0]  = MIRROR_SEL_CH0_0;
  transferBytes[1]  = MIRROR_SEL_CH0_1;
  transferBytes[2]  = MIRROR_SEL_CH1_0;
  transferBytes[3]  = MIRROR_SEL_CH1_1;
  transferBytes[4]  = MIRROR_SEL_CH2_0;
  transferBytes[5]  = MIRROR_SEL_CH2_1;
  transferBytes[6]  = MIRROR_SEL_CH3_0;
  transferBytes[7]  = MIRROR_SEL_CH3_1;
  transferBytes[8]  = MIRROR_SEL_CH4_0;
  transferBytes[9]  = MIRROR_SEL_CH4_1;
  transferBytes[10] = MIRROR_SEL_CH5_0;
  transferBytes[11] = MIRROR_SEL_CH5_1;
  transferBytes[12] = MIRROR_SEL_CH6_0;
  transferBytes[13] = MIRROR_SEL_CH6_1;
  transferBytes[14] = MIRROR_SEL_CH7_0;
  transferBytes[15] = MIRROR_SEL_CH7_1;
  transferBytes[16] = MIRROR_SEL_CH8_0;
  transferBytes[17] = MIRROR_SEL_CH8_1;
  transferBytes[18] = MIRROR_SEL_CH9_0;
  transferBytes[19] = MIRROR_SEL_CH9_1;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_MIRROR_SELECTION_CH0, 20, transferBytes, STOP);
  Serial.println("\t\t2. Write Mirror Selection CH 0-9");

  /* Change the Mirror Selection CH 10-19 */
  /* Memory Map Position 0x3014 - 0x301D */
  transferBytes[0]  = MIRROR_SEL_CH10_0;
  transferBytes[1]  = MIRROR_SEL_CH10_1;
  transferBytes[2]  = MIRROR_SEL_CH11_0;
  transferBytes[3]  = MIRROR_SEL_CH11_1;
  transferBytes[4]  = MIRROR_SEL_CH12_0;
  transferBytes[5]  = MIRROR_SEL_CH12_1;
  transferBytes[6]  = MIRROR_SEL_CH13_0;
  transferBytes[7]  = MIRROR_SEL_CH13_1;
  transferBytes[8]  = MIRROR_SEL_CH14_0;
  transferBytes[9]  = MIRROR_SEL_CH14_1;
  transferBytes[10] = MIRROR_SEL_CH15_0;
  transferBytes[11] = MIRROR_SEL_CH15_1;
  transferBytes[12] = MIRROR_SEL_CH16_0;
  transferBytes[13] = MIRROR_SEL_CH16_1;
  transferBytes[14] = MIRROR_SEL_CH17_0;
  transferBytes[15] = MIRROR_SEL_CH17_1;
  transferBytes[16] = MIRROR_SEL_CH18_0;
  transferBytes[17] = MIRROR_SEL_CH18_1;
  transferBytes[18] = MIRROR_SEL_CH19_0;
  transferBytes[19] = MIRROR_SEL_CH19_1;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_MIRROR_SELECTION_CH10, 20, transferBytes, STOP);
  Serial.println("\t\t3. Write Mirror Selection CH 10-19");

  /* Change the Calibration Parameters CH 0-9 */
  /* Memory Map Position 0x3028 - 0x3031 */
  transferBytes[0]  = CALIB_STEP_CH0;
  transferBytes[1]  = CALIB_CORRECT_CH0;
  transferBytes[2]  = CALIB_STEP_CH1;
  transferBytes[3]  = CALIB_CORRECT_CH1;
  transferBytes[4]  = CALIB_STEP_CH2;
  transferBytes[5]  = CALIB_CORRECT_CH2;
  transferBytes[6]  = CALIB_STEP_CH3;
  transferBytes[7]  = CALIB_CORRECT_CH3;
  transferBytes[8]  = CALIB_STEP_CH4;
  transferBytes[9]  = CALIB_CORRECT_CH4;
  transferBytes[10] = CALIB_STEP_CH5;
  transferBytes[11] = CALIB_CORRECT_CH5;
  transferBytes[12] = CALIB_STEP_CH6;
  transferBytes[13] = CALIB_CORRECT_CH6;
  transferBytes[14] = CALIB_STEP_CH7;
  transferBytes[15] = CALIB_CORRECT_CH7;
  transferBytes[16] = CALIB_STEP_CH8;
  transferBytes[17] = CALIB_CORRECT_CH8;
  transferBytes[18] = CALIB_STEP_CH9;
  transferBytes[19] = CALIB_CORRECT_CH9;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_CALIBRATION_PARAMETERS_CH0, 20, transferBytes, STOP);
  Serial.println("\t\t4. Write Calibration Parameters CH 0-9");

  /* Change the Calibration Parameters CH 10-19 */
  /* Memory Map Position 0x3042 - 0x304B */
  transferBytes[0]  = CALIB_STEP_CH10;
  transferBytes[1]  = CALIB_CORRECT_CH10;
  transferBytes[2]  = CALIB_STEP_CH11;
  transferBytes[3]  = CALIB_CORRECT_CH11;
  transferBytes[4]  = CALIB_STEP_CH12;
  transferBytes[5]  = CALIB_CORRECT_CH12;
  transferBytes[6]  = CALIB_STEP_CH13;
  transferBytes[7]  = CALIB_CORRECT_CH13;
  transferBytes[8]  = CALIB_STEP_CH14;
  transferBytes[9]  = CALIB_CORRECT_CH14;
  transferBytes[10] = CALIB_STEP_CH15;
  transferBytes[11] = CALIB_CORRECT_CH15;
  transferBytes[12] = CALIB_STEP_CH16;
  transferBytes[13] = CALIB_CORRECT_CH16;
  transferBytes[14] = CALIB_STEP_CH17;
  transferBytes[15] = CALIB_CORRECT_CH17;
  transferBytes[16] = CALIB_STEP_CH18;
  transferBytes[17] = CALIB_CORRECT_CH18;
  transferBytes[18] = CALIB_STEP_CH19;
  transferBytes[19] = CALIB_CORRECT_CH19;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_CALIBRATION_PARAMETERS_CH10, 20, transferBytes, STOP);
  Serial.println("\t\t5. Write Calibration Parameters CH 10-19");

  /* Change the Effective Max Delta CH 0-9 */
  /* Memory Map Position 0x3050 - 0x3059 */
  transferBytes[0]  = MAX_DELTA_E_0_0;
  transferBytes[1]  = MAX_DELTA_E_0_1;
  transferBytes[2]  = MAX_DELTA_E_1_0;
  transferBytes[3]  = MAX_DELTA_E_1_1;
  transferBytes[4]  = MAX_DELTA_E_2_0;
  transferBytes[5]  = MAX_DELTA_E_2_1;
  transferBytes[6]  = MAX_DELTA_E_3_0;
  transferBytes[7]  = MAX_DELTA_E_3_1;
  transferBytes[8]  = MAX_DELTA_E_4_0;
  transferBytes[9]  = MAX_DELTA_E_4_1;
  transferBytes[10] = MAX_DELTA_E_5_0;
  transferBytes[11] = MAX_DELTA_E_5_1;
  transferBytes[12] = MAX_DELTA_E_6_0;
  transferBytes[13] = MAX_DELTA_E_6_1;
  transferBytes[14] = MAX_DELTA_E_7_0;
  transferBytes[15] = MAX_DELTA_E_7_1;
  transferBytes[16] = MAX_DELTA_E_8_0;
  transferBytes[17] = MAX_DELTA_E_8_1;
  transferBytes[18] = MAX_DELTA_E_9_0;
  transferBytes[19] = MAX_DELTA_E_9_1;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_EFFECTIVE_MAX_DELTA_CH0, 20, transferBytes, STOP);
  Serial.println("\t\t6. Write Effective Max Delta CH 0-9");

  /* Change the Effective Max Delta CH 10-19 */
  /* Memory Map Position 0x3064 - 0x306D */
  transferBytes[0]  = MAX_DELTA_E_10_0;
  transferBytes[1]  = MAX_DELTA_E_10_1;
  transferBytes[2]  = MAX_DELTA_E_11_0;
  transferBytes[3]  = MAX_DELTA_E_11_1;
  transferBytes[4]  = MAX_DELTA_E_12_0;
  transferBytes[5]  = MAX_DELTA_E_12_1;
  transferBytes[6]  = MAX_DELTA_E_13_0;
  transferBytes[7]  = MAX_DELTA_E_13_1;
  transferBytes[8]  = MAX_DELTA_E_14_0;
  transferBytes[9]  = MAX_DELTA_E_14_1;
  transferBytes[10] = MAX_DELTA_E_15_0;
  transferBytes[11] = MAX_DELTA_E_15_1;
  transferBytes[12] = MAX_DELTA_E_16_0;
  transferBytes[13] = MAX_DELTA_E_16_1;
  transferBytes[14] = MAX_DELTA_E_17_0;
  transferBytes[15] = MAX_DELTA_E_17_1;
  transferBytes[16] = MAX_DELTA_E_18_0;
  transferBytes[17] = MAX_DELTA_E_18_1;
  transferBytes[18] = MAX_DELTA_E_19_0;
  transferBytes[19] = MAX_DELTA_E_19_1;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_EFFECTIVE_MAX_DELTA_CH10, 20, transferBytes, STOP);
  Serial.println("\t\t7. Write Effective Max Delta CH 10-19");

  /* Change the Individual Thresholds */
  transferBytes[0]  = INDIVIDUAL_THRESHOLDS_0;
  transferBytes[1]  = INDIVIDUAL_THRESHOLDS_1;
  transferBytes[2]  = INDIVIDUAL_THRESHOLDS_2;
  transferBytes[3]  = INDIVIDUAL_THRESHOLDS_3;
  transferBytes[4]  = INDIVIDUAL_THRESHOLDS_4;
  transferBytes[5]  = INDIVIDUAL_THRESHOLDS_5;
  transferBytes[6]  = INDIVIDUAL_THRESHOLDS_6;
  transferBytes[7]  = INDIVIDUAL_THRESHOLDS_7;
  transferBytes[8]  = INDIVIDUAL_THRESHOLDS_8;
  transferBytes[9]  = INDIVIDUAL_THRESHOLDS_9;
  transferBytes[10] = INDIVIDUAL_THRESHOLDS_10;
  transferBytes[11] = INDIVIDUAL_THRESHOLDS_11;
  transferBytes[12] = INDIVIDUAL_THRESHOLDS_12;
  transferBytes[13] = INDIVIDUAL_THRESHOLDS_13;
  transferBytes[14] = INDIVIDUAL_THRESHOLDS_14;
  transferBytes[15] = INDIVIDUAL_THRESHOLDS_15;
  transferBytes[16] = INDIVIDUAL_THRESHOLDS_16;
  transferBytes[17] = INDIVIDUAL_THRESHOLDS_17;
  transferBytes[18] = INDIVIDUAL_THRESHOLDS_18;
  transferBytes[19] = INDIVIDUAL_THRESHOLDS_19;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_INDIVIDUAL_THRESHOLDS_CH0, 20, transferBytes, STOP);
  Serial.println("\t\t8. Write Individual Thresholds");

  /* Change the Channel Select and Disable */
  transferBytes[0]  = CYCLE_0_SELECT;
  transferBytes[1]  = CYCLE_1_SELECT;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_CYCLE_0_CHANNELS, 2, transferBytes, STOP);
  Serial.println("\t\t9. Write Channel Select and Disable");

  /* Change the Rx Select */
  transferBytes[0]  = RX_SELECT_0;
  transferBytes[1]  = RX_SELECT_1;
  transferBytes[2]  = RX_SELECT_2;
  transferBytes[3]  = RX_SELECT_3;
  transferBytes[4]  = RX_SELECT_4;
  transferBytes[5]  = RX_SELECT_5;
  transferBytes[6]  = RX_SELECT_6;
  transferBytes[7]  = RX_SELECT_7;
  transferBytes[8]  = RX_SELECT_8;
  transferBytes[9]  = RX_SELECT_9;
  transferBytes[10] = RX_SELECT_10;
  transferBytes[11] = RX_SELECT_11;
  transferBytes[12] = RX_SELECT_12;
  transferBytes[13] = RX_SELECT_13;
  transferBytes[14] = RX_SELECT_14;
  transferBytes[15] = RX_SELECT_15;
  transferBytes[16] = RX_SELECT_16;
  transferBytes[17] = RX_SELECT_17;
  transferBytes[18] = RX_SELECT_18;
  transferBytes[19] = RX_SELECT_19;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_RX_SELECT, 20, transferBytes, STOP);
  Serial.println("\t\t10. Write Rx Select");

  /* Change the Tx Select */
  transferBytes[0]  = TX_SELECT_0;
  transferBytes[1]  = TX_SELECT_1;
  transferBytes[2]  = TX_SELECT_2;
  transferBytes[3]  = TX_SELECT_3;
  transferBytes[4]  = TX_SELECT_4;
  transferBytes[5]  = TX_SELECT_5;
  transferBytes[6]  = TX_SELECT_6;
  transferBytes[7]  = TX_SELECT_7;
  transferBytes[8]  = TX_SELECT_8;
  transferBytes[9]  = TX_SELECT_9;
  transferBytes[10] = TX_SELECT_10;
  transferBytes[11] = TX_SELECT_11;
  transferBytes[12] = TX_SELECT_12;
  transferBytes[13] = TX_SELECT_13;
  transferBytes[14] = TX_SELECT_14;
  transferBytes[15] = TX_SELECT_15;
  transferBytes[16] = TX_SELECT_16;
  transferBytes[17] = TX_SELECT_17;
  transferBytes[18] = TX_SELECT_18;
  transferBytes[19] = TX_SELECT_19;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_TX_SELECT, 20, transferBytes, STOP);
  Serial.println("\t\t11. Write Tx Select");

  /* Change the ATI Target and Band */
  transferBytes[0]  = ATI_TARGET_0;
  transferBytes[1]  = ATI_TARGET_1;
  transferBytes[2]  = ATI_BAND_0;
  transferBytes[3]  = ATI_BAND_1;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_ATI_TARGET, 4, transferBytes, STOP);
  Serial.println("\t\t12. Write ATI Target and Band");

  /* Change the Thresholds */
  transferBytes[0]  = ACTIVATION_THRESHOLD;
  transferBytes[1]  = REFERENCE_HALT_THRESHOLD;
  transferBytes[2]  = FAST_REF_THRESHOLD;
  transferBytes[3]  = MOVEMENT_THRESHOLD;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_ACTIVATION_THRESHOLD, 4, transferBytes, STOP);
  Serial.println("\t\t13. Write Thresholds");

  /* Change the Filter Values */
  transferBytes[0]  = BETA_LTA_NP;
  transferBytes[1]  = BETA_LTA_LP;
  transferBytes[2]  = BETA_LTA_ULP;
  transferBytes[3]  = BETA_FAST_LTA_NP;
  transferBytes[4]  = BETA_FAST_LTA_LP;
  transferBytes[5]  = BETA_FAST_LTA_ULP;
  transferBytes[6]  = BETA_COUNTS_NP;
  transferBytes[7]  = BETA_COUNTS_LP;
  transferBytes[8]  = BETA_COUNTS_ULP;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_LTA_BETA_FILTER, 9, transferBytes, STOP);
  Serial.println("\t\t14. Write Filter Values");

  /* Change the Reference Halt Timeout */
  transferBytes[0]  = REF_HALT_TIMEOUT_0;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_REFERENCE_HALT_TIMEOUT, 1, transferBytes, STOP);
  Serial.println("\t\t15. Write Reference Halt Timeout");

  /* Change the Activation Hysteresis */
  transferBytes[0]  = ACTIVATION_HYSTERESIS_0;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_ACTIVATION_HYSTERESIS, 1, transferBytes, STOP);
  Serial.println("\t\t16. Write Activation Hysteresis");

  #ifdef IQS9320_V0_7
  /* Change the Timing Generator Settings */
  /* Memory Map Position 0x3146 - 0x3147 */
  transferBytes[0]  = TIMING_GENERATOR_0;
  transferBytes[1]  = TIMING_GENERATOR_0;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_ACTIVATION_HYSTERESIS, 1, transferBytes, STOP);
  Serial.println("\t\t17. Write Timing Generator Settings");

  /* Change the Hardware Settings */
  /* Memory Map Position 0x3148 - 0x3149 */
  transferBytes[0]  = HARDWARE_SETTINGS_0;
  transferBytes[1]  = HARDWARE_SETTINGS_1;
  writeRandomBytes16(_deviceAddress, IQS9320_MM_ACTIVATION_HYSTERESIS, 1, transferBytes, STOP);
  Serial.println("\t\t18. Write Hardware Settings");
  #endif
}

/**
  * @name   reconfigureDevice
  * @brief  A method that calls the reconfigure bit to upload and use all settings
  * previously defined to the IQS9320.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *              			        Use the STOP and RESTART definitions.
  * @retval None.
  * @note   This bit should always be called after settings has been changed in order
  *         for it to take effect.
  */
void IQS9320::reconfigureDevice(bool stopOrRestart)
{
  uint8_t transferByte[2]; // Array to store the bytes transferred.

  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, STOP);
  /* Set the the RECONFIG_DEV_BIT in the SYSTEM_CONTROL register */
  transferByte[0] = setBit(transferByte[0], IQS9320_RECONFIG_DEV_BIT);
  /* Write the new byte to the required device. */
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, stopOrRestart);

}

/**
  * @name   enableMovement
  * @brief  A method that enables or disbales the movement tracking.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *              			        Use the STOP and RESTART definitions.
  * @retval None.
  * @note   This bit should always be called after settings has been changed in order
  *         for it to take effect.
  */
void IQS9320::enableMovement(bool enable, bool stopOrRestart)
{
  uint8_t transferByte[2]; // Array to store the bytes transferred.

  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONFIGURATION, 2, transferByte, STOP);

  /* Set the the IQS9320_MOVE_EN_BIT in the IQS9320_MM_SYSTEM_CONFIGURATION register */
  if(enable)
  {
    transferByte[1] = setBit(transferByte[1], IQS9320_MOVE_EN_BIT);
  }
  else
  {
    transferByte[1] = clearBit(transferByte[1], IQS9320_MOVE_EN_BIT);
  }

  /* Write the new byte to the required device. */
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONFIGURATION, 2, transferByte, stopOrRestart);
  reconfigureDevice(STOP);
}

/**
  * @name   reconfigureDevice
  * @brief  A method that calls the execute callibration bit to run the POSC
  * callibration routine.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *              			        Use the STOP and RESTART definitions.
  * @retval None.
  * @note   This bit should always be called after settings has been changed and ATI
  *         is completed in order for it to take effect.
  */
void IQS9320::executeCallibration(bool stopOrRestart)
{
  uint8_t transferByte[2]; // Array to store the bytes transferred.

  readRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, STOP);
  /* Set the the IQS9320_EXE_CALLIBRATION_BIT in the SYSTEM_CONTROL register */
  transferByte[0] = setBit(transferByte[0], IQS9320_EXE_CALLIBRATION_BIT);
  /* Write the new byte to the required device. */
  writeRandomBytes16(_deviceAddress, IQS9320_MM_SYSTEM_CONTROL, 2, transferByte, stopOrRestart);

}

/**
  * @name   readATIMirrors
  * @brief  A method that reads the ATI Mirrors and save it to memory.
  * callibration routine.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *              			        Use the STOP and RESTART definitions.
  * @retval None.
  * @note
  */
void IQS9320::readATIMirrors(bool stopOrRestart)
{
  readRandomBytes16(_deviceAddress, IQS9320_MM_MIRROR_SELECTION_CH0, 40, IQSMemoryMap.MIRROR_SELECTION, STOP);
}

/**
  * @name   changeDefaultRead
  * @brief  A method that changes the default read address on the IQS9320.
  * @param  stopOrRestart ->  Specifies whether the communications window must
  *                           be kept open or must be closed after this action.
  *              			        Use the STOP and RESTART definitions.
  * @retval None.
  * @note   This bit should always be called after settings has been changed in order
  *         for it to take effect.
*/
void IQS9320::changeDefaultRead(uint16_t read_address, bool stopOrRestart)
{
  uint8_t transferByte[2]; // Array to store the bytes transferred.
  transferByte[0] = ((uint16_t)read_address >> 0) & 0xFF;
  transferByte[1] = ((uint16_t)read_address >> 8) & 0xFF;

  writeRandomBytes16(_deviceAddress, IQS9320_MM_DEFAULT_READ_LOCATION, 2, transferByte, stopOrRestart);
}

/**
  * @name   getChannelActivation
  * @brief  A method that returns the current activation bit for the chosen channel.
  * @param  ch ->  The channel for which the activation bit is returned
  * @retval bool -> true or false depending on the activation
*/
bool IQS9320::getChannelActivation(iqs9320_channel_e ch)
{
  if (ch < 8)
  {
    return getBit(IQSMemoryMap.ACTIVATION_FLAGS[0], ch);
  }
  else if (ch < 16)
  {
    return getBit(IQSMemoryMap.ACTIVATION_FLAGS[1], ch - 8);
  }
  else
  {
    return getBit(IQSMemoryMap.ACTIVATION_FLAGS[2], ch - 16);
  }
}

/**
  * @name   getChannelFilterHalt
  * @brief  A method that returns the current filter halt bit bit for the chosen channel.
  * @param  ch ->  The channel for which the activation bit is returned
  * @retval bool -> true or false depending on the activation
*/
bool IQS9320::getChannelFilterHalt(iqs9320_channel_e ch)
{
  if (ch < 8)
  {
    return getBit(IQSMemoryMap.FILTER_HALT_FLAGS[0], ch);
  }
  else if (ch < 16)
  {
    return getBit(IQSMemoryMap.FILTER_HALT_FLAGS[1], ch - 8);
  }
  else
  {
    return getBit(IQSMemoryMap.FILTER_HALT_FLAGS[2], ch - 16);
  }
}

/**
  * @name   getChannelNormDelta
  * @brief  A method that returns the current normalized delta value for the given channel.
  * @param  ch ->  The channel for which the delta value is returned
  * @retval uint8_t -> unsigned 8 bit value
  * @note   Delta is only read from IQS9320 when Debug is enabled.
*/
uint8_t IQS9320::getChannelNormDelta(iqs9320_channel_e ch)
{
  return IQSMemoryMap.CH_NORM_DELTA[ch];
}

/**
  * @name   getChannelMovement
  * @brief  A method that returns the current movement value for the given channel.
  * @param  ch ->  The channel for which the delta value is returned
  * @retval uint8_t -> unsigned 8 bit value
  * @note   Delta is only read from IQS9320 when Debug is enabled.
*/
uint8_t IQS9320::getChannelMovement(iqs9320_channel_e ch)
{
  return IQSMemoryMap.CH_MOVEMENT[ch];
}

/**
  * @name   getChannelDelta
  * @brief  A method that returns the current delta value for the given channel. Not to be confused by Normalized delta.
  * @param  ch ->  The channel for which the delta value is returned
  * @retval uint8_t -> unsigned 8 bit value
  * @note   Delta is only read from IQS9320 when Debug is enabled.
*/
int16_t IQS9320::getChannelDelta(iqs9320_channel_e ch)
{
  uint8_t low_byte = 0;          // Temporary storage for the low byte.
  uint8_t high_byte = 0;         // Temporary storage for the high byte.
  int16_t ret_value = 0;          // The 16bit return value.

  low_byte = IQSMemoryMap.CH_DELTA[2*ch];
  high_byte = IQSMemoryMap.CH_DELTA[2*ch + 1];

  // Construct the 16bit return value.
  ret_value = (low_byte);
  ret_value |= (high_byte<<8);

  return ret_value;
}

/**
  * @name   getPowerMode
  * @brief  A method that returns the current power mode state of the IQS9320.
  * @param  None
  * @retval iqs9320_power_mode_e -> power mode enum, Normal, low or ulp.
*/
iqs9320_power_mode_e IQS9320::getPowerMode(void)
{
  uint8_t ss = IQSMemoryMap.SYSTEM_STATUS[0]; // load the system status byte
  ss = ss & 0x03; // extract the power mode bits
  return (iqs9320_power_mode_e)ss;
}

/*****************************************************************************/
/*									     		ADVANCED PUBLIC METHODS							    	 		   */
/*****************************************************************************/


/*****************************************************************************/
/*                            PRIVATE METHODS                                */
/*****************************************************************************/
/**
 * @name    readRandomBytes8
 * @brief   A method that reads a specified number of bytes from a specified
 *          8 bit address and saves it into a user-supplied array.
 * @param   memoryAddress -> The memory address at which to start reading bytes
 *                           from.
 * @param   numBytes      -> The number of bytes that must be read.
 * @param   bytesArray    -> The array which will store the bytes to be read,
 *                           this array will be overwritten.
 * @param   stopOrRestart -> A boolean that specifies whether the communication
 *                           window should remain open or be closed after transfer.
 *                           False keeps it open, true closes it. Use the STOP
 *                           and RESTART definitions.
 * @retval  No value is returned, however, the user-supplied array is overwritten.
 * @note    Uses standard Arduino "Wire" library which is for I2C communication.
 *          Take note that C++ cannot return an array, therefore, the array which
 *          is passed as an argument is overwritten with the required values.
 *          Pass an array to the method by using only its name, e.g. "bytesArray",
 *          without the brackets, this passes a pointer to the array.
 */
void IQS9320::readRandomBytes8(uint8_t deviceAddress, uint8_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart)
{
	uint8_t i = 0;  // A simple counter to assist with loading bytes into the user supplied array.
	uint8_t error_s = 0; // I2C Error variable to track any issues during communication

	/* Select the device with the address of "deviceAddress" and start communication. */
	Wire.beginTransmission(deviceAddress);
	/* Send a bit asking for the "memoryAddress" register. */
	Wire.write(memoryAddress);
	/* Complete the selection and communication initialization. */
	error_s = Wire.endTransmission(RESTART);  // Restart transmission for reading that follows.
	/* The required device has now been selected and it has been told which register to send information from. */

	/* Request "numBytes" bytes from the device which has address "deviceAddress"*/
	uint8_t counter = 0;
	do
	{
		Wire.requestFrom((int)deviceAddress, (int)numBytes, (int)stopOrRestart);

		/* break out of request loop if max retry is reached */
		if(counter++ >= IQS9320_I2C_RETRY)
		{
			return;
		}
	}while(Wire.available() == 0);  // Wait for response, this sometimes takes a few attempts

	/* Load the received bytes into the array until there are no more */
	while(Wire.available())
	{
		/* Load the received bytes into the user supplied array */
		bytesArray[i] = Wire.read();
		i++;
	}
}

/**
 * @name    readRandomBytes16
 * @brief   A method that reads a specified number of bytes from a specified
 *          16 bit address and saves it into a user-supplied array.
 * @param   memoryAddress -> The memory address at which to start reading bytes
 *                           from.
 * @param   numBytes      -> The number of bytes that must be read.
 * @param   bytesArray    -> The array which will store the bytes to be read,
 *                           this array will be overwritten.
 * @param   stopOrRestart -> A boolean that specifies whether the communication
 *                           window should remain open or be closed after transfer.
 *                           False keeps it open, true closes it. Use the STOP
 *                           and RESTART definitions.
 * @retval  No value is returned, however, the user-supplied array is overwritten.
 * @note    Uses standard Arduino "Wire" library which is for I2C communication.
 *          Take note that C++ cannot return an array, therefore, the array which
 *          is passed as an argument is overwritten with the required values.
 *          Pass an array to the method by using only its name, e.g. "bytesArray",
 *          without the brackets, this passes a pointer to the array.
 */
void IQS9320::readRandomBytes16(uint8_t deviceAddress, uint16_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart)
{
	uint8_t i = 0;  // A simple counter to assist with loading bytes into the user supplied array.
	uint8_t error_s = 0; // I2C Error variable to track any issues during communication

	// Select the device with the address of "deviceAddress" and start communication.
	Wire.beginTransmission(deviceAddress);
	/* Specify the memory address */
	uint8_t addr_h, addr_l;
	addr_h = memoryAddress >> 8;
	addr_l = memoryAddress;
	Wire.write(addr_l);
	Wire.write(addr_h);

	/* Complete the selection and communication initialization. */
	error_s = Wire.endTransmission(RESTART);  // Restart transmission for reading that follows.
	/* The required device has now been selected and it has been told which register to send information from. */

	/* Request "numBytes" bytes from the device which has address "deviceAddress"*/
	uint8_t counter = 0;
	do
	{
		Wire.requestFrom((int)deviceAddress, (int)numBytes, (int)stopOrRestart);

		/* break out of request loop if max retry is reached */
		if(counter++ >= IQS9320_I2C_RETRY)
		{
			return;
		}
	}while(Wire.available() == 0);  // Wait for response, this sometimes takes a few attempts

	/* Load the received bytes into the array until there are no more */
	while(Wire.available())
	{
		/* Load the received bytes into the user supplied array */
		bytesArray[i] = Wire.read();
		i++;
	}
}

/**
  * @name   writeRandomBytes8
  * @brief  A method that writes a specified number of bytes to a specified
  *         8 bit address, the bytes to write are supplied using an array pointer.
  * @param  deviceAddress -> The slave device address to which the communication should be transmitted.
  * 		memoryAddress -> The memory address at which to start writing the
  *         bytes to.
  *         numBytes      -> The number of bytes that must be written.
  *         bytesArray    -> The array which stores the bytes which will be
  *                          written to the memory location.
  *         stopOrRestart -> A boolean that specifies whether the communication
  *                          window should remain open or be closed of transfer.
  *                          False keeps it open, true closes it. Use the STOP
  *                          and RESTART definitions.
  * @retval No value is returned, only the IQS device registers are altered.
  * @note   Uses standard Arduino "Wire" library which is for I2C communication.
  *         Take note that a full array cannot be passed to a function in C++.
  *         Pass an array to the function by using only its name, e.g. "bytesArray",
  *         without the square brackets, this passes a pointer to the
  *         array. The values to be written must be loaded into the array prior
  *         to passing it to the function.
  */
void IQS9320::writeRandomBytes8(uint8_t deviceAddress, uint8_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart)
{
	uint8_t error_s = 0; // I2C Error variable to track any issues during communication

	/* Select the device with the address of "deviceAddress" and start communication. */
	Wire.beginTransmission(deviceAddress);
	/* Specify the memory address */
	Wire.write(memoryAddress);
	/* Write the bytes as specified in the array which "arrayAddress" pointer points to. */
	for(int i=0; i<numBytes; i++)
	{
		Wire.write(bytesArray[i]);
	}
	/* End the transmission, user decides to STOP or RESTART. */
	error_s = Wire.endTransmission(stopOrRestart);
}

/**
  * @name   writeRandomBytes16
  * @brief  A method that writes a specified number of bytes to a specified
  *         16 bit address, the bytes to write are supplied using an array pointer.
  * @param  deviceAddress -> The slave device address to which the communication should be transmitted.
  * 		memoryAddress -> The memory address at which to start writing the
  *         bytes to.
  *         numBytes      -> The number of bytes that must be written.
  *         bytesArray    -> The array which stores the bytes which will be
  *                          written to the memory location.
  *         stopOrRestart -> A boolean that specifies whether the communication
  *                          window should remain open or be closed of transfer.
  *                          False keeps it open, true closes it. Use the STOP
  *                          and RESTART definitions.
  * @retval No value is returned, only the IQS device registers are altered.
  * @note   Uses standard Arduino "Wire" library which is for I2C communication.
  *         Take note that a full array cannot be passed to a function in C++.
  *         Pass an array to the function by using only its name, e.g. "bytesArray",
  *         without the square brackets, this passes a pointer to the
  *         array. The values to be written must be loaded into the array prior
  *         to passing it to the function.
  */
void IQS9320::writeRandomBytes16(uint8_t deviceAddress, uint16_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart)
{
	uint8_t error_s = 0; // I2C Error variable to track any issues during communication

	// Select the device with the address of "deviceAddress" and start communication.
	Wire.beginTransmission(deviceAddress);

	/* Specify the memory address */
	uint8_t addr_h, addr_l;
	addr_h = memoryAddress >> 8;
	addr_l = memoryAddress;
	Wire.write(addr_l);
	Wire.write(addr_h);

	// Write the bytes as specified in the array which "arrayAddress" pointer points to.
	for(int i=0; i<numBytes; i++)
	{
	Wire.write(bytesArray[i]);
	}
	// End the transmission, user decides to STOP or RESTART.
	error_s = Wire.endTransmission(stopOrRestart);
}

/**
  * @name   getBit
  * @brief  A method that returns the chosen bit value of the provided byte.
  * @param  data       -> byte of which a given bit value needs to be calculated.
  * @param  bit_number -> a number between 0 and 7 representing the bit in question.
  * @retval The boolean value of the specific bit requested.
  */
bool IQS9320::getBit(uint8_t data, uint8_t bit_number)
{
  return (data & ( 1 << bit_number )) >> bit_number;
}

/**
  * @name   setBit
  * @brief  A method that returns the chosen bit value of the provided byte.
  * @param  data       -> byte of which a given bit value needs to be calculated.
  * @param  bit_number -> a number between 0 and 7 representing the bit in question.
  * @retval Returns an 8-bit unsigned integer value of the given data byte with
  *         the requested bit set.
  */
uint8_t IQS9320::setBit(uint8_t data, uint8_t bit_number)
{
	return (data |= 1UL << bit_number);
}

/**
  * @name   clearBit
  * @brief  A method that returns the chosen bit value of the provided byte.
  * @param  data       -> byte of which a given bit value needs to be calculated.
  * @param  bit_number -> a number between 0 and 7 representing the bit in question.
  * @retval Returns an 8-bit unsigned integer value of the given data byte with
  *         the requested bit cleared.
  */
uint8_t IQS9320::clearBit(uint8_t data, uint8_t bit_number)
{
	return (data &= ~(1UL << bit_number));
}
