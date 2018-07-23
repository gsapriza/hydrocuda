
/**************
* HydroCuda model
*
* Set of auxiliar functions simulate hydrological models response
* using c and cuda
***************/

#include <netcdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hydrocuda.h"

int getindx(model_vars *mv, char *c){
  // Get index of different variables
  int i;
  for ( i = 0; i < mv->nvars; i++){
    if (strcmp( c, mv->info[i].name) == 0){
      i = mv->info[i].indx;
      break;
    }
  }
  return i;
}


int read_netcdf(char *location, char *name, size_t *start, size_t *count, float *var){
  // Reaf NetCDF files
  int nc_id, nc_error, var_id;
  nc_error = nc_open(location, NC_NOWRITE, &nc_id);
  nc_error = nc_inq_varid(nc_id, name, &var_id);
  nc_error = nc_get_vara_float(nc_id, var_id, start, count, var);
  return nc_error;
}


float min(float *a, int b){
  // Gets the minimum of a vector
  float val = a[0];
  for (int i = 1; i<b; i++){
	  if (val>a[i]){
	    val = a[i];
	  }
  }
  return val;
}


float max(float *a, int b){
  // Gets the maximum of a vector
  float val = a[0];
  for (int i = 1; i<b; i++){
	  if (val<a[i]){
	    val = a[i];
	  }
  }
  return val;
}

