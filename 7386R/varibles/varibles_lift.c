#define pwr_lift_up_max           127
#define pwr_lift_down_max         -127
#define pwr_lift_keep_lowest      -18
#define pwr_lift_keep_highest      20

//////////////////////////////////////////////////


#define limit_lift_dn_pressed    (SensorValue[limit_lift_dn]==0)
#define limit_lift_up_pressed   (SensorValue[limit_lift_up]==0)

typedef enum
{
	lift_dir_dn  = -1,
	lift_dir_up = 1,
	lift_dir_none  = 0,
} lift_dir_Types;


typedef struct
{
	lift_dir_Types     dir;
	float              pwr;

	int                one_key_flag;
} lift_Struct;

Separator __________________________lift = _;
lift_Struct lift;

void lift_Struct_init()
{

}
