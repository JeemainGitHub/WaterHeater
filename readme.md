# Controller for water heater

## abstract
ATtiny microcontroller connected water heater. Original hardware of heater used, but replacement of microcontroller.

## discription
### used hardware:
- Atiny chip
- Water heater with 
  - temperature sensor
  - button "start / stop heating" with status led
  - button "reheating on / off"
  - button "temperature selection"
  - 4 led for temperature display (actual and preselected temperature)
  - pieco beeper to signal end of heating process 
- Relay Board: 16-channel relay board with 12 VDC power input, 5 VDC voltage regulator for relay control, optocoupler, 250 VAC 10A main relays, led indicator lights, max. power consumption 0,5A @ 12V
- connector pcb: own build connector pcb to connect ESP32 to MCP and relay board

### used software:
- engineering done with Microsoft Visual code with PlatformIO
- own created libraries "heaterBoard" for led matrix control and "blinking" for led control

### software structure
|folder   |comment                                    |
|---------|-------------------------------------------|
|.pio     |fies for platformIO (config files ...)     |
|.vscode  |files for visual studio code               |
|docu     |documentation                              |
|include  |source code                                |
|lib      |created libraries                          |
|src      |source code                                |
|test     |code for testing device (not used)         |

## versions
### V1_0: 2019-03-14
- tested version used in water heater
- prevision test versions not tracked
