// Refer to md5 from https://github.com/ZTao-z/WebSecurity
// Refer to aes from https://github.com/kokke/tiny-AES-c
// Thank ZTao-z and kokke and all contributors
#ifndef __REMMEL_CRYPTO__
#define __REMMEL_CRYPTO__

#include "constant.hpp"
#include "bitarray.hpp"

namespace remmel
{
    /*
        MD5
    */

    static constexpr char MD5_HEX[] = "0123456789abcdef";

    static constexpr uint32_t MD5_T[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    static constexpr uint32_t MD5_S[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                                         5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                                         4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                                         6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

#define MD5_F(b, c, d) (uint32_t)((b & c) | ((~b) & d))
#define MD5_G(b, c, d) (uint32_t)((b & d) | (c & (~d)))
#define MD5_H(b, c, d) (uint32_t)(b ^ c ^ d)
#define MD5_I(b, c, d) (uint32_t)(c ^ (b | (~d)))
#define MD5_SHIFT(a, n) (uint32_t)((a << n) | (a >> (32 - n)))

    Str MD5(Str);
    void md5_iterateFunc(uint32_t *, uint32_t &, uint32_t &, uint32_t &, uint32_t &, int size = 16);
    Vec<uint32_t> md5_padding(Str, uint32_t &);
    Str md5_format(uint32_t);

    /*
        AES
    */

// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES encryption in CBC-mode of operation.
// CTR enables encryption in counter-mode.
// ECB enables the basic ECB 16-byte block algorithm. All can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
#define CBC 1
#endif

#ifndef ECB
#define ECB 1
#endif

#ifndef CTR
#define CTR 1
#endif

#define AES128 1
    //#define AES192 1
    //#define AES256 1

#define AES_BLOCKLEN 16 // Block length in bytes - AES is 128b block only

#if defined(AES256) && (AES256 == 1)
#define AES_KEYLEN 32
#define AES_keyExpSize 240
#elif defined(AES192) && (AES192 == 1)
#define AES_KEYLEN 24
#define AES_keyExpSize 208
#else
#define AES_KEYLEN 16 // Key length in bytes
#define AES_keyExpSize 176
#endif

    struct AES_ctx
    {
        uint8_t RoundKey[AES_keyExpSize];
#if (defined(CBC) && (CBC == 1)) || (defined(CTR) && (CTR == 1))
        uint8_t Iv[AES_BLOCKLEN];
#endif
    };

    void AES_init_ctx(struct AES_ctx *ctx, const uint8_t *key);
#if (defined(CBC) && (CBC == 1)) || (defined(CTR) && (CTR == 1))
    void AES_init_ctx_iv(struct AES_ctx *ctx, const uint8_t *key, const uint8_t *iv);
    void AES_ctx_set_iv(struct AES_ctx *ctx, const uint8_t *iv);
#endif

#if defined(ECB) && (ECB == 1)
    // buffer size is exactly AES_BLOCKLEN bytes;
    // you need only AES_init_ctx as IV is not used in ECB
    // NB: ECB is considered insecure for most uses
    void AES_ECB_encrypt(const struct AES_ctx *ctx, uint8_t *buf);
    void AES_ECB_decrypt(const struct AES_ctx *ctx, uint8_t *buf);

#endif // #if defined(ECB) && (ECB == !)

#if defined(CBC) && (CBC == 1)
    // buffer size MUST be mutile of AES_BLOCKLEN;
    // Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
    // NOTES: you need to set IV in ctx via AES_init_ctx_iv() or AES_ctx_set_iv()
    //        no IV should ever be reused with the same key
    void AES_CBC_encrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length);
    void AES_CBC_decrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length);

#endif // #if defined(CBC) && (CBC == 1)

#if defined(CTR) && (CTR == 1)

    // Same function for encrypting as for decrypting.
    // IV is incremented for every block, and used after encryption as XOR-compliment for output
    // Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
    // NOTES: you need to set IV in ctx with AES_init_ctx_iv() or AES_ctx_set_iv()
    //        no IV should ever be reused with the same key
    void AES_CTR_xcrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length);

#endif // #if defined(CTR) && (CTR == 1)

    static constexpr uint8_t AES_KEY[] = "THE_REMMEL_KEY";
    static constexpr uint8_t AES_IV[] = {0x03, 0x0f, 0x01, 0x02, 0x06, 0x0b, 0x04, 0x0c, 0x08, 0x0a, 0x09, 0x05, 0x07, 0x0d, 0x00, 0x0e};

    void SimpleAESEncode(BitArray &);
    void SimpleAESDecode(BitArray &);
}

#endif