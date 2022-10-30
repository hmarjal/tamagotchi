#include <inttypes.h>

uint8_t* cmdStr(uint8_t cmd, uint8_t amount);
uint8_t* customMsg(uint8_t n, uint8_t status);
uint16_t parseMsg(const char* msg, uint16_t* receiver);
