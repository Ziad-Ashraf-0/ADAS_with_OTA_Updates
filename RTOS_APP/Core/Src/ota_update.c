/*
 * ota_update.c
 *
 *  Created on: Apr 19, 2023
 *      Author: FOTA
 */
#include "ota_update.h"

uint8_t supported_commands[5] = {
BL_GET_VER,
BL_GET_HELP,
BL_GO_TO_ADDR,
BL_FLASH_ERASE,
BL_MEM_WRITE_DATA, };
uint16_t SIZE;
uint32_t ADDRESS = 0x08100000;
uint8_t first_time = 1;

/* Shared variables ---------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern UART_HandleTypeDef huart1;

extern CAN_RxHeaderTypeDef RxHeader;
extern CAN_TxHeaderTypeDef TxHeader;
extern uint32_t TxMailbox;
extern uint8_t RxData[8];
extern uint8_t TxData[8];
uint8_t ack_no = 0;

void toggleBankAndReset() {
	FLASH_AdvOBProgramInitTypeDef OBInit;

	// Unlock the flash module and Option Bytes (OB) registers
	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();

	// Retrieve the current Option Bytes configuration
	HAL_FLASHEx_AdvOBGetConfig(&OBInit);

	// Configure the Option Bytes for boot bank selection
	OBInit.OptionType = OPTIONBYTE_BOOTCONFIG;

	// Toggle the boot bank configuration(BFB2)
	if (((OBInit.BootConfig) & (OB_DUAL_BOOT_ENABLE)) == OB_DUAL_BOOT_ENABLE) {
		OBInit.BootConfig = OB_DUAL_BOOT_DISABLE;
	} else {
		OBInit.BootConfig = OB_DUAL_BOOT_ENABLE;
	}

	// Program the updated Option Bytes configuration
	if (HAL_FLASHEx_AdvOBProgram(&OBInit) != HAL_OK) {
		// Error occurred while programming Option Bytes, toggle GPIO pin indefinitely
		while (1) {
			HAL_Delay(1000);
			HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
		}
	}

	// Launch the Option Bytes configuration and reset the system
	if (HAL_FLASH_OB_Launch() != HAL_OK) {
		// Error occurred while launching Option Bytes, toggle GPIO pin indefinitely
		while (1) {
			HAL_Delay(100);
			HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
		}
	}

	// Lock the Option Bytes and flash module
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();

	// Perform a system reset
	HAL_NVIC_SystemReset();
}

uint32_t get_Active_Bank_no(void) {
	// Read the value of the UFB_MODE bit in the SYSCFG_MEMRMP register
	uint32_t checkBank = READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_UFB_MODE);

	// Check the value of the UFB_MODE bit to determine the active bank
	if (checkBank == 0) {
		// UFB_MODE bit is cleared, indicating Bank 1 is active
		printf("Program Running in Bank 1 \r\n");
	} else {
		// UFB_MODE bit is set, indicating Bank 2 is active
		printf("Program Running in Bank 2 \r\n");
	}

	// Return the value of the UFB_MODE bit
	return checkBank;
}

void sendHeartbeat() {
	uint32_t dummy;

	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &dummy);
}

/****************************************************************************************
 ********************* implementation of bootloader command handle functions *************
 *****************************************************************************************/

/*Helper function to handle BL_GET_HELP command
 * Bootloader sends out All supported Command codes
 */
void bootloader_handle_gethelp_cmd(void) {
	TxHeader.StdId = BL_GET_HELP;

	for (uint32_t i = 0; i < 5; i++) {
		TxData[i] = supported_commands[i];
	}

	//send the supported commands to the node_mcu
	bootloader_can_write_data(1);
}

/**
 * @brief  Helper function to handle BL_GET_VER command.
 * @param  None
 * @retval sets Txdata[0] to app version
 */
