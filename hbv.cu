#include <math.h>
__global__ void hbv_dynamic( float *q, float *etr, float *qin, float *qlz, float *qq, float *qi, float *qcf, float *sp, float *inet, float *qdr, float *pp, float *etp, float *sm, float *fc, float *vlz, float *vuz, const float cflux, const float icf, const float beta, const float lp, const float perc, float *uzl, const float klz, const float ki, const float kq)
{
  const int i = blockDim.x*blockDim.y*blockIdx.y*gridDim.x + blockDim.x*blockDim.y*blockIdx.x + blockDim.x*threadIdx.y + threadIdx.x;
  
  qin[i] = max(pp[i] - icf, 0.f);
  etr[i] = min(icf, etp[i]);
  
  sm[i] = sm[i] + qin[i];
  qdr[i] = max(sm[i] - fc[i], 0.f);
  sm[i] = sm[i] - qdr[i];
  inet[i] = qin[i] - qdr[i];
  sp[i] = pow(sm[i] / fc[i],beta) * inet[i];
  sm[i] = sm[i] - sp[i];
  
  etp[i] = etp[i] - etr[i];
  etr[i] = min(min(sm[i] * etp[i] / (lp * fc[i]),etp[i]),sm[i]);
  // etr[i] = etp[i];
  // if (sm[i] < (lp * fc[i])) {
  //     etr[i] = sm[i] * etp[i] / (lp * fc[i]) ;
  //     }
  sm[i] = sm[i] - etr[i];
  
  vlz[i] = vlz[i] + min(perc,qdr[i] + sp[i]);
  vuz[i] = vuz[i] + max(0.f,qdr[i] + sp[i] - perc);
  
  qcf[i] = cflux * (fc[i] - sm[i]) / fc[i];
  sm[i] = sm[i] + min(vuz[i],qcf[i]);
  vuz[i] = max(vuz[i] - qcf[i],0.f);
  
  qq[i] = max(kq * (vuz[i] - uzl[i]),0.f);
  qi[i] = ki * min(uzl[i],vuz[i]);
  
  qlz[i] = klz * vlz[i];
  
  q[i] = qlz[i] + qi[i] + qq[i];
}

