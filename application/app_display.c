#include ".\app_configure.h"

#define true						1
#define false						0


void app_dis(uint16_t adress, uint16_t dat)
{
	uint8_t writebuf[] = {0, 0};
	writebuf[0] = (uint8_t)(dat>>8);
	writebuf[1] = (uint8_t)(dat);
	WriteDGUS(adress,writebuf,2);
}

void app_dis_1(uint16_t adress, uint16_t offset_dat, uint16_t dat)
{
	uint8_t writebuf[] = {0, 0};
	uint16_t datbuf = dat + offset_dat;
	writebuf[0] = (uint8_t)(datbuf>>8);
	writebuf[1] = (uint8_t)(datbuf);
	WriteDGUS(adress, writebuf, 2);	
}


void app_dis_error(uint16_t errordata)
{
	uint8_t i;
	uint16_t basic_data = 0x0001;
	uint16_t adress = 0;
	uint16_t pic_data = 0;
	for(i = 0; i < 16; i++)
	{
		switch(errordata & (basic_data << i))
		{
			/*case 0x0001: break;
			case 0x0002: break;
			case 0x0004: break;
			case 0x0008: break;
			case 0x0010: break;
			case 0x0020: break;
			case 0x0040: break;
			case 0x0080: break;
			case 0x0100: break;*/
			case 0x0200: 
						adress = REG_ERROR_BIT9; 
						pic_data = 1;//图标序号
						break;
			case 0x0400: 
						adress = REG_ERROR_BIT10; 
						pic_data = 2;//图标序号
						break;
			case 0x0800: 
						adress = REG_ERROR_BIT11; 
						pic_data = 3;//图标序号
						break;
			case 0x1000: 
						adress = REG_ERROR_BIT12; 
						pic_data = 4;//图标序号
						break;
			case 0x2000: 
						adress = REG_ERROR_BIT13; 
						pic_data = 5;//图标序号
						break;
			case 0x4000: 
						adress = REG_ERROR_BIT14; 
						pic_data = 6;//图标序号
						break;
			case 0x8000: 
						adress = REG_ERROR_BIT15; 
						pic_data= 6;//图标序号
						break;
			default: break;
		}
		if(adress != 0)
		{
			app_dis(adress,pic_data);
			adress = 0;
			pic_data = 0;
		}
	}
}

void app_dis_powOffMode(void)
{

}

