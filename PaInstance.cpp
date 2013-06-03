/*! --------------------------------------------------------------------------------------
 
 @file      PaInstance.cpp
 @brief		Portaudio instance definition.
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

#include "PaInstance.h"
#include "CSDelay.h"


/*!
    @brief Audio callback routine.
    @details This is where all the audio processing happens. Specific DSP data or processes are passed
	in via userData. The pointer to userData is given to the initialize method in PaInstance.
    @warning This function operates at a high priority level, so the code placed in here should be as 
    lighweight as possible. The code within the callback should not call any function that may block, such 
    as locks or memory allocation.
    @param input The input buffer; interleaved if more than one channel.
    @param output The output buffer; interleaved if more than one channel.
    @param samples The number of samples passed to the callback to process. You must process exactly
    the given number of samples, or clicks and pops will result.
	@sa PaInstance
 */
int audioCallback (const void* input, void* output, unsigned long samples,
                   const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
	const float *in = (const float*)input; 
	float *out = (float*)output;
	CSDelay *delay = (CSDelay*)userData;
	float delaySample;

	for (int i = 0; i < samples; ++i)
	{
        // left channel
		delaySample = delay->read();
		delay->write(*in);
        *out++ = delay->processSample(*in++, delaySample);
        
        // right channel
		delaySample = delay->read();
		delay->write(*in);
        *out++ = delay->processSample(*in++, delaySample);
	}

	return paContinue;
}

/* -----------------------------------------------------------------------------------------
 
    Portaudio instance definition
 
 ------------------------------------------------------------------------------------------- */

PaInstance* PaInstance::mInstance = nullptr;

PaInstance* PaInstance::Instance ()
{
	if (mInstance == nullptr)
	{
		mInstance = new PaInstance;
	}
	return mInstance;
}

PaInstance::PaInstance ()
: mAudioStream(nullptr)
{
}

/*!
 @brief Initializes Portaudio.
 @details Both the default input and output devices are chosen. If no default devices are found, the program exits.
 @param userData User data to pass to the callback function.
 @sa audioCallback
 */
bool PaInstance::initialize (const int inChannels, const int outChannels, void* userData)
{
	PaStreamParameters inputParams, outputParams;
    PaError error;

	std::cout << "Initializing Portaudio.\n\n";
    
	error = Pa_Initialize();
    if (error != paNoError)
    {
		// If Pa_Initialize fails, Pa_Terminate should not be called, which is why 
		// errorHandler isn't called.
        std::cerr << "Portaudio failed to initialize. Error " << error << "\n";
		std::cerr << Pa_GetErrorText(error) << "\n\n";
        return false;
    }
    
    if ( ! getInputDevice(inputParams, inChannels) )
    {
        return false;
    }
    
    if ( ! getOutputDevice(outputParams, outChannels) )
    {
        return false;
    }
	
	error = Pa_OpenStream(&mAudioStream, &inputParams, &outputParams, SAMPLING_RATE, SAMPLE_BLOCK, paClipOff, audioCallback, userData);
    if (error != paNoError)
    {
        errorHandler(error);
        return false;
    }
    
    return true;
}

bool PaInstance::terminate ()
{
	PaError error = Pa_Terminate();
    if (error != paNoError)
    {
        errorHandler(error);
        return false;
    }
    
    std::cout << "Terminating Portaudio.\n";
    
    return true;
}

bool PaInstance::startStream ()
{
    PaError error = Pa_StartStream(mAudioStream);
    if (error != paNoError)
    {
        errorHandler(error);
        return false;
    }
    
	std::cout << "\nPortaudio is running...\n";
    return true;
}

bool PaInstance::stopStream ()
{
    PaError error;
    
	error = Pa_StopStream(mAudioStream);
    if (error != paNoError)
    {
        errorHandler(error);
        return false;
    }
    
	error = Pa_CloseStream(mAudioStream);
    if (error != paNoError)
    {
        errorHandler(error);
        return false;
    }
    
    return true;
}

void PaInstance::errorHandler (PaError errorCode)
{
    std::cerr << "Portaudio error " << errorCode << "\n";
    std::cerr << Pa_GetErrorText(errorCode) << "\n\n";
    
    Pa_Terminate();
}

bool PaInstance::getInputDevice (PaStreamParameters& streamParams, const int numChannels)
{
    PaDeviceIndex inputDevice = Pa_GetDefaultInputDevice();
    if (inputDevice == paNoDevice)
    {
        std::cerr << "Error: no default input device.\n";
        return false;
    }
    
    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(inputDevice);
    const PaHostApiInfo *hostApiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
	
    std::cout << "Opening audio input device: " << hostApiInfo->name << " " << deviceInfo->name << "\n";
    
	streamParams.device = inputDevice;
	streamParams.channelCount = numChannels;
	streamParams.sampleFormat = paFloat32;
	streamParams.suggestedLatency = deviceInfo->defaultLowOutputLatency;
	streamParams.hostApiSpecificStreamInfo = NULL;
    
    return true;
}

bool PaInstance::getOutputDevice (PaStreamParameters& streamParams, const int numChannels)
{
    PaDeviceIndex outputDevice = Pa_GetDefaultOutputDevice();
    if (outputDevice == paNoDevice)
    {
        std::cout << "Error: no default output device.\n";
        return false;
    }
    
	const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(outputDevice);
	const PaHostApiInfo *hostApiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
    
    std::cout << "Opening audio output device: " << hostApiInfo->name << " " << deviceInfo->name << "\n";
    
	streamParams.device = outputDevice;
	streamParams.channelCount = numChannels;
	streamParams.sampleFormat = paFloat32;
	streamParams.suggestedLatency = deviceInfo->defaultLowOutputLatency;
	streamParams.hostApiSpecificStreamInfo = NULL;
    
    return true;
}
