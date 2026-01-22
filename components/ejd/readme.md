external_components:
  - source:
      type: git
      url: https://github.com/cctweaker/esphome_json_data
    components: [ ejd ]
    refresh: 0s # ensure a fresh pull from GitHub - only required if you think things will have changed.

# Enable logging
logger:
  level: VERBOSE #makes uart stream available in esphome logstream
  baud_rate: 0 #disable logging over uart

uart:
  id: ejd
  rx_pin: 3
  tx_pin: 1
  baud_rate: 115200

one_wire:
  - platform: gpio
    pin: 12

sensor:
  - platform: ejd
    p1:
      id: iv
      name: Vrms
      retain: false
    p2:
      id: msg
      name: Message Number
      retain: false
    p3:
      id: p1
      name: Kitchen Power
      retain: false

  # only one device
  - platform: dallas_temp
    name: temperature
    update_interval: 120s
  # specific address
  - platform: dallas_temp
    address: 0x1234567812345628
    name: temperature2
  # second device
  - platform: dallas_temp
    index: 1
    name: temperature1