//The MIT License (MIT)
//
//Copyright (c) <2015>
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


#include "Asteroid.hpp"
#include "effects/bombardment_effect.hpp"

using namespace MeshGen;

std::string Asteroid::mineral_names[]={ "Olivine","Ammonia Ice","Ni-Fe","Magnesium-Silicate","Pyroxene","Water Ice","Methane"};
char Asteroid::type_letters[NUM_ASTEROID_TYPES] = {'A','C','D','E','I','M','P','R','S'};
std::string Asteroid::type_descriptions[NUM_ASTEROID_TYPES]={
    "A-type- <1% contain much olivine, (MgFe)2SiO4 and a gemstone. igneous asteroid.",
    "C-type asteroids - 75% of known asteroids. The C stands for \"carbonaceous.\" They are extremely dark (albedo 0.03), similar to carbonaceous chondrite meteorites. These asteroids have approximately the same chemical composition as the Sun, minus hydrogen, helium and other volatiles. The spectra of these asteroids have relatively blue colors and are fairly flat and featureless.",
    "D-Type: redder than P-type",
    "E-Type: contain much Enstatite.",
    "I-Type: Icy: comets: water, dust, rock, frozen gases such as ammonia, methane",
    "M-type asteroids - This class includes most of the rest of the asteroids. The M stands for metallic; they are bright asteroids (albedo .10-.18), made of pure nickel-iron. There are also a number of rarer asteroid types, the number of types continuing to grow as more asteroids are studied.",
    "P-type: reddish, unknown composition",
    "R-type asteroids - The R stands for red.",
    "S-type asteroids - This type of asteroids represents about 17% of known asteroids. The S stands for silicaceous. They are relatively bright objects (albedo .10-.22). They have a metallic composition (mainly nickel, iron and magnesium-silicates). The spectra of this class are reddish and similar to those of stony-iron meteorites.  Contain Pyroxene, Olivine. "
};

Asteroid::Asteroid(){}

void Asteroid::init(){

}

void Asteroid::generate(){

    //load_sphere_320();
    //load_sphere_81920();
    dump_summary( stdout);

    // ====== apply really cool effects  ======
    
    BombardmentEffect bomb;
    bomb.setMesh(this);
    bomb.ApplyMeteorImpacts( 1, 10, 1000);

    //bomb.applyEffect(1,10,1000);
     
    return;
}

void Asteroid::apply_simplex_effect(){
    //double theta_r;
    //double phi_r;

    // double theta_p = theta_r / M_2PI;
    // double phi_p = phi_r / M_2PI;
    
    // parameterize theta and phi to [0,1], and use this as input to
    // the perlin / simplex noise functions from the documentation directory....
    

}
