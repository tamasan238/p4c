/* Automatically generated by p4c-ubpf from /home/iwai/p4c/testdata/p4_16_samples/ubpf.p4 on Mon Feb  5 09:56:55 2024
 */
#include "ubpf.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "ubpf_common.h"

#define BPF_MASK(t, w) ((((t)(1)) << (w)) - (t)1)
#define BYTES(w) ((w) / 8)

void* memcpy(void* dest, const void* src, size_t num);

static void *(*ubpf_map_lookup)(const void *, const void *) = (void *)1;
static int (*ubpf_map_update)(void *, const void *, void *) = (void *)2;
static int (*ubpf_map_delete)(void *, const void *) = (void *)3;
static int (*ubpf_map_add)(void *, const void *) = (void *)4;
static uint64_t (*ubpf_time_get_ns)() = (void *)5;
static uint32_t (*ubpf_hash)(const void *, uint64_t) = (void *)6;
static void (*ubpf_printf)(const char *fmt, ...) = (void *)7;
static void *(*ubpf_packet_data)(const void *) = (void *)9;
static void *(*ubpf_adjust_head)(const void *, uint64_t) = (void *)8;
static uint32_t (*ubpf_truncate_packet)(const void *, uint64_t) = (void *)11;
static int (*getResult)()=(void *)20;
static void (*myPrintf)(const int) = (void *)21;


#define write_partial(a, w, s, v) do { *((uint8_t*)a) = ((*((uint8_t*)a)) & ~(BPF_MASK(uint8_t, w) << s)) | (v << s) ; } while (0)
#define write_byte(base, offset, v) do { *(uint8_t*)((base) + (offset)) = (v); } while (0)

static uint32_t
bpf_htonl(uint32_t val) {
    return htonl(val);
}
static uint16_t
bpf_htons(uint16_t val) {
    return htons(val);
}
static uint64_t
bpf_htonll(uint64_t val) {
    return htonll(val);
}

inline uint16_t csum16_add(uint16_t csum, uint16_t addend) {
    uint16_t res = csum;
    res += addend;
    return (res + (res < addend));
}
inline uint16_t csum16_sub(uint16_t csum, uint16_t addend) {
    return csum16_add(csum, ~addend);
}
inline uint16_t csum_replace2(uint16_t csum, uint16_t old, uint16_t new) {
    return (~csum16_add(csum16_sub(~csum, old), new));
}

inline uint16_t csum_fold(uint32_t csum) {
    uint32_t r = csum << 16 | csum >> 16;
    csum = ~csum;
    csum -= r;
    return (uint16_t)(csum >> 16);
}
inline uint32_t csum_unfold(uint16_t csum) {
    return (uint32_t)csum;
}
inline uint32_t csum32_add(uint32_t csum, uint32_t addend) {
    uint32_t res = csum;
    res += addend;
    return (res + (res < addend));
}
inline uint32_t csum32_sub(uint32_t csum, uint32_t addend) {
    return csum32_add(csum, ~addend);
}
inline uint16_t csum_replace4(uint16_t csum, uint32_t from, uint32_t to) {
    uint32_t tmp = csum32_sub(~csum_unfold(csum), from);
    return csum_fold(csum32_add(tmp, to));
}
uint64_t entry(void *ctx, struct standard_metadata *std_meta){
    void *pkt = ubpf_packet_data(ctx);
    uint32_t pkt_len = std_meta->packet_length;
    struct Headers_t headers = {
        .ethernet = {
            .ebpf_valid = 0
        },
        .ipv4 = {
            .ebpf_valid = 0
        },
        .icmp = {
            .ebpf_valid = 0
        },
    };
    struct metadata meta = {
    };
    int packetOffsetInBits = 0;
    uint8_t pass = 1;
    uint8_t hit = 0;
    unsigned char ebpf_byte;
    uint32_t ebpf_zero = 0;
    int packetTruncatedSize = -1;

    goto start;
    start: {
        /* extract(headers.ethernet)*/
        if (pkt_len < BYTES(packetOffsetInBits + 112)) {
            goto reject;
        }
        
        headers.ethernet.dstAddr = (uint64_t)((load_dword(pkt, BYTES(packetOffsetInBits)) >> 16) & BPF_MASK(uint64_t, 48));
        packetOffsetInBits += 48;

        headers.ethernet.srcAddr = (uint64_t)((load_dword(pkt, BYTES(packetOffsetInBits)) >> 16) & BPF_MASK(uint64_t, 48));
        packetOffsetInBits += 48;

        headers.ethernet.etherType = (uint16_t)((load_half(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 16;

        headers.ethernet.ebpf_valid = 1;
        /* extract(headers.ipv4)*/
        if (pkt_len < BYTES(packetOffsetInBits + 160)) {
            goto reject;
        }
        
        headers.ipv4.version = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits)) >> 4) & BPF_MASK(uint8_t, 4));
        packetOffsetInBits += 4;

        headers.ipv4.ihl = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits))) & BPF_MASK(uint8_t, 4));
        packetOffsetInBits += 4;

        headers.ipv4.diffserv = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 8;

        headers.ipv4.totalLen = (uint16_t)((load_half(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 16;

        headers.ipv4.identification = (uint16_t)((load_half(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 16;

        headers.ipv4.flags = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits)) >> 5) & BPF_MASK(uint8_t, 3));
        packetOffsetInBits += 3;

        headers.ipv4.fragOffset = (uint16_t)((load_half(pkt, BYTES(packetOffsetInBits))) & BPF_MASK(uint16_t, 13));
        packetOffsetInBits += 13;

        headers.ipv4.ttl = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 8;

        headers.ipv4.protocol = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 8;

        headers.ipv4.hdrChecksum = (uint16_t)((load_half(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 16;

        headers.ipv4.srcAddr = (uint32_t)((load_word(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 32;

        headers.ipv4.dstAddr = (uint32_t)((load_word(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 32;

        headers.ipv4.ebpf_valid = 1;
        uint8_t select_0;
        select_0 = headers.ipv4.protocol;
        if (select_0 == 1)goto parse_icmp;
        if ((select_0 & 0x0) == (0x0 & 0x0))goto accept;
        else goto reject;
    }
    parse_icmp: {
        /* extract(headers.icmp)*/
        if (pkt_len < BYTES(packetOffsetInBits + 32)) {
            goto reject;
        }
        
        headers.icmp.type_ = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 8;

        headers.icmp.code = (uint8_t)((load_byte(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 8;

        headers.icmp.hdrChecksum = (uint16_t)((load_half(pkt, BYTES(packetOffsetInBits))));
        packetOffsetInBits += 16;

        headers.icmp.ebpf_valid = 1;
        goto accept;
    }

    reject: { return 1; }

    accept:
    {
        uint8_t tmp = 0;
        {

            if (headers.ipv4.protocol == 1) {
                if (headers.icmp.type_ == 8) {

                    tmp = external_func();
;
                    if (tmp == 0) {
                        pass = false;
                    }

                }            }

        }    }
    deparser:
    {
        int outHeaderLength = 0;
        {
        }
        int outHeaderOffset = BYTES(outHeaderLength) - BYTES(packetOffsetInBits);
        pkt = ubpf_adjust_head(ctx, outHeaderOffset);
        pkt_len += outHeaderOffset;
        packetOffsetInBits = 0;
        if (packetTruncatedSize > 0) {
            pkt_len -= ubpf_truncate_packet(ctx, packetTruncatedSize);
        }
        
    }
    if (pass)
        return 1;
    else
        return 0;
}