void app_dis_runMode(void)
{
    SysPara_t *ptSysPara;  	
	uint8_t readbuf[2] ={0,0};
	uint8_t greenwind = 0;
	int16_t modestate = 0;
	uint16_t dis_adress[] ={0};
	uint16_t dis_offset_dat[] ={0};
	uint16_t i = 0;

	//disdata_t dismes[] = {};

	
	
	ptSysPara =  controler_getSysParaPt();

	ReadDGUS(RTC,(u8 *)&rtc_time.year,8);

	//get_dis_bit()

	//new
	//显示分图标显示和数字显示，图标显示是需要地址偏移，数字地址偏移为0
		//给一个起始地址自动自加，但是若遇到间隔的地址该如何处理，某些需要给页码做一些预留
		//
	
	//每次更新数据是默认刷新一次，具体显示不显示还是需要根据当前状态来判断，直接从sys变量中摘选需要显示的赋值，定时数据除外
		//当前显示状态需赋予显示的初始地址，更新当前页的所有数据，数据需要一种类似分页的机制
		//数字都实时更新.1s的频率



	
	//需要显示之前将所有数据读取到一个结构体里面显示，这样自加就不会乱。控制好大小 指针就不会溢出
	//for(; i < 256; i++)
	//{
		//if(*(pdisbit + i) == 1)//最后参数由指针指向结构体 地址++运算来得出显示数据的有效性
		//{
		//	app_dis_1(dis_adress[i], dis_offset_dat[i]);//数字是直接显示的，图标需要显示偏移地址，没准需要分开两个函数
		//}		
	//}
	
	//end
	
	//待机界面
	//app_dis(REG_DYNAMIC_CIRCULAR_ADRESS,ptSysPara->dynamic_circular);
//	app_dis(REG_SCREEN_SAVER_CO2_NUMBER,ptSysPara->measure_co2);//450-2000
//	app_dis(REG_SCREEN_SAVER_PM25_NUMBER,ptSysPara->measure_pm25);//0~999
//	app_dis(REG_SCREEN_SAVER_HUMIDITY,ptSysPara->measure_humidity);//0~100
	app_dis(REG_SCREEN_SAVER_TEMP,(ptSysPara->measure_temp/10));//-99~99
	
	//主控界面
	
	//app_dis(REG_MASTER_CONTROL_DIS_TIMING,ptSysPara->timer);
	//app_dis(REG_MASTER_CONTROL_DIS_SETTING,ptSysPara->setting);
	//app_dis(REG_MASTER_CONTROL_DIS_POWEROFF,ptSysPara->poweroff);
	//app_dis(REG_MASRER_CONTROL_DIS_HUMUDUTY_KEYT,ptSysPara->humidity_dis_key);
	//app_dis(REG_MASRER_CONTROL_DIS_MODE_KEYT,ptSysPara->mode_dis_key);

	app_dis(REG_MASTER_CONTROL_DIS_MODE,ptSysPara->mode);//模式
	app_dis(REG_MASTER_CONTROL_DIS_WINDSTATUS,ptSysPara->airmode + 8);//通风状态 
	app_dis(REG_MASTER_CONTROL_DIS_WINDSPEDD,ptSysPara->windspeed + 4);//设定风速
	app_dis(REG_MASTER_CONTROL_DIS_TEMPSET,ptSysPara->temp_set/10);//设定温度
	app_dis(REG_MASTER_CONTROL_DIS_HUMIDITYSET,ptSysPara->humidity_set);//设定湿度
	
	//输出及故障显示

	if((ptSysPara->outputstate & 0x0001) == 0x0001)
	{
		app_dis(REG_ELECTRIC_HEATING_ADRESS,24);//23 正常  24异常
	}
	else
	{
		app_dis(REG_ELECTRIC_HEATING_ADRESS,23);
	}

	if((ptSysPara->outputstate & 0x0002) == 0x0002)
	{
		app_dis(REG_FRE_ADRESS,26);
	}
	else
	{
		app_dis(REG_FRE_ADRESS,25);
	}
	if((ptSysPara->outputstate & 0x0004) == 0x0004)
	{
		app_dis(REG_BYPASS_ADRESS,28);
	}
	else
	{
		app_dis(REG_BYPASS_ADRESS,27);
	}
	if((ptSysPara->outputstate & 0x0008) == 0x0008)
	{
		app_dis(REG_REC_ADRESS,30);
	}
	else
	{
		app_dis(REG_REC_ADRESS,29);
	}
	if((ptSysPara->errorstate & 0x0001) == 0x0001)
	{
		app_dis(REG_BACK_FANSPEED_ERROR_ADRESS,32);//异常
	}
	else
	{
		app_dis(REG_BACK_FANSPEED_ERROR_ADRESS,31);
	}
	if((ptSysPara->errorstate & 0x0002) == 0x0002)
	{
		app_dis(REG_WENSHIDU_ERROE_ADRESS,34);//异常
	}
	else
	{
		app_dis(REG_WENSHIDU_ERROE_ADRESS,33);
	}

	//固定显示
	app_dis(REG_FREQ_CHAR_DIS_ADRESS,35);
	app_dis(REG_FRE_SPEED_DIS_ADRESS,37);
	app_dis(REG_REC_SPEED_DIS_ADRESS,38);

	//具体转速
	app_dis(REG_FREQ_CHAR,ptSysPara->freq);
	app_dis(REG_FRE_SPEED_NUMBER_ADRESS,ptSysPara->fre_speed);
	app_dis(REG_REC_SPEED_NUMBER_ADRESS,ptSysPara->rec_speed);

	

	app_dis(REG_FANSET_MOTOR_TYPE_ADRESS,ptSysPara->fanset_param.motor_type+142);

	app_dis(REG_FANSET_LOWSPEED_ADRESS,ptSysPara->fanset_param.low_param);
	app_dis(REG_FANSET_MIDPEED_ADRESS,ptSysPara->fanset_param.mid_param);
	app_dis(REG_FANSET_HIGHSPEED_ADRESS,ptSysPara->fanset_param.high_param);

	
	/*app_dis(REG_RTC_YEAR_ADRESS,(uint16_t)(rtc_time.year+2000));
	app_dis(REG_RTC_MONTH_TEN_ADRESS,(uint16_t)(rtc_time.month/10));
	app_dis(REG_RTC_MONTH_ADRESS,(uint16_t)(rtc_time.month%10));
	app_dis(REG_RTC_DAY_TEN_ADRESS,(uint16_t)(rtc_time.day)/10);
	app_dis(REG_RTC_DAY_ADRESS,(uint16_t)(rtc_time.day)%10);
	app_dis(REG_RTC_HOUR_TEN_ADRESS,(uint16_t)(rtc_time.hour/10));
	app_dis(REG_RTC_HOUR_ADRESS,(uint16_t)(rtc_time.hour%10));
	app_dis(REG_RTC_MIN_TEN_ADRESS,(uint16_t)(rtc_time.min/10));
	app_dis(REG_RTC_MIN_ADRESS,(uint16_t)(rtc_time.min%10));
	app_dis(REG_RTC_CHAR1_ADRESS,134);
	app_dis(REG_RTC_CHAR2_ADRESS,134);
	app_dis(REG_RTC_CHAR3_ADRESS,135);*/
}
void app_display_week_select(uint16_t offset)
{
	app_dis(REG_TIME_CONTROL_WEEK_1, 0);
	app_dis(REG_TIME_CONTROL_WEEK_2, 0);
	app_dis(REG_TIME_CONTROL_WEEK_3, 0);
	app_dis(REG_TIME_CONTROL_WEEK_4, 0);
	app_dis(REG_TIME_CONTROL_WEEK_5, 0);
	app_dis(REG_TIME_CONTROL_WEEK_6, 0);
	app_dis(REG_TIME_CONTROL_WEEK_7, 0);
	app_dis((REG_TIME_CONTROL_WEEK_BASE + offset), 1);
}

