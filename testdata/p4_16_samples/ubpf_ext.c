//#include <stdbool.h>
#include "ubpf.h"
#include "ubpf_ext.h"
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
