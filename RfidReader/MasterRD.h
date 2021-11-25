/******** 功能：获取动态库版本号 2字节 *******************/
//  返回: 成功返回0
/*********************************************************/
extern "C" int WINAPI lib_ver(unsigned int *nVer);


/******** 功能：DES 算法加密函数 *************************/
//  参数：szOut:  加密结果，长度等于加密数据长度
//        szIn:   加密数据
//        inlen:  加密数据长度,8字节的整数倍
//        key:    密钥
//        keylen: 密钥长度,如果大于8字节，是3des,如果小于等于8字节单des.不足补零
//  返回: 成功返回0
/*********************************************************/
extern "C" int (WINAPI* des_encrypt)(unsigned char *szOut,unsigned char *szIn , unsigned int inlen,unsigned char *key,unsigned int keylen);


/******** 功能：DES 算法解密函数 *************************/
//  参数：szOut:  解密结果，长度等于解密数据长度
//        szIn:   解密数据
//        inlen:  解密数据长度,8字节的整数倍
//        key:    密钥
//        keylen: 密钥长度,如果大于8字节，是3des,如果小于等于8字节单des.不足补零
//  返回: 成功返回0
/*********************************************************/
extern "C" int (WINAPI* des_decrypt)(unsigned char *szOut,unsigned char *szIn , unsigned int inlen,unsigned char *key,unsigned int keylen);


/******** Function: Initialize serial port ******************************* /
// Parameters: port: Serial port number, ranging from 1 to 4
// baud: communication baud rate 4800 ~ 115200
// Returns: 0 on success
/*********************************************************/
extern "C" int WINAPI rf_init_com(int port,long baud);


/******** Function: specify the device identification ***************************** /
// Parameters: icdev: communication device identifier, 0-65536
// Returns: 0 if successful
/*********************************************************/
extern "C" int WINAPI rf_init_device_number(unsigned short icdev);


/******** Function: read device identification *****************************/
// parameter: Icdev: communication device identifier
// Returns: 0 if successful
/***************************************************** ********/
extern "C" int WINAPI rf_get_device_number(unsigned short *Icdev);


/******** Function: Get the reader hardware version number, 2 bytes *********** /
// Parameters: icdev: communication device identifier
// Version: store return version information
// Returns: 0 on success
/*********************************************************/
extern "C" int WINAPI rf_get_model(unsigned short icdev,unsigned short *Version);


/******** Function: get the reader serial number, 8 bytes ***********/
// Parameters: icdev: communication device identifier
// Snr: store back to read the card serial number
// Returns: 0 on success
/*********************************************************/
extern "C" int WINAPI rf_get_snr(unsigned short icdev,unsigned char *Snr);


/******** 功能：蜂鸣 *************************************/
//  参数：icdev：通讯设备标识符
//        msec： 蜂鸣时限，单位是10 毫秒
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_beep(unsigned short icdev,unsigned char msec);


/******** 功能：设置读写卡器sam 卡通讯波特率 *************/
//  参数：icdev：通讯设备标识符
//        bound: sam 卡波特率，取值为9600、38400
//  返回：成功则返回0
//  说明：bound=0:9600
//        bound=1:38400
/*********************************************************/
extern "C" int WINAPI rf_init_sam(unsigned short icdev,unsigned char bound);


/******* 功能：复位sam 卡 ********************************/
//  参数：icdev： 通讯设备标识符
//        pData：返回的复位信息内容
//        pMsgLg：返回复位信息的长度
//  返回：成功则返回0
//  说明：
/*********************************************************/
extern "C" int WINAPI rf_sam_rst(unsigned short icdev, unsigned char *pData,unsigned char *pMsgLg);
/*例：
     unsigned int icdev;
     unsigned char pData[MAX_RF_BUFFER];
     unsigned char len;
     status = rf_sam_rst(icdev,pData,&len);
     
*/


