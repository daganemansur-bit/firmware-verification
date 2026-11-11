#include "monitor.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    struct monitor m = {0};
    assert(monitor_step(&m, true, 2800) == NORMAL);
    assert(monitor_step(&m, true, 2800) == NORMAL);
    assert(monitor_step(&m, true, 2799) == NORMAL);
    assert(monitor_step(&m, true, 2800) == NORMAL);
    assert(monitor_step(&m, true, 3300) == NORMAL);
    assert(monitor_step(&m, true, 2800) == ALARM);
    assert(monitor_step(&m, true, 2601) == ALARM);
    assert(monitor_step(&m, true, 2600) == NORMAL);
    assert(monitor_step(&m, true, 3301) == SENSOR_FAULT);
    assert(monitor_step(&m, true, 2600) == SENSOR_FAULT);
    assert(monitor_step(&m, false, 0) == SENSOR_FAULT);
    assert(monitor_step(&m, true, 0) == SENSOR_FAULT);
    assert(monitor_step(&m, true, 2601) == SENSOR_FAULT);
    assert(monitor_step(&m, true, 0) == SENSOR_FAULT);
    assert(monitor_step(&m, true, 2600) == NORMAL);
    assert(monitor_step(&m, true, -1) == SENSOR_FAULT);
    puts("PASS: alarm debounce, hysteresis, input boundaries, fault and recovery");
    return 0;
}
