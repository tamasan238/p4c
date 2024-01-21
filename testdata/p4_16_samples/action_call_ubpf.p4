#include <core.p4>
#include <ubpf_model.p4>
#include "standard_headers.p4"

#define IP_PROTO_ICMP 1
#define ICMP_ECHO_REQUEST_TYPE 8

struct Headers_t {
    ethernet_h ethernet;
    ipv4_h ipv4;
    icmp_h icmp;
}

struct metadata {
}

parser prs(packet_in p, out Headers_t headers, inout metadata meta, inout standard_metadata std_meta) {
    state start {
        p.extract(headers.ethernet);
        transition parse_ipv4;
    }

    state parse_ipv4 {
        p.extract(headers.ipv4);
        transition select(headers.ipv4.protocol) {
            IP_PROTO_ICMP: parse_icmp;
            default: accept;
        }
    }

    state parse_icmp {
        p.extract(headers.icmp);
        transition accept;
    }
}

extern bool external_func();

control pipe(inout Headers_t headers, inout metadata meta, inout standard_metadata std_meta) {
    apply {
        if (headers.icmp.type_ == ICMP_ECHO_REQUEST_TYPE) {
	    if (external_func()) {
	        mark_to_drop();
	    }
        }
    }
}

control dprs(packet_out packet, in Headers_t headers) {
    apply { }
}

ubpf(prs(), pipe(), dprs()) main;
