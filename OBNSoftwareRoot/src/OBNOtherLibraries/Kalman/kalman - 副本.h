#define ARMA_DONT_USE_WRAPPER 1
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
using std::string;
#define flush_std fflush(stdout);
const float PI = 4.0*atan(1.0);
#include "complex_TJU_PENG.h"
#include "arma.h"

#include "kalman_global.h"

/*============================================================================*/
/* Inner Variables of Kalman filtering
 */
struct Kalman_InnerVars
{
    float dt;      // time interval between obs-samples
    fmat  Q1;      // Covariance of state var状态协方差
    float Q2;      // Covariance of obs-samples观测协方差
    fmat  C ;      // operator   of observation观测矩阵
    fmat  F ;      // forward operator of the PDE状态矩阵
//    fmat  F1;  //状态转移矩阵
//    fmat  P0;  //状态协方差矩阵
//    fmat  Q;   //状态转移协方差矩阵
//    fmat  R;   //观测噪声方差
//    fmat  H;   //观测矩阵


    Kalman_InnerVars( float _dt, float _sgm_acc, float _sgm_obs )
    {
        /*-----*/
        dt = _dt;
        /*-----*/
        Q1.set_size(3,3);
        Q1.zeros();
        Q1 (2,2) = _sgm_acc;         // variance of accelaration
        /*-----*/
        Q2       = _sgm_obs;         // variance of obs
        /*-----*/
        C.set_size(1,3);
        C.zeros();
        C(0) = 1.0f;
        /*-----*/
        F.set_size(3,3);
        F   << 1.0f << dt   << 0.0f << endr
            << 0.0f << 1.0f << dt   << endr
            << 0.0f << 0.0f << 0.0f << endr;

//        F1.set_size(3,3);
//        F1  << 1.0f << dt   << 0.0f << 0.0f << endr
//            << 0.0f << 1.0f << 0.0f << 0.0f << endr
//            << 0.0f << 0.0f << 1.0f << dt << endr
//            << 0.0f << 0.0f << 0.0f << 1.0f << endr
//        P0.set_size(3,3);
//        P0.eye(3);
//        Q.set_size(3,3);
//        Q.diag([0.5,1,0.5,1]);
//        R.set_size(1,1);
//        R.eye(1);
//        H.set_size(1,3);
//        H  <<1.0f << 0.0f << 0.0f << 0.0f << endr
//           <<0.0f << 0.0f << 1.0f << 0.0f << endr
    }
};
typedef Kalman_InnerVars KIV;

#ifdef __cplusplus
extern "C"{
#endif

/* ------ Calculation Step of Kalman filtering ------*/
int  KALMANSHARED_EXPORT Kalman_Calc     (   int i , float  acc_in, float  d, float & d_esti, fvec & x_esti, fmat & K, const KIV & kiv);
/* ------Read data ------ */
int Get_data    (   int nt, fvec & gps_xn, fvec & gps_yn);

#ifdef __cplusplus
}
#endif

static inline FILE* fopen_xp(const string & fn,const char* mode)
{
    FILE* fp;
    fp=fopen(fn.c_str(),mode);
    if (fp==NULL)
    {
        printf("Failed to open %s !\n",fn.c_str());
    }
    return fp;
}




