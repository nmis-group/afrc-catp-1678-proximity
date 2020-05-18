
AT COMMANDS
When in AT command mode, to query nearby devices, first initialised SSP
AT (check everything is OK)
AT+ROLE=1
AT+INIT
AT+INQM=1,x,y (change x to an integer corresponding to number of inquiries, y is timeout value between 1 and 48, with 48 being roughly 60 s - a command would be AT+INQM=1,1000,48)
AT+INQ

example return of AT+INQ:

+INQ:14:3:55B0F,1F00,FFDA

Last 4 characters indicate RSSI - need to convert from hexadecimals to integers








rssi-values

AT+INQM=1,9,48\r\n

AT+INQ?\r\n

other sensor tech:

Ultra-wideband
https://www.decawave.com/product/dwm1000-module/