void app_display_week_program_type(void)
{
    SysPara_t *ptSysPara; 
	uint8_t i,j;
	uint8_t addcount = 0;
	uint16_t week_baseadress;
	uint16_t dis_adress = 0;
	uint16_t picture_adress = 0;
	ptSysPara =  controler_getSysParaPt();		
	for(i = 0; i < 7; i++)
	{
		switch(i)
		{
			case 0: week_baseadress = REG_TIME_CONTROL_WEEK_1_NUMBER1; break;
			case 1: week_baseadress = REG_TIME_CONTROL_WEEK_2_NUMBER1; break;
			case 2: week_baseadress = REG_TIME_CONTROL_WEEK_3_NUMBER1; break;
			case 3: week_baseadress = REG_TIME_CONTROL_WEEK_4_NUMBER1; break;
			case 4: week_baseadress = REG_TIME_CONTROL_WEEK_5_NUMBER1; break;
			case 5: week_baseadress = REG_TIME_CONTROL_WEEK_6_NUMBER1; break;
			case 6: week_baseadress = REG_TIME_CONTROL_WEEK_7_NUMBER1; break;
			default :break;
		}	
		dis_adress = week_baseadress;
		addcount = 0;
		if((ptSysPara->week_type_line[0] & 0x7f) == 0x7f)//只有第一行能显示“一周”
		{
			//若显示一周的数据
			app_dis(REG_TIME_CONTROL_WEEK_1_NUMBER7, 30);
			//则清除详情信息
			for(j = 0; j < 7; j++)
			{
				app_dis(week_baseadress, 0);					
				week_baseadress += 2;
			}
		}
		else if((ptSysPara->week_type_line[i] & 0x80) == 0x00)
		{
			for(j = 0; j < 7; j++)
			{
				app_dis(dis_adress, picture_adress);
				dis_adress += 2;		
				picture_adress = 0;
			}
		}
		else
		{
			for(j = 0; j < 7; j++)
			{
				if(ptSysPara->week_type_line[i] & (0x01 << j))
				{
					picture_adress = 23 + j;
				}
				else
				{
					picture_adress = 0;
				}
				
				if(picture_adress != 0)
				{
					app_dis(dis_adress, picture_adress);
					addcount++;
					dis_adress += 2;
					picture_adress = 0;
				}
				else if(j == 6 && addcount <= 6)
				{
					for(; addcount <= 6; addcount++)//余下地址若没有数据，则需要清除数据
					{
						app_dis(dis_adress, picture_adress);						
						dis_adress += 2;
					}
				}
				else
				{

				}

			}
		}
	}
	
}

void app_display_week_strip(uint16_t adress)
{
	app_dis(REG_DIS_WEEK_ADRESS, adress + 2);
}

