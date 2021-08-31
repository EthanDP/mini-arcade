# Mini Arcade Cabinet
Ever wanted to play a game like Simon on your own miniature arcade cabinet? This repo contains all the code, schematics, and stl files needed to create your very own mini Simon arcade machine running on an ATTiny85 microcontroller with an Arduino bootloader.

## Required materials:
* 1x DIP8 ATTiny85 microcontroller
* 1x Arduino Uno or similar microcontroller that can be used as an ISP
* 1x 3D Printer with filament of your choosing (if you don't have one many places such as local libraries have printers you can temporarily use)
* 1x Red LED
* 1x Green LED
* 1x Blue LED
* 1x Yellow LED
* ~2 Feet of 22 AWG solid core wire or ~20x jumper wires
* 4x 6mm Push Buttons
* 2x Breadboards (One should have 170 tie points) OR 1x breadboard and 1x Perf Board (one that fits into the arcade cabinet is best)
* 1x Small Perf Board (This is for the buttons, you will probably need to cut it down to size)
* 4x Through Hole Schottky Diodes
* 4x 220 or 330 Ohm Resistors (Choose depending on desired brightness of LEDs)
* 1x Two Port Screw Terminals OR Two Jumper Wires to solder to your USB cable
* 1x USB cable that you can cut one end off of

## How to Make
1. Make sure you have all required materials. You don’t need a 3D printer to make a functioning version of Simon but it will make your project look 1000 times cooler if it’s housed in a miniature arcade cabinet. :)
2. For this project I used an Arduino UNO as an ISP (In System Programmer) in order to program the ATTiny85. You’ll want to set up your Tiny on a breadboard and connect it according to the following diagram: 
![arduino_isp](https://user-images.githubusercontent.com/38187410/131546024-652cdb14-9be0-411e-af5b-62461158afd9.png) Note: the capacitor is used to make sure your Arduino UNO doesn’t reset when your Tiny is being programmed.
3. Next, move your Tiny over to your second breadboard (placing it somewhere on the end works best). This will be what actually goes inside of your arcade so make sure to use the 140 tie point breadboard. 
4. Place your diodes (I recommend cutting the leads down so they take up only a little space) according to this schematic: 
![arcade_schematic](https://user-images.githubusercontent.com/38187410/131546022-7fac3ae6-14c3-4a33-97fe-e413f56ae9da.png) Don’t worry about attaching buttons or LED’s yet since those won’t be on this breadboard. At this point your breadboard should look something like this (make sure the lines on your diodes match up with this diagram or your buttons won’t work): ![diode_placement](https://user-images.githubusercontent.com/38187410/131546030-0be443a8-ef1c-4aea-bdc6-05aee2d4fe55.png)
5. Next, put your four resistors on the breadboard and make sure each has one lead connected to ground (since we don’t have a ground connection set up yet you can decide which rows on your bread board will be the ground lines). Here’s how I set my resistors up (I’m using the right side of my board as the ground lines) ![resistor_placement](https://user-images.githubusercontent.com/38187410/131546034-b2b6285d-5c20-40d0-888a-2d7630c5d4cd.png)
6. Next you’ll connect up your power source. I’m using a screw terminal that I’ve stuck the 5V and GND wires of my USB cable into (which you’ll do in step 8), but you can also just solder the ends of the USB cable to jumper wires when you get there (make sure to cover the soldered ends in electrical tape so you don’t accidentally short the wires!). Your breadboard should now look like this (or should have two jumpers connected if you’re not using a screw terminal): ![terminal_placement](https://user-images.githubusercontent.com/38187410/131546036-674106bb-d466-44f3-bc78-91b2b790d8d0.png)
7. Now we’re going to wire up our power and ground connections. This is where solid core wire comes in handy since you can easily cut it down to any size you need. Once you’re done your connections should look something like this: ![power_connections](https://user-images.githubusercontent.com/38187410/131546033-e4d56dcf-60d6-4f0d-8054-52eb99f3ddc8.png)
8. Now it's time to get our USB cable connected so we can actually power this thing. Take your USB cable and cut one end off (the end that isn’t type A male) and then strip about a half inch of the covering off. Now cut the green and white wires as well (those are the data lines which we won’t be needing today). Finally, strip the tiny red and black wires and place the exposed copper wire into your screw terminal (or solder them to jumper wires if you want). Make sure these two aren’t touching by using some electrical tape. ![usb_power](https://user-images.githubusercontent.com/38187410/131546038-bcbfb3b1-9c57-4c0e-8310-f070806ff0a6.png)
9. Now for the buttons, grab a piece of perf board, you can cut it down to size beforehand (it needs to fit in the button part of the arcade cabinet) or later on once you have your 3D printed cabinet. If you are just prototyping the Simon game then you can do this one another breadboard. ![button_board](https://user-images.githubusercontent.com/38187410/131546027-1732c706-727b-40bc-9373-eda984ed7ff8.png)
10. Now we’re going to connect the buttons to our breadboard so they can supply a signal to our microcontroller and light up our LEDs. Your wiring should look something like this: ![button_connections](https://user-images.githubusercontent.com/38187410/131546029-5c8cb66e-c552-4ed4-9ec2-5fd6226bc258.png) Note: this wiring may look a bit confusing but don’t worry! I am taking advantage of the fact that these types of buttons have two sides. The two leads on the left side of a button are connected and the two leads on the right side are connected as well. When you press the button these two sides are temporarily connected!
11. And now the last step on the electronics side, we’re going to connect our LEDs according to the following image: ![led_connections](https://user-images.githubusercontent.com/38187410/131546032-d3925cbf-3123-45f4-8cea-cde4a4cc62b9.png) Note: At this point the diagram is starting to get a little complicated, don’t be afraid to retrace your steps to make sure you have everything connected correctly.
Code How-To coming soon!
