#define LCD_Btn_Left    0b001 //1
#define LCD_Btn_Center  0b010 //2
#define LCD_Btn_Right   0b100 //4
#define LCD_Btn_Pressed( btn )  (  (nLCDButtons & (btn) )!=0  )

#define LCD_wait_for_press(btn)      { while( ! LCD_Btn_Pressed( btn ) ) {wait1Msec(5);} }
#define LCD_wait_for_release(btn)    { while(   LCD_Btn_Pressed( btn ) ) {wait1Msec(5);} }

#define LCD_while_not_pressing(btn)   while(! LCD_Btn_Pressed( btn ) )  // no ;   here
#define LCD_while_pressing(btn)       while(  LCD_Btn_Pressed( btn ) )  // no ;   here

void LCD_Clear()  {clearLCDLine(0);clearLCDLine(1);}

