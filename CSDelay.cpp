/*! --------------------------------------------------------------------------------------
 
 @file      CSDelay.cpp
 @brief     Basic delay line effect definition.
 @details	Creating Sound DSP Audio Programming series.
 
 @author    Christian Floisand
 @version   1.0
 @date      Created: 2013/05/30
            Updated: 2013/05/31
 @copyright Copyright (C) 2013  Creating Sound
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ----------------------------------------------------------------------------------------- */

#include <memory.h>
#if defined _WIN32 || defined _WIN64
#include <malloc.h>     // for aligned dynamic memory allocation
#endif

#include "CSDelay.h"


CSDelay::CSDelay ()
: mBuffer(nullptr)
, mBufferLength(0)
, mPos(0)
, mGain(1.f)
, mFeedback(0.f)
, mDry(0.f)
, mWet(0.f)
{
}

/*!
 @brief CSDelay constructor.
 @details The dynamic allocation of the delay buffer requires 16-byte alignment with the 
 Portaudio engine. Data alignment is automatic in OS X.
 @param delayTime The time of the delay line in seconds.
 @param gain The gain adjustment of the delay effect in amplitude.
 @param feedback Amount of feedback in the delay effect in amplitude. Must be < 1, or it will cause
 oscillation or system overflow.
 @param wetAmount Level of the wet (delayed) signal.
 @param dryAmount Level of the dry (original) signal.
*/
CSDelay::CSDelay (const float delayTime, const float gain, const float feedback, const double sampleRate,
                  const int numChannels, const float dryAmount, const float wetAmount)
: mBuffer(nullptr)
, mBufferLength(0)
, mPos(0)
, mGain(gain)
, mFeedback(feedback)
, mDry(wetAmount)
, mWet(dryAmount)
{
	mBufferLength = static_cast<int>(delayTime * sampleRate) * numChannels;
    int bufferSize = mBufferLength * sizeof(float);
    
#if defined _WIN32 || defined _WIN64
    mBuffer = (float*)_aligned_malloc(bufferSize, 16);
#else
	mBuffer = new float[mBufferLength];
#endif
    
	memset(mBuffer, 0, bufferSize);
}

CSDelay::~CSDelay ()
{
#if defined _WIN32 || defined _WIN64
    _aligned_free(mBuffer);
#else
	delete[] mBuffer;
#endif
}

