#include <stdbool.h>
#include "action_call_ubpf.h"

bool external_func(){
	if(getResult()==1)
		return true;
	return false;
}
