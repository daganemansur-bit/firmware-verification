# Firmware Verification Lab

A host-side C11 exercise in sensor validation. A deterministic stream represents
samples an ADC driver could deliver. This project does not contain an ADC driver,
board support code, or measurements from hardware.

| Behavior | Rule | Why |
| --- | --- | --- |
| Enter alarm | Three consecutive valid readings at or above 2800 mV | Ignore brief spikes |
| Clear alarm | A valid reading at or below 2600 mV | Avoid toggling near the alarm threshold |
| Report sensor fault | Missing sample or reading outside 0–3300 mV | Preserve the difference between a bad sensor and a high reading |
| Recover | Two consecutive valid readings at or below 2600 mV | Do not call a sensor healthy after one good reading |
| Reset history | A sample below the alarm threshold resets the high count; any fault resets both counters | Require consecutive evidence |

The interface accepts readings in millivolts; a platform adapter would perform
sampling and ADC conversion. The monitor has no heap allocation or I/O. Its
output is a logical state for this exercise, not a hardware safety signal.

```sh
make test all
./demo
./demo > /tmp/firmware-demo.csv
```

A sample at 2800 mV is high; 2799 mV is not. After an alarm, 2700 mV
preserves the alarm and 2600 mV clears it. Missing readings are represented by an
empty field in the CSV. The CSV can be replayed into Sensor Ops, whose API reports
instantaneous sample categories, independent of the C monitor's latched state.

The next experiment is to drive the exact same interface with recorded bench
measurements, document sample timing and sensor tolerances, and repeat the tests.
