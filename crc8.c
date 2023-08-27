/**
 * @file crc8.c
 * @author Recep Sahin
 * @brief CRC8 calculation can be done pushing bytes in different times
 * or using a batch of accumulated data at a time. This implementation 
 * supports both of them.
 * @version 1.0
 * @date 2023-08-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "crc8.h"

#define DEFAULT_CRC_INITVAL       (0xFFU)
#define DEFAULT_FINAL_EXORVAL     (0x00U)
#define DEFAULT_POLYNOMIAL        (0xB7U)

/**
 * @brief Initializes crc struct with default values;
 * 
 * @param crc Pointer of the crc struct to be initialized.
 */
void CRC8InitDefault(CRC8_t *crc){
    crc->crcInitialVal = DEFAULT_CRC_INITVAL;
    crc->crcFinalExorVal = DEFAULT_FINAL_EXORVAL;
    crc->polynomial = DEFAULT_POLYNOMIAL;
    crc->crc = crc->crcInitialVal;
}

/**
 * @brief Initializes crc struct with given parameters.
 * 
 * @param crc Pointer of the crc struct to be initialized.
 * @param polynomial Polynomial to be used in calculation.
 * @param crcInitialVal Initial value of crc, it is also be used as reset value.
 * @param crcFinalExorVal The value which is used to calculate final crc of a block of data.
 */
void CRC8InitCustom(CRC8_t *crc, uint8_t polynomial, uint8_t crcInitialVal, uint8_t crcFinalExorVal){
    crc->polynomial = polynomial;
    crc->crcInitialVal = crcInitialVal;
    crc->crcFinalExorVal = crcFinalExorVal;
    crc->crc = crc->crcInitialVal;
}

/**
 * @brief Pushes one byte into crc calculation.
 * 
 * @param crc Pointer of the crc configuration.
 * @param currentByte Byte to be taken into account.
 * @return uint8_t Instant CRC value, assuming each byte is the last byte.
 * Returns crc value by exoring with final exor value. 
 */
uint8_t CRC8PushByte(CRC8_t *crc, uint8_t currentByte){

    crc->crc ^= currentByte;

    for(uint8_t i = 0; i < 8; i++){
        if(crc->crc & 0x80){
            crc->crc = (crc->crc << 1) ^ crc->polynomial;
        }else{
            crc->crc <<= 1;
        }
    }

    return (crc->crc ^ crc->crcFinalExorVal);
}

/**
 * @brief Resets crc value to its initial value.
 * 
 * @param crc Pointer of crc configuration to be reset.
 */
void CRC8Reset(CRC8_t *crc){
    crc->crc = crc->crcInitialVal;
}

/**
 * @brief Returns crc result by exoring it with final exor value.
 * 
 * @param crc Pointer of the crc configuration.
 * @return uint8_t Calculated crc value.
 */
uint8_t CRC8Get(CRC8_t *crc){
    return (crc->crc ^ crc->crcFinalExorVal);
}

/**
 * @brief Calculates crc of batch of data.
 * 
 * @param crc Pointer of the crc configuration.
 * @param data Start address of data set.
 * @param size The size of data set.
 * @return uint8_t Calculated crc value of given data set.
 */
uint8_t CRC8Batch(CRC8_t *crc, const uint8_t *data, uint32_t size){

    for(uint32_t i = 0; i < size; i++){
        CRC8PushByte(crc, data[i]);
    }

    return (crc->crc ^ crc->crcFinalExorVal);
}