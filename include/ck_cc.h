/*
 * Copyright 2009-2014 Samy Al Bahra.
 * Copyright 2014 Paul Khuong.
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

#ifndef _CK_CC_H
#define _CK_CC_H

#if defined(__GNUC__) || defined(__SUNPRO_C)
#include "gcc/ck_cc.h"
#endif

/*
 * Container function.
 * This relies on (compiler) implementation-defined behavior.
 */
#define CK_CC_CONTAINER(F, T, M, N)						\
	CK_CC_INLINE static T *							\
	N(F *p)									\
	{									\
		const F *n = p;							\
		return (T *)(void *)(((char *)n) - ((size_t)&((T *)0)->M));	\
	}

#define CK_CC_PAD(x) union { char pad[x]; }

#ifndef CK_CC_ALIASED
#define CK_CC_ALIASED
#endif

#ifndef CK_CC_UNUSED
#define CK_CC_UNUSED
#endif

#ifndef CK_CC_USED
#define CK_CC_USED
#endif

#ifndef CK_CC_IMM
#define CK_CC_IMM
#endif

#ifndef CK_CC_PACKED
#define CK_CC_PACKED
#endif

#ifndef CK_CC_WEAKREF
#define CK_CC_WEAKREF
#endif

#ifndef CK_CC_ALIGN
#define CK_CC_ALIGN(X)
#endif

#ifndef CK_CC_CACHELINE
#define CK_CC_CACHELINE
#endif

#ifndef CK_CC_LIKELY
#define CK_CC_LIKELY(x) x
#endif

#ifndef CK_CC_UNLIKELY
#define CK_CC_UNLIKELY(x) x
#endif

#ifndef CK_F_CC_FFS
#define CK_F_CC_FFS
CK_CC_INLINE static int
ck_cc_ffs(unsigned int x)
{
	unsigned int i;

	if (x == 0)
		return 0;

	for (i = 1; (x & 1) == 0; i++, x >>= 1);

	return i;
}
#endif

#ifndef CK_F_CC_CLZ
#define CK_F_CC_CLZ
#include <ck_limits.h>

CK_CC_INLINE static int
ck_cc_clz(unsigned int x)
{
	unsigned int count, i;

	for (count = 0, i = sizeof(unsigned int) * CHAR_BIT; i > 0; count++) {
		unsigned int bit = 1U << --i;

		if (x & bit)
			break;
	}

	return count;
}
#endif

#ifndef CK_F_CC_CTZ
#define CK_F_CC_CTZ
CK_CC_INLINE static int
ck_cc_ctz(unsigned int x)
{
	unsigned int i;

	if (x == 0)
		return 0;

	for (i = 0; (x & 1) == 0; i++, x >>= 1);

	return i;
}
#endif

#ifndef CK_F_CC_POPCOUNT
#define CK_F_CC_POPCOUNT
CK_CC_INLINE static int
ck_cc_popcount(unsigned int x)
{
	unsigned int acc = x;

	acc = (acc & 0x55555555) + (acc >> 1 & 0x55555555);
	acc = (acc & 0x33333333) + (acc >> 2 & 0x33333333);
	acc = acc + (acc >> 4)  & 0x0F0F0F0F;
	acc = acc + (acc >> 8)  & 0x00FF00FF;
	acc = acc + (acc >> 16) & 0x0000FFFF;

	return acc;
}

CK_CC_INLINE static int
ck_cc_popcountll(unsigned long long x)
{
	unsigned long long acc;

	acc = v - ((v >> 1) & 0x5555555555555555ull);
	acc =     ((acc >> 2) & 0x3333333333333333ull) + (acc & 0x3333333333333333ull);
	acc =     ((acc >> 4)  + acc) & 0x0F0F0F0F0F0F0F0Full;
	acc =     ((acc >> 8)  + acc) & 0x00FF00FF00FF00FFull;
	acc =     ((acc >> 16) + acc) & 0x0000FFFF0000FFFFull;
	acc =     ((acc >> 32) + acc) & 0x00000000FFFFFFFFull;

	return (int)acc;
}

#endif

#endif /* _CK_CC_H */
