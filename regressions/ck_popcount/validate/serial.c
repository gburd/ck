/*
 * Copyright 2014 Gregory Burd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <ck_cc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common.h"


int
main(void) //(int argc, char *argv[])
{
	unsigned int i = 0;
	unsigned int v; // current permutation of bits
	unsigned int w; // next permutation of bits

	v = 0xdeadbeef; // 24 set bits, to start

	do {
		// permute bits in v
		unsigned int r, t = (v | (v - 1)) + 1;
		w = v==0 ? 0 : t | ((((t & -t) / (v & -v)) >> 1) - 1);

		// count on bits, the slow way
		unsigned int acc, q = v;
		for (acc = 0; q != 0; q >>= 1) acc += q & 1;

		// ensure popcount is the same
		if ((r = ck_cc_popcount(v)) != acc)
			ck_error("[%u] ERROR: Expected %u bits set : %u\n", i, acc, r);
		v = w;
	} while(i++ < 10000000); // check 1M bit permutations

	return 0;
}
