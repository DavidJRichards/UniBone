/* utils.hpp: misc. utilities

   Copyright (c) 2018, Joerg Hoppe
   j_hoppe@t-online.de, www.retrocmp.com

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   JOERG HOPPE BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


   12-nov-2018  JH      entered beta phase
   20-may-2018  JH      created
*/

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include <string>
#include <algorithm> // TRIM_STRING

#include "logger.hpp"

#define MILLION 1000000L
#define BILLION (1000L * MILLION)

#ifndef _UTILS_CPP_
extern volatile int SIGINTreceived;
#endif


// my version
void strcpy_s(char *dest, int len, const char *src) ;

// mark unused parameters
#define UNUSED(x) (void)(x)

#define USE(x) (void)(x)

void SIGINTcatchnext();

// dummy to have an executable line for break points
void break_here(void) ;

class timeout_c: public logsource_c {
private:
	struct timespec starttime;
	uint64_t duration_ns;
public:
	timeout_c() ;
	void start(uint64_t duration_ns);
	uint64_t elapsed_ns(void);bool reached(void);
	void wait_ns(uint64_t duration_ns);
	void wait_us(unsigned duration_us);
	void wait_ms(unsigned duration_ms);

};


class progress_c {
private:
	unsigned linewidth;
	unsigned cur_col;
public:
	progress_c(unsigned linewidth);
	void init(unsigned linewidth);
	void put(const char *info);
};

unsigned random24();

char *cur_time_text(void) ;

// remove leading/trailing spaces
// https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
#define TRIM_STRING(str) str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end())

bool fileExists(const std::string& filename) ;

//ool caseInsCompare(const std::string& s1, const std::string& s2) ;


// add a number of microseconds to a time
struct timespec timespec_add_us(struct timespec ts, unsigned us) ;
// add microseconds to current time
struct timespec timespec_future_us(unsigned offset_us) ;


#endif /* _UTILS_H_ */
