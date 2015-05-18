/*
 * Author: Makoto Inoue <maksjapan@yahoo.com>
 * Copyright (c) 2015 PolyTechs,Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <ctime>
#include <signal.h>
#include <unistd.h>

#include "mraa.hpp"
#include "Adafruit_RGBLCDShield_mraa.hpp"

/*
 * Adafruit RGB LCD Shield C++ example using MRAA
 *
 * Demonstrate how to use the Adafruit RGB LCDshield using the MRAA library.
 *
 * Hardware required:
 *     1. Adafruit RGB LCD Shield (obviously)
 *     2. Intel Edison for Arduino (it should work on Intel Galileo boards, but not tested).
 *
 * Additional linker flags: none
 */

// These #defines make it easy to set the back light color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int running = 0;

void sig_handler(int signo)
{
    if (signo == SIGINT) {
        printf("stopping demo...\n");
        running = -1;
    }
}

int main()
{
	Adafruit_RGBLCDShield_mraa lcd(6);  //I2C bus number must be 6 for Intel Edison Arduino board
	lcd.begin(16,2);

	std::time_t _start_time = std::time(0);

	std::clock_t _start_clock = std::clock();
	lcd.print("Hello World!!");
	std::clock_t _end_clock = std::clock();
    std::cout << "Took " << 1000.0 * (_end_clock - _start_clock) / CLOCKS_PER_SEC << " ms" << std::endl;

    std::time_t _prev_time = 0;
    signal(SIGINT, sig_handler);

    while (running == 0) {
		// set the cursor to column 0, line 1
		// (note: line 1 is the second row, since counting begins with 0):
		lcd.setCursor(0, 1);

		std::time_t _time = std::time(0);
		//update only when second changes
		if(_time != _prev_time ){
			// print the number of seconds since start of application:
			lcd.print(_time - _start_time);
			_prev_time = _time;
		}

		uint8_t buttons = lcd.readButtons();

		if (buttons) {
			lcd.clear();
			lcd.setCursor(0,0);
			if (buttons & BUTTON_UP) {
				lcd.print("UP ");
				lcd.setBacklight(RED);
			}
			if (buttons & BUTTON_DOWN) {
				lcd.print("DOWN ");
				lcd.setBacklight(YELLOW);
			}
			if (buttons & BUTTON_LEFT) {
				lcd.print("LEFT ");
				lcd.setBacklight(GREEN);
			}
			if (buttons & BUTTON_RIGHT) {
				lcd.print("RIGHT ");
				lcd.setBacklight(TEAL);
			}
			if (buttons & BUTTON_SELECT) {
				lcd.print("SELECT ");
				lcd.setBacklight(VIOLET);
			}
		}
	}

    lcd.noDisplay();
    lcd.setBacklight(0);
	return 0;
}
