/**
 * @file test.c
 * @author Recep Sahin
 * @brief Tests CRC8 calculations using known data sets and their calculated crc8 values.
 * @version 1.0
 * @date 2023-08-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "crc8.h"
#include <stdio.h>

#define DATA_SIZE (20U)
#define DATA2_SIZE (22U)

static const uint8_t test_data[DATA_SIZE] = {
    0x12, 0x63, 0xaa, 0xbb, 0xcc, 0xcd, 0x02, 0x0f, 0x00, 0x4d,
    0x12, 0x63, 0xaa, 0xbb, 0xcc, 0xcd, 0x02, 0x0f, 0x00, 0x4d
};

static const uint8_t dataCrc = 0x03u;

static const uint8_t test_data2[DATA2_SIZE] = {
    0x12, 0x63, 0xaa, 0xbb, 0xcc, 0xcd, 0x02, 0x0f, 0x00, 0x4d,
    0x12, 0x63, 0xaa, 0xbb, 0xcc, 0xcd, 0x02, 0x0f, 0x00, 0x4d,
    0xc2, 0x6a
};

static const uint8_t data2Crc = 0x90U;
static const uint8_t customCrc = 0x49U;

/**
 * @brief Prints test result message.
 * 
 * @param knownVal Precalculated value.
 * @param calculatedVal Calculated value to be verified.
 */
static void PrintResult(uint8_t knownVal, uint8_t calculatedVal){
    if(knownVal == calculatedVal){
        puts("Test ok!\r\n");
    }else{
        puts("Test failed!\r\n");
    }
}

/**
 * @brief Start point of program. Tests crc calculation and related functions using data sets.
 * 
 * @return int 
 */
int main(){

    CRC8_t crc;
    CRC8_t *pCrc = &crc;

    CRC8InitDefault(pCrc);

    for(uint32_t i = 0; i < DATA_SIZE; i++){
        printf("Current CRC: 0x%02x\n\r", CRC8PushByte(pCrc, test_data[i]));
    }

    printf("Result : 0x%02x\r\n", CRC8Get(pCrc));
    PrintResult(dataCrc, CRC8Get(pCrc));

    // calculate crc of data set in batch mode
    CRC8Reset(pCrc);// dont forget the reset the crc configuration before using it
    uint8_t result = CRC8Batch(pCrc,test_data, DATA_SIZE);
    PrintResult(dataCrc, result);

    // use the same crc configuration for different data set by reseting it
    CRC8Reset(pCrc);

    for(uint32_t i = 0; i < DATA2_SIZE; i++){
        printf("Current CRC: 0x%02x\n\r", CRC8PushByte(pCrc, test_data2[i]));
    }

    printf("Result : 0x%02x\r\n", CRC8Get(pCrc));
    PrintResult(data2Crc, CRC8Get(pCrc));

    // create a custom crc calculation configuration
    CRC8InitCustom(pCrc, 0x07U, 0x00U, 0xffU);

    for(uint32_t i = 0; i < DATA2_SIZE; i++){
        printf("Current CRC: 0x%02x\n\r", CRC8PushByte(pCrc, test_data2[i]));
    }

    printf("Result : 0x%02x\r\n", CRC8Get(pCrc));
    PrintResult(customCrc, CRC8Get(pCrc));

    return 0;
}