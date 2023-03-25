#include "appglobal.h"

AppGlobal* AppGlobal::s_AppGlobal = NULL;

AppGlobal::AppGlobal() : m_crentLanguageIdx(-1)
{
    /// ====== 初始化获取语言设置配置文件内容
    QString nLanguageConfigFName = QApplication::applicationDirPath() + Dir_Separator + "../.config/language.cfg";
    QFileInfo fileInfo(nLanguageConfigFName);
    if(!fileInfo.exists())
    {
        m_crentLanguageIdx = 0;
        setCurrentLanguageMode(0);
    }
    else
    {
        QFile file(nLanguageConfigFName);
        if(file.open(QIODevice::ReadOnly))
        {
            /// ====== 读取旧的文件内容
            QString nInformJsonFile = file.readAll();
            if(!nInformJsonFile.isEmpty())
            {
                QJsonParseError parseJsonErr;
                QJsonDocument document = QJsonDocument::fromJson(nInformJsonFile.toUtf8(), &parseJsonErr);
                if (!(parseJsonErr.error == QJsonParseError::NoError))
                {
                    return;
                }
                QJsonObject jsonObject = document.object();
                if(jsonObject.contains("language"))
                {
                    m_crentLanguageIdx = jsonObject.value("language").toInt();
                }
            }
        }
    }
}

void AppGlobal::setCurrentLanguageMode(const int& index)
{
    m_crentLanguageIdx = index;
    /// ====== 设置Json信息到语言设置配置文件
    QString nCurentLanguageFName = QApplication::applicationDirPath() + Dir_Separator + "../.config/language.cfg";

    /// ======
    QFile file(nCurentLanguageFName);
    if(file.exists())
    {
        file.remove();
    }
    if(file.open(QIODevice::WriteOnly))
    {
        QJsonObject jsonObject;
        jsonObject.insert("language", index);
        QJsonDocument documentToString;
        documentToString.setObject(jsonObject);
        QByteArray byteArray = documentToString.toJson(QJsonDocument::Compact);
        /// ======
        file.write(byteArray);
        /// ======
        file.close();
    }
}

int  AppGlobal::getCurrentLanguageMode()
{
    return m_crentLanguageIdx;
}
