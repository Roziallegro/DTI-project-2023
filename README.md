# DTI-project-2023
_Code name: سالم (Salem or Peace in Arabic)_  
_This project focuses on how light structures can help integrate interaction and promote youth culture amongst youths_  
[full project report](http://asd.courses.sutd.edu.sg/dti-teams/projects-2023/cohort-4-projects-2023/cohort-4-team-2/)  
<br>

## The process  
Change the light patterns according to how the hand gesture detected
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Lights%20animation%201.png">  
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Lights%20animation%202.png">  
<br>

## Hardwares used
1x Arduino Uno  
3x Arduino Nano  
4x NRF24L01 Wireless transmission radio  
1x PAJ7620 Hand gesture sensor [Datasheet](https://www.epsglobal.com/Media-Library/EPSGlobal/Products/files/pixart/PAJ7620U2.pdf)   
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
Overall layout
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Overall%20node.png">

<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Arduino%20schematics%20updated.png">

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
            <td>3.3V</td>
            <td>3.3V</td>
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

<table>
        <tr>
            <th>Arduino Uno Pins</th>
            <th>PAJ7620 Pins</th>
        </tr>
        <tr>
            <td>3.3V</td>
            <td>VIN</td>
        </tr>
        <tr>
            <td>GND</td>
            <td>GND</td>
        </tr>
        <tr>
            <td>A5</td>
            <td>SCL</td>
        </tr>
        <tr>
            <td>A4</td>
            <td>SCA</td>
        </tr>
</table>

<table>
        <tr>
            <th>Arduino Uno Pins</th>
            <th>Ultrasonic sensor Pins</th>
        </tr>
        <tr>
            <td>3.3V</td>
            <td>Vcc</td>
        </tr>
        <tr>
            <td>AD</td>
            <td>Trig</td>
        </tr>
        <tr>
            <td>D7</td>
            <td>Echo</td>
        </tr>
        <tr>
            <td>GND</td>
            <td>Gnd</td>
        </tr>
</table>
<br>

## Appendix
A brief rundown as to how the server, client, hand gesture and wireless transmission radio works
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Server.png">  
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Client.png"> 
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Hand%20gesture.png">  
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Transmission.png">  
<img src="https://github.com/Roziallegro/DTI-project-2023/blob/main/assets/Ultrasonic.png">  
<br>

## References
1. https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
2. https://howtomechatronics.com/tutorials/arduino/how-to-build-an-arduino-wireless-network-with-multiple-nrf24l01-modules/
3. https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor
4. https://github.com/palsayantan/Gesture-Control-Neopixel-LED-game/blob/master/Gesture_Game/Gesture_Game.ino