/* Helper function to handle BL_GET_VER command */
void bootloader_handle_getver_cmd(void) {
	// Variable to store the application version
	uint8_t app_version;

	// Retrieve the application version using a helper function (get_app_version())
	app_version = get_app_version();

	// Prepare the response message
	TxHeader.StdId = BL_GET_VER;
	TxData[0] = app_version;

	// Write the response message to the CAN bus
	bootloader_can_write_data(1);

	// End of the function
}

/*Helper function to handle BL_GO_TO_ADDR command */
void bootloader_handle_go_cmd(void) {
	TxHeader.StdId = BL_GO_TO_ADDR;

	uint8_t VERIFICATION_ADDRESS = (uint8_t) ADDR_INVALID;

	uint32_t *ptr_address = &RxData;

	uint32_t address = *(ptr_address);

	//VERIFICATION_ADDRESS = verify_address(address);

	if (VERIFICATION_ADDRESS == (uint8_t) ADDR_VALID) {
		TxData[0] = (uint8_t) VERIFICATION_ADDRESS;

		//tell node_mcu that address is fine
		bootloader_can_write_data(1);

		/*jump to "go" address.
		 we dont care what is being done there.
		 host must ensure that valid code is present over there
		 Its not the duty of bootloader. so just trust and jump */

		/* Not doing the below line will result in hardfault exception for ARM cortex M */
		//watch : https://www.youtube.com/watch?v=VX_12SjnNhY
		uint32_t go_address = address;

		go_address += 1; //make T bit =1

		void (*lets_jump)(void) = (void *)go_address;

		lets_jump();

	} else {
		TxData[0] = (uint8_t) VERIFICATION_ADDRESS;

		//tell host that address is invalid
		bootloader_can_write_data(1);
	}
}

/*Helper function to handle BL_FLASH_ERASE command */
void bootloader_handle_flash_erase_cmd(void) {
	uint8_t ERASE_STATUS = (uint8_t) FLASH_ERASE_FAILED;

	uint32_t *ptr = &RxData;
	uint32_t initial_sector = *(ptr);
	uint32_t number_of_sectors = *(ptr + 1);

	ERASE_STATUS = execute_flash_erase(initial_sector, number_of_sectors);

	TxHeader.StdId = BL_FLASH_ERASE;

	if (ERASE_STATUS == (uint8_t) FLASH_ERASE_SUCCESS) {
		TxData[0] = (uint8_t) FLASH_ERASE_SUCCESS;
	} else if (ERASE_STATUS == (uint8_t) FLASH_ERASE_FAILED) {
		TxData[0] = (uint8_t) FLASH_ERASE_FAILED;
	} else {
		TxData[0] = (uint8_t) INVALID_SECTOR;
	}

	//bootloader_can_write_data(1);
}

/**
 * @brief  Sets SIZE global variable to the received size.
 * @param  size received over can
 * @retval None
 */
void bootloader_handle_mem_write_size_cmd(void) {
	// Pointer to the received data buffer
	uint16_t *ptr_size = &RxData;

	// Extract the size value from the received data and assign it to SIZE variable
	SIZE = *(ptr_size);

	// Prepare the response message
	TxHeader.StdId = BL_MEM_WRITE_SIZE;

	// Increment the acknowledgment number
	ack_no++;

	// End of the function
}

void bootloader_handle_mem_write_address_cmd(void) {
	uint32_t *ptr_address = &RxData;

	ADDRESS = *(ptr_address);
}

/*Helper function to handle BL_MEM_WRITE_DATA command */
void bootloader_handle_mem_write_data_cmd() {
	uint8_t WRITE_STATUS = (uint8_t) FLASH_WRITE_FAILED;
	uint8_t VERIFICATION_ADDRESS = (uint8_t) ADDR_INVALID;
	TxHeader.StdId = BL_MEM_WRITE_DATA;
	uint32_t mem_address = ADDRESS;
	//VERIFICATION_ADDRESS = verify_address(mem_address);
	if (VERIFICATION_ADDRESS == (uint8_t) ADDR_VALID) {
		//execute mem write
		WRITE_STATUS = execute_mem_write();
		if (WRITE_STATUS == (uint8_t) FLASH_WRITE_SUCCESS) {
			TxData[0] = (uint8_t) FLASH_WRITE_SUCCESS;
		} else {
			TxData[0] = (uint8_t) FLASH_WRITE_FAILED;
		}
	} else {
		TxData[0] = (uint8_t) ADDR_INVALID;
	}
	//inform host about the status
	//bootloader_can_write_data(1);
}