void app_dis_timing_week(void)//页34 定时 显示星期数据
{	
    SysPara_t *ptSysPara;  	
	ptSysPara =  controler_getSysParaPt();		

	app_display_week_select((uint16_t)(ptSysPara->week_cursor * 2));//星期-高亮调切换显示
	app_display_week_program_type();//定时界面 星期种类
	app_display_week_strip((uint16_t)ptSysPara->week_cursor);
	
	//时段选中控制条
	app_dis(REG_TIME_CONTROL_TIME_1, 0);
	app_dis(REG_TIME_CONTROL_TIME_2, 0);
	app_dis(REG_TIME_CONTROL_TIME_3, 0);
	app_dis(REG_TIME_CONTROL_TIME_4, 0);
	app_dis(REG_TIME_CONTROL_TIME_5, 0);
	app_dis(REG_TIME_CONTROL_TIME_6, 0);
	app_dis(REG_TIME_CONTROL_TIME_7, 0);

}

void app_dis_week_choose(void)
{
    SysPara_t *ptSysPara;  	
	uint8_t i;
	uint8_t week_message = 0;
	ptSysPara =  controler_getSysParaPt();

	ptSysPara->dis_week.mon = 0;
	ptSysPara->dis_week.tues = 0;
	ptSysPara->dis_week.wed = 0;
	ptSysPara->dis_week.thur = 0;
	ptSysPara->dis_week.fri = 0;
	ptSysPara->dis_week.sat = 0;
	ptSysPara->dis_week.sun = 0;
	
	for(i = 0; i < 7; i++)
	{
		if((ptSysPara->week_type_line[i] & 0x80) == 0x80)
		{
			//读取已被选中的信息
			week_message |= (ptSysPara->week_type_line[i]&0x7f);//
		}
	}

	/*if(ptSysPara->week_function_type == 1)//add
	{
		//显示不可选中 x
		//显示没选中 灰
		//显示正在选中的 √
	}
	else if(ptSysPara->week_function_type == 2)//edit
	{
		//显示不可选中的图标
		
	}
	else
	{

	}*/
	for(i = 0; i < 8; i++)//编辑界面显示当前
	{
		switch(ptSysPara->key_week_message & (0x01 << i))
		{
			case 0x01: 
				ptSysPara->dis_week.mon = MONDAY_VALID;
				break;
			case 0x02: 
				ptSysPara->dis_week.tues = TUESDAY_VALID;
				break;
			case 0x04: 
				ptSysPara->dis_week.wed = WEDNESDAY_VALID;
				break;
			case 0x08: 
				ptSysPara->dis_week.thur = THURSDAY_VALID;
				break;
			case 0x10: 
				ptSysPara->dis_week.fri = FRIDAY_VALID;
				break;
			case 0x20: 
				ptSysPara->dis_week.sat = SATURDAY_VALID;
				break;
			case 0x40: 
				ptSysPara->dis_week.sun = SUNDAY_VALID;
				break;
			default: 
			break;
		}
	}

	//显示不可选中的图标(红叉)
	//显示可选中的图标(灰色)
	for(i = 0; i < 8; i++)
	{
		switch(week_message & (0x01 << i))
		{
			case 0x01: 
					ptSysPara->dis_week.mon = MONDAY_INVALID;
					break;
			case 0x02: 
					ptSysPara->dis_week.tues = TUESDAY_INVALID;
					break;
			case 0x04: 
					ptSysPara->dis_week.wed = WEDNESDAY_INVALID;
					break;
			case 0x08: 
					ptSysPara->dis_week.thur = THURSDAY_INVALID;
					break;
			case 0x10: 
					ptSysPara->dis_week.fri = FRIDAY_INVALID;
					break;
			case 0x20: 
					ptSysPara->dis_week.sat = SATURDAY_INVALID;
					break;
			case 0x40: 
					ptSysPara->dis_week.sun = SUNDAY_INVALID;
					break;
			default: 
					break;
		}
	}
	app_dis(REG_MASTER_WEEK_MONDAY,ptSysPara->dis_week.mon);
	app_dis(REG_MASTER_WEEK_TUESDAY,ptSysPara->dis_week.tues);
	app_dis(REG_MASTER_WEEK_WEDNESDAY,ptSysPara->dis_week.wed);
	app_dis(REG_MASTER_WEEK_THURSDAY,ptSysPara->dis_week.thur);
	app_dis(REG_MASTER_WEEK_FRIDAY,ptSysPara->dis_week.fri);
	app_dis(REG_MASTER_WEEK_SATURDAY,ptSysPara->dis_week.sat);
	app_dis(REG_MASTER_WEEK_SUNDAY,ptSysPara->dis_week.sun);
}

void app_dis_highSetMode(void)
{
	SysPara_t *ptSysPara;  	
	uint8_t watch5buf[2] = {0, 0};
	ptSysPara =  controler_getSysParaPt();


}

void app_dis_wifi(void)
{

}

