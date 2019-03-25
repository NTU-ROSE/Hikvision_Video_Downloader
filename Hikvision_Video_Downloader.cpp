#include <stdio.h> 
#include <iostream> 
#include <unistd.h>
#include <cstdlib>
#include "./lib/HCNetSDK.h" 
using namespace std;
int main(int argc, char** argv) {
    //---------------------------------------
    // 初始化
    NET_DVR_Init(); //设置连接时间与重连时间 
    NET_DVR_SetConnectTime(2000, 1); 
    NET_DVR_SetReconnect(10000, true);
    
    LONG lUserID;
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    lUserID = NET_DVR_Login_V30(argv[1], 8000, argv[2], argv[3], &struDeviceInfo); 
    if (lUserID < 0)
    {
    printf("Login error, %d\n", NET_DVR_GetLastError()); NET_DVR_Cleanup();
    return 0;
    }
     
    NET_DVR_PLAYCOND struDownloadCond={0};
    struDownloadCond.dwChannel= atoi(argv[4]); //通道号
    struDownloadCond.struStartTime.dwYear = atoi(argv[5]);
    struDownloadCond.struStartTime.dwMonth = atoi(argv[6]);
    struDownloadCond.struStartTime.dwDay = atoi(argv[7]);
    struDownloadCond.struStartTime.dwHour = atoi(argv[8]);
    struDownloadCond.struStartTime.dwMinute = atoi(argv[9]); 
    struDownloadCond.struStartTime.dwSecond =atoi(argv[10]);
    
    struDownloadCond.struStopTime.dwYear = atoi(argv[5]);
    struDownloadCond.struStopTime.dwMonth = atoi(argv[6]);
    struDownloadCond.struStopTime.dwDay = atoi(argv[7]);
    struDownloadCond.struStopTime.dwHour = atoi(argv[11]);
    struDownloadCond.struStopTime.dwMinute = atoi(argv[12]);
    struDownloadCond.struStopTime.dwSecond = atoi(argv[13]);
    //---------------------------------------
    //按时间下载
    int hPlayback;
    hPlayback = NET_DVR_GetFileByTime_V40(lUserID, argv[14],&struDownloadCond);
    if(hPlayback < 0)
    {
    printf("NET_DVR_GetFileByTime_V40 fail,last error %d\n",NET_DVR_GetLastError());
    NET_DVR_Logout(lUserID);
    NET_DVR_Cleanup();
    return 0;
    }
    
    if(!NET_DVR_PlayBackControl_V40(hPlayback, NET_DVR_PLAYSTART, NULL, 0, NULL,NULL))
    {
        printf("Play back control failed [%d]\n",NET_DVR_GetLastError());
        NET_DVR_Logout(lUserID); 
        NET_DVR_Cleanup(); 
        return 0 ;
    }
    
    int nPos = 0;
    for(nPos = 0; nPos < 100&&nPos>=0; nPos = NET_DVR_GetDownloadPos(hPlayback)) 
    {
        printf("Be downloading... %d %%\n",nPos); //下载进度
        usleep(5000); //millisecond 
    }
    
    
    if(!NET_DVR_StopGetFile(hPlayback)) {
        printf("failed to stop get file [%d]\n",NET_DVR_GetLastError());
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return 0;
    }
    
    if(nPos<0||nPos>100) {
        printf("download err [%d]\n",NET_DVR_GetLastError()); NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return 0;
    }
    
    printf("Be downloading... %d %%\n",nPos);
    
    //注销用户 
    NET_DVR_Logout(lUserID); 
    //释放 SDK 资源 
    NET_DVR_Cleanup(); 
    return 1;
}