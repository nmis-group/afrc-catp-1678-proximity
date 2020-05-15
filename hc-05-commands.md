For HC05: Type "AT" (without the quotes) on the serial monitor and press enter. If "OK" appears then everything is all right and the module is ready to take command. Now you can change the name of the module, retrieve address or version or even reset to factory settings. To see the default name, type AT+NAME. The name will be prompted, by default it is HC-05 or JY_MCU or something like that. To change the name just type AT+NAME=your desired name.

Here is an important note, if the key pin is not high, i.e. not connected to 3.3V while receiving AT commands it will not work.

Most useful AT commands are

AT : Ceck the connection.
AT+NAME : See default name
AT+ADDR : see default address
AT+VERSION : See version
AT+UART : See baudrate
AT+ROLE: See role of bt module(1=master/0=slave)
AT+RESET : Reset and exit AT mode
AT+ORGL : Restore factory settings
AT+PSWD: see default password

For HC06: On arduino serial monitor type "AT" (without the quotes) and press enter, "OK" will confirm AT mode. Unlike HC05, you can't see the default name or baud rate. You can only change them. To change name type AT+NAMEDESIRED NAME, notice that there should be no space between the command and name. The module will reply OKyour set name. For example, AT+NAMEPROTOTYPE will set the name to PROTOTYPE. To change baud rate, type AT+BAUDX, where X=1 to 9.

1 set to 1200bps
2 set to 2400bps
3 set to 4800bps
4 set to 9600bps (Default)
5 set to 19200bps
6 set to 38400bps
7 set to 57600bps
8 set to 115200bps

Example: sending AT+BAUD4 will set the baud rate to 9600.

For Tera Term write down the commands somewhere else and paste it on the console by right clicking. No need of pressing enter. The command will be executed immediately and confirmed.

HC 06 AT commands are limited:

AT : check the connection
AT+NAME: Change name. No space between name and command.
AT+BAUD: change baud rate, x is baud rate code, no space between command and code.
AT+PIN: change pin, xxxx is the pin, again, no space.
AT+VERSION
