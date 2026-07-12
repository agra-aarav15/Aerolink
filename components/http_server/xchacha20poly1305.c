/*
 * XChaCha20-Poly1305 AEAD implementation for AeroLink.
 *
 * Replaces the XChaCha20-Poly1305 that was bundled with esp_wireguard.
 * Used by config import/export for encrypted backups.
 *
 * Algorithm:
 *   1. HChaCha20(key, nonce[0..15]) → subkey
 *   2. ChaCha20-Poly1305(subkey, nonce[16..23] || 0x00000000, plaintext, aad)
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define CHACHA20_BLOCK_SIZE 64

/* ChaCha20 quarter-round */
#define QR(a, b, c, d) \
    do { \
        a += b; d ^= a; d = (d << 16) | (d >> 16); \
        c += d; b ^= c; b = (b << 12) | (b >> 20); \
        a += b; d ^= a; d = (d << 8)  | (d >> 24); \
        c += d; b ^= c; b = (b << 7)  | (b >> 25); \
    } while (0)

/* ChaCha20 block function — produces 64 bytes of keystream */
static void chacha20_block(uint8_t out[64], const uint32_t key[8],
                           uint32_t counter, const uint32_t nonce[3])
{
    uint32_t state[16];
    /* "expand 32-byte k" */
    state[0]  = 0x61707865;
    state[1]  = 0x3320646e;
    state[2]  = 0x79622d32;
    state[3]  = 0x6b206574;
    memcpy(&state[4],  key, 32);
    state[12] = counter;
    memcpy(&state[13], nonce, 12);

    uint32_t working[16];
    memcpy(working, state, 64);

    /* 20 rounds = 10 double-rounds */
    for (int i = 0; i < 10; i++) {
        /* Column rounds */
        QR(working[0], working[4], working[8],  working[12]);
        QR(working[1], working[5], working[9],  working[13]);
        QR(working[2], working[6], working[10], working[14]);
        QR(working[3], working[7], working[11], working[15]);
        /* Diagonal rounds */
        QR(working[0], working[5], working[10], working[15]);
        QR(working[1], working[6], working[11], working[12]);
        QR(working[2], working[7], working[8],  working[13]);
        QR(working[3], working[4], working[9],  working[14]);
    }

    for (int i = 0; i < 16; i++) {
        working[i] += state[i];
    }

    memcpy(out, working, 64);
}

/* XOR src into dst (both len bytes) */
static void chacha20_xor(uint8_t *dst, const uint8_t *src, size_t len,
                         const uint32_t key[8], uint32_t counter,
                         const uint32_t nonce[3])
{
    uint8_t block[CHACHA20_BLOCK_SIZE];
    size_t pos = 0;
    while (pos < len) {
        chacha20_block(block, key, counter++, nonce);
        size_t chunk = len - pos;
        if (chunk > CHACHA20_BLOCK_SIZE) chunk = CHACHA20_BLOCK_SIZE;
        for (size_t i = 0; i < chunk; i++) {
            dst[pos + i] = src[pos + i] ^ block[i];
        }
        pos += chunk;
    }
}

/* HChaCha20: derive a 32-byte subkey from a 32-byte key and 16-byte nonce */
static void hchacha20(uint8_t out[32], const uint32_t key[8], const uint8_t nonce[16])
{
    uint32_t state[16];
    state[0]  = 0x61707865;
    state[1]  = 0x3320646e;
    state[2]  = 0x79622d32;
    state[3]  = 0x6b206574;
    memcpy(&state[4], key, 32);
    /* nonce as 4 uint32s */
    uint32_t n[4];
    memcpy(n, nonce, 16);
    state[12] = n[0];
    state[13] = n[1];
    state[14] = n[2];
    state[15] = n[3];

    uint32_t working[16];
    memcpy(working, state, 64);

    for (int i = 0; i < 10; i++) {
        QR(working[0], working[4], working[8],  working[12]);
        QR(working[1], working[5], working[9],  working[13]);
        QR(working[2], working[6], working[10], working[14]);
        QR(working[3], working[7], working[11], working[15]);
        QR(working[0], working[5], working[10], working[15]);
        QR(working[1], working[6], working[11], working[12]);
        QR(working[2], working[7], working[8],  working[13]);
        QR(working[3], working[4], working[9],  working[14]);
    }

    /* Output: state[0..3] || state[12..15] */
    memcpy(out,      &working[0], 16);
    memcpy(out + 16, &working[12], 16);
}

