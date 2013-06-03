/*! --------------------------------------------------------------------------------------
 
 @file      PaInstance.h
 @brief     Portaudio instance.
 @details	Creating Sound DSP Audio Programming series.
 
 @author    Christian Floisand
 @version   1.0
 @date      Created: 2013/05/30
            Updated: 2013/05/31
 @copyright Copyright (C) 2013  Creating Sound
 
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
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 furnished to do so, subject to the following conditions:
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 ----------------------------------------------------------------------------------------- */

#ifndef _PaInstance_h_
#define _PaInstance_h_

#include <iostream>
#include <cmath>

#include "portaudio.h"


#define SAMPLE_BLOCK        (256)
#define SAMPLING_RATE       (44100.)


/*! --------------------------------------------------------------------
 
 @class PaInstance
 @brief Portaudio instance.
 @details Wrapped C++ interface to the Portaudio engine, implemented as a
 singleton class. Extend this class to add more interactions with Portaudio.
 
 ----------------------------------------------------------------------- */

class PaInstance
{
public:

	static PaInstance* Instance ();

	bool initialize (const int inChannels, const int outChannels, void* userData);
	bool terminate ();

	bool startStream ();
	bool stopStream ();

private:

	static PaInstance* mInstance;
	PaStream *mAudioStream;
    
    PaInstance ();
    
    void errorHandler (PaError errorCode);
    
    bool getInputDevice (PaStreamParameters& streamParams, const int numChannels);
    bool getOutputDevice (PaStreamParameters& streamParams, const int numChannels);

};


#endif // _PaInstance_h_
