/**************
* meteo_forcing
*
* Set of basic function to init, set, read of meteorological focing and update
* using c and cuda
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;
extern model_time modeltime;

void init_forcing(meteo_forcing *forcing){
  
  if (options.meteoModel == 'Pp&Ev'){
    forcing->nmeteo = 2; // Precip and pet
    // For loading forcing options
    meteo_ids *met_ids = (meteo_ids*) malloc(forcing->nmeteo * sizeof(meteo_ids));
    strcpy(met_ids[0].mids,"Pp"); // Precipitation
    strcpy(met_ids[1].mids,"Ev"); // Potential evotranspiration
    // Auxiliar
    meteo_ids *met_ids_aux = (meteo_ids*) malloc(forcing->nmeteo * sizeof(meteo_ids));
    strcpy(met_ids_aux[0].mids,"Pp");
    strcpy(met_ids_aux[1].mids,"Ev");
  }
  else if (options.meteoModel == 'Pp&Penman'){
    forcing->nmeteo = 8; // Precip and variables to Penman pet calc
  }
  // Allocate meteo_info
  forcing->info = (meteo_info*) malloc(forcing->nmeteo * sizeof(meteo_info));
  // Read variables
  for (int i = 0; i < forcing->nmeteo; i++){
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_units"), "%s", forcing->info[i].units);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_name"), "%s", forcing->info[i].name);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_longname"), "%s", forcing->info[i].longname);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
  }
  //forcing->info[0].units    = 'mm/day'; //Units have to be set from options
  //forcing->info[0].name     = 'precip';
  //forcing->info[0].longname = 'precipitation';
  //forcing->info[1].units    = 'mm/day';
  //forcing->info[1].name     = 'evap';
  //forcing->info[1].longname = 'PotEvapotranspiration';
}

void allocate_forcing(meteo_forcing *forcing){
  // Allocation and setting to zero
  // We shoud distingush between ntime block allocating,
  // All time steps or in each time step
  
  for (int i = 0; i < forcing->nmeteo; i++){
    forcing->info[i].meteo = (float*) malloc(sizeof(float) * domain.ntgt * modeltime.nt);
    //forcing->precip = (float*)*malloc(sizeof(float)*domain.ntgt*modeltime.nt);
    //forcing->pet    = (float*)*malloc(sizeof(float)*domain.ntgt*modeltime.nt);
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
  
  for (int i = 0; i < forcing->nmeteo; i++){
    free(forcing->info[i].meteo);
    //free(forcing->precip);
    //free(forcing->pet);
  }

}
