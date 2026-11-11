#include "monitor.h"

enum state monitor_step(struct monitor *m, bool present, int mv)
{
    if (!present || mv < 0 || mv > 3300) {
        *m = (struct monitor){.state = SENSOR_FAULT};
        return m->state;
    }
    if (m->state == SENSOR_FAULT) {
        if (mv > 2600) {
            m->recovery_count = 0;
        } else if (++m->recovery_count == 2) {
            *m = (struct monitor){.state = NORMAL};
        }
    } else if (m->state == ALARM) {
        if (mv <= 2600) {
            *m = (struct monitor){.state = NORMAL};
        }
    } else if (mv >= 2800) {
        if (++m->high_count == 3) {
            m->state = ALARM;
        }
    } else {
        m->high_count = 0;
    }
    return m->state;
}
