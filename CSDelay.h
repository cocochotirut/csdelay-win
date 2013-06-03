/*! --------------------------------------------------------------------------------------
 
 @file      CSDelay.h
 @brief     Basic delay line effect.
 @details   Creating Sound DSP Audio Programming series.
 
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

#ifndef _CSDelay_h_
#define _CSDelay_h_


/*! --------------------------------------------------------------------
 
 @class CSDelay
 @brief Simple delay line.
 @details Supports gain and feedback amounts as well as wet/dry mix.  With 
 multichannel audio, the delay buffer is stored in interleaved format.
 Incrementing the buffer position happens automatically after writing to it.
 
 ----------------------------------------------------------------------- */

class CSDelay
{
public:

	CSDelay (const float delayTime, const float gain, const float feedback, const double sampleRate,
             const int numChannels, const float dryAmount, const float wetAmount);
	~CSDelay ();

	inline float read () const
	{
		return mBuffer[mPos] * mGain;
	}

	inline void write (const float value)
	{
		mBuffer[mPos] = value + (mBuffer[mPos] * mFeedback);
		incr();
	}
    
	/*!
	 @brief Processes an audio sample according to the dry/wet mix.
     @param drySample Audio sample from the original signal.
     @param wetSample Delayed audio sample, fetched from the delay buffer.
	*/
    inline float processSample (const float drySample, const float wetSample) const
	{
		return drySample * mDry + wetSample * mWet;
	}

private:

	float *mBuffer;
	int mBufferLength,
        mPos;
	float   mGain,
            mFeedback,
            mDry,
            mWet;
    
    CSDelay ();
    
    inline void incr ()
	{
		mPos = (mPos < mBufferLength ? mPos + 1 : 0);
	}

};


#endif // _CSDelay_h_
