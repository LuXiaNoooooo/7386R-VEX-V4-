void Robot_Move(int vy, int turn, float vy_max_speed, float turn_max_speed, float abs_max_speed)
{
	float vl;
	float vr;

	if(abs(vy) <= 13)
		vy = 0;
	if(abs(turn) <= 13)
		turn = 0;

	vy = vy * vy_max_speed / 127.0;
	turn = turn * turn_max_speed / 127.0;

	vl = vy + turn;
	vr = vy - turn;

	if(abs(vl) >= abs_max_speed)
		vl = sgn(vl) * abs_max_speed;

	if(abs(vr) >= abs_max_speed)
		vr = sgn(vr) * abs_max_speed;

	motor[mtr_LF] = vl;
	motor[mtr_RF] = vr;

}
