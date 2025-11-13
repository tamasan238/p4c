#include "ubpf.h"
#include "ubpf_ext.h"

#include <syslog.h>

uint64_t get_vm_info(){
	syslog(LOG_INFO, "@@@ get_vm_info() is called. @@@");
	return read_vm_info();
}
