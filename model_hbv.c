/**************
* HydroCuda model - model HVB
*
* Set of basic function to init, set, read of states options
* using c and cuda
****************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;
extern model_time modeltime;

void init_hbv(model_vars modelvars){
  // Initialize parameter, states and flows
//   modelvars.nparams = 10;
//   modelvars.nstates = 3;
//   modelvars.nflows = 9;
  modelvars.nvars = 22; // HBV: 10 params + 3 states + 9 flow
  // For loading variables options
  aux_ids *var_ids = (aux_ids*) malloc(modelvars.nvars * sizeof(aux_ids));
  int vtipe[modelvars.nvars];
  //tipe variable: 1=Flux, 2=Param, 3=StateVariable
  // Parameters
  strcpy(var_ids[0].ids,"icf");   // Infiltration
  vtipe[0] = 2;
  strcpy(var_ids[1].ids,"fc");    // Feild capacity
  vtipe[1] = 2;
  strcpy(var_ids[2].ids,"beta");  // Seepage
  vtipe[2] = 2;
  strcpy(var_ids[3].ids,"lp");    // Real Evapotranspiration factor
  vtipe[3] = 2;
  strcpy(var_ids[4].ids,"perc");  // Maxumim percolation
  vtipe[4] = 2;
  strcpy(var_ids[5].ids,"cflux");  // Maximum capillar flow
  vtipe[5] = 2;
  strcpy(var_ids[6].ids,"uzl");   // Upper zone limit
  vtipe[6] = 2;
  strcpy(var_ids[7].ids,"kq");    // Quickflow constant
  vtipe[7] = 2;
  strcpy(var_ids[8].ids,"ki");    // Interflow constant
  vtipe[8] = 2;
  strcpy(var_ids[9].ids,"klz");   // Lower zone constant
  vtipe[9] = 2;
  // State variables
  strcpy(var_ids[10].ids,"sm");   // Soil moisture
  vtipe[10] = 3;
  strcpy(var_ids[11].ids,"vlz");  // Lower zone volume
  vtipe[11] = 3;
  strcpy(var_ids[12].ids,"vuz");  // Upper zone volume
  vtipe[12] = 3;
  // Internal flows
  strcpy(var_ids[13].ids,"qin");  // In flow
  vtipe[13] = 1;
  strcpy(var_ids[14].ids,"etr");  // Real Evapotranspiration
  vtipe[14] = 1;
  strcpy(var_ids[15].ids,"qdr");  // Drainage flow
  vtipe[15] = 1;
  strcpy(var_ids[16].ids,"inet"); // Net in flow
  vtipe[16] = 1;
  strcpy(var_ids[17].ids,"sp");   // Seepage flow
  vtipe[17] = 1;
  strcpy(var_ids[18].ids,"qcf");  // Captllar flow
  vtipe[18] = 1;
  strcpy(var_ids[19].ids,"qq");   // Quick flow
  vtipe[19] = 1;
  strcpy(var_ids[20].ids,"qi");   // Inter flow
  vtipe[20] = 1;
  strcpy(var_ids[21].ids,"qlz");  // Base flow
  vtipe[21] = 1;
  
  // Auxiliar to read integer
  char caux[15];
  // Auxiliar
  aux_ids *var_ids_aux = (aux_ids*) malloc(modelvars.nvars * sizeof(aux_ids));
  // Allocate vars_info
  modelvars.info = (vars_info*) malloc(modelvars.nvars * sizeof(vars_info));
  for (int i = 0; i < modelvars.nvars; i++){
    // Fill auxiliar
    strcpy(var_ids_aux[i].ids,var_ids[i].ids);
    // Read variables
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_units"), "%s", modelvars.info[i].units);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    if (strcmp(modelvars.info[i].units, "") == 0 ){
      strcpy(modelvars.info[i].units, ""); //hacer esto??
    }
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_location"), "%s", modelvars.info[i].location);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    // Variable known declaration
    strcpy(modelvars.info[i].name,var_ids_aux[i].ids);
    modelvars.info[i].indx = i;
    modelvars.info[i].tipe = vtipe[i];
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_timetipe"), "%s", caux);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    modelvars.info[i].timetipe = atoi(caux);
  }
}

void allocate_hbv(model_vars modelvars){
  // Allocate parametes, state and flows matrix
  for (int i = 0; i < modelvars.nvars; i++){
    modelvars.info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt);
  }
}

void read_hbv_netcdf(model_vars modelvars, size_t *start, size_t *count){
  // Read netvariables from location, setting default value if it's NULL
  int error;
  for (int i = 0; i < modelvars.nvars; i++){
    if (strcmp(modelvars.info[i].location, "") == 0 ){
      // Set default value
      for (int j = 0; j < domain.ntgt; j++){
        modelvars.info[i].vars[j] = 0;
      }
    }
    else {
      // Read netcdf
      error = read_netcdf(modelvars.info[i].location, modelvars.info[i].name, start, count, &modelvars.info[i].vars[0]);
      if (error > 0){
        printf("Error reading %s file \n", modelvars.info[i].location);
        exit(1);
      }
    }
  }
}

void free_hbv(model_vars modelvars){
  // Free HBV parameters, states and flows
  for (int i = 0; i < modelvars.nvars; i++){
    free(modelvars.info[i].vars);
  }
}

void update_hbv(model_vars modelvars){
  // Update HBV parameters, states and flows
  size_t start[] = {0, 0, 0};
  size_t count[] = {1, domain.nx, domain.ny};
  for (int i = 0; i < forcing.nvars; i++){
    read_hbv_netcdf(&modelvars, start, count);
  }
}

void compute_hbv(model_vars modelvars, model_vars forcing){
  // Run HBV model in C on one time
  float faux[2];
  int pp_i    = getindx(forcing, "pp");
  int etp_i   = getindx(forcing, "etp");
  int qin_i   = getindx(modelvars, "qin");
  int icf_i   = getindx(modelvars, "icf");
  int sm_i    = getindx(modelvars, "sm");
  int qdr_i   = getindx(modelvars, "qdr");
  int fc_i    = getindx(modelvars, "fc");
  int inet_i  = getindx(modelvars, "inet");
  int sp_i    = getindx(modelvars, "sp");
  int beta_i  = getindx(modelvars, "beta");
  int etr_i   = getindx(modelvars, "etr");
  int lp_i    = getindx(modelvars, "lp");
  int vlz_i   = getindx(modelvars, "vlz");
  int perc_i  = getindx(modelvars, "perc");
  int vuz_i   = getindx(modelvars, "vuz");
  int qcf_i   = getindx(modelvars, "qcf");
  int cflux_i = getindx(modelvars, "cflux");
  int qq_i    = getindx(modelvars, "qq");
  int kq_i    = getindx(modelvars, "kq");
  int uzl_i   = getindx(modelvars, "uzl");
  int qi_i    = getindx(modelvars, "qi");
  int ki_i    = getindx(modelvars, "ki");
  int qlz_i   = getindx(modelvars, "qlz");
  int klz_i   = getindx(modelvars, "klz");
  int q_i     = getindx(modelvars, "q");
  for (int i = 0; i < domain.ntgt; i++){
    // In flows
    faux[0] = forcing.info[pp_i].vars[i] - modelvars.info[icf_i].vars[i];
    faux[1] = 0.f;
    modelvars.info[qin_i].vars[i]  = max(faux, 2);
    faux[0] = modelvars.info[icf_i].vars[i];
    faux[1] = forcing.info[etp_i].vars[i];
    modelvars.info[etr_i].vars[i]  = min(faux, 2);
    // State variables
    modelvars.info[sm_i].vars[i]   = modelvars.info[sm_i].vars[i] + modelvars.info[qin_i].vars[i];
    faux[0] = modelvars.info[sm_i].vars[i] - modelvars.info[fc_i].vars[i];
    faux[1] = 0.f;
    modelvars.info[qdr_i].vars[i]  = max(faux, 2);
    modelvars.info[sm_i].vars[i]   = modelvars.info[sm_i].vars[i] - modelvars.info[qdr_i].vars[i];
    modelvars.info[inet_i].vars[i] = modelvars.info[qin_i].vars[i] - modelvars.info[qdr_i].vars[i];
    modelvars.info[sp_i].vars[i]   = pow(modelvars.info[sm_i].vars[i] / modelvars.info[fc_i].vars[i], modelvars.info[beta_i].vars[i]) * modelvars.info[inet_i].vars[i];
    modelvars.info[sm_i].vars[i]   = modelvars.info[sm_i].vars[i] - modelvars.info[sp_i].vars[i];
    // Evapotranspirations
    forcing.info[etp_i].vars[i]    = forcing.info[etp_i].vars[i] - modelvars.info[etr_i].vars[i];
    faux[0] = modelvars.info[sm_i].vars[i] * forcing.info[etp_i].vars[i] / (modelvars.info[lp_i].vars[i] * modelvars.info[fc_i].vars[i]);
    faux[1] = forcing.info[etp_i].vars[i];
    faux[0] = min(faux, 2);
    faux[1] = modelvars.info[sm_i].vars[i];
    modelvars.info[etr_i].vars[i]  = min(faux, 2);
    modelvars.info[sm_i].vars[i]   = modelvars.info[sm_i].vars[i] - modelvars.info[etr_i].vars[i];
    // Volume states
    faux[0] = modelvars.info[perc_i].vars[i];
    faux[1] = modelvars.info[qdr_i].vars[i] + modelvars.info[sp_i].vars[i];
    modelvars.info[vlz_i].vars[i]  = modelvars.info[vlz_i].vars[i] + min(faux, 2);
    faux[0] = 0.f;
    faux[1] = modelvars.info[qdr_i].vars[i] + modelvars.info[sp_i].vars[i] - modelvars.info[perc_i].vars[i];
    modelvars.info[vuz_i].vars[i]  = modelvars.info[vuz_i].vars[i] + max(faux, 2);
    // Capillar flow
    modelvars.info[qcf_i].vars[i]  = modelvars.info[cflux_i].vars[i] * (modelvars.info[fc_i].vars[i] - modelvars.info[sm_i].vars[i]) / modelvars.info[fc_i].vars[i];
    faux[0] = modelvars.info[vuz_i].vars[i];
    faux[1] = modelvars.info[qcf_i].vars[i];
    modelvars.info[sm_i].vars[i]   = modelvars.info[sm_i].vars[i] + min(faux, 2);
    faux[0] = modelvars.info[vuz_i].vars[i] - modelvars.info[qcf_i].vars[i];
    faux[1] = 0.f;
    modelvars.info[vuz_i].vars[i]  = max(faux, 2);
    // Quick and inter flow
    faux[0] = modelvars.info[kq_i].vars[i] * (modelvars.info[vuz_i].vars[i] - modelvars.info[uzl_i].vars[i]);
    faux[1] = 2;
    modelvars.info[qq_i].vars[i]   = max(faux, 2);
    faux[0] = modelvars.info[uzl_i].vars[i];
    faux[1] = modelvars.info[vuz_i].vars[i];
    modelvars.info[qi_i].vars[i]   = modelvars.info[ki_i].vars[i] * min(faux, 2);
    // Base flow
    modelvars.info[qlz_i].vars[i]  = modelvars.info[klz_i].vars[i] * modelvars.info[vlz_i].vars[i];
    // Final flow
    modelvars.info[q_i].vars[i]    = modelvars.info[qlz_i].vars[i] + modelvars.info[qi_i].vars[i] + modelvars.info[qq_i].vars[i];
  }
}

void compute_hbv_cuda(model_vars modelvars, model_vars forcing){
  // Run HBV model in CUDA on one time
}


