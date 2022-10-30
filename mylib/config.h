/*
 * THESE ARE CONFIGS
 *
 */

#include <inttypes.h>

/*
 * @param configMask for configuring behaviour
 * Multiple options can be set/unset combining bits to one mask
 * bit 0x01 Use display
 * bit 0x02 Use MPU9250 3-axis acceleration sensor
 * bit 0x04 Use tmp007 Temperature sensor
 * bit 0x08 Use opt3001 Optical sensor
 * bit 0x10 Use Buzzer without songs
 * bit 0x20 Use Buzzer and play songs
 * bit 0x40 Use Radio
 * bit 0x80
 * bit 0xFF Use ALL
 * Default config:
 */
typedef uint8_t configMask_t; /*= 0x2 | 0x0 | 0x20 | 0x40;*/
static configMask_t configMask =  0x2 | 0x0 | 0x10 | 0x40;
void setConfigMask(configMask_t mask);
configMask_t getConfigMask();
