/*
 * common.h
 *
 *  Created on: 2014-8-13
 *      Author: Administrator
 */

#ifndef COMMON_H_
#define COMMON_H_

//-------------------版本----------------------------//
#define VERSION_YEARS 3014		//高位v3.0，低位14年
#define MONTHS_DATA 804		//高位1月，低位8日

typedef unsigned char u8;
typedef unsigned char bool;
typedef unsigned int u16;
typedef unsigned long u32;
#define NULL                     (0)
#ifndef true
#define true          (1)
#endif
#ifndef false
#define false         (0)
#endif

typedef struct {
	u16 userID0_3; //用户卡号0-3位17f0,//最右边低位
	u16 userID4_7; //用户卡号4-7位
	u16 userID8_11; //用户卡号8-11位
	u16 userID12_15; //用户卡号12-15位
	u16 yuYueIdA; //5
	u16 yuYueIdB; //6
	u32 cardBalance; //卡内剩余的余额7
	u16 pageNum; //过压过负荷告警控制9,1800
	u16 buttonNum; //下位机已经读到卡返回的命令10 卡状态1802
	u16 hmiPageNum; //目前充电状态标志位变量11,1804
	u16 inputMoney; //键盘上输入的需要充电的金额或电量12,1806
	u16 chargeMode; //发给下位机的充电模式选择13,1808
	u16 chargeTime; //预约充电时间14,180a
	u16 userIdA0_3; //A口用户卡号低15,180c
	u16 userIdA4_7; //A口用户卡180e
	u16 userIdA8_11; //A口用户卡1810
	u16 userIdA12_15; //A口用户卡1812
	u32 balanceA; //A口余额低1814
	u16 inputMoneyA; //输入金额或电量1818
	u16 chargeModeA; //充电模式181a
	u16 chargeTimeHoursA; //没有使用
	u16 chargeTimeMinuA; //A口充电分钟数24,181e，预约剩余时间
	u16 chargeElecA; //A口已充电电量25,1820
	u32 chargeMoneyA; //A口已充电金额26,1822
	u16 cardMoneyA; //A口卡余额低28,1824
	u32 startElecA; //启动时电量
	u16 stateA; //31
	//1-5-电表异常，结算设备与电表通讯异常(启动失败)
	//2-结算设备与无线模块通讯异常
	//6-通讯板异常
	//7-黑名单卡
	//40-停止充电（卡内余额不足停止）
	//41-停止充电（选择的条件满足后停止）
	//60-结算时与开始充电卡号不同
	//61-    无  卡
	//62-无法找到用电纪录
	//63-扣款失败
	//65-此卡正在充电
	u16 alarmType; //32   //电表异常
	u32 passwordCom; //发给下位机的密码值33,1830
	u16 userIdB0_3; //B口用户卡号低35,1834
	u16 userIdB4_7; //B口用户卡号1836
	u16 userIdB8_11; //B口用户卡号1838
	u16 userIdB12_15; //B口用户卡号183a
	u32 balanceB; //183c，余额
	u16 inputMoneyB; //用户输入金额或电量
	u16 chargeModeB; //充电模式
	u16 chargeTimeHoursB; //没有使用
	u16 chargeTimeMinuB; //B口已充电分钟数44,1846,预约剩余时间
	u16 chargeElecB; //B口已充电电量45,1848
	u16 chargeMoneyB; //B口已充电金额46,184a
	u32 cardMoneyB; //B口卡余额低位47,184c
	u32 rtElecA; //49实时电量
	u16 stateB; //51
	////////////100///////////////////
	u16 lcdTimePtr;		//52
	u16 u1858;
	u16 realTime[7];		//54
//	u16 secondsmmmm; //年54
//	u16 seconds; //时钟秒55
//	u16 minutes; //时钟分56
//	u16 hours; //时钟时57
//	u16 dates; //时钟日58
//	u16 months; //时钟月59
//	u16 yearsL; //时钟年60

	//交流电压采样结果
	u16 voltageArms; //A口实时充电电压61,1868
	//交流电压采样结果
	u16 voltageBrms; //B口实时充电电压62,186a
	//交流电压采样结果
	u16 voltageCrms; //C相电压63,186c
	u16 currentArms; //A口实时充电电流64,186e
	u16 adc4; //1870
	u16 adc5; //1872
	u16 currentBrms; //B口实时充电电流67,1874
	u16 adc7; //1876
	u16 adc8; //1878
	u16 record_ov_value; //记录下交流量告警值70，过压值,187a

	//写入EEPROM起始地址，长度60字节
	u16 ov_vlaue; //过压基准,187c
	u16 uv_vlaue; //欠压基准,187e
	u16 oi_vlaue; //过流基准,0x1f4=500,1880
	u16 pwmDuty; //74占空比
	u16 u1884; //0x3a98; //15000
	u16 u1886; //0x2710; //10000
	u16 u1888; //0x1388; //5000

	u16 ammeCount; //电表地址数量78,188a
	u16 ammeAdd5A; //电表地址第5位,188c
	u16 ammeAdd4A; //电表地址第4位,188e
	u16 ammeAdd3A; //电表地址第3位,1890
	u16 ammeAdd2A; //电表地址第2位,1892
	u16 ammeAdd1A; //电表地址第1位,1894
	u16 ammeAdd0A; //电表地址第0位,1896
	u16 ammeAdd5B; //电表地址第5位,1898
	u16 ammeAdd4B; //电表地址第4位,189a
	u16 ammeAdd3B; //电表地址第3位,189c
	u16 ammeAdd2B; //电表地址第2位,189e
	u16 ammeAdd1B; //电表地址第1位,18a0
	u16 ammeAdd0B; //电表地址第0位90,18a2

	u16 coef_voltageA; //A相电压系数，18a4
	u16 coef_voltageB; //B相电压系数，
	u16 coef_voltageC; //C相电压系数，
	u16 coef_currentA; //A相电流系数，
	u16 coef_adc4; //
	u16 coef_adc5; //
	u16 coef_currentB; //B相电流系数，
	u16 coef_adc7; //18b2
	u16 coef_adc8; //18b4

	u16 sumCheck_18b6; //99校验
	//写入EEPROM结尾地址，长度3C

	//故障记录
	u16 readFlag;		//1-读取故障记录标志
	u16 readChargeFlag;	//1-读取充电记录标志
	u16 recordNum; //记录号
	u16 ttt[20]; //备用

	u16 years_v; //124，主板程序版本
	u16 data_v;
	u16 years2_v; //通讯板程序版本
	u16 data2_v;
	u16 priceH;
	u16 priceL; //电价
	//
	u16 wsPwm; //130由握手信号板上传
	u16 woshouVolt; //握手板校准电压131
	u16 wsVoltA; //由握手信号板上传
	u16 wsVoltB; //由握手信号板上传
	u32 congealMoney; //134冻结金额
	u16 deviceID; //136,站内充电桩编号
	u16 id_num1; //137,二维码ID高位
	u16 id_num2; //138
	u16 id_num3;
	u16 id_num4; //140,10位ID起始地址
	u16 id_num5; //141
	u16 id_num6;
	u16 id_num7;
	u16 id_num8; //144ID低位

	u16 e1; //145//显示屏传过来的屏幕号,后五个字节保留
	u16 hmiPageNum2; //146
	u16 e3; //
	u16 e4; //
	u16 e5; //
	u16 e6; //150

	u16 AmeterVoltA; //A口A相电压151
	u16 AmeterVoltB; //A口B相电压
	u16 AmeterVoltC; //A口C相电压
	u16 AmeterCurrA; //A口A相电流154
	u16 AmeterCurrB; //A口B相电流
	u16 AmeterCurrC; //A口C相电流
	u16 BmeterVoltA; //B口A相电压157
	u16 BmeterVoltB; //B口B相电压
	u16 BmeterVoltC; //B口C相电压
	u16 BmeterCurrA; //B口A相电流160
	u16 BmeterCurrB; //B口B相电流
	u16 BmeterCurrC; //B口C相电流162
	u16 tta[8]; //163-169备用

	u8 record[240]; //171

} YCBUF, *pYCBUF;

