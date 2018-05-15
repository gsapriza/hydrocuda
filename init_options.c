/**************
* Function to init option model
* The struct defined for model option are initialized
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/
#include "hydrocuda.h"


void init_modeloptions(){

  // optns.domainModel =  'gridcells';
  // optns.meteoModel  = 'Pp&Ev';
  // optns.istimeblock = 1;
  ini_sget(options.config, "ModelDomain", "suport_type", "%s", optns.domainModel);
  ini_sget(options.config, "MeteoModel", "forcing_type", "%s",  optns.meteoModel);
  ini_sget(options.config, "TimeControl", "isblock", "%d", optns.istimeblock);

}
