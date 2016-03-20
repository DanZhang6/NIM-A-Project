﻿/*************************************************
*描述：
*    测量函数设置
*功能：
*    1.选择探头工作，初始化8253，并开启定时器；
*    2.显示时间和探头设置，等待定时到；
*    3.定时到，刷新屏幕，显示计数率；

**************************************************/
#include "STC12C5A60S2.h"
#include "intrins.h"
#include "config.h" 
#include "absacc.h"	 

void ShowSetResult();

void measure()
{   
	 uchar j;
     Signal1=Var_Signal1;                   //选择探头
     Signal2=Var_Signal2;
     Signal3=Var_Signal3; 
     ShowSetResult(); 					   //显示当前参数结果
     if((Flag_ParaChange == 1)||(Flag_InputChange == 1))   //探头或参数有修改
     {
	     Flag_ParaChange = 0;
   	     Flag_InputChange = 0;
	  /*设置完的参数存储到AT24C16*/
	     if(Incinput<9)	 
            dt_in[330]=Incinput;			//IIC存储数组(探头个数标志)
	     else								//注意到这里强制探头数量必须小于9
		 {
	  	    Incinput=8;
			dt_in[330]=Incinput;
		 }
	     DS_SaveData(dt_in);                 //把调节系数的数据保存到AT24C16芯片中 
     }
	 jishucount=0;
	 for(j=0;j<8;j++)						//置零用来算三次平滑平均值的数组
	 {
	 	save0[j]=0;
		save1[j]=0;
		save2[j]=0;
	 }
	 Init_8253();                             //8253初始化     
}

void ShowSetResult()
{
  Flag_RefrInput=0;
  Flag_RefrPara=0;
  Flag_RefrRight=0;
  Flag_RefrTime=0;
  Clear();
  Lcd_Clear();
  if(measure_flag==1)
  {
     Txtext(152,148,"探头共计：");
     Tnumber(392,148,Incinput);
     Txtext(440,148,"个");
     Txtext(152,216,"测量时间：");
     Tnumber(392,216,Redrawtime);
     Txtext(480,216,"秒");
     Txtext(152,284,"进行测量中..."); 
  }
  else
  {
     Txtext(152,148,"标定测量：第");
     Tnumber(450,148,biaoding_input);
     Txtext(484,148,"个探头");
     Txtext(152,216,"测量时间：");
     Tnumber(392,216,Redrawtime);
     Txtext(480,216,"秒");
     Txtext(152,284,"进行标定测量中..."); 
  } 
 }
