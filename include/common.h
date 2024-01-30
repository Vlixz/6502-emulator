#ifndef INC_COMMON_H
#define INC_COMMON_H

#define Word unsigned short
#define Byte unsigned char

/**
 * Macros
 *
 */
#define IS_NEGATIVE(x) (((x) & BIT_MASK_SIGNED) > 0)
#define IS_ZERO(x) ((x) == 0)
#define DID_CROSS_PAGE_BOUNDARY(LSB, X) ((Byte)(LSB + X) < X)
#define COMBINE_BYTES_LITTLE_ENDIAN(HIGH, LOW) ((HIGH << 8) | LOW)
#define GET_BIT_PSR(flag, psr, n) ((flag) = ((psr) >> (n)) & (0x01))
#define SET_BIT_PSR(psr, flag, n) ((psr) |= (flag << (n)))

/**
 * Handy constants
 * 
 */
#define NO_EXTRA_CYCLES 0

/*
 * Bitmasks
 */
#define BIT_MASK_SIGNED 0b10000000
#define BIT_MASK_CARRY 0b100000000
#define BIT_MASK_FIRST_BYTE 0x00FF
#define BIT_MASK_LAST_BYTE 0xFF00

#endif /* INC_COMMON_H*/
