void auto_manager()
{
	pwr_off = 0;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//     ###    ##     ## ########  #######  
//    ## ##   ##     ##    ##    ##     ## 
//   ##   ##  ##     ##    ##    ##     ## 
//  ##     ## ##     ##    ##    ##     ## 
//  ######### ##     ##    ##    ##     ## 
//  ##     ## ##     ##    ##    ##     ## 
//  ##     ##  #######     ##     #######  

	auto_set(auto.ROLE, auto.Route); 

	switch(auto.Route)
	{
		case 1:
		auto_route_1();
		break;
		case 2:
		auto_route_2();
		break;
		case 3:
		auto_route_3();
		break;
		case 4:
		auto_route_4();
		break;
		default:
		auto_route_1();
		break;
	}
	stop_all_motors();
}


task autonomous()
{
	srand( nSysTime );
	writeDebugStream("******autonomous******\n");

	pwr_off = 0;

	StopTask(usercontrol);


	auto_manager();

	while(1)
		wait1Msec(500);
	writeDebugStream("******end of autonomous******\n");
}