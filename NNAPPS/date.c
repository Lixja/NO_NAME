#include "../NNAPI/nnclient.h"

int main(){
	connect_to_nnserver();
	wait_for_connecting();
	time_t now;
	time(&now);
	struct tm *now_tm;
	now_tm = localtime(&now);
	write_msg(asctime(now_tm));
	close_connection();
	return 0;
}