typedef struct {
	//196c
	unsigned opFlag0 :1; //RG7,A握手信号PP
	unsigned opFlag1 :1; //RG8,接触器A采样
	unsigned opFlag2 :1; //RG9,B握手信号PP
	unsigned opFlag3 :1; //RB2,接触器B采样
	unsigned opFlag4 :1; //RB3
	unsigned opFlag5 :1; //RB4
	unsigned opFlag6 :1; //RB5
	unsigned opFlag7 :1; //RB6

	//196d,AB口充电控制
	unsigned u196d_0 :1; //196d-0
	unsigned readyLampA :1; //A口握手灯,196d-1
	unsigned chargeACtrl :1; //A口控制,196d-2
	unsigned readyLampB :1; //B口握手灯,196d-3
	unsigned chargeBCtrl :1; //B口控制,196d-4
	unsigned chargeLampA :1; //A口充电指示灯,196d-5
	unsigned chargeLampB :1; //B口充电指示灯.196d-6
	unsigned u196d_7 :1; //196d-7

	//如果卡内余额大于1元，则置1，跳转到输入密码界面
	unsigned icCardMoneOk_196e_0 :1; //第一次读卡成功
	unsigned u196ebit1 :1;
	unsigned u196ebit2 :1;
	unsigned u196ebit3 :1;
	unsigned u196ebit4 :1;
	unsigned u196ebit5 :1;
	unsigned u196ebit6 :1;
	unsigned u196ebit7 :1; //前次充电未结算

	//196f
	unsigned inCard :1; //发给下位机要准备读卡的命令25
	unsigned sendPassword :1; //发送密码给下位机同时置该位
	/* 在点击屏幕确定按钮时，显示屏程序把该位设置为1。
	 * 控制程序把19a0置1，发送读卡命令，返回数据，
	 * 并且余额大于一定数额时。把该位清零。
	 * */
	unsigned firstCard :1; //首次插卡提示27
	unsigned writeCard :1; //结算写卡失败
	unsigned otherCard :1; //与启动充电卡号不同
	unsigned selectPortA :1; //选择A口后发给下位机的标志
	unsigned selectPortB :1; //选择B口后发给下位机的标志
	//先更新页面再置位Over
	unsigned outCard :1; //退卡命令32,196f-7

	//1970,告警
	unsigned voltageAlarmA :1; //输入过欠压为1//充电口A电压异常告警33
	unsigned voltageAlarmB :1; //输入过欠压为1//充电口B电压异常告警
	unsigned enableA :1; //A插口可选按钮35
	unsigned enableB :1; //B插口可选36
	unsigned u1970bit4 :1; //
	unsigned u1970bit5 :1; //
	unsigned currAlarmA :1; //A口过载
	unsigned currAlarmB :1; //B口过载

	//1971,1-空闲，0-充电完成，未结算
	unsigned settlFinishA :1; //1-A口结算写卡未能成功,1971-0
	//1-空闲，0-完成
	unsigned settlFinishB :1; //1-B口结算写卡未能成功？1971-1
	unsigned stopA :1; //发命令中止A口充电43,1971-2
	unsigned stopB :1; //发命令中止B口充电,1971-3
	unsigned portErrA :1; //A插口故障,1971-4
	unsigned portErrB :1; //B插口故障46,1971-5
	unsigned settlementA :1; //结算A插口金额,1971-6
	unsigned settlementB :1; //结算B插口金额48,1971-7

	//告警1972
	unsigned u1972bit0 :1; //49输入过欠压为1
	unsigned u1972bit1 :1;
	unsigned u1972bit2 :1;
	unsigned u1972bit3 :1;
	unsigned u1972bit4 :1; //输入过欠压为1
	unsigned u1972bit5 :1;
	unsigned u1972bit6 :1;
	unsigned u1972bit7 :1; //56
	//预约充电1973
	unsigned yueA :1; //A口已经预约,57
	unsigned yueAstart :1; //预约用户开始充电
	unsigned yueB :1; //B口已经预约,59
	unsigned yueBstart :1; //预约用户开始充电
	unsigned u1973bit4 :1;
	unsigned u1973bit5 :1;
	unsigned u1973bit6 :1;
	unsigned u1973bit7 :1; //64

	//定时充电
	unsigned u1974bit0 :1; //65
	unsigned u1974bit1 :1; //时间格式错误，没用到
	unsigned showStopPasswordA :1; //67显示停止充电密码框
	unsigned showStopPasswordB :1; //68显示停止充电密码框
	unsigned stopPasswordVerify :1; //69停止充电时密码验证
	unsigned receivingPassword :1; //0-正在接收密码，1-已经接收到密码
	unsigned chargingTxtA :1; //0-充电中，1-暂停71
	unsigned chargingTxtB :1; //0-充电中，1-暂停
	//
	unsigned verifyTimePassword :1; //73下发验证密码命令
	unsigned isCard :1; //74是否有卡
	unsigned isTiming :1; //75是否定时
	unsigned verifyPasswordOK :1; //密码是否正确
	unsigned hideChargeButton :1; //77AB口都定时充电，隐藏充电按钮。
	unsigned pwmOnA :1; //握手板上传占空比是否已经开启
	unsigned pwmOnB :1; //握手板上传占空比是否已经开启
	unsigned woshouban_set :1; //80显示屏发送握手板校准命令

} YXBUF, *pYXBUF; //共20个

typedef struct {
	unsigned resBegin :1; //接收到起始码
	unsigned resLen :1; //接收到数据域长度码
	unsigned resFinish :1; //接收完成
	unsigned enableSend :1; //使能发送
	unsigned aa1 :1; //备用
	unsigned aa2 :1;
	unsigned aa3 :1;
	unsigned aa4 :1;
	u8 rxdptr;
	u16 rxdlen;
	u8 txdptr;
	u8 txdlen;
	u8* pRxdBuf;
	u8* pTxdBuf;
	u8 uartState; //通信状态
	u16 faultPtr; //异常计数
} UartTag, *pUartTag;


void memCpy(u8* pDst, u8* pSrc, u16 len);
u8 memComp(u8* pDst, u8* pSrc, u16 len);
void copyU16ToU8(u8*pdst, u16*psrc, u8 len);
void copyU8ToU16(u16*pdst, u8*psrc, u8 len);
void clrMem(u8*psrc, u16 len);


#endif /* COMMON_H_ */
