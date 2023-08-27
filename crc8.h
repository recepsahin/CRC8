/**
 * @file crc8.h
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

#ifndef CRC8_H_
#define CRC8_H_

#include <stdint.h>

typedef struct{
    uint8_t crc;
    uint8_t polynomial;
    uint8_t crcInitialVal;
    uint8_t crcFinalExorVal;
}CRC8_t;

/*  public functions  */

/**
 * @brief Initializes crc struct with default values;
 * 
 * @param crc Pointer of the crc struct to be initialized.
 */
void CRC8InitDefault(CRC8_t *crc);

/**
 * @brief Initializes crc struct with given parameters.
 * 
 * @param crc Pointer of the crc struct to be initialized.
 * @param polynomial Polynomial to be used in calculation.
 * @param crcInitialVal Initial value of crc, it is also be used as reset value.
 * @param crcFinalExorVal The value which is used to calculate final crc of a block of data.
 */
void CRC8InitCustom(CRC8_t *crc, uint8_t polynomial, uint8_t crcInitialVal, uint8_t crcFinalExorVal);

/**
 * @brief Pushes one byte into crc calculation.
 * 
 * @param crc Pointer of the crc configuration.
 * @param currentByte Byte to be taken into account.
 * @return uint8_t Instant CRC value, assuming each byte is the last byte.
 * Returns crc value by exoring with final exor value. 
 */
uint8_t CRC8PushByte(CRC8_t *crc, uint8_t currentByte);

/**
 * @brief Resets crc value to its initial value.
 * 
 * @param crc Pointer of crc configuration to be reset.
 */
void CRC8Reset(CRC8_t *crc);

/**
 * @brief Returns crc result by exoring it with final exor value.
 * 
 * @param crc Pointer of the crc configuration.
 * @return uint8_t Calculated crc value.
 */
uint8_t CRC8Get(CRC8_t *crc);

/**
 * @brief Calculates crc of batch of data.
 * 
 * @param crc Pointer of the crc configuration.
 * @param data Start address of data set.
 * @param size The size of data set.
 * @return uint8_t Calculated crc value of given data set.
 */
uint8_t CRC8Batch(CRC8_t *crc, const uint8_t *data, uint32_t size);

#endif