void app_dis_filter(void)
{

}

void app_dis_timeset(void)
{
	SysPara_t *ptSysPara;	
	dis_timeset_t month ={0, 0, 0};
	dis_timeset_t day ={0, 0, 0};
	dis_timeset_t hour ={0, 0, 0};
	dis_timeset_t minute ={0, 0, 0};
	ptSysPara =  controler_getSysParaPt();

	month.now = ptSysPara->set_time.month;
	day.now = ptSysPara->set_time.day;
	hour.now = ptSysPara->set_time.hour;
	minute.now = ptSysPara->set_time.minute;
	
	//最高位+1还需做处理
	//0~2050
	if(0 == ptSysPara->set_time.year)
	{
		app_dis(REG_MORE_YEARS_UP_ADRESS,2050);
	}
	else
	{
		app_dis(REG_MORE_YEARS_UP_ADRESS,ptSysPara->set_time.year - 1);
	}
	
	app_dis(REG_MORE_YEARS_ADRESS,(ptSysPara->set_time.year));

	if(50 == ptSysPara->set_time.year)
	{
		app_dis(REG_MORE_YEARS_DOWN_ADRESS,0);
	}
	else
	{
		app_dis(REG_MORE_YEARS_DOWN_ADRESS,(ptSysPara->set_time.year + 1));
	}
	
	//月
	if(1 == month.now)//已选中 月 上方位置 1上方应为12
	{
		month.up = 12;
	}
	else
	{
		month.up = month.now - 1;
	}

	if(12 == month.now)
	{
		month.down = 1;
	}
	else
	{
		month.down = month.now + 1;
	}
	app_dis(REG_MORE_MONTH_UP_TEN_ADRESS,month.up/10);
	app_dis(REG_MORE_MONTH_UP_ADRESS,month.up%10);
	app_dis(REG_MORE_MONTH_TEN_ADRESS,month.now/10);
	app_dis(REG_MORE_MONTH_ADRESS,month.now%10);
	app_dis(REG_MORE_MONTH_DOWN_TEN_ADRESS,month.down/10);
	app_dis(REG_MORE_MONTH_DOWN_ADRESS,month.down%10);

	//日 1~31
	if(1 == day.now)//已选中 月 上方位置 1上方应为12
	{
		day.up = 12;
	}
	else
	{
		day.up = day.now - 1;
	}

	if(31 == day.now)
	{
		day.down = 1;
	}
	else
	{
		day.down = day.now + 1;
	}
	app_dis(REG_MORE_DAY_UP_TEN_ADRESS,day.up/10);
	app_dis(REG_MORE_DAY_UP_ADRESS,day.up%10);
	app_dis(REG_MORE_DAY_TEN_ADRESS,day.now/10);
	app_dis(REG_MORE_DAY_ADRESS,day.now%10);
	app_dis(REG_MORE_DAY_DOWN_TEN_ADRESS,day.down/10);
	app_dis(REG_MORE_DAY_DOWN_ADRESS,day.down%10);
	
	//小时0~23
	if(0 == hour.now)//已选中 月 上方位置 1上方应为12
	{
		hour.up = 23;
	}
	else
	{
		hour.up = hour.now - 1;
	}

	if(23 == day.now)
	{
		hour.down = 0;
	}
	else
	{
		hour.down = hour.now + 1;
	}
	app_dis(REG_MORE_HOURS_UP_TEN_ADRESS,hour.up/10);
	app_dis(REG_MORE_HOURS_UP_ADRESS,hour.up%10);
	app_dis(REG_MORE_HOURS_TEN_ADRESS,hour.now/10);
	app_dis(REG_MORE_HOURS_ADRESS,hour.now%10);
	app_dis(REG_MORE_HOURS_DOWN_TEN_ADRESS,hour.down/10);
	app_dis(REG_MORE_HOURS_DOWN_ADRESS,hour.down%10);
	
	//0~59
	if(0 == minute.now)//已选中 月 上方位置 1上方应为12
	{
		minute.up = 59;
	}
	else
	{
		minute.up = minute.now - 1;
	}

	if(59 == minute.now)
	{
		minute.down = 0;
	}
	else
	{
		minute.down = minute.now + 1;
	}
	app_dis(REG_MORE_MINUTE_UP_TEN_ADRESS,minute.up/10);
	app_dis(REG_MORE_MINUTE_UP_ADRESS,minute.up%10);
	app_dis(REG_MORE_MINUTE_TEN_ADRESS,minute.now/10);
	app_dis(REG_MORE_MINUTE_ADRESS,minute.now%10);
	app_dis(REG_MORE_MINUTE_DOWN_TEN_ADRESS,minute.down/10);
	app_dis(REG_MORE_MINUTE_DOWN_ADRESS,minute.down%10);
}

