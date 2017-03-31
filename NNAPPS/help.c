#include <dirent.h>
#include "../NNAPI/nnclient.h"

int main(){
	connect_to_nnserver();
	wait_for_connecting();
	char pfad[] = "./bin";
 	DIR *dir;
	struct dirent *file;
	dir = opendir(pfad);
  	while (file = readdir(dir)) {
    		write_msg(file->d_name);
    		write_msg("\n");
  	}
	close_connection();
	return 0;
}
