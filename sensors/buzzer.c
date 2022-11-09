

// TI RTOS drivers
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>

// Temporary PWM solution directly on DriverLib
// (until a Timer RTOS driver is in place)
#include <ti/drivers/pin/PINCC26XX.h>
#include <driverlib/timer.h>

#include "buzzer.h"

/* -----------------------------------------------------------------------------
*  Local variables
* ------------------------------------------------------------------------------
*/
static PIN_Handle hPin = NULL;
void buzzerOpen(PIN_Handle hGpioPin)
{
    hPin = hGpioPin;

    // Turn on PERIPH power domain and clock for GPT0 and GPIO
    Power_setDependency(PowerCC26XX_PERIPH_GPT0);
    Power_setConstraint(PowerCC26XX_SB_DISALLOW);

    // Assign GPT0
    TimerConfigure(GPT0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM);

    // Configure pin for PWM output
    PINCC26XX_setMux(hPin, Board_BUZZER, IOC_PORT_MCU_PORT_EVENT0);
}
bool buzzerSetFrequency(uint16_t freq)
{
    uint32_t ticks;
    uint32_t loadLow;
    uint32_t loadHigh;
    uint32_t matchLow;
    uint32_t matchHigh;

    if (freq < BUZZER_FREQ_MIN && freq > BUZZER_FREQ_MAX)
    {
        return false;
    }

    // Stop timer during reconfiguration
    TimerDisable(GPT0_BASE, TIMER_A);

    // Calculate timer load and match values
    ticks = 48000000 / freq;
    loadLow = ticks & 0x0000FFFF;
    loadHigh = (ticks & 0x00FF0000) >> 16;
    matchLow = (ticks / 2) & 0x0000FFFF;
    matchHigh = ((ticks / 2) & 0x00FF0000) >> 16;

    // Set timer load
    TimerLoadSet(GPT0_BASE, TIMER_A, loadLow);
    TimerPrescaleSet(GPT0_BASE, TIMER_A, loadHigh);

    // Set timer match
    TimerMatchSet(GPT0_BASE, TIMER_BOTH, matchLow);
    TimerPrescaleMatchSet(GPT0_BASE, TIMER_A, matchHigh);

    // Start timer
    TimerEnable(GPT0_BASE, TIMER_A);
    return true;
}
void buzzerClose(void)
{
    // Configure pin as GPIO
    PINCC26XX_setMux(hPin, Board_BUZZER, IOC_PORT_GPIO);

    // Turn off PERIPH power domain and clock for GPT0
    Power_releaseDependency(PowerCC26XX_PERIPH_GPT0);
    Power_releaseConstraint(PowerCC26XX_SB_DISALLOW);
}