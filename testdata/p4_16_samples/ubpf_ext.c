#include "ubpf.h"
#include "ubpf_ext.h"

uint64_t get_vm_info(){
	return read_vm_info();
}