/******** 功能：向SAM 卡发送COS 命令 *********************/
//  参数：icdev：  通讯设备标识符
//        command：cos 命令
//        cmdLen:  cos 命令长度
//        pDate： 卡片返回的数据，含SW1、SW2
//        pMsgLg： 返回数据长度
//  返回：成功则返回0
//  说明：
/*********************************************************/
extern "C" int WINAPI rf_sam_cos(unsigned short icdev, unsigned char *command,unsigned char cmdLen ,unsigned char *pData,unsigned char* Length);
/*例：
     unsigned char icdev;
     unsigned char* cmd;
     unsigned char pData[MAX_RF_BUFFER];
     unsigned char len;
     status = rf_sam_cos(icdev,cmd,sizeof(cmd),pData,&len);
     
*/


/*******  功能：设置读写卡器非接触工作方式为 *************/ 
//              ISO14443 TYPE A OR ISO14443 TYPE B
//  参数：icdev：通讯设备标识符
//        type:  读写卡器工作方式
//  返回：成功则返回0
//  说明：type='A':设置为TYPE_A方式
//        type='B':设置为TYPE_B方式
//        type='r':设置为AT88RF020卡方式
/*********************************************************/
extern "C" int WINAPI rf_init_type(unsigned short icdev,unsigned char type);


/*******  功能：关闭或启动读写卡器天线发射 ***************/
//  参数：icdev：通讯设备标识符
//        model：天线状态
//  返回：成功则返回0
//  说明：model=0:关闭天线
//        model=1:开启天线
/*********************************************************/
extern "C" int WINAPI rf_antenna_sta(unsigned short icdev, unsigned char model);


/******** Function: to find ISO14443-3 TYPE_A card ******************* /

// Parameters: icdev: communication device identifier
// model: card mode
// TagType: returns the card type value
// Returns: 0 on success
// Description: mode = 0x26: find the card did not enter hibernation
// mode = 0x52: find all state cards

/*********************************************************/
extern "C" int WINAPI rf_request(unsigned short icdev, unsigned char model, unsigned short *TagType);


/********* Function: ISO14443-3 TYPE_A card anti-collision ************** /
// Parameters: icdev: communication device identifier
// bcnt: number of bytes in the card serial number, the value 4,7,10, Mifare card value 4
// pSnr: The returned card serial number
// pRLength: card serial number length
// Returns: 0 on success
// Description:
/*********************************************************/
extern "C" int WINAPI rf_anticoll(unsigned short icdev, unsigned char bcnt, unsigned char *pSnr,unsigned char* pRLength);
/*例：int status
      unsigned char icdev;
      unsigned char snr[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_anticoll(icdev,4,snr,&len);      
*/


/******** Function: Lock an ISO14443-3 TYPE_A card ************* /
// Parameters: icdev: communication device identifier
// pSnr: card serial number
// srcLen: card serial number length, MifareOne card this value is equal to 4
// Size: return the card capacity
// Returns: 0 on success
/*********************************************************/
extern "C" int WINAPI rf_select(unsigned short icdev,unsigned char *pSnr,unsigned char srcLen,unsigned char *Size);


/******* 功能：命令已激活的ISO14443-3 TYPE_A卡进入休眠状态*/
//  参数：icdev：通讯设备标识符
//  返回：成功则返回0
/**********************************************************/
extern "C" int WINAPI rf_halt(unsigned short icdev);


/***** 功能：用指定的密钥验证Mifare One 卡*****************/
//  参数：icdev：通讯设备标识符
//        model：密码验证模式
//        block：要验证密码的绝对块号（0～63）
//        key：  密钥内容，6 字节
//  返回：成功则返回0
//  说明：model=0x60:验证A密钥
//        model=0x61:验证B密钥
/**********************************************************/
extern "C" int WINAPI rf_M1_authentication2(unsigned short icdev,unsigned char model,unsigned char block,unsigned char *key);


