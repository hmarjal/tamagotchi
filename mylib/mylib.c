#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <xdc/runtime/System.h>
#include "wireless/address.h"

#define len 16

const char *msg_array[6] = {"I could use a scratch",
                            "Severe warning about my wellbeing",
                            "Running low on food",
                            "Feels good, but take a break",
                            "Too fitness, I need a moment",
                            "Calm down, I just cannot eat that much"
};

const char *cmd_array[4] = {
        "PET:",
        "EXERCISE:",
        "EAT:",
        "ACTIVATE:"
};

const char *custom_msg_array[2] = {"MSG1:",
                                   "MSG2:"
};

const char *status_msg_array[4] = {"DAY",
                                   "NIGHT",
                                   "WARM",
                                   "COLD"
};

uint8_t *customMsg(uint8_t n, uint8_t status) {
    char *c = NULL;
    c = malloc(len * sizeof(uint8_t));
    System_sprintf(c, "%s%s\0", custom_msg_array[n], status_msg_array[status]);
    return (uint8_t *) c;
}

uint8_t *cmdStr(uint8_t cmd, uint8_t amount) {
    char *s = NULL;
    s = malloc(len * sizeof(uint8_t));
    if (s == NULL) {
        System_printf("Malloc error in cmdStr\n");
        System_flush();
    }
    System_sprintf(s, "%s%d\0", cmd_array[cmd], amount);
    //sprintf(s, "%s%hhu\0", cmd_array[cmd], amount);
    return (uint8_t *) s;

}

uint16_t parseMsg(const char *msg, uint16_t *receiver) {
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t ret = 0;
    char msgArr[3][80] = {0};
    char tempArr[80] = {0};
    const char delim[2] = ";";
    char *token;

    sscanf(msg, "%hu", receiver);
    if (*receiver != 280) {
        return NULL;
    }
    strcpy(tempArr, msg);
    while (tempArr[i] != ':') {
        ++i;
    }
    size_t s_len = strlen(tempArr);
    memmove(&tempArr[0], &tempArr[i + 1], s_len);
    i = 0;
    token = strtok(tempArr, delim);
    while (token != NULL) {
        strcpy(msgArr[i], token);
        ++i;
        token = strtok(NULL, delim);
    }

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 6; ++j) {
            if ((strcmp(msgArr[i], msg_array[j])) == 0) {
                ret = ret + (1 << j);
            }
        }
    }
    return ret;
}

