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

void init_forcing(model_vars forcing){
  
  if (options.meteoModel == "Pp&Ev"){
    forcing.nvars = 2; // Precip and pet
    // For loading forcing options
    aux_ids *met_ids = (aux_ids*) malloc(forcing.nvars * sizeof(aux_ids));
    strcpy(met_ids[0].ids,"Pp"); // Precipitation
    strcpy(met_ids[1].ids,"Ev"); // Potential evotranspiration
  }
  else if (options.meteoModel == "Pp&Penman"){
    forcing.nvars = 8; // Precip and variables to Penman pet calc
  }
  // Allocate auxiliar
  aux_ids *met_ids_aux = (aux_ids*) malloc(forcing.nvars * sizeof(aux_ids));
  // Allocate meteo_info
  forcing.info = (vars_info*) malloc(forcing.nvars * sizeof(vars_info));
  for (int i = 0; i < forcing.nvars; i++){
    // Fill auxiliar
    strcpy(var_ids_aux[i].ids,met_ids[i].ids);
    // Read variables
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_units"), "%s", forcing.info[i].units);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    //ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_name"), "%s", forcing.info[i].name);
    //strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    //ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_longname"), "%s", forcing.info[i].longname);
    //strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_location"), "%s", forcing.info[i].location);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    // Variable known declaration
    strcpy(modelvars.info[i].name,var_ids_aux[i].ids);
    forcing.info[i].indx = i;
  }
  //forcing->info[0].units    = 'mm/day'; //Units have to be set from options
  //forcing->info[0].name     = 'precip';
  //forcing->info[0].longname = 'precipitation';
  //forcing->info[1].units    = 'mm/day';
  //forcing->info[1].name     = 'evap';
  //forcing->info[1].longname = 'PotEvapotranspiration';
}

void allocate_forcing(model_vars forcing){
  // Allocation and setting to zero
  // We shoud distingush between ntime block allocating,
  // All time steps or in each time step
  
  for (int i = 0; i < forcing.nvars; i++){
    forcing.info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt * modeltime.nt);
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

void free_forcing(model_vars forcing){
  
  for (int i = 0; i < forcing.nvars; i++){
    free(forcing.info[i].vars);
    //free(forcing->precip);
    //free(forcing->pet);
  }

}
