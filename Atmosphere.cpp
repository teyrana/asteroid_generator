//The MIT License (MIT)
//
//Copyright (c) <2012>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this 
// software and associated documentation files (the "Software"), to deal in the Software 
// without restriction, including without limitation the rights to use, copy, modify, 
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so, subject to the following 
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// =====================
// Author:
//       Daniel Williams
//

#include "Atmosphere.hpp"
using namespace MeshGen;

const float Atmosphere::density_air_standard_kgm3=1.225f; // units: kg/m3
const float Atmosphere::gravity_earth_standard_mss= 9.801f; // units: m/s/s
const float Atmosphere::pressure_earth_standard_pa = 101325.0f; // units: Pa
const float Atmosphere::specific_gas_constant_air=287.058f;  // units: J/kg/K
const float Atmosphere::temperature_zero_C_K = 273.15f; // units: degrees kelvin

// ====== =======  // ====== =======  Atmosphere Methods // ====== =======// ====== =======
Atmosphere::Atmosphere(){  setDefaultClimate(); }
Atmosphere::~Atmosphere(){}

float Atmosphere::calculate_evaporation_myr(float pressure, float temperature, float airflow, float humidity){
    // validation values:  should be 0.762 to 3 meters / year
    //const float vapor_pressure_water_kPa = 2300; // units: Pa @ STP
    const float k_evap = 4.0;
    
    // ambient_partial_pressure;
    float delta_pressure = (4-expf(- airflow/80) - log(pressure/pressure_earth_standard_pa));
    evaporation_myr= -k_evap*delta_pressure *exp(9-3500/(temperature+temperature_zero_C_K));
    evaporation_myr += 0*humidity; // not sure how to apply humidity
    
    return evaporation_myr;
}

float Atmosphere::calculate_pressure_pa(float rho, float temp ){
    float R = specific_gas_constant_air;
    // P = \rho R T   (=== PV = nRT)
	pressure_pa = rho * R * (temp+temperature_zero_C_K);
	return pressure_pa;
}

// ====== =======  set Preset Climates: // ====== =======
const char * Atmosphere::get_climate_t_names(climate_t clim_type){
	static char* toret=0;
	if(0!=toret){
		delete toret; }
	switch(clim_type){
	case CLIMATE_ARCTIC: toret = strdup("Arctic"); break;
	case CLIMATE_ASTEROID: toret = strdup("Asteroid"); break;
	default:
	case CLIMATE_CUSTOM: toret = strdup("Custom"); break;
	case CLIMATE_DEFAULT: toret = strdup("Default"); break;
	case CLIMATE_DESERT: toret = strdup("Desert"); break;
	case CLIMATE_JUNGLE: toret = strdup("Jungle"); break;
	case CLIMATE_SAVANNA: toret = strdup("Savanna"); break;
	case CLIMATE_TEMPERATE: toret = strdup("Temperate"); break;
	case CLIMATE_TEST: toret = strdup("Test"); break;
	case CLIMATE_TUNDRA: toret = strdup("Tundra"); break;
	case CLIMATE_WATERWORLD: toret = strdup("Waterworld"); break;
	}
	return toret;
}

// ====== =======  set Preset Climates: // ====== =======
void Atmosphere::set(climate_t clim){
	climate_here = clim;
	switch(climate_here){
	case CLIMATE_ARCTIC: setArcticClimate(); break;
	case CLIMATE_ASTEROID: setAsteroidClimate(); break;
	default:  // fall through to custom
	case CLIMATE_CUSTOM: break; // do nothing.
	case CLIMATE_DEFAULT: setDefaultClimate(); break; // already set.
	case CLIMATE_DESERT: setDesertClimate(); break;
	case CLIMATE_JUNGLE: setJungleClimate(); break;
	case CLIMATE_SAVANNA: setSavannaClimate(); break;
	case CLIMATE_TEMPERATE: setTemperateClimate(); break;
	case CLIMATE_TEST: setTestClimate(); break;
	case CLIMATE_TUNDRA: setTundraClimate(); break;
	case CLIMATE_WATERWORLD: setWaterworldClimate(); break;
	}
	return;
}

void Atmosphere::setArcticClimate(){
	climate_here = CLIMATE_ARCTIC;
    //precipitation_myr = 0.8f;
    temperature_C = -4.0f;
}


void Atmosphere::setAsteroidClimate(){
	climate_here = CLIMATE_ASTEROID;
    density_kgm3=0.0;
    gravity_mss=1.0;
    precipitation_myr=0;
    temperature_C=0;
}

void Atmosphere::setDefaultClimate(){
	climate_here = CLIMATE_DEFAULT;
    density_kgm3=density_air_standard_kgm3;
    evaporation_myr=0.0f;
    gravity_mss=9.8f;   // earth normal
	altitude_m = 100.0f;
    precipitation_myr=1.2f;
	pressure_pa=0;
    temperature_C = 12.0f;
	windflow_m3s=200;

	calculate_pressure_pa(density_air_standard_kgm3, 15);
	calculate_evaporation_myr( pressure_pa, temperature_C, windflow_m3s, precipitation_myr);
}

void Atmosphere::setDesertClimate(){
	climate_here = CLIMATE_DESERT;
    //evaporation_myr=-0.3f;  // empirical
    precipitation_myr=0.1f;
    temperature_C = 20.0f;
}

void Atmosphere::setCustomClimate(){
	climate_here = CLIMATE_CUSTOM;
}

void Atmosphere::setJungleClimate(){
    climate_here = CLIMATE_JUNGLE;
	precipitation_myr = 2.0f;
    temperature_C = 18.0f;
}

void Atmosphere::setSavannaClimate(){
	climate_here = CLIMATE_SAVANNA;
    precipitation_myr = 0.4f;
    temperature_C = 18;
}

void Atmosphere::setTemperateClimate(){
	climate_here = CLIMATE_TEMPERATE;
    precipitation_myr= 1.2f;
    temperature_C= 8.0f;
}

void Atmosphere::setTestClimate(){
	climate_here = CLIMATE_TEST;
}

void Atmosphere::setTundraClimate(){
	climate_here = CLIMATE_TUNDRA;
    altitude_m = -1000.0f;
    precipitation_myr = 0.8f;
    temperature_C = 0.0f;
}

void Atmosphere::setWaterworldClimate(){
	climate_here = CLIMATE_WATERWORLD;
    altitude_m = -1000.0f;
}

void Atmosphere::printAtmosphericParameters(){
	fprintf(logfile, "Atmospheric Parameters\n");
	fprintf(logfile, "     Set Climate Type:        %s \n", get_climate_t_names(climate_here));
	fprintf(logfile, "     Altitude:                %g m\n", altitude_m);
	fprintf(logfile, "     Density:                 %g kg/m3\n", density_kgm3);
	fprintf(logfile, "     Evaporation:             %g m/yr \n", evaporation_myr);
	fprintf(logfile, "     Gravity:                 %g m/s^2 \n", gravity_mss);
	fprintf(logfile, "     Precipitation:           %g m/yr\n", precipitation_myr);
	fprintf(logfile, "     Pressure:                %g Atm \n", pressure_pa/pressure_earth_standard_pa);
	fprintf(logfile, "     Temperature:             %g C \n", temperature_C);
	fprintf(logfile, "\n");
}
