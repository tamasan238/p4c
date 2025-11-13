#include "ubpf.h"
#include "ubpf_ext.h"

// #include <syslog.h>
// 外部関数ではsyslog呼べない．
// Failed to load code: bad R_BPF_64_64 relocation section って言われる．

uint64_t get_vm_info(){
	// syslog(LOG_INFO, "@@@ get_vm_info() is called. @@@");
	return read_vm_info();
}
