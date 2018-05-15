/**************
* meteo_forcing
*
* Set of basic function to init, set, read of meteorological focing and update
* using c and cuda
*******************/

#include "hydrocuda.h"

void init_domain(){

  //This can be another alternative don't pass as
  extern model_domain options
  extern model_domain domain
  
  if (options.domainModel == 'gridcells'){
    domain.nx   = 2; //estas opciones estarian dentro de options??
    domain.ny   = 2;
    domain.ntgt = domain.nx*domain.ny;
    domain.dx   = 1000.0;
    domain.dy   = 1000.0;
  }
}
