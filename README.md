# Arduino Pong
A simple recreation of the classic game on an Arduino using an OLED screen.

![](https://raw.githubusercontent.com/jerwil/Arduino_Pong/master/Media/Arduino_Pong_Gif.gif "Arduino Pong Animation")

## Features

* Classic pong action
* Uses push-buttons to control up/down motion of paddles
* Generates beeps for paddle hits and point gains

## Video Demo

Check out Arduino Pong in action! The video is marginally more exciting than the gif.

<https://www.youtube.com/watch?v=9ip8cONzBe4>

## Design

### Hardware

![](https://github.com/jerwil/Arduino_Pong/raw/master/Media/Arduino_Pong_Image.jpg "Breadboard Image")

* Arduino Uno or equivalent
* 128x64 OLED display
* 1 220Ω resistor
* 4 10kΩ resistors
* 4 tact buttons
* Piezo buzzer or speaker
* Breadboard or PCB

### Schematics

![](https://raw.githubusercontent.com/jerwil/Arduino_Pong/master/Media/Arduino_Pong_bb.png "Sleep Coach schematic")

See the included Fritzing diagram (.fzz file) for details.

## Thanks

Thanks to Adafruit for the awesome [SSD1306 OLED driver library](https://github.com/adafruit/Adafruit_SSD1306) and [GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)! 

## License

<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">Arduino Pong</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="http://www.JeremyAdamWilson.com">Jeremy Wilson</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.

