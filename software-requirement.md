
HIGH LEVEL PROTOTYPE
- get rssi signals from different device by polling
- reset device if polling fails
- sort by ID with RSSI signal
- determine decimal RSSI signal
- determine which ids/rssi signals are above a given threshold
- flash external LED pin for above threshold
- turn off LED when back under threshold
- test for multiple devices in proximity (5)


Issues
- polling stops randomly

MARK 1
debug mode on pcb (isolate power)

- log this infraction to storage
storage device
- log every timestamp and ID of infracting hc-05 device to sd
- log the rssi value as well


list of gripes
- how to define a 'infraction'?
- voltage/current regulation
- 7 segment display might be difficult to implement
- suggest
