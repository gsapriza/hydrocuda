/**************
* HydroCuda model
*
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/

// General Program Options

typedef struct {
  char  domainModel[8];//*
  char  meteoModel[5];//*
  int  istimeblock;
} model_option;

// General Model domain discretization
typedef struct{
  int   ntgt;    // number of unique space domains in case of gridcells = nx*ny
  int   nx;      // number of columns
  int   ny;      // number of rows
  float dx;      // Space discretization x direction
  float dy;      // Space discretization y direction
} model_domain;


// Model time discretization
typedef struct{
    char freq;         // Time frequency
    int nt;            // Total number of time steps
    int start_second;  // second start time
    int start_min;     // minutes start time
    int start_hour;    // hour start time
    int start_day;     // day start time
    int start_month;   // month start time
    int start_year;    // year start time
    int end_second;    // second end time
    int end_min;       // minutes end time
    int end_hour;      // hour end time
    int end_day;       // day end time
    int end_month;     // month end time
    int end_year;      // year end time
    int timestep;      // time step in seconds
    int ntblock;       // number of block time
    int *datetime[];   // all dates time
} model_time;

//We define model topology
typedef struct{
  float *area[]; // Area of each grid cell
  int   *ldd[];  // Directions
} model_topology;

// Parameter definition for hbv
// Model class acá agregamos lo de las clasess de C++
typedef struct {
    float *field_capacity[];
    float *kquick[];
} param_hbv;

typedef struct {
  float *soilmoist[];
  float *gw1[];
  float *gw2[];
} state_hbv;

typedef struct {
  float *qsurf[]; // Surface runoff generation
  float *qintf[]; // Inferflow runoff generation
  float *qbase[]; //
} flux_hbv;

typedef struct {
  float *precip[];  // Precipitation
  float *pet[];     // Potential Evapotranspiration
  float *tair[];    // Air Temperature
  int    nmeteo;    // Number of meteorological variables to be used
  meteo_info   *info[]; // Variables id to be initialized
} meteo_forcing;

typedef struct{
  char units[10];
  char name[15];
  char longname[25];
} meteo_info;

//Structures declaration
model_options optns;
model_domain dom;
model_time times;
model_topology topo*;
meteo_forcing forcing*;
meteo_info info;
//no se si ya definirla aca
param_hbv params; // agregar resto de parametros
state_hbv state; // agregar resto de estados
flux_hbv flux; // agregar resto de flujos

void init_modeloptions()
void init_domain(*model_domain)
//Function declaration asociated with meteorological forcing
void init_forcing(*meteo_forcing)
void allocate_forcing(*meteo_forcing)
void read_forcing_netdf4()
void update_forcing()
void free_forcing(*meteo_forcing)