/* ---- Poly1305 ---- */

typedef struct {
    uint32_t r[4];   /* key part r (clamped) */
    uint32_t h[4];   /* accumulator */
    uint32_t pad[4]; /* key part s */
    uint8_t  block[16];
    size_t   block_len;
} poly1305_state;

static uint64_t mul32(uint32_t a, uint32_t b)
{
    return (uint64_t)a * (uint64_t)b;
}

/* Clamp r per RFC 8439 */
static void poly1305_clamp(uint8_t r[16])
{
    r[3]  &= 15;
    r[7]  &= 15;
    r[11] &= 15;
    r[15] &= 15;
    r[4]  &= 252;
    r[8]  &= 252;
    r[12] &= 252;
}

static void poly1305_init(poly1305_state *st, const uint8_t key[32])
{
    uint8_t r_bytes[16];
    memcpy(r_bytes, key, 16);
    poly1305_clamp(r_bytes);

    /* r in little-endian uint32 */
    st->r[0] = r_bytes[0]  | ((uint32_t)r_bytes[1]  << 8) | ((uint32_t)r_bytes[2]  << 16) | ((uint32_t)r_bytes[3]  << 24);
    st->r[1] = r_bytes[4]  | ((uint32_t)r_bytes[5]  << 8) | ((uint32_t)r_bytes[6]  << 16) | ((uint32_t)r_bytes[7]  << 24);
    st->r[2] = r_bytes[8]  | ((uint32_t)r_bytes[9]  << 8) | ((uint32_t)r_bytes[10] << 16) | ((uint32_t)r_bytes[11] << 24);
    st->r[3] = r_bytes[12] | ((uint32_t)r_bytes[13] << 8) | ((uint32_t)r_bytes[14] << 16) | ((uint32_t)r_bytes[15] << 24);

    memset(st->h, 0, sizeof(st->h));
    memcpy(st->pad, key + 16, 16);
    st->block_len = 0;
}

