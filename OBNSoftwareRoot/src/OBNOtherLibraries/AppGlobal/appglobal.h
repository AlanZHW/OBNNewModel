#ifndef APPGLOBAL_H
#define APPGLOBAL_H

#include <QFile>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QFileInfo>
#include <QApplication>

#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "macro.h"
#include "appglobal_global.h"

class APPGLOBAL_EXPORT AppGlobal
{
public:
    /// ====== 实例化单例类
    static AppGlobal* getInstance()
    {
        if(NULL == s_AppGlobal)
        {
            s_AppGlobal = new AppGlobal;
        }
        return s_AppGlobal;
    }
    void setCurrentLanguageMode(const int&);
    int  getCurrentLanguageMode();
private:
    AppGlobal();
    int    m_crentLanguageIdx;
    static AppGlobal *s_AppGlobal;
};
#endif // APPGLOBAL_H
