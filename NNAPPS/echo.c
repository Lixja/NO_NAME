#include "../NNAPI/nnclient.h"

int main(int argc, char* argv[]){
	connect_to_nnserver();
	wait_for_connecting();
	if(argc > 1){
		write_msg(argv[1]);
	}else{
		write_msg("echo ...");
	}
	close_connection();
	return 0;
}