/*******  功能：读取Mifare One 卡一块数据 ****************/
//  参数：icdev： 通讯设备标识符
//        block： M1卡绝对块号（0～63）
//        pData：读出数据
//        pLen:   读出数据的长度
//  返回：成功则返回0
//  说明：
/*********************************************************/
extern "C" int WINAPI rf_M1_read(unsigned short icdev, unsigned char block, unsigned char *pData,unsigned char *pLen);
/*例：int status
      unsigned short icdev
      unsigned char pData[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_M1_read(icdev,0,pData,&len);
      
*/


/*******  功能：向Mifare One 卡中写入一块数据 ************/
//  参数：icdev：通讯设备标识符
//        block：M1卡绝对块号（0～63)
//        data： 写入的数据，16 字节
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_M1_write(unsigned short icdev, unsigned char block, unsigned char *data);


/*******  功能：将Mifare One 卡某一扇区初始化为钱包 *******/
//  参数：icdev：通讯设备标识符
//        block：M1 卡块地址（0～63）
//        value：初始值
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_M1_initval(unsigned short icdev, unsigned char block, long value);


/*******  功能：读Mifare One 钱包值 **********************/
//  参数：icdev： 通讯设备标识符
//        block： M1 卡块地址（0～63）
//        pValue：返回的值
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_M1_readval(unsigned short icdev, unsigned char block,long* pValue);


/*******  功能：Mifare One 扣款 **************************/
//  参数：icdev：通讯设备标识符
//        block：M1 卡块地址（0～63）
//        value：要扣的值
//  返回：成功则返回0
//  说明：此函数执行成功后，结果保存在卡片的BUFFER 内，
//        尚未改写相应块的内容，若要将结果保存到卡片
//        相应块中需紧跟执行rf_M1_restore 函数
/*********************************************************/
extern "C" int WINAPI rf_M1_decrement(unsigned short icdev, unsigned char block,long value);


/******** 功能：Mifare One 充值 **************************/
//  参数：icdev：通讯设备标识符
//        block：M1 卡块地址（0～63）
//        value：要增加的值
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_M1_increment(unsigned short icdev, unsigned char block,long value);


/******** 功能：Mifare One 卡值回传 **********************/
//  参数：icdev：通讯设备标识符
//        block：M1 卡块地址（0～63）
//  返回：成功则返回0
//  说明：用此函数将指定的块内容传入卡的buffer，然后可用
//        rf_M1transfer()函数将buffer 中数据再传送到另一块中去
/*********************************************************/
extern "C" int WINAPI rf_M1_restore(unsigned short icdev, unsigned char block);


/****** 功能：将Mifare One数据传送 ***********************/
//  参数：icdev：通讯设备标识符
//        block：M1 卡块地址（0～63）
//  返回：成功则返回0
//  说明：该函数仅在increment、decrement和restore 命令之后调用。
/*********************************************************/
extern "C" int WINAPI rf_M1_transfer(unsigned short icdev, unsigned char block);


/******** 功能：复位符合ISO14443-A 标准的CPU 卡 **********/
//  参数：icdev： 通讯设备标识符
//        model:  寻卡方式
//        pDate：返回的复位信息内容
//        pMsgLg：返回复位信息长度
//  返回：成功则返回0
//  说明：
/*********************************************************/
extern "C" int WINAPI rf_typea_rst(unsigned short icdev,unsigned char model,unsigned char *pData,unsigned char *pMsgLg);
/*例：int status
      unsigned short icdev
      unsigned char pData[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_typea_rst(icdev,0,pData,&len);      
*/


