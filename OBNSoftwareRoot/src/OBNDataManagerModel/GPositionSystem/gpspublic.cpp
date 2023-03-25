#include "gpspublic.h"
#include "geo2xy_utm.h"

//#include "kalman.h" ///< zhw-update

GpsCoord::GpsCoord()
{

}
GpsCoord GpsCoord::toXy()
{
    double kalX,kalY;
    double gpsX,gpsY;
    const float dt      = 1;            // time interval (second)
    const float sgm_acc = 1e-4;         // Standard deviation of acceleration
    const float sgm_obs = 10;
//    const KIV kiv_x(dt,sgm_acc,sgm_obs);    ///< zhw-update

    GpsCoord xyCord = *this;
    geo2xy_utm(this->x,this->y,&xyCord.gpsX,&xyCord.gpsY);
    gpsX = xyCord.gpsX;
    gpsY = xyCord.gpsY;
//    Kalman_gps(gpsX ,gpsY,kalX,kalY,kiv_x); ///< zhw-update
    xyCord.x=kalX;
    xyCord.y=kalY;

    return xyCord;
}
