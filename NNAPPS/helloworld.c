#include "../NNAPI/nnclient.h"

int main(){
	connect_to_nnserver();
	wait_for_connecting();
	write_msg("Hello World.\n");
	close_connection();
	return 0;
}