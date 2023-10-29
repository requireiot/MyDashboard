MyDashboard - openHAB at a Glance
====

## Use Cases
* when leaving the house, see at a glance all relevant home automation information, such as
  * are all windows closed?
  * are all appliances turned off?
  * what is the outside temperature? i.e. should I wear a coat?

## Requirements

### Connectivity
- [x] `R001` the dashboard has a wireless connection to the home automation system, i.e. WiFi or MySensors RF24
- [x] `R002` the dashboard can display information from any OpenHAB item, not just MySensors or MQTT based items
  - [x] `R002.1` information is retrieved from OpenHAB via the REST API

### Hardware
- [x] `R010` the dashboard runs on batteries
- [x] `R011` if non-rechargeable batteries are used, they  must last for at least a year
- [ ] `R012` if rechargeable batteries are used, they must be last for at least a month on one charge

### Configuration 
- [ ] `R020` the set of information items displayed can be configured without changing source code
- [x] `R021` an item's label is configurable
- [x] `R022` the x/y position on the screen of a display item is configurable

### Displayed information
- [x] `R030` the dashboard can display static labels
- [x] `R031` the dashboard can display OpenHAB items of type Switch (on/off or open/closed)
- [x] `R032` the dashboard can display OpenHAB items of type Number, in particular temperatures

### Visualization
- [x] `R040` in the active or unexpected state of a Switch or Contact item, its label is shown in red
- [x] `R041` in the passive or expected state of a Switch or Contact item, its label is shown in black
- [x] `R042` items of type Number are formatted as defined in OpenHAB

## Architecture
- [x] `R101` the dashboard uses an e-Ink display. Rationale: only way to satisfy battery life requirements
- [x] `R102` the dashboard uses a Wifi-capable processor, i.e. ESP8266 or ESP32. Rationale: ability to contact OpenHAB REST API directly
