#include "../NNAPI/nnclient.h"

int main(){
	connect_to_nnserver();
	wait_for_connecting();
	write_msg("NO_NAME V0.1\n");
	close_connection();
	return 0;
}