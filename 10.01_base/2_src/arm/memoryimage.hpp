/* memoryimage.cpp - reading and saving several memory file formats

 Copyright (c) 2017, Joerg Hoppe, j_hoppe@t-online.de, www.retrocmp.com

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

  - Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  12-nov-2018  JH      entered beta phase
  18-Jun-2017  JH      created

 */

#ifndef _MEMORYIMAGE_HPP_
#define _MEMORYIMAGE_HPP_

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "unibus.h"

typedef enum {
	fileformat_none = 0,
	fileformat_addr_value_text = 1,
	fileformat_macro11_listing = 2,
	fileformat_papertape = 3,
	fileformat_binary = 4
} memory_fileformat_t;

#define MEMORY_ADDRESS_INVALID	0x7fffffff

#define MEMORY_WORD_COUNT	UNIBUS_WORDCOUNT	//128 kwords, 18 bit addresses
#define MEMORY_DATA_MASK	0xffff	// lower 16bits are valid

class memoryimage_c: public logsource_c {
private:
	uint16_t get_word(unsigned addr) {
		return data.words[addr / 2];
	}
	void put_word(unsigned addr, uint16_t w) {
		data.words[addr / 2] = w;
		valid[addr / 2] = true;
	}

	void put_byte(unsigned addr, unsigned b);

	bool valid[MEMORY_WORD_COUNT]; // 0 = memory words[] invalid

	void assert_address(unsigned addr) {
		assert((addr) / 2 < MEMORY_WORD_COUNT);
	}

public:
	// word idx IS NOT the addr, addr = idx + 2
	unibus_memory_t data; // array with data words
	//uint16_t words[MEMORY_WORD_COUNT];
	int entry_address; // start address, if found. MEMORY_ADDRESS_INVALID = invalid

	memoryimage_c() {
		log_label = "MEMIMG" ;
	}

	void init(void);

	// is words[addr] initialized?
	bool is_valid(unsigned addr) {
		unsigned wordidx = addr / 2;
		assert_address(addr);
		return valid[wordidx];
	}
	void fill(uint16_t fillword) ;

	void get_addr_range(unsigned *first, unsigned* last);
	unsigned get_word_count(void);
	void set_addr_range(unsigned first, unsigned last) ;


	bool load_addr_value_text(const char *fname);bool load_macro11_listing(const char *fname,
			const char *entrylabel);bool load_papertape(const char *fname);bool load_binary(
			const char *fname);

	void save_binary(const char *fname, unsigned bytecount);

	void info(FILE *f);
	void dump(FILE *f);

};

extern memoryimage_c *membuffer;

#endif /* MEMORY_H_ */
