/*! --------------------------------------------------------------------------------------
 
 @file      main.cpp
 @brief     Program entry point.
 @details   Creating Sound DSP Audio Programming series.
 
 @author    Christian Floisand
 @version   1.0
 @date      Created: 2013/05/31
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
 
 You should have received a c opy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ---------------------------------------------------------------------------------------- */

#include <iostream>

#include "CSDelay.h"
#include "PaInstance.h"


// delay parameters
#define DELAY_TIME      (0.42f)
#define DELAY_GAIN      (0.85f)
#define DELAY_FEEDBACK  (0.42f)
#define DELAY_DRY       (0.8f)
#define DELAY_WET       (0.55f)

#define INPUT_CHANNELS  (2)
#define OUTPUT_CHANNELS (2)


int main(int argc, const char * argv[])
{

    CSDelay delay(DELAY_TIME, DELAY_GAIN, DELAY_FEEDBACK, SAMPLING_RATE, OUTPUT_CHANNELS, DELAY_DRY, DELAY_WET);
    
    if ( PaInstance::Instance()->initialize(INPUT_CHANNELS, OUTPUT_CHANNELS, &delay) )
    {
        PaInstance::Instance()->startStream();
        
		std::cout << "Enter 'q' to quit: ";
        while (getchar() != 'q')
            Pa_Sleep(100);
        
        PaInstance::Instance()->stopStream();
        PaInstance::Instance()->terminate();
    }
    
    return 0;
}

