typedef  enum _______________________ {_ = '_'} _______________________;
#define Separator     _______________________

#include "key.h"

//auto
#define T_auto_timer  T3
#define T_auto_gbl_timer T1
#define T_lift_handle T4

#define T_claw_handle T1
#define T_swing_handle T2
//key press
#define wait_for_press(key)      { while(!key) {wait1Msec(5);} }
#define wait_for_release(key)    { while( key) { RT_MOVE(); } }

#define while_not_pressing(key)   while(! key )  // no ;   here
#define while_pressing(key)       while(  key )  // no ;   here

int  pwr_off = 1;

//simplified move
void  set_move_pwr_7386x(int L, int R)
{
	motor[mtr_LF] = L;
	motor[mtr_RF] = R;
}
#define move(forward_7386x,turn_7386R);   set_move_pwr_7386x((forward_7386x)+(turn_7386R), (forward_7386x)-(turn_7386R) )

//
void pre_auton();
task autonomous();
task usercontrol();

//basic func
void claw_func(int pwr );
void updown_func(int pwr );

//auto
void auto_route_1();
void auto_route_2();
void auto_route_3();
void auto_route_4();

//robot_move
void Robot_Move(int vy, int turn, float vy_max_speed, float turn_max_speed, float abs_max_speed);
#define RT_MOVE()     Robot_Move(vexRT[Ch3],vexRT[Ch4],pwr_RT_max_vy,pwr_RT_max_turn,pwr_RT_abs_max)
#define Move_Stop()   Robot_Move(0,0,0,0,0)

//handle
void special_key_handle();
void claw_handle();

void updown_handle_button(int key_updown_up_x, int key_updown_dn_x);
void updown_handle_joystick(int ch_src);

void swing_handle_button(int key_swing_up_x, int key_swing_dn_x);
void swing_handle_joystick( int ch_src );

void lift_one_key_lowest_with_swing_down();
void lift_handle();
void manual_handle();

typedef enum
{
	handle_mode_updown_joystick,
	handle_mode_updown_button,
} handle_mode_Types;
handle_mode_Types handle_mode = handle_mode_updown_joystick;


//auto info

typedef enum
{
	Role_Left  = 1,
	Role_Right = -1,
} role_x;

typedef struct
{
	role_x ROLE ;
	int Route;
} auto_Struct;
auto_Struct auto;

void auto_Struct_init()
{
	auto.ROLE = Role_Left;
	auto.Route = 1;
}

void auto_set( role_x role, int route)
{
	auto.ROLE = role;
	auto.Route = route;
}


#define STOPCAR 1

#define stop_all_motors()  \
{\
	Move_Stop();\
	updown_func(0);\
	claw_func(0);\
	swing_func( 0 );\
	lift_func( 0 );\
}


#include "RT_move.c"
#include "lcd\LCD.c"


#include "varibles\______varibles______.h"

#include "swing\______swing______.h"
#include "updown\______updown______.h"
#include "claw\______claw______.h"
#include "lift\______lift______.h"

#include "auto\______auto______.h"

#include "pre_auto\______pre_auto______.h"

#include "______.______h"

#include "special_key.c"

#include "__capture\______capture______.h"

#include "LIB_ManualHandle.c"









////////////////////////////////////////////////updown