void app_dis_factory(void)
{
	
}

void app_dis_more_message(void)
{
	SysPara_t *ptSysPara;	
	ptSysPara =  controler_getSysParaPt();
	//固定显示
	app_dis(REG_MORE_KEY_MESSAGE,38);
	app_dis(REG_MORE_PROTECE_MESSAGE,21);
	app_dis(REG_MORE_FAULT_MESSAGE,22);
	app_dis(REG_MORE_STATE_MESSAGE,40);
	app_dis(REG_MORE_INWIND_TEMP_ADRESS,35);
	app_dis(REG_MORE_LOWTEMP_TEMP_ADRESS,36);
	app_dis(REG_MORE_HIGHTEMP_TEMP_ADRESS,37);
	app_dis(REG_MORE_JUMP_ADRESS,39);
	//温度显示
	app_dis(REG_MORE_INWIND_TEMP,ptSysPara->read_2411_adress_data);
	app_dis(REG_MORE_LOW_TEMP,ptSysPara->read_2412_adress_data);	
	app_dis(REG_MORE_HIGH_TEMP,ptSysPara->read_2413_adress_data);
	//保护
	if((ptSysPara->read_240D_adress_data & 0x0001) == 0x0001)
	{
		app_dis(REG_MORE_DEF_PROTECE_MESSAGE,1);
	}
	else
	{
		app_dis(REG_MORE_DEF_PROTECE_MESSAGE,2);
	}
	
	if((ptSysPara->read_240D_adress_data & 0x0002) == 0x0002)
	{
		app_dis(REG_MORE_LOW_PRESSURE_PROTECE_MESSAGE,3);
	}
	else
	{
		app_dis(REG_MORE_LOW_PRESSURE_PROTECE_MESSAGE,4);
	}

	if((ptSysPara->read_240D_adress_data & 0x0004) == 0x0004)
	{
		app_dis(REG_MORE_INWIND_TEMP_PROTECE__MESSAGE,5);
	}
	else
	{
		app_dis(REG_MORE_INWIND_TEMP_PROTECE__MESSAGE,6);
	}
	
	if((ptSysPara->read_240D_adress_data & 0x0008) == 0x0008)
	{
		app_dis(REG_MORE_HIGH_TEMP_PROTECE_MESSAGE,7);
	}
	else
	{
		app_dis(REG_MORE_HIGH_TEMP_PROTECE_MESSAGE,8);
	}
	
	if((ptSysPara->read_240D_adress_data & 0x0010) == 0x0010)
	{
		app_dis(REG_MORE_LOW_PRESSURE_WARNING_PROTECE_MESSAGE,9);
	}
	else
	{
		app_dis(REG_MORE_LOW_PRESSURE_WARNING_PROTECE_MESSAGE,10);
	}
	
	if((ptSysPara->read_240E_adress_data & 0x0001) == 0x0001)
	{
		app_dis(REG_MORE_INWIND_SENSOR_FAULT_MESSAGE,11);
	}
	else
	{
		app_dis(REG_MORE_INWIND_SENSOR_FAULT_MESSAGE,12);
	}
	if((ptSysPara->read_240E_adress_data & 0x0002) == 0x0002)
	{
		app_dis(REG_MORE_LOWTEMP_SENSOR_FAULT_MESSAGE,13);
	}
	else
	{
		app_dis(REG_MORE_LOWTEMP_SENSOR_FAULT_MESSAGE,14);
	}
	if((ptSysPara->read_240E_adress_data & 0x0004) == 0x0004)
	{
		app_dis(REG_MORE_WENSHIDU_SENSOR_FAULT_MESSAGE,15);
	}
	else
	{
		app_dis(REG_MORE_WENSHIDU_SENSOR_FAULT_MESSAGE,16);
	}
	if((ptSysPara->read_240E_adress_data & 0x0008) == 0x0008)
	{
		app_dis(REG_MORE_HIGH_SENSOR_FAULT_MESSAGE,17);
	}
	else
	{
		app_dis(REG_MORE_HIGH_SENSOR_FAULT_MESSAGE,18);
	}
	if((ptSysPara->read_240E_adress_data & 0x0010) == 0x0010)
	{
		app_dis(REG_MORE_OUTWATCH_SENSOR_FAULT_MESSAGE,19);
	}
	else
	{
		app_dis(REG_MORE_OUTWATCH_SENSOR_FAULT_MESSAGE,20);
	}
	
	if((ptSysPara->read_2415_adress_data & 0x0001) == 0x0001)
	{
		app_dis(REG_MORE_REC_STATE_MESSAGE,23);
	}
	else
	{
		app_dis(REG_MORE_REC_STATE_MESSAGE,24);
	}

	if((ptSysPara->read_2415_adress_data & 0x0002) == 0x0002)
	{
		app_dis(REG_MORE_FRE_STATE_MESSAGE,25);
	}
	else
	{
		app_dis(REG_MORE_FRE_STATE_MESSAGE,26);
	}
	if((ptSysPara->read_2415_adress_data & 0x0004) == 0x0004)
	{
		app_dis(REG_MORE_LIFT_WATCH_STATE_MESSAGE,27);
	}
	else
	{
		app_dis(REG_MORE_LIFT_WATCH_STATE_MESSAGE,28);
	}
	if((ptSysPara->read_2415_adress_data & 0x0008) == 0x0008)
	{
		app_dis(REG_MORE_WATCH_HEIGHT_STATE_MESSAGE,30);
	}
	else
	{
		app_dis(REG_MORE_WATCH_HEIGHT_STATE_MESSAGE,29);
	}
	if((ptSysPara->read_2415_adress_data & 0x0010) == 0x0010)
	{
		app_dis(REG_MORE_AC_STATE_MESSAGE,31);
	}
	else
	{
		app_dis(REG_MORE_AC_STATE_MESSAGE,32);
	}
	if((ptSysPara->read_2415_adress_data & 0x0020) == 0x0020)
	{
		app_dis(REG_MORE_LOW_PRESSURE_STATE_MESSAGE,31);
	}
	else
	{
		app_dis(REG_MORE_LOW_PRESSURE_STATE_MESSAGE,32);
	}
}
void app_dis_fault(void)
{
	SysPara_t *ptSysPara;	
	uint16_t error1 = 0; 
	uint16_t error2 = 0;
	uint16_t error3 = 0;
	uint16_t error4 = 0;
	uint16_t error5 = 0;
	uint16_t error6 = 0;
	uint16_t error7 = 0;
	
	ptSysPara =  controler_getSysParaPt();
	if(ptSysPara->communicationflag > 60)//控制面板通讯 60s
	{
		error1 = 1;
	}
	if((ptSysPara->read_240E_adress_data & 0x0008) == 0x0008)//高温盘管故障18
	{
		error2 = 2;
	}
	if((ptSysPara->read_240E_adress_data & 0x0002) == 0x0002)//蒸发温度故障(低温盘管故障17)
	{
		error3 = 3;
	}
	if((ptSysPara->read_240E_adress_data & 0x0010) == 0x0010)//排水故障//22
	{
		error4 = 4;
	}
	if((ptSysPara->read_240E_adress_data & 0x0004) == 0x0004)//温湿度传感器故障20
	{
		error5 = 5;
	}
	if((ptSysPara->read_240E_adress_data & 0x0001) == 0x0001)//进风温度故障19
	{
		error6 = 6;
	}
	if((ptSysPara->read_240D_adress_data & 0x0010) == 0x0010)//低压保护开启13 关闭14
	{
		error7 = 7;
	}

	app_dis(REG_FAULT_COMMUNICATION,error1);
	app_dis(REG_FAULT_HIGH_NTC,error2);
	app_dis(REG_FAULT_LOW_NTC,error3);
	app_dis(REG_FAULT_OUT_WATCH,error4);
	app_dis(REG_FAULT_WENSHIDU,error5);
	app_dis(REG_FAULT_INWIND_NTC,error6);
	app_dis(REG_FAULT_LOW_PRESS_PROTECT,error7);

	//设备状态值

	if((ptSysPara->read_2415_adress_data & 0x0010) == 0x0010)
	{
		app_dis(REG_DEBUG_AC,1);
	}
	else
	{
		app_dis(REG_DEBUG_AC,2);
	}
	if(ptSysPara->read_2406_adress_data == 0x0000)//风机关3 低4 中5 高6 
	{
		app_dis(REG_DEBUG_FAN,3);	
	}
	else if(ptSysPara->read_2406_adress_data == 0x0001)
	{
		app_dis(REG_DEBUG_FAN,4);	
	}
	else if(ptSysPara->read_2406_adress_data == 0x0002)
	{
		app_dis(REG_DEBUG_FAN,5);	
	}
	else if(ptSysPara->read_2406_adress_data == 0x0003)
	{
		app_dis(REG_DEBUG_FAN,6);	
	}
	
	if((ptSysPara->read_2415_adress_data & 0x0200) == 0)//新风阀开启7 关闭8
	{
		app_dis(REG_DEBUG_FRE,8);
	}
	else if((ptSysPara->read_2415_adress_data & 0x0002) == 0x0002)
	{
		app_dis(REG_DEBUG_FRE,7);
	}
	
	if((ptSysPara->read_2415_adress_data & 0x0001) == 0)//内循环开启9 关闭10
	{
		app_dis(REG_DEBUG_REC,10);
	}
	else if((ptSysPara->read_2415_adress_data & 0x0001) == 0x0001)
	{
		app_dis(REG_DEBUG_REC,9);
	}
	
	if((ptSysPara->read_240D_adress_data & 0x0010) == 0x0010)//低压保护开启13 关闭14
	{
		app_dis(REG_DEBUG_LOW_PRESS_PROTECT,13);
	}
	else
	{
		app_dis(REG_DEBUG_LOW_PRESS_PROTECT,14);
	}
	
	if((ptSysPara->read_2415_adress_data & 0x0004) == 0)//提水泵 开启11 关闭12
	{
		app_dis(REG_DEBUG_TISHUIBENG_PROTECT,12);
	}
	else
	{
		app_dis(REG_DEBUG_TISHUIBENG_PROTECT,11);
	}

	if((ptSysPara->read_240D_adress_data & 0x0001) == 0x0001)//化霜保护 开启15 关闭16
	{
		app_dis(REG_DEBUG_HUASHUANG_PROTECT,15);
	}
	else
	{
		app_dis(REG_DEBUG_HUASHUANG_PROTECT,16);
	}
	//更多信息

	app_dis_more_message();
}

