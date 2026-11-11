#include "monitor.h"
#include <stdio.h>

int main(void)
{
    const int samples[] = {2400, 2799, 2800, 2900, 3000, 2700, 2600, -1, 2400, 2450};
    const char *states[] = {"NORMAL", "ALARM", "SENSOR_FAULT"};
    struct monitor monitor = {0};
    puts("sequence,millivolts,state");
    for (size_t i = 0; i < sizeof samples / sizeof samples[0]; ++i) {
        bool present = samples[i] >= 0;
        enum state state = monitor_step(&monitor, present, samples[i]);
        if (present) printf("%zu,%d,%s\n", i, samples[i], states[state]);
        else printf("%zu,,%s\n", i, states[state]);
    }
    return 0;
}
