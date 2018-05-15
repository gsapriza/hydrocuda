/**************
* HydroCuda model
*
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/

#include "hydrocuda.h"
#include <stdio.h>
#include <stdlib.h>
//global variables

model_option options;
model_domain domain;

int main (int argc, char *argv[])
{
    // Variable declraration
    meteo_forcing *forcing; //Declare as pointer forcing
    model_time *modeltime; //tiene que declararse aca??
    // Model Initialization

    if(argc < 2){
      printf("Usage : ./a.out <filename>");
      exit(0);
    }
    options.config=ini_load(argv[1]);

    init_modeloptions();
    init_domain();
    // set_options(in_file);
    // init_params();
    // init_states();
    init_times();
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