void moveCar() {
	switch (RxData[0]) {
	case FORWARD:
		Car_Void_GoForward(RxData[1]);
		// Handle "Get Help" command
		break;
	case BACKWARD:
		Car_Void_GoBackward(RxData[1]);
		// Handle "Get Version" command
		break;
	case RIGHT:
		Car_Void_TurnRight(0, 80);
		// Handle "Flash Erase" command
		break;
	case LEFT:
		Car_Void_TurnLeft(100, 100);
		// Handle "Memory Write Size" command
		break;
	case STOP:
		Car_Void_Stop();
		// Handle "Memory Write Address" command
		break;

	}
}

/* This function reads the data from CAN1 */
void bootloader_can_read_data() {
	// Switch statement to handle different types of CAN messages based on the received StdId
	switch (RxHeader.StdId) {
	case BL_GET_HELP:
		bootloader_handle_gethelp_cmd();
		// Handle "Get Help" command
		break;
	case BL_GET_VER:
		bootloader_handle_getver_cmd();
		// Handle "Get Version" command
		break;
	case BL_FLASH_ERASE:
		bootloader_handle_flash_erase_cmd();
		// Handle "Flash Erase" command
		break;
	case BL_MEM_WRITE_SIZE:
		bootloader_handle_mem_write_size_cmd();
		// Handle "Memory Write Size" command
		break;
	case BL_MEM_WRITE_ADDRESS:
		bootloader_handle_mem_write_address_cmd();
		// Handle "Memory Write Address" command
		break;
	case BL_MEM_WRITE_DATA:
		bootloader_handle_mem_write_data_cmd();
		// Handle "Memory Write Data" command
		break;
	case BL_GO_TO_ADDR:
		bootloader_handle_go_cmd();
		// Handle "Go to Address" command
		break;
	case FIRMWARE_OVER_THE_AIR:
		UpdateAPP();
		// Handle "Firmware Over the Air" command by calling the UpdateAPP() function
		break;
	case MV_CAR:
		moveCar();
		// Handle "Firmware Over the Air" command by calling the UpdateAPP() function
		break;

	}
}

/* This function write data into can1 */
void bootloader_can_write_data(uint32_t length_of_data) {
	for (uint32_t i = 0; i < length_of_data; i++) {
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
	}

	memset(TxData, 0, 8);
}

/*Just returns the macro value */
uint8_t get_app_version(void) {
	return (uint8_t) APP_VERSION;
}

uint8_t execute_flash_erase(uint32_t initial_sector_number,
		uint32_t number_of_sector) {
	//we have totally 12 sectors in one bank .. sector[0 to 11]
	//number_of_sector has to be in the range of 0 to 11
	// if sector_number = 0xff , that means mass erase !

	FLASH_EraseInitTypeDef flashErase_handle;
	uint32_t sectorError = 0;
	uint8_t erase_status = 0x01;

	if (number_of_sector > 23)
		return (uint8_t) INVALID_SECTOR;

	if ((initial_sector_number == 0xFFFFFFFF) || (number_of_sector <= 23)) {
		if (number_of_sector == (uint32_t) 0xFFFFFFFF) {
			flashErase_handle.TypeErase = FLASH_TYPEERASE_MASSERASE;
			flashErase_handle.Banks = FLASH_BANK_1;
		} else {
			/*Here we are just calculating how many sectors needs to erased */
			uint32_t remanining_sector = 24 - number_of_sector;
			if (number_of_sector > remanining_sector) {
				number_of_sector = remanining_sector;
			}
			flashErase_handle.TypeErase = FLASH_TYPEERASE_SECTORS;
			flashErase_handle.Sector = initial_sector_number; // this is the initial sector
			flashErase_handle.NbSectors = number_of_sector;
		}

		/*Get access to touch the flash registers */
		HAL_FLASH_Unlock();
		flashErase_handle.VoltageRange = FLASH_VOLTAGE_RANGE_3; // our MCU will work on this voltage range
		erase_status = (uint8_t) HAL_FLASHEx_Erase(&flashErase_handle,
				&sectorError);
		HAL_FLASH_Lock();

		return (uint8_t) erase_status;
	}

	return (uint8_t) INVALID_SECTOR;
}

