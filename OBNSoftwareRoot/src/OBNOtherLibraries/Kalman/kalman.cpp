#include "kalman.h"



/*============================================================================*/
/**
 * ------ Calculation Step of Kalman filtering ------
 * Input  :
 *          i       = time index
 *          d       = data of time(i)
 *          acc_in  = input acceleration
 *          kiv     = Kalman_InnerVars
 * Output :
 *          d_esti  = "filtered data" of time(i)
 *
 * Input & Output :
 *          K       = IN  : K(i  ,i-1)
 *                    OUT : K(i+1,i  )
 *          x_esti  = IN  : estimated "state var" of time(i-1),
 *                    OUT : overwriten as estimated "state var" of time(i)
 */
int Kalman_Calc( int i, float acc_in, float d, float & d_esti, fvec & x_esti, \
                 fmat & K , const KIV & kiv)
{
    const fmat  & Q1 = kiv.Q1;
    const float & Q2 = kiv.Q2;
    const fmat  & C  = kiv.C;
    const fmat  & F  = kiv.F;

    /* Calc G       ----------*/

    float R_alpha =  as_scalar( C*K*C.t()+Q2 );
    fmat  Gc(3,1);
    Gc = K*C.t() / (R_alpha) ;

    /* 1-step prediction of x_esti */
    x_esti(2) += acc_in;
    fvec x_esti_1p  = F * x_esti;

    /* Calc alpha   ----------*/
    float d_esti_1p = as_scalar (C * x_esti_1p);
    float alpha  = d - d_esti_1p;

    /* Calc x_esti  ----------*/
    x_esti = x_esti_1p + Gc*alpha;    // update!
    d_esti = as_scalar (C * x_esti);  // update!

    /* UPDATE K(i+1,i)----------*/
    fmat P     = K - Gc*C*K;
    K = F*P*F.t() + Q1;

    return 0;
}
int Kalman_gps(double gpsx,double gpsy,double &outX,double &outY,const KIV & kiv)
{
    const mat  & FT = kiv.FT;
    const mat  & Q  = kiv.Q;
    const mat  & R  = kiv.R;
    const mat  & H  = kiv.H;
    mat X,Z;
//    fmat Q1(4,4),R1(2,2),a(4,1);

    int N=2;
    X.set_size(4,N);
    X.zeros();
    X(0,0)=gpsx;
    X(1,0)=1;
    X(2,0)=gpsy;
    X(3,0)=0.9;
//    X.print("X:");
//    qDebug()<<QString("%1").arg(X(0,0), 0, 'd', 4) ;
//    qDebug()<<QString("%1").arg(X(1,0), 0, 'd', 4) ;
//    qDebug()<<QString("%1").arg(X(2,0), 0, 'd', 4) ;
//    qDebug()<<QString("%1").arg(X(3,0), 0, 'd', 4) ;
    Z.set_size(2,N);
    Z.zeros();
    Z(0,0)=X(0,0);
    Z(1,0)=X(2,0);
//    Z.print("Z:");
    float delta_w=0.01;
    mat Q1;
    Q1.set_size(4,4);
//    Q.print("Q:");
//    fmat Q1(4,4);
    Q1=delta_w*Q; //状态转移协方差矩阵
//    Q1.print("Q1:");
    mat R1(2,2);
    R1=2*R;   //观测噪声方差
    mat a(4,1);
    a.fill(1);

    vec b(2);
    b.fill(1);


    for (int t=1;t<N;t++)
    {
        X.col(t)=FT*X.col(t-1)+sqrtmat_sympd(Q1)*a;
        Z.col(t)=H*X.col(t)+sqrtmat_sympd(R1)*b;  //观测值
    }

//    qDebug()<<QString("%1").arg(X(0,0), 0, 'd', 4) ;
//    qDebug()<<QString("%1").arg(X(2,0), 0, 'd', 4) ;
//    qDebug()<<QString("%1").arg(X(0,1), 0, 'd', 4) ;
//    qDebug()<<QString("%1").arg(X(2,1), 0, 'd', 4) ;
    mat Xkf(4,N);
    Xkf.zeros();
    Xkf.col(0)=X.col(0);
    mat P0,I;
    P0.eye(4,4);
    mat Xn(4,1);
    mat P1(4,4);
    P1.zeros();
    mat K(4,2);
//    FT.print("FT");
    for(int i=1;i<N;i++)
    {
      //上一观测值的预测
       Xn=FT*Xkf.col(i-1);
       P1=FT*P0*FT.t()+Q1;

       //当前观测值更新
       K=P1*H.t()*inv(H*P1*H.t()+R1);
       Xkf.col(i)=Xn+K*(Z.col(i)-H*Xn);
       P0=(I.eye(4,4)-K*H)*P1;
    }

//     qDebug()<<QString("%1").arg(Xkf(0,0), 0, 'f', 4) ;
//     qDebug()<<QString("%1").arg(Xkf(2,0), 0, 'f', 4) ;
//     qDebug()<<QString("%1").arg(Xkf(0,1), 0, 'f', 4) ;
//     qDebug()<<QString("%1").arg(Xkf(2,1), 0, 'f', 4) ;
    outX=Xkf(0,1);
    outY=Xkf(2,1);
//    float testZ1,testZ2;
//    testZ1=Z(0,1);
//    testZ2=Z(1,1);

    return 0;
}
/*============================================================================*/
/* Read data (gps-samples)
 */
int Get_data(int nt, fvec & gps_xn,fvec & gps_yn)
{
    string dir = "/home/peng/Ex_WSL/kalman/";
    string fn  = dir + "noised_gpsxy_nt1000_dt1_sgm80.dat";

    FILE * fp  =  fopen_xp(fn,"r");
    fread( &gps_xn(0), sizeof(float), nt, fp );
    fread( &gps_yn(0), sizeof(float), nt, fp );
    fclose(fp);
    return 0;

}