/* Process a 16-byte block (full or final) */
static void poly1305_process_block(poly1305_state *st, const uint8_t block[16], bool is_final)
{
    uint32_t n[4];
    n[0] = block[0]  | ((uint32_t)block[1]  << 8) | ((uint32_t)block[2]  << 16) | ((uint32_t)block[3]  << 24);
    n[1] = block[4]  | ((uint32_t)block[5]  << 8) | ((uint32_t)block[6]  << 16) | ((uint32_t)block[7]  << 24);
    n[2] = block[8]  | ((uint32_t)block[9]  << 8) | ((uint32_t)block[10] << 16) | ((uint32_t)block[11] << 24);
    n[3] = block[12] | ((uint32_t)block[13] << 8) | ((uint32_t)block[14] << 16) | ((uint32_t)block[15] << 24);

    if (is_final) {
        n[3] |= (1u << 24); /* pad bit */
    } else {
        n[3] |= 0; /* no pad */
    }

    /* h += n */
    uint64_t h0 = (uint64_t)st->h[0] + n[0];
    uint64_t h1 = (uint64_t)st->h[1] + n[1];
    uint64_t h2 = (uint64_t)st->h[2] + n[2];
    uint64_t h3 = (uint64_t)st->h[3] + n[3];

    /* h * r mod (2^130 - 5) */
    uint64_t d0 = mul32(st->r[0], (uint32_t)h0) + mul32(st->r[3], (uint32_t)(h0 >> 32)) +
                  mul32(st->r[2], (uint32_t)(h1 >> 32)) + mul32(st->r[1], (uint32_t)(h2 >> 32));
    uint64_t d1 = mul32(st->r[0], (uint32_t)h1) + mul32(st->r[1], (uint32_t)h0) +
                  mul32(st->r[3], (uint32_t)(h1 >> 32)) + mul32(st->r[2], (uint32_t)(h2 >> 32));
    uint64_t d2 = mul32(st->r[0], (uint32_t)h2) + mul32(st->r[2], (uint32_t)h0) +
                  mul32(st->r[1], (uint32_t)h1) + mul32(st->r[3], (uint32_t)(h2 >> 32));
    uint64_t d3 = mul32(st->r[0], (uint32_t)h3) + mul32(st->r[3], (uint32_t)h0) +
                  mul32(st->r[2], (uint32_t)h1) + mul32(st->r[1], (uint32_t)h2);

    /* Carry chain */
    d1 += d0 >> 32;
    d2 += d1 >> 32;
    d3 += d2 >> 32;

    /* Partial reduction: carry overflow back from d3 >> 32
     * 2^130 - 5 ≡ 5 (mod 2^130), so overflow wraps to +5*overflow */
    uint64_t carry = d3 >> 32;
    d0 = (uint32_t)d0 + mul32((uint32_t)carry, 5);
    d1 += d0 >> 32;
    d0 &= 0xFFFFFFFF;
    d1 += (uint32_t)carry * 5ULL * 0x100000000ULL; /* d1 already handles the rest via carries */
    /* Simplified: redo properly */
    /* Actually, let me redo this more carefully */
    {
        /* Recompute cleanly: h * r with proper carry and reduction */
        uint64_t t[4];
        t[0] = mul32(st->r[0], (uint32_t)h0) + mul32(st->r[3], (uint32_t)(h0 >> 32)) +
               mul32(st->r[2], (uint32_t)(h1 >> 32)) + mul32(st->r[1], (uint32_t)(h2 >> 32));
        t[1] = mul32(st->r[1], (uint32_t)h0) + mul32(st->r[0], (uint32_t)h1) +
               mul32(st->r[3], (uint32_t)(h1 >> 32)) + mul32(st->r[2], (uint32_t)(h2 >> 32));
        t[2] = mul32(st->r[2], (uint32_t)h0) + mul32(st->r[1], (uint32_t)h1) +
               mul32(st->r[0], (uint32_t)h2) + mul32(st->r[3], (uint32_t)(h2 >> 32));
        t[3] = mul32(st->r[3], (uint32_t)h0) + mul32(st->r[2], (uint32_t)h1) +
               mul32(st->r[1], (uint32_t)h2) + mul32(st->r[0], (uint32_t)h3);

        t[1] += t[0] >> 32; t[0] &= 0xFFFFFFFF;
        t[2] += t[1] >> 32; t[1] &= 0xFFFFFFFF;
        t[3] += t[2] >> 32; t[2] &= 0xFFFFFFFF;

        uint64_t top = t[3] >> 32;
        t[3] &= 0xFFFFFFFF;

        /* Reduction: overflow * 2^130 = overflow * (2^130 - 5 + 5) ≡ overflow * 5 */
        t[0] += top * 5;
        t[1] += t[0] >> 32; t[0] &= 0xFFFFFFFF;
        t[2] += t[1] >> 32; t[1] &= 0xFFFFFFFF;
        t[3] += t[2] >> 32; t[2] &= 0xFFFFFFFF;

        st->h[0] = (uint32_t)t[0];
        st->h[1] = (uint32_t)t[1];
        st->h[2] = (uint32_t)t[2];
        st->h[3] = (uint32_t)t[3];
    }
}

static void poly1305_update(poly1305_state *st, const uint8_t *data, size_t len)
{
    size_t pos = 0;
    while (pos < len) {
        size_t rem = 16 - st->block_len;
        size_t chunk = len - pos;
        if (chunk > rem) chunk = rem;
        memcpy(st->block + st->block_len, data + pos, chunk);
        st->block_len += chunk;
        pos += chunk;
        if (st->block_len == 16) {
            poly1305_process_block(st, st->block, false);
            st->block_len = 0;
        }
    }
}

