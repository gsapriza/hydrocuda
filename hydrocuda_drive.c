/**************
* HydroCuda model
*
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/

#include <stdio.h>
#include <stdlib.h>
#include "hydrocuda.h"

// Global variables
model_option options;
model_domain domain;
model_time modeltime;

int main (int argc, char *argv[])
{
    // Variable declraration
    model_vars forcing;
    model_vars modelvars;

    // Model Initialization
    if(argc < 2){
      printf("Usage : ./a.out <filename>");
      exit(0);
    }
    options.config = ini_load(argv[1]);

    init_modeloptions();
    init_domain();
    init_times();

    //
    init_hbv(&modelvars);
    init_forcing(&forcing); //init forcing
    //Aca es donde iteramos por bloques llamando a la f
    // evaluate_model()
    // for(itblock = 0; itblock<nblock,itblock++){
    //     //esta funcion tiene que ser la que se aplica cuda
    //     compute_waterbalance();
    //     compute_transit();
    //     //Leemos el siguient bloque de datos temporales
    //     update_forcing();
    // }

    ini_free(options.config);
    return 0;
}
