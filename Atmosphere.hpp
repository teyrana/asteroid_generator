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


#ifndef __ATMOSPHERE_HPP__
#define __ATMOSPHERE_HPP__
#include "common.hpp"

// ====== =======  // ====== =======  Atmosphere.hpp // ====== =======// ====== =======
namespace MeshGen{

    class Atmosphere {
    public:
	enum climate_t {
	    CLIMATE_ARCTIC,
	    CLIMATE_ASTEROID,
	    CLIMATE_CUSTOM,  // everything else
	    CLIMATE_DEFAULT,
	    CLIMATE_DESERT,
	    CLIMATE_JUNGLE,  // == rainforest, monsoon
	    CLIMATE_SAVANNA,
	    CLIMATE_TEMPERATE,
	    CLIMATE_TEST,
	    CLIMATE_TUNDRA, // == alpine, steppe, steppe
	    CLIMATE_WATERWORLD
	};
	climate_t climate_here;
    
	// altitude terrain is built from:
	// minimum altitude of terrain.
	// n.b.: 0:   sea level
	//      <0:   underwater
	//    near 0: shoreline
	// units: m
	float altitude_m;
	float height_scale_m;

	// density at sea level
	// units: kg/m^3
	// 1.2 kg/m3 = 0.0012 g/cc (at standard temperature and pressure (@STP))
	static const float density_air_standard_kgm3;
	float density_kgm3;

	// how much water (or other fluid evaporates)
	// units: m/yr
	float evaporation_myr;
	
	// acceleration due to gravity
	// units:m/s^2
	// == 1g == earth standard gravity
	static const float gravity_earth_standard_mss;
	float gravity_mss;

	// mean yearly precipitation
	// 1200 mm/year is roughly average for temperate climes
	// units: m/year
	float precipitation_myr;
	// a measure of how much the rain is spread out...
	// 1 is all at once (flash flood)
	// 0 is completely spread out.
	float precip_distribution;

	// derived.
	// units: 1 Pa = 1 kg/m/s^2
	// 1 atm = 101.325 kPa (at standard temperature and pressure (@STP))
	// == earth standard pressure at sea level
	static const float pressure_earth_standard_pa; 
	float pressure_pa;

	// constant
	// units: J/(kg degK)
	static const float specific_gas_constant_air;

	// mean yearly temperature
	// units: degrees Celsius
	float temperature_C;
	// 0 deg Celsius = 273.15 deg Kelvin
	static const float temperature_zero_C_K;
	//float temperature_variance_dc;

	float windflow_m3s;
	// ====== =======  Calculate Methods: // ====== =======
    public:
	Atmosphere();
	~Atmosphere();

	// out units:  meters / year
	float calculate_evaporation_myr(float pressure, float temperature, float airflow, float humidity);

	// out units: Pa
	float calculate_pressure_pa(float rho, float temp );

	// ====== =======  Get Methods // ====== =======
	static const char* get_climate_t_names(climate_t clim_type);
	climate_t get_climate(){return climate_here;}

	// ====== =======  Set Methods // ====== =======
	void set(climate_t clim);
	void setArcticClimate();
	void setAsteroidClimate();
	void setDefaultClimate();
	void setDesertClimate();
	void setCustomClimate();
	void setJungleClimate();
	void setSavannaClimate();
	void setTemperateClimate();
	void setTestClimate();
	void setTundraClimate();
	void setWaterworldClimate();
    
	void printAtmosphericParameters();

    }; // class

} // namespace

#endif // #ifndef __ATMOSPHERE_HPP__