/* This function writes the contents of pBuffer to "mem_address" byte by byte */
// Note1: Currently this function supports writing to Flash only.
// Note2: This function does not check whether "mem_address" is a valid address of the flash range.
uint8_t execute_mem_write() {
	HAL_StatusTypeDef write_status = HAL_ERROR;

	uint32_t *ptr_data = &RxData;
	// Declare a pointer to the received data array "RxData"

	// We have to unlock the flash module to get control of registers
	HAL_FLASH_Unlock();

	// Here we program the flash byte by byte
	write_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ADDRESS,
			ptr_data[0]);
	// Program the first 4 bytes (32 bits) of data to the flash memory at the address specified by "ADDRESS"

	write_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ADDRESS + 4,
			ptr_data[1]);
	// Program the next 4 bytes (32 bits) of data to the flash memory at the address offset by 4 bytes from "ADDRESS"

	ADDRESS = ADDRESS + 8;
	// Increment the "ADDRESS" by 8 bytes (64 bits) for the next write operation

	HAL_FLASH_Lock();
	// Lock the flash module to prevent accidental writes

	return (uint8_t) write_status;
	// Return the write status as a uint8_t type
}

/**
 * @brief  Flash one can frame.
 * @param  Global variable containing current can frame index to be flashed
 * @retval erase_status
 */
uint8_t UpdateAPP() {
	uint8_t erase_status = HAL_ERROR;
	HAL_StatusTypeDef write_status = HAL_ERROR;
	ack_no++; // Increment the acknowledgment number
	if (first_time) {
		ADDRESS = (uint32_t) 0x08110000; // Set the starting address for firmware update

		// If running from Bank1 erase Bank2 and vice versa
		if (get_Active_Bank_no() == 0) {
			erase_status = execute_flash_erase(16, 3);
			// Erase flash memory sectors for the firmware update
		} else {
			erase_status = execute_flash_erase(4, 3);
			// Erase flash memory sectors for the firmware update
		}
		first_time = 0; // Clear the first_time flag
	} else {
		erase_status = FLASH_ERASE_SUCCESS;
		// If it's not the first time, assume erase was successful
	}
	if (erase_status == FLASH_ERASE_SUCCESS) {
		SIZE -= 1; // Decrement the size counter
		write_status = execute_mem_write(); // Write firmware data to flash memory
		if (SIZE == 0) {
			if (ack_no == 2) {
				ack_no = 0;
				bootloader_can_write_data(1); // Send acknowledgment over CAN bus
			}
			toggleBankAndReset();
			// Switch the active firmware bank and reset the system
		}
	} else {
		TxHeader.StdId = FIRMWARE_OVER_THE_AIR;
		TxData[0] = erase_status;
		bootloader_can_write_data(1);
		// Send erase status over CAN bus
		return erase_status;
	}
	TxHeader.StdId = FIRMWARE_OVER_THE_AIR;
	TxData[0] = write_status;
	// Prepare write status data to be sent over CAN bus
	if (ack_no == 2) {
		ack_no = 0;
		bootloader_can_write_data(1);
		// Send acknowledgment over CAN bus
	}
	return write_status; // Return the write status
}
