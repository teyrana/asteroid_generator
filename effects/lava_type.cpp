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

#include "volcano_effect.hpp"
using namespace MeshGen;

// ====== // ======  LavaType.cpp // ====== // ======

const char* LavaType::getMagmaTypeName(composition_t type){
	return getLavaTypeName(type);
}

const char* LavaType::getLavaTypeName(composition_t type){
	static char* toret=0;
	if(0!=toret){
		delete toret; }

	switch(type){
	case LAVA_FELSIC: toret = strdup("Rhyolitic"); break;
	default:
	case LAVA_ANDESITIC: toret = strdup("Andesitic"); break;
	case LAVA_MAFIC: toret = strdup("Basaltic"); break;
	}
	return toret;
}

LavaType* LavaType::setType(composition_t type){
	switch(type){
	default:
	case LAVA_FELSIC: return setFelsicArchetype(); break;
	case LAVA_ANDESITIC: return setAndesiticArchetype(); break;
	case LAVA_MAFIC: return setMaficArchetype(); break;
	}
}

LavaType* LavaType::setFelsicArchetype(){
        // Felsic (aka Rhyolitic)
        // ~70% silica; ; ~2% Fe,Mg
        // Temp: <900 C
        // Viscosity: High  (10^3-10^11 Pas)
        // Behavior: explosive | effusive
        // tends to form stratovolcanes, lava domes
        // Dry rhyolite at 900°C: viscosity= 100 MPaS
        // Rhyolite w/ 10% dissolved water: (900 C?), viscosity 800 PaS

        composition = LAVA_FELSIC;
        frac_silica_u=0.7f;
        frac_crystal_max_u=0.5f;
        temperature_exit_C = 900;
        temperature_solidus_C = 900; //1200?
        viscosity_exit_pas=800;
        return this;
}

LavaType* LavaType::setAndesiticArchetype(){
        // Intermediate (aka andesitic)
        // ~63% silica; ~3% Fe,Mg
        // Temp:  ~1000 C
        // Viscosity: intermediate (10^5-10^7 Pas)
        // Behavior: explosive | effusive
        // tends to form "andesitic" volcanes above subduction zones.
        // usually a mixture (magma + other).

        composition = LAVA_ANDESITIC;
        frac_silica_u = 0.63f;
        frac_crystal_max_u = 0.5f;
        temperature_exit_C = 1000;
        temperature_solidus_C = 900; //1200?
        viscosity_exit_pas=600000;
        return this;
}

LavaType* LavaType::setMaficArchetype(){
        // Mafic (aka basaltic)
        // <50% silica, ~10% Fe,Mg
        // Temp: 950-1300 C  (hotter than felsic lavas)
        // Viscosity: Low (10^2-10^3 Pas)
        // Behavior: Gentle
        // basalt at 1200°C: viscosity= 50 PaS
        // (higher concentrations of Mg, Fe, or basalt

        composition = LAVA_MAFIC;
        frac_silica_u=0.5f;
        frac_crystal_max_u=0.5f;
        temperature_exit_C = 1200;
        temperature_solidus_C = 900; //1200?
        viscosity_exit_pas= 50;
        return this;
}
