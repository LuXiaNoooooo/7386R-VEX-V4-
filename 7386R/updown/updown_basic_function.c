#include "includes.c"

void updown_func(int pwr )
{
    if(pwr_off)
        return;

    motor[mtr_UpDown] = pwr;
    motor[mtr_UpDown3] = pwr;
    updown.pwr = pwr;
}

void updown_keep_lowest()
{
    updown_func(pwr_updown_keep_lowest);
}

task updown_key_up_task();
task updown_key_down_task();

task updown_key_up_task()
{
    unsigned long time0 = time1[T_auto_gbl_timer];
    float kp = 0.6;
    int dir;
    int err_updown;
    //
    while(1)
    {
        if(time1[T_auto_gbl_timer] > (550 + time0))
        {
            break;
        }
        else
        {
            err_updown = enc_updown_up - SensorValue[enc_updown];
            if(err_updown > 0)
                dir = 1;
            if(err_updown < 0)
                dir = -1;
            //
            if(dir == 1)
            {
                if(err_updown < (kp * enc_updown_up))
                    updown_func( pwr_updown_up_max );
                else
                    updown_func( pwr_updown_up_max * kp );
            }
            if(dir == -1)
            {
                if(abs(err_updown) < (enc_updown_up * kp)
            {
                break;
            }
            else
            {
                updown_func( pwr_updown_keep_lowest);
                }
            }
        }
    }
    updown_func( pwr_updown_hold_hgt );
}
task updown_key_down_task()
{
    stopTask(updown_key_up_task);
    unsigned long time0 = time1[T_auto_gbl_timer];
    while(1)
    {
        updown_func(pwr_updown_down_max - 5);
        if(time1[T_auto_gbl_timer] > (800 + time0))
            break;
        if(limit_updown_down_pressed)
            break;
    }
    updown_func(pwr_updown_keep_lowest);
}

typedef struct
{
    int aim;
    int dir;
    int pwr;
    int exit_time;
    TTimers timer_x;
} updown_enc_Struct;

updown_enc_Struct updown_auto;


task updown_enc_task()
{
    int err, output;

    clearTimer(updown_auto.timer_x);
    updown_func( updown_auto.dir * updown_auto.pwr );
    while(1)
    {
        if(time1[updown_auto.timer_x] > updown_auto.exit_time)
            break;
        if(abs(SensorValue[enc_updown] - updown_auto.aim) < 5)
        {
            if(updown_auto.dir == -1)
                updown_func( pwr_updown_keep_lowest );
            else
                updown_func( pwr_updown_hold_hgt );
            break;
        }
        if(SensorValue[limit_updown_dn] == 0 && updown_auto.dir == -1)
            updown_func( pwr_updown_keep_lowest );
        wait1Msec(20);
    }
    //
    clearTimer(updown_auto.timer_x);
    while(time1[updown_auto.timer_x] < 1500)
    {
        err = updown_auto.aim - SensorValue[enc_updown];
        output = 1.2 * err;
        output = abs(output) > 23 ? sgn(output) * 23 : sgn(output) * 17;
        wait1Msec(20);
    }
}

void updown_enc_TASK_FUNC(int aim, int dir, int pwr, int exit_time, TTimers timer_x)
{
    stopTask(updown_key_down_task);
    updown_auto.aim = aim;
    updown_auto.dir = dir;
    updown_auto.pwr = pwr;
    updown_auto.exit_time = exit_time;
    updown_auto.timer_x=timer_x;
    startTask(updown_enc_task);
}
