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

	app_dis(REG_SCREEN_SAVER_TEMP,(ptSysPara->measure_temp/10));//-99~99


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

	

}
void app_display_week_select(uint16_t offset)
{

	
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

void app_dis_timeset(uint16_t *adress_index, uint16_t *dat_number)
{
	*adress_index = 1;
	*dat_number = 5;
}

void app_dis_factory(void)
{
	
}

void app_dis_more_message(void)
{

}
void app_dis_fault(void)
{
	
}

void app_dis_about(void)
{

}

void app_dis_other(void)
{

}

 
const uint16_t dis_page_adress_offset[DIS_NUMBER][3] =
{	//页码								地址								偏移
	REG_DIS_PAGENUMBER_PAGE_29,			REG_DIS_NUMBER_ADRESS,			REG_DIS_NUMBER_OFFSET,
	REG_DIS_PAGENUMBER_PAGE_41,			REG_DIS_SETTIME_YEAR_ADRESS,	REG_DIS_SETTIME_OFFSET,
	REG_DIS_PAGENUMBER_PAGE_41,			REG_DIS_SETTIME_MONTH_ADRESS,	REG_DIS_SETTIME_OFFSET,
	REG_DIS_PAGENUMBER_PAGE_41,			REG_DIS_SETTIME_DAY_ADRESS,		REG_DIS_SETTIME_OFFSET,
	REG_DIS_PAGENUMBER_PAGE_41,			REG_DIS_SETTIME_HOUR_ADRESS,	REG_DIS_SETTIME_OFFSET,
	REG_DIS_PAGENUMBER_PAGE_41,			REG_DIS_SETTIME_MINTUE_ADRESS,	REG_DIS_SETTIME_OFFSET
	//在建立一个获取写入数据的数组，基本显示数据这块就完成了，
	//显示数组的索引和这边的索引应一一对应，哪怕是强制赋值获取sys里面的状态
};

//定义后初始化0，定时从sys里面的元素直接获得需要的元素，直接赋值，不是规则的数据，无法通过指针访问
uint16_t dis_dis_data[DIS_NUMBER] =
{
	0, 0
};

void app_dis_message(uint16_t adress_index, uint16_t dat_number)
{
	uint16_t i = 0;
	for(i = adress_index; i < dat_number; i++)
	{
		app_dis(dis_page_adress_offset[i][1],dis_dis_data[i]+dis_page_adress_offset[i][2]);
	}
}

void app_display_updata(systemRunStatus_t sysRunStatus)
{
	uint16_t adress_index = 0;
	uint16_t dat_number = 0;
	
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
	   case SYS_STATUS_TIME:				app_dis_timeset(&adress_index,&dat_number);			break;
	   case SYS_STATUS_FACTORY:				app_dis_factory();			break;
	   case SYS_STATUS_FAULT:				app_dis_fault();			break;
	   case SYS_STATUS_ABOUT:				app_dis_about();			break;
	   case SYS_STATUS_OTHER:				app_dis_other();			break;
       default:break;
    }      

	app_dis_message(adress_index,dat_number);
	
}

void app_display_scanTask(void)
{         
    SysPara_t *ptSysPara;  
    static unsigned char initFlag = false;
	uint16_t i = 0;
	ptSysPara =  controler_getSysParaPt();

    if(initFlag == false)
    {
		initFlag = true;
        ptSysPara->updataflag = true;
		
		dis_dis_data[0] = ptSysPara->temp_set/10;
		dis_dis_data[1] = ptSysPara->set_time.year;
		dis_dis_data[2] = ptSysPara->set_time.month;
		dis_dis_data[3] = ptSysPara->set_time.day;
		dis_dis_data[4] = ptSysPara->set_time.hour;
		dis_dis_data[5] = ptSysPara->set_time.minute;
		for(; i < DIS_NUMBER; i++)
		{
			app_dis(dis_page_adress_offset[i][1],dis_dis_data[i]+dis_page_adress_offset[i][2]);
		}
    }
	
    if(ptSysPara->updataflag)
    {
        ptSysPara->updataflag--;
        app_display_updata(ptSysPara->sys_runstatus); 

		dis_dis_data[0] = ptSysPara->temp_set/10;
		dis_dis_data[1] = ptSysPara->set_time.year;
		dis_dis_data[2] = ptSysPara->set_time.month;
		dis_dis_data[3] = ptSysPara->set_time.day;
		dis_dis_data[4] = ptSysPara->set_time.hour;
		dis_dis_data[5] = ptSysPara->set_time.minute;
		//每次进来都要从数据中获得最新数据，需不需要更新后面决定

		
		/*for(; i < 10; i++)
		{
			if(ptSysPara->page_number == dis_page_adress_offset[i][0])
			{
				//更新数据
				app_dis(dis_page_adress_offset[i][1],dis_dis_data[i]+dis_page_adress_offset[i][2]);
			}
		}*/
    }	
}
//------------------------------E N D-------------------------------------------



//-------------------------APP_Display.c--END-----------------------------------




