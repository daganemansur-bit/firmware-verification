#ifndef MONITOR_H
#define MONITOR_H
#include <stdbool.h>

enum state { NORMAL, ALARM, SENSOR_FAULT };
struct monitor { enum state state; unsigned high_count, recovery_count; };
enum state monitor_step(struct monitor *m, bool present, int millivolts);
#endif
