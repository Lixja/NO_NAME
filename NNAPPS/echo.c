#include "../NNAPI/nnclient.h"

int main(int argc, char* argv[]){
	connect_to_nnserver();
	wait_for_connecting();
	if(argc > 1){
		for(int i=1; i<argc; i++){
			write_msg(argv[i]);
			if((i+1) < argc){
			write_msg(" ");
			}
		}
	}else{
		write_msg("echo ...");
	}
	close_connection();
	return 0;
}
