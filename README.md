## Wake a computer and a video projector with a push button, using Wake on LAN and HDMI-CEC

### Hardware
For this project we used : 
* a feather huzzah (https://www.adafruit.com/product/2821)
* a ethernet shield for feather (https://www.adafruit.com/product/3201)
* a push button
* a resistance 
* a PC (an Intel NUC for example), HDMI-CEC compatible
* a video projector, with the HDMI-CEC standard

### Assembly
The feather huzzah and the ethernet shield are fixed together. 
The push button is connected to the shield : the NO port to one input port (such as the 16) and the 3V port through the resistance.
The COM port is connected to the ground.  

The ethernet shield is connected to the PC we want to wake up with an ethernet cable. 

Finally the PC and the video projector are connected with an HDMI cable. 

### PC configuration
First we allow Wake on LAN on the PC (https://www.lifewire.com/wake-on-lan-4149800). 
Then we configure the ethernet connection with IPv4 : 
* IP address = 192.168.1.2
* Mask = 255.255.255.0
* Gateway = 192.168.1.1

We also notice the MAC address of the ethernet port. 

### Video projector configuration 
We allow the video projector to wake up when receiving a HDMI signal. 
This configuration depends on the video projector model. 

### Code
The code for the feather is attached. 
The ethernet library used must be compatible with the W5500 chip and ESP8266. 

Two lines have to be changed : 
* the MAC address of the ethernet shield 
* the MAC address of the PC ethernet port 


### Use 
Push for more than 1 second the button, the PC will start with the video projector. 