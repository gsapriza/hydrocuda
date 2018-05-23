/**************
* HydroCuda model - model_time
*
* Set of basic function to init, set, read of states options
* using c and cuda
****************/

#include <stdio.h>
#include <stdlib.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;
extern model_time modeltime;

// Initialize parameter, states and flows
void init_psf(model_vars modelvars){
  
  char caux[15]; // Auxiliar to read integer
  if (options.hydroModel == "HBV"){
//     modelvars.nparams = 10;
//     modelvars.nstates = 3;
//     modelvars.nflows = 1;
    modelvars.nvars = 14; // HBV: 10 params + 3 states + 1 flow
    // For loading variables options
    aux_ids *var_ids = (aux_ids*) malloc(modelvars.nvars * sizeof(aux_ids));
    strcpy(var_ids[0].ids,"icf");   // Infiltration
    strcpy(var_ids[1].ids,"fc");    // Feild capacity
    strcpy(var_ids[2].ids,"beta");  // Seepage
    strcpy(var_ids[3].ids,"lp");    // Real ET
    strcpy(var_ids[4].ids,"perc");  // Maxumim percolation
    strcpy(var_ids[5].ids,"cflx");  // Maximum capillarity flux
    strcpy(var_ids[6].ids,"uzl");   // Upper zona limit
    strcpy(var_ids[7].ids,"kq");    // Quickflow constant
    strcpy(var_ids[8].ids,"ki");    // Interflow constant
    strcpy(var_ids[9].ids,"klz");   // Lower zona constant
    strcpy(var_ids[10].ids,"sm");   // Soil moisture
    strcpy(var_ids[11].ids,"vlz");  // Lower zona volume
    strcpy(var_ids[12].ids,"vuz");  // Upper zona volume
    strcpy(var_ids[13].ids,"q");    // Final flow 
  }
  else if (options.hydroModel == "Temez"){
    modelvars.nvars = 7; // Temez: 3 params + 2 states + 2 flows
  }
  // Auxiliar
  aux_ids *var_ids_aux = (aux_ids*) malloc(forcing.nmeteo * sizeof(aux_ids));
  // Allocate vars_info
  modelvars.info = (vars_info*) malloc(modelvars.nvars * sizeof(vars_info));
  for (int i = 0; i < modelvars.nvars; i++){
    // Fill auxiliar
    strcpy(var_ids_aux[i].ids,met_ids[i].ids);
    // Read variables
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_units"), "%s", modelvars.info[i].units);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_name"), "%s", modelvars.info[i].name);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_longname"), "%s", modelvars.info[i].longname);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
  }
  
}

void allocate_psf(model_vars modelvars){
  // Flows have different shape than parameters and states
  int nflows;
  if (options.hydroModel == "HBV"){
    nflows = 1;
  }
  else if (options.hydroModel == "Temez"){
    nflowz = 2;
  }
  // Allocate parametes and state initial matrix
  for (int i = 0; i < (modelvars.nvars - nflows); i++){
    modelvars.info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt);
  }
  // Allocate flows matrix
  for (i = (modelvars.nvars - nflows); i < modelvars.nvars; i++){
    modelvars.info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt);
  }
  
}

void free_psf(model_vars modelvars){
  // Free parameters, states and flows
  for (int i = 0; i < modelvars.nvars; i++){
    free(modelvars.info[i].vars);
  }
  
}
