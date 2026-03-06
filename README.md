# Garden Guard: keep your plants healty and strong <3

This is an Low Cost Project because I made a mistake (or AliExpress fool me) buying a Raspberry Pi Pico W for 4 USD, but it was **CLONED** board. That's mean the native WiFi driver doesn't work.

So I tried differents solutions (some of them are bellow), but to use WiFi and "easy" MQTT conection this is what work for me.

## Requierements

- [Clonned Raspeberry Pi Pico W with esp8285 wifi chip](https://a.aliexpress.com/_mMKS0eh)
- [Capacitive Soil Moisture Sensor](https://a.aliexpress.com/_msCFI89) 
- esptool
- Ubuntu 22.04
- (if you need as me) [custome Firmware for esp8285](files/ESP_AT_Firmware_V2.2.0.bin).

```sh
    sudo apt instal esptool
```

### Just WiFI
You can use [this code](files/main.cpp) right away. Don't be shy

This code also is usefull to check your firmware version.

### WiFi + MQTT (need your this repo)
If your version is lower than V2.0, you need to follow this steps.

Drop this [pass-through code](files/Serial_port_transmission.uf) on you RPI Pico W. It's a code to "connect direct" to the second microcontroller.

Now you can check your chip, remember press the button (that one far from usb port) while you're plugging your pico board.

```sh
# Check your chip, crystal oscillator 
#Remember ajust the port
esptool --port /dev/ttyACM0 chip_id
```

Now run this in the shell to 

```sh
# First erase everything
esptool --port /dev/ttyACM0 erase_flash

# Now, updated the new one, please check the port, chip, baudrate, crystal oscillator and flash_size have to be 1MB
esptool --port /dev/ttyACM0 --chip esp8266 --baud 115200  write_flash 
        --flash_mode dout --flash_freq 26m --flash_size 1MB 
        0x0000  docs/ESP_AT_Firmware_V2.2.0.bin 
```

now, check again your firmware version, should show "V2.0.0".

# Thanks to:
- [rp2040 with esp8285](https://github.com/mocacinno/rp2040_with_esp8285/tree/main)
- [Custom Compiled ESP-AT Firmware Binaries](https://github.com/CytronTechnologies/esp-at-binaries)