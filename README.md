# Creating Sound DSP Audio Programming Series #

Welcome to the [Creating Sound](http://creatingsound.com) DSP Audio Programming series. This series will be introducing simple DSP audio effects that run in real time using the Portaudio sound engine, a cross-platform simple C API for interfacing with a wide variety of PC audio systems on Mac, Windows, and Linux. 

These projects include already-built binaries of Portaudio, but it may be necessary to download and build them yourself in some cases.  These binaries were built on Mac OSX 10.8.3 and Windows 7.  To build Portaudio yourself, go to [Portaudio](http://www.portaudio.com/download.html) and follow the build instructions. 

To run, simply build and execute the application, or run in debug mode from Xcode or Visual Studio. To keep things simple, the applications run in the console. If no errors occur and Portaudio is initialized, the message `Portaudio is running...` appears on the screen and you are free to play sounds/music using an instrument or microphone through the input audio device to hear the effect.

This series is meant to be educational towards audio DSP effects. While the programming is not overly complicated, a reasonable knowledge of C++, IDEs (Xcode/Visual Studio), and build environments is assumed.

## CSDelay ##

A simple delay effect that runs in real time using the Portaudio engine.  Parameters include *delay time*, *gain*, *feedback*, and *dry/wet mix*.
> *delay time*  
> The length of the delay in seconds.

> *gain*  
> The level adjustment of the delayed signal in amplitude.

> *feedback*  
> Controls the amount, given in amplitude, of the delayed signal feeding back into the delay line.

> *dry/wet mix*  
> Sets the level of the original unaffected signal and the delayed signal, between 0 and 1.

#### Extending the effect ####
Delay is one of the most basic and fundamental of DSP effects that serves as a foundation for many other, more sophisticated effects such as reverb, filtering, chorus, etc. On its own, however, it can be extended in many interesting ways:  

* Make it a true stereo delay by giving each channel unique parameters.
* Make a tap delay where you can specify a number of unique delay times, which allow you to create interesting delay rhythms.
* Make a variable delay that can be modulated by an LFO that, at low frequencies, will result in vibrato.

---

Copyright (C) 2013  Creating Sound
 
This program is free software: you can redistribute it and/or modify it under the terms 
of the GNU General Public License as published by the Free Software Foundation, either 
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
See the  GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  
If not, see <http://www.gnu.org/licenses/>.
 
 
PortAudio Portable Real-Time Audio Library  
Copyright (C) 1999-2011 Ross Bencina and Phil Burk
 
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