void app_dis_about(void)
{

}

void app_dis_other(void)
{

}
void app_display_updata(systemRunStatus_t sysRunStatus)
{
    switch(sysRunStatus)
    {               
       case SYS_STATUS_POWER_OFF:           app_dis_powOffMode();      break;
	   case SYS_STATUS_SCREEN_SAVER:									;break;
       case SYS_STATUS_RUN_MODE:            app_dis_runMode();         break;
       case SYS_STATUS_SETTING:         	app_dis_highSetMode();     break;    
	   case SYS_STATUS_TIMING_WEEK:			app_dis_timing_week();		break;    
	   case SYS_STATUS_TIMING_INTERVAL: 			break;    
	   case SYS_STATUS_TIMING_WEEK_ADD: 	app_dis_week_choose();		break;
	   case SYS_STATUS_WIFI:				app_dis_wifi();				break;
	   case SYS_STATUS_FILTER:				app_dis_filter();			break;
	   case SYS_STATUS_TIME:				app_dis_timeset();			break;
	   case SYS_STATUS_FACTORY:				app_dis_factory();			break;
	   case SYS_STATUS_FAULT:				app_dis_fault();			break;
	   case SYS_STATUS_ABOUT:				app_dis_about();			break;
	   case SYS_STATUS_OTHER:				app_dis_other();			break;
       default:break;
    }      
	
}

const uint16_t dis_page_adress_offset[DIS_NUMBER][3] =
{
	REG_DIS_PAGENUMBER,		REG_DIS_ADRESS,	REG_DIS_OFFSET,	
	//在建立一个获取写入数据的数组，基本显示数据这块就完成了，
	//显示数组的索引和这边的索引应一一对应，哪怕是强制赋值获取sys里面的状态
};

//定义后初始化0，定时从sys里面的元素直接获得需要的元素，直接赋值，不是规则的数据，无法通过指针访问
uint16_t dis_dis_data[DIS_NUMBER] =
{
	REG_DIS_PAGENUMBER, REG_DIS_PAGENUMBER,
};

void app_display_scanTask(void)
{         
    SysPara_t *ptSysPara;  
    static unsigned char initFlag = false;
	
	ptSysPara =  controler_getSysParaPt();

    if(initFlag == false)
    {
		initFlag = true;
        ptSysPara->updataflag = true;
    }
	
    if(ptSysPara->updataflag)
    {
        ptSysPara->updataflag = false;
        app_display_updata(ptSysPara->sys_runstatus); 
    }
}
//------------------------------E N D-------------------------------------------



//-------------------------APP_Display.c--END-----------------------------------




