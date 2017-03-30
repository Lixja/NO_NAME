#include "../NNAPI/nnclient.h"

int main(){
	connect_to_nnserver();
	wait_for_connecting();
	return 0;
}