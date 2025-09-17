#include <core.p4>
#include <ubpf_model.p4>
#include "standard_headers.p4"

#define IP_PROTO_TCP 6

struct Headers_t {
    ethernet_h ethernet;
    ipv4_h ipv4;
    tcp_h tcp;
}

struct metadata {
}

parser prs(packet_in p, out Headers_t headers, inout metadata meta, inout standard_metadata std_meta) {
    /*
    state start {
        transition accept;
    }
    */
    state start {
        p.extract(headers.ethernet);
        transition parse_ipv4;
    }

    state parse_ipv4 {
        p.extract(headers.ipv4);
        transition select(headers.ipv4.protocol) {
            IP_PROTO_TCP: parse_tcp;
            default: accept;
        }
    }

    state parse_tcp {
        p.extract(headers.tcp);
        transition accept;
    }
}

extern bit<64> get_vm_info();

control pipe(inout Headers_t headers, inout metadata meta, inout standard_metadata std_meta) {
    bit<64> vm_info; // (unsigned long threshld, used_bytes)

    apply {
        if (headers.ipv4.protocol == IP_PROTO_TCP){
            if ((headers.tcp.flags & 0x10) == 0) { // ack is false
                if ((headers.tcp.flags & 0x02) != 0) { // syn is true
                    vm_info = get_vm_info();
                    if (vm_info[63:32] < vm_info[31:0]) { // threshold < used_bytes
                        mark_to_drop();
                    }
                }
            }
        }
    }
}

control dprs(packet_out packet, in Headers_t headers) {
    apply { }
}

ubpf(prs(), pipe(), dprs()) main;
