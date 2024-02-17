# Controller for water heater

## abstract
Water heater with temperature selection is controlled with ATtiny. Original hardware of heater used, but replacement of microcontroller.

## discription
### used hardware:
- ATtiny chip
- Water heater with 
  - temperature sensor
  - button "start / stop heating" with status led
  - button "reheating on / off"
  - button "temperature selection"
  - 4 led for temperature display (actual and preselected temperature)
  - pieco beeper to signal end of heating process 

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
