//#include <stdbool.h>
#include "action_call_ubpf.h"
#include "action_call_ubpf_ext.h"
/*
bool external_func(){
	if(getResult()==1)
		return true;
	return false;
}
*/

int external_func(){
	return getResult();
}