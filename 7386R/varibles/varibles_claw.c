
// claw_varibles
#define agl_claw_open      100
#define agl_claw_closed     0

#define pwr_claw_open      (125*claw_dir_open)
#define pwr_claw_close     (122*claw_dir_close)
#define pwr_claw_hold_open  (15*claw_dir_open)
#define pwr_claw_hold_close (22*claw_dir_close)
#define pwr_claw_hold_close_powerful  (15*claw_dir_close)


typedef enum
{
	claw_dir_open  = -1,
	claw_dir_close = 1,
	claw_dir_none  = 0,
} claw_dir_Types;

typedef enum
{
	claw_sta_hold_close_powerful,
	claw_sta_opening,
	claw_sta_closing,
	claw_sta_pwr_off,
} claw_status_Types;

typedef struct
{
	int                pwr;
	claw_dir_Types     dir;
	int                reset;
	claw_status_Types  status;
} claw_Struct;

Separator __________________________claw = _;
claw_Struct claw;

void claw_Struct_init()
{

}