static void poly1305_finish(poly1305_state *st, uint8_t tag[16])
{
    if (st->block_len > 0) {
        uint8_t final_block[16] = {0};
        memcpy(final_block, st->block, st->block_len);
        poly1305_process_block(st, final_block, true);
    }

    /* Add pad */
    uint64_t f = (uint64_t)st->h[0] + st->pad[0];
    tag[0]  = (uint8_t)(f); f >>= 8;
    tag[1]  = (uint8_t)(f); f >>= 8;
    tag[2]  = (uint8_t)(f); f >>= 8;
    tag[3]  = (uint8_t)(f);

    f = (uint64_t)st->h[1] + st->pad[1] + (f >> 32);
    tag[4]  = (uint8_t)(f); f >>= 8;
    tag[5]  = (uint8_t)(f); f >>= 8;
    tag[6]  = (uint8_t)(f); f >>= 8;
    tag[7]  = (uint8_t)(f);

    f = (uint64_t)st->h[2] + st->pad[2] + (f >> 32);
    tag[8]  = (uint8_t)(f); f >>= 8;
    tag[9]  = (uint8_t)(f); f >>= 8;
    tag[10] = (uint8_t)(f); f >>= 8;
    tag[11] = (uint8_t)(f);

    f = (uint64_t)st->h[3] + st->pad[3] + (f >> 32);
    tag[12] = (uint8_t)(f); f >>= 8;
    tag[13] = (uint8_t)(f); f >>= 8;
    tag[14] = (uint8_t)(f); f >>= 8;
    tag[15] = (uint8_t)(f);
}

/* ---- XChaCha20-Poly1305 AEAD ---- */

/*
 * Poly1305 key from XChaCha20: encrypt a zero block with the subkey.
 * key = HChaCha20(main_key, nonce[0..15])
 * poly1305_key = ChaCha20(key, counter=0, nonce[16..23] || 0x00000000)[0..31]
 */
static void derive_poly1305_key(uint8_t poly_key[32], const uint32_t subkey[8],
                                const uint8_t nonce_suffix[8])
{
    uint32_t nonce[3] = {0};
    nonce[0] = nonce_suffix[0] | ((uint32_t)nonce_suffix[1] << 8) |
               ((uint32_t)nonce_suffix[2] << 16) | ((uint32_t)nonce_suffix[3] << 24);
    nonce[1] = nonce_suffix[4] | ((uint32_t)nonce_suffix[5] << 8) |
               ((uint32_t)nonce_suffix[6] << 16) | ((uint32_t)nonce_suffix[7] << 24);
    nonce[2] = 0;

    uint8_t block[64];
    chacha20_block(block, subkey, 0, nonce);
    memcpy(poly_key, block, 32);
}

void xchacha20poly1305_encrypt(uint8_t *dst, const uint8_t *src, size_t src_len,
                               const uint8_t *ad, size_t ad_len,
                               const uint8_t nonce[24], const uint8_t key[32])
{
    /* Step 1: HChaCha20 to get subkey */
    uint8_t subkey_raw[32];
    hchacha20(subkey_raw, (const uint32_t *)key, nonce);
    uint32_t subkey[8];
    memcpy(subkey, subkey_raw, 32);

    /* Step 2: Derive Poly1305 key */
    uint8_t poly_key[32];
    derive_poly1305_key(poly_key, subkey, nonce + 16);

    /* Step 3: ChaCha20 encrypt with subkey, nonce = nonce[16..23] || 0x00000000 */
    uint32_t enc_nonce[3] = {0};
    enc_nonce[0] = nonce[16] | ((uint32_t)nonce[17] << 8) |
                   ((uint32_t)nonce[18] << 16) | ((uint32_t)nonce[19] << 24);
    enc_nonce[1] = nonce[20] | ((uint32_t)nonce[21] << 8) |
                   ((uint32_t)nonce[22] << 16) | ((uint32_t)nonce[23] << 24);
    /* enc_nonce[2] = 0 (counter starts at 0, but we skip the first 64 bytes
     * which are the poly1305 key). Actually for XChaCha20-Poly1305 we start
     * the counter at 0 and skip block 0 (poly1305 key). */

    /* Encrypt: skip first 64 bytes (poly1305 key), so start counter at 1 */
    chacha20_xor(dst, src, src_len, subkey, 1, enc_nonce);

    /* Step 4: Poly1305 tag over AD || ciphertext || padding || lengths */
    poly1305_state poly;
    poly1305_init(&poly, poly_key);

    /* AAD */
    if (ad && ad_len > 0) {
        poly1305_update(&poly, ad, ad_len);
        /* Pad AAD to 16-byte boundary */
        size_t ad_pad = (16 - (ad_len % 16)) % 16;
        if (ad_pad) {
            uint8_t z[16] = {0};
            poly1305_update(&poly, z, ad_pad);
        }
    }

    /* Ciphertext */
    poly1305_update(&poly, dst, src_len);
    /* Pad ciphertext to 16-byte boundary */
    size_t ct_pad = (16 - (src_len % 16)) % 16;
    if (ct_pad) {
        uint8_t z[16] = {0};
        poly1305_update(&poly, z, ct_pad);
    }

    /* Lengths block (little-endian) */
    uint8_t len_block[16] = {0};
    uint64_t ad_len_64 = ad_len;
    uint64_t ct_len_64 = src_len;
    memcpy(len_block,      &ad_len_64, 8);
    memcpy(len_block + 8,  &ct_len_64, 8);
    poly1305_update(&poly, len_block, 16);

    /* Tag appended after ciphertext */
    poly1305_finish(&poly, dst + src_len);
}

