![](logo.png)
# PhoenixFC
A potentially disastrous attempt at writing a quadcopter flight controller from scratch.

## Overview

I have a strange ambition to write my own flight controller. I really have no idea what I'm doing but I'm hoping to have some fun and learn something as I go.

**01-02-2015** - I've just completed my first goal of hooking up a receiver and reading some control yay!

## Hardware

- [mbed LPC1768](http://developer.mbed.org/platforms/mbed-LPC1768/)
- [Spektrum AR7010 receiver](http://www.spektrumrc.com/Products/Default.aspx?ProdId=SPMAR7010)
- [Spektrum DX61 transmitter](https://www.spektrumrc.com/Products/Default.aspx?ProdId=SPM6600)

## Prerequisites

- Mac OSX 10.10
- XCode 5+ (and command line tools)

## Build

Simply checkout the code and run ```make``` from the project root.

## Install

Plugin the LPC1768 via USB and run ```make deploy``` from the project root. When it's finished press the reset button on the LPC1768.

## Output 

The easiest way to view the output from PhoenixFC is to use [CoolTerm](http://freeware.the-meiers.org/). Just configure it to connect to ```usbmodem1412``` with baudrate ```9600``` and you're good to go.



