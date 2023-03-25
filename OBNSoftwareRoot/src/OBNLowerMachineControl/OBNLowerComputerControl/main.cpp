
#include <QPixmap>
#include <QSplashScreen>

#include <QApplication>
#include <QTranslator>

#include "obnlowercomputercontrol.h"

// #define BOOT_ANIMATION /// ====== 是否播放启动动画

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator* qtTranslator = new QTranslator;
    if(qtTranslator->load("../zh.qm"))
    {
        a.installTranslator(qtTranslator);
    }
    OBNLowerComputerControl cw;
    cw.show();

#ifdef BOOT_ANIMATION   /// ====== 播放开机动画
#if 0
    QPixmap pixmap("qrc:/Image/BootAnimation/bootAnimation.png");
#else
    QPixmap pixmap("/home/datuo/ZHW/Tool/OBNLowerComputerControlRoot/OBNLowerComputerControl/Image/BootAnimation/bootAnimation.png");
#endif
    QSplashScreen splash(pixmap);
    splash.show();
    for(long i = 0; i < 50000; i ++)
        for(long j = 0; j < 20000; j ++);
#endif

#ifdef BOOT_ANIMATION
    /// ======
    splash.finish(&owm);
#endif

    return a.exec();
}
