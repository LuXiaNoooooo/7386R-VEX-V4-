task main()
{

	PlayTone(110, 150);
	playTone(800,100);
	pre_auton();
	StartTask(usercontrol);
	while(1)
	{
		//writeDebugStream("%d\n",SensorValue[enc_updown]);
		wait1Msec(1500);
	}
}
