#ifndef SEGY
#define SEGY

#include<math.h>
#include <stdio.h>
#include <QDir>
#include <QMap>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>

#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <arpa/inet.h>
#endif

#include "core_global.h"
#include "../../../include/publicHostInform.h"

class GobsInterface
{
private:
    GobsInterface();
    static GobsInterface *GobsInface;
public:
    static GobsInterface *getInstance()
    {
        if(NULL == GobsInface)
            GobsInface = new GobsInterface;
        return GobsInface;
    }
    //===打开SEGY文件
    int OpenSEGYFileFunc(OpenTrace *openTr, QString SEGYFName, int Mode, char *Bna3200, BinaryHead *BinHead, SegyInfo *DtInfo);
    //====写数据时将400字节卷头小端转换为大端
    void WriteGetBinHead400(BinaryHead *);
    //====读取数据时将400字节卷头大端转换为小端
    void CreateBinHead(BinaryHead *);
    //====读数据时将3200字节卷头转换编码
    void EBD2QStr(char *);
    //====写数据时将3200字节卷头转换编码
    void QStr2EBD(char *);

    //===读取数据
    int ReadSEGYDataFunc(OpenTrace *openTr, long long statnum, long long trnum, TraceHead *trhead, char *trdata, long long *currtr);
    void ChangeTraceDataBigEndian(OpenTrace *openTr, char *tracedata, long long CurrTrNum);
    void ibm_to_ieee( int *from, int *to, int n );
    void ChangeTraceHeadBigEndian(TraceHead *g_TrHead_240, long long CurrTrNum);

    //===关闭数据
    int CloseSEGYDataFunc(OpenTrace *openTr);

    //===写数据
    int WriteSEGYDataFunc(OpenTrace *openTr, TraceHead *trhead, char *trdata);
    void ChangeTraceHeadLittleEndian(TraceHead *trhead);//===写数据将道头小端转换为大端
    void changeEnd(char *trace_data, int ns);           //===写数据将数据小端转换为大端
    void ieee_to_ibm(int from[], int to[], int n);      //===写数据将IEEE数据转换为IBM数据
};


//iointerfaces-----------------------------------------------------
//===打开SEGY数据接口
//===参数说明:
//=== path      ： 文件存放路径
//=== filename  ： 文件名
//=== mode      ： 打开文件模式 0:只读;1:只写;2:读写
//=== Bnary3200 : 3200字节卷头
//=== binary_head：读打开是返回400字节卷头信息,写打开时将400字节卷头写入到SEGY数据文件中
//=== datainfo  ： 当前数据部分信息
//=== fileptr   ： 返回值，文件句柄，用于读写
//=== ok        ： 返回值，成功返回0,失败返回非0
CORESHARED_EXPORT OpenTrace *gobs_open_segy_func(const char*filename, int *mode, char *Bnary3200, BinaryHead *binary_head, SegyInfo *datainfo, int *ok);

//===读取SEGY数据接口
//===参数说明:
//=== fileptr ： open时返回的文件句柄
//=== statnum ： 读取数据的起始道
//=== trnum   ： 读取数据的道数
//=== headbuff:  存放道头
//=== databuff:  存放数据
//=== currtrnum: 实际读取的道数
//=== ok      ： 返回值，成功返回0，失败返回非0
CORESHARED_EXPORT void gobs_read_segy_func(OpenTrace *openTr, long long statnum, long long trnum, TraceHead *headbuff, char *databuff, long long *currtrnum, int *ok);

//===写SEGY数据接口
//===参数说明:
//=== fileptr ： open时返回的文件句柄
//=== statnum ： 写数据的起始道
//=== trnum   ： 写数据的道数
//=== headbuff:  道头
//=== databuff:  数据
//=== ok      ： 返回值，成功返回0，失败返回非0
CORESHARED_EXPORT void gobs_write_segy_func(OpenTrace *openTr, TraceHead *headbuff, char *databuff, int *ok);

//===关闭open时打开的文件
//===参数说明
//===   fileptr : open时返回的文件句柄
CORESHARED_EXPORT void gobs_close_segy_func(OpenTrace *openTr, int *ok);


#endif // SEGY
































