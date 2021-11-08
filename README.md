# Due Logs In
Based on a keyboard emulation using an Arduino Due, this firmware logs into a known-password user session. 
Additionally, it can perform some other custom actions by having the ability to send keyboard pressing actions.

## How to program an Arduino Due
1. Install latest Arduino IDE.
- [Arduino IDE website](https://www.arduino.cc/en/software).
2. Install the Arduino Due board.
- Go to Tools > Board Manager and install latest version of "Arduino SAM Boards"
![installingDueBoard](/assets/images/installingDueBoard.png)
3. Connect the Arduino Due using its programming port.
![Due ports](/assets/images/duePorts.jpg)
4. Choose the Arduino Due board.
![Choosing Arduino Due Board](/assets/images/selectBoard.png)
5. Connect the corresponding Arduino Due port (Programming Port).
![Choosing Arduino Due Serial Port](/assets/images/selectPort.png)

For more details, see: https://www.arduino.cc/en/Guide/ArduinoDue

## How to set a custom password for logging.
1. Change the value of the 'password' variable in line 25.
![Change password](/assets/images/setPassword.png)
2. Upload the firmware following the steps to program an Arduino due previously mentioned. 
3. Connect the Arduino Due to the PC using its Native USB port and enjoy it. 

## What can this firmware do?
This firmware can be modified to get the device:
-  Starting applications
- Opening cmd or powershell instances to run bash/powershell commands.
- Launching text editors and writing texts on them.
- Shutdown the PC after performing certain action.
- Etc..