/******** 功能：向符合ISO14443-4标准的CPU卡发送COS 命令***/
//  参数：icdev：  通讯设备标识符
//        command：cos 命令
//        cmdLen:  cos 命令长度
//        pDate： 卡片返回的数据，含SW1、SW2
//        pMsgLg： 返回数据长度
//  返回：成功则返回0
//  说明：
/*********************************************************/
extern "C" int WINAPI rf_cos_command(unsigned short icdev,unsigned char *command,unsigned char cmdLen,unsigned char *pData,unsigned char* pMsgLg);
/*例：int status
      unsigned short icdev
      unsigned char* cmd;
      unsigned char pData[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_typea_cos(icdev,cmd,sizeof(cmd),pData,&len);      
*/


/******** 功能：激活符合ISO14443 TYPE_B 标准的卡 *********/
//  参数：icdev： 通讯设备标识符
//        model： 寻卡方式0＝REQB,1=WUPB
//        pDate：卡片返回的数据
//        pMsgLg：返回数据的长度
//  返回：成功则返回0
//  说明：
/*********************************************************/
extern "C" int WINAPI rf_atqb(unsigned short icdev,unsigned char model,unsigned char *pData,unsigned char *pMsgLg);
/*例：int status
      int icdev
      unsigned char msglg
      unsigned char pDate[MAX_RF_BUFFER];
      status = rf_atqb(icdev,0,pDate,&msglg);      
*/

/******** 功能：命令一选中的TYPE_B卡进入HALT 状态*********/
//  参数：icdev：通讯设备标识符
//        PUPI： 卡片唯一标识符
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_hltb(unsigned short icdev,unsigned long PUPI);
//??

/******** 功能：验证AT88RF020 卡密码 *********************/
//  参数：icdev：通讯设备标识符
//        key：  密码，8 字节
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_at020_check(unsigned short icdev, unsigned char *key);


//******* 功能：读AT88RF020 卡一页数据 *******************/
//  参数：icdev： 通讯设备标识符
//        page：  页地址，（0～31）
//        pDate：返回的数据
//        pMsgLen:返回数据的长度
//  返回：成功则返回0
//  说明：
/*********************************************************/
extern "C" int WINAPI rf_at020_read(unsigned short icdev, unsigned char page, unsigned char *pData,unsigned char* pMsgLen);
/*
例：int status
    int icdev
    unsigned char pData[MAX_RF_BUFFER];
    unsigned char len;
    status = rf_at020_read(icdev,0,pData,&len);    
*/


/******** 功能：写AT88RF020 卡一页数据 *******************/
//  参数：icdev：通讯设备标识符
//        page： 页地址，（0～31）
//        Date： 要写入的数据，8 字节
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_at020_write(unsigned short icdev, unsigned char page, unsigned char *data);
 

/******** 功能：LOCK AT88RF020卡**************************/
//  参数：icdev：通讯设备标识符
//        date： 数据，4 字节
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_at020_lock(unsigned short icdev,unsigned char *data);


/******** 功能：AT88RF020卡计数函数 **********************/
//  参数：icdev：通讯设备标识符
//        date： 数据，6 字节
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_at020_count(unsigned short icdev,unsigned char *data);


/******** 功能：命令AT88RF020 卡进入HALT 状态 ************/
//  参数：icdev：通讯设备标识符
//  返回：成功则返回0
/*********************************************************/
extern "C" int WINAPI rf_at020_deselect(unsigned short icdev);


/******** 功能：控制灯的颜色 *****************************/
//  参数：icdev：通讯设备标识符
//        color: 0 ,熄灯
//               1 ,红灯
//               2 ,绿灯
//               3 ,黄灯
//  返回：成功返回0
/*********************************************************/
extern "C" int WINAPI rf_light(unsigned short icdev,unsigned char color);



//******* 功能：释放memory *******************************/
//extern "C" void WINAPI rf_free(void* pData);


/******** 功能：关闭Com端口 ******************************/
//  返回：成功返回0
/*********************************************************/
extern "C" int WINAPI rf_ClosePort();


/******** 功能：返回状态字 *******************************/
//  返回：错误代码
/*********************************************************/
extern "C" int WINAPI rf_GetErrorMessage();


