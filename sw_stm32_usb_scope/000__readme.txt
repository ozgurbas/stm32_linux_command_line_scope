
ultra low cost stm32 usb scope:
4 channel   x   19000sample x   12bit, 
record data can be saved as binary file for future analysis.

example stm32 usage of timer tirggered adc which writes to ram via DMA

uses stm32f103r8 which costs $2.
for low cost floating channel option HCNR linear optocoupler schematics & pcb are available.

sample interval is selectable between 20 to 1000 us (1 to 65000 us is possible with firmware modification)

direct capture is available.
output trigger mode ise available which can be used to trigger external devices and to start scope record at a specified time.
parameters are T1234 on & off times and record start time 0-10000 ms.

digital input triggered record mode is available.  