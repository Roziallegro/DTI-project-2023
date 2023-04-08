# DTI-project-2023
_Code name: سالم (Salem or Peace in Arabic)_  
_This project focuses on how light structures can help integrate interaction and promote youth culture amongst youths_  
[full project report](http://asd.courses.sutd.edu.sg/dti-teams/projects-2023/cohort-4-projects-2023/cohort-4-team-2/)  
<br>

## Hardwares used
1x Arduino Uno  
3x Arduino Nano  
4x NRF24L01 Wireless transmission radio  
1x PAJ7620 Hand gesture sensor  
1x Ultrasonic sensor  

Wires  
5m Neopixel LED (5V or 12V)  
*When facing issues with neopixels refer to this thread: https://blog.adafruit.com/2016/10/28/tips-for-troubleshooting-neopixel-glitches/  
PCB  
Voltage regulator  
10x 3pin-head with screws  
Optional: resistors, Battery clips  
<br>

## Libraries used
[Neopixel library](https://github.com/adafruit/Adafruit_NeoPixel)  
[Gesture sensor PAJ7620 library](https://github.com/Seeed-Studio/Gesture_PAJ7620)  
[RF24 Network library](https://www.arduinolibraries.info/libraries/rf24-network)  
[RF24 library](https://www.arduinolibraries.info/libraries/rf24-network)  
[SPI library](https://github.com/codebendercc/arduino-library-files/tree/master/libraries/SPI)  
<br>

## Wiring
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Arduino%20schematics.png">

<table>
        <tr>
            <th>Arduino Nano Pins</th>
            <th>Arduino Uno Pins</th>
            <th>NRF24L01 Pins</th>
            <th>Arduino Uno Pins</th>
            <th>Arduino Nano Pins</th>
        </tr>
        <tr>
            <td>GND</td>
            <td>GND</td>
            <td>GND | VCC</td>
            <td>GND</td>
            <td>GND</td>
        </tr>
        <tr>
            <td>D10</td>
            <td>D9</td>
            <td>CE | CSN</td>
            <td>D10</td>
            <td>D9</td>
        </tr>
        <tr>
            <td>D13</td>
            <td>D13</td>
            <td>SCK | MOSI</td>
            <td>D11</td>
            <td>D11</td>
        </tr>
        <tr>
            <td>D12</td>
            <td>D12</td>
            <td>MISO | IRQ</td>
            <td>-</td>
            <td>-</td>
        </tr>
    </table>
