I compared super_fast_hash from http://www.azillionmonkeys.com/qed/hash.html, FNV from http://www.isthe.com/chongo/src/fnv/hash_32.c, and murmurhas from https://code.google.com/p/smhasher/source/browse/trunk/MurmurHash3.cpp.

I compared the distributions of the hashes generated from the S&P 500 and the
NASDAQ, and all of the distributions were very similar.

The difference was that super_fast_hash was in fact the fastest hash by a
large margin.