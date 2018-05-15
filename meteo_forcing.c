/**************
* meteo_forcing
*
* Set of basic function to init, set, read of meteorological focing and update
* using c and cuda
*******************/

#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;

void init_forcing(meteo_forcing *forcing){
  
  if (options.meteoModel == 'Pp&Ev'){
    forcing->nmeteo = 2;
    //Allocate meteo_info
    forcing->info = (meteo_info *)malloc(forcing.nmeteo * sizeof(meteo_info));
    forcing->info[0]->units    = 'mm/day'; //Units have to be set from options
    forcing->info[0]->name     = 'precip';
    forcing->info[0]->longname = 'precipitation';
    forcing->info[1]->units    = 'mm/day';
    forcing->info[1]->name     = 'evap';
    forcing->info[1]->longname = 'PotEvapotranspiration';
  }
}

void allocate_forcing(meteo_forcing *forcing){
  // Allocation and setting to zero
  // We shoud distingush between ntime block allocating,
  // All time steps or in each time step

  if (options.meteoModel == 'Pp&Ev'){
    forcing->precip = (*float)*malloc(sizeof(float)*domain.ntgt*modeltime.nt);
    forcing->pet    = (*float)*malloc(sizeof(float)*domain.ntgt*modeltime.nt);
  }
}
// 
// void read_forcing_netdf4(){
//
// }
//
// void update_forcing(){
//
// }

void free_forcing(meteo_forcing *forcing){
  
  if (options.meteoModel == 'Pp&Ev'){
    free(forcing->info);
    free(forcing->precip);
    free(forcing->pet);
  }

}