bool xchacha20poly1305_decrypt(uint8_t *dst, const uint8_t *src, size_t src_len,
                               const uint8_t *ad, size_t ad_len,
                               const uint8_t nonce[24], const uint8_t key[32])
{
    if (src_len < 16) return false;

    size_t ct_len = src_len - 16; /* tag is last 16 bytes */
    const uint8_t *tag = src + ct_len;

    /* Step 1: HChaCha20 */
    uint8_t subkey_raw[32];
    hchacha20(subkey_raw, (const uint32_t *)key, nonce);
    uint32_t subkey[8];
    memcpy(subkey, subkey_raw, 32);

    /* Step 2: Poly1305 key */
    uint8_t poly_key[32];
    derive_poly1305_key(poly_key, subkey, nonce + 16);

    /* Step 3: Poly1305 over AD || ciphertext */
    poly1305_state poly;
    poly1305_init(&poly, poly_key);

    if (ad && ad_len > 0) {
        poly1305_update(&poly, ad, ad_len);
        size_t ad_pad = (16 - (ad_len % 16)) % 16;
        if (ad_pad) {
            uint8_t z[16] = {0};
            poly1305_update(&poly, z, ad_pad);
        }
    }

    poly1305_update(&poly, src, ct_len);
    size_t ct_pad = (16 - (ct_len % 16)) % 16;
    if (ct_pad) {
        uint8_t z[16] = {0};
        poly1305_update(&poly, z, ct_pad);
    }

    uint8_t len_block[16] = {0};
    uint64_t ad_len_64 = ad_len;
    uint64_t ct_len_64 = ct_len;
    memcpy(len_block,      &ad_len_64, 8);
    memcpy(len_block + 8,  &ct_len_64, 8);
    poly1305_update(&poly, len_block, 16);

    uint8_t computed_tag[16];
    poly1305_finish(&poly, computed_tag);

    /* Constant-time tag comparison */
    uint8_t diff = 0;
    for (int i = 0; i < 16; i++) {
        diff |= tag[i] ^ computed_tag[i];
    }
    if (diff != 0) return false;

    /* Step 4: Decrypt */
    uint32_t enc_nonce[3] = {0};
    enc_nonce[0] = nonce[16] | ((uint32_t)nonce[17] << 8) |
                   ((uint32_t)nonce[18] << 16) | ((uint32_t)nonce[19] << 24);
    enc_nonce[1] = nonce[20] | ((uint32_t)nonce[21] << 8) |
                   ((uint32_t)nonce[22] << 16) | ((uint32_t)nonce[23] << 24);

    chacha20_xor(dst, src, ct_len, subkey, 1, enc_nonce);
    return true;
}
