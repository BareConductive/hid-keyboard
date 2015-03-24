[![Bare Conductive](https://www.dropbox.com/s/p0p71yid2t8tenp/LOGO_256x106.png?dl=1)](http://www.bareconductive.com/)

# Bare Conductive HID keyboard Demo Code

Simple proximity-triggered MP3 code for the [Bare Conductive Touch Board](http://www.bareconductive.com/shop/touch-board/). Touch electrode 0, **TRACK000.MP3** plays from the micro SD card. Touch electrode 1, **TRACK001.MP3** plays from the micro SD card, and so on.  This is a small evolution of the [Touch MP3](https://github.com/BareConductive/touch-mp3) code that ships with the [Touch Board](http://www.bareconductive.com/shop/touch-board/).

## Requirements
* [Arduino](http://arduino.cc/en/Main/Software) 1.5.6 or later

* Arduino's instructions for installing libraries are available [here](http://arduino.cc/en/Guide/Libraries)
	
* [Bare Conductive MPR121 library](https://github.com/bareconductive/mpr121) (zip file download [here](https://github.com/bareconductive/mpr121/archive/public.zip))

* [Bare Conductive Arduino Hardware Plugins](https://github.com/bareconductive/bare-conductive-arduino) (zip file download [here](https://github.com/bareconductive/bare-conductive-arduino/archive/public.zip)) - instructions on installing this hardware plugin folder are available [here](https://github.com/bareconductive/bare-conductive-arduino).


## Install

1. Close the Arduino IDE if you have it open.
1. Download the [.zip](https://github.com/BareConductive/hid-keyboard/archive/public.zip) or clone the repository to your local machine - if downloading the .zip, extract the contents somewhere that suits you.
1. Take the **HID_Keyboard** folder and move it to **Arduino Sketchbook Folder**. This will be different for each operating system: 

	**Windows**
	
	Libraries\\Documents\\Arduino
	
	or
	
	My Documents\\Arduino	
	
	**Mac**
	
	Documents/Arduino
	
	**Linux (Ubuntu)**
	
	Home/Arduino


	If this folder does not exist, create it first.
1. Reopen the Arduino IDE - you should now be able to open the sketch in the **File -> Sketchbook** menu.