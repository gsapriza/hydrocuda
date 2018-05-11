/**************
* Function to init option model
* The struct defined for model option are initialized
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/
#include "hydrocuda.h"


void init_modeloptions(){

  extern model_options optns

  optns.domainModel = 'gridcells';
  optns.meteoModel  = 'Pp&Ev';
  optns.istimeblock = 1;
}
