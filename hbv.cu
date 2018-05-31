/**************
* HydroCuda model
*
* HBV hydrological model
* using cuda
***************/

#include <math.h>

__global__ void hbv_dynamic( float *q    ,
                             float *etr  ,
                             float *qin  ,
                             float *qlz  ,
                             float *qq   ,
                             float *qi   ,
                             float *qcf  ,
                             float *sp   ,
                             float *inet ,
                             float *qdr  ,
                             float *pp   ,
                             float *etp  ,
                             float *sm   ,
                             float *fc   ,
                             float *vlz  ,
                             float *vuz  ,
                             float *cflux,
                             float *icf  ,
                             float *beta ,
                             float *lp   ,
                             float *perc ,
                             float *uzl  ,
                             float *klz  ,
                             float *ki   ,
                             float *kq   )
{
  const int i = blockDim.x*blockDim.y*blockIdx.y*gridDim.x + blockDim.x*blockDim.y*blockIdx.x + blockDim.x*threadIdx.y + threadIdx.x;
  // In flows
  qin[i]  = max(pp[i] - icf, 0.f);
  etr[i]  = min(icf, etp[i]);
  // State variables
  sm[i]   = sm[i] + qin[i];
  qdr[i]  = max(sm[i] - fc[i], 0.f);
  sm[i]   = sm[i] - qdr[i];
  inet[i] = qin[i] - qdr[i];
  sp[i]   = pow(sm[i] / fc[i], beta[i]) * inet[i];
  sm[i]   = sm[i] - sp[i];
  // Evapotranspirations
  etp[i]  = etp[i] - etr[i];
  etr[i]  = min(min(sm[i] * etp[i] / (lp[i] * fc[i]), etp[i]), sm[i]);
  sm[i]   = sm[i] - etr[i];
  // Volume states
  vlz[i]  = vlz[i] + min(perc[i], qdr[i] + sp[i]);
  vuz[i]  = vuz[i] + max(0.f, qdr[i] + sp[i] - perc[i]);
  // Capillar flow
  qcf[i]  = cflux[i] * (fc[i] - sm[i]) / fc[i];
  sm[i]   = sm[i] + min(vuz[i], qcf[i]);
  vuz[i]  = max(vuz[i] - qcf[i], 0.f);
  // Quick and inter flow
  qq[i]   = max(kq[i] * (vuz[i] - uzl[i]), 0.f);
  qi[i]   = ki[i] * min(uzl[i], vuz[i]);
  // Base flow
  qlz[i]  = klz[i] * vlz[i];
  // Final flow
  q[i]    = qlz[i] + qi[i] + qq[i];
  
}

