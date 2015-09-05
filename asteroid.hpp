#ifndef _ASTEROID_CLASS_
#define _ASTEROID_CLASS_

#include "common.hpp"
#include "Mesh.hpp"

namespace MeshGen {

    class Asteroid: public Mesh {
    public:
	static const uint NUM_MINERALS = 7;
	static std::string mineral_names[NUM_MINERALS];
	static const uint NUM_ASTEROID_TYPES = 9;
	static char type_letters[NUM_ASTEROID_TYPES];
	static std::string type_descriptions[NUM_ASTEROID_TYPES];
        /* 
	   A-type- <1% contain much olivine, (MgFe)2SiO4 and a gemstone. igneous asteroid. 
	   C-type asteroids - 75% of known asteroids. The C stands for "carbonaceous." They are extremely dark (albedo 0.03), similar to carbonaceous chondrite meteorites. These asteroids have approximately the same chemical composition as the Sun, minus hydrogen, helium and other volatiles. The spectra of these asteroids have relatively blue colors and are fairly flat and featureless.   
	   D-Type: redder than P-type
	   E-Type: contain much Enstatite. 
	   M-type asteroids - This class includes most of the rest of the asteroids. The M stands for metallic; they are bright asteroids (albedo .10-.18), made of pure nickel-iron. There are also a number of rarer asteroid types, the number of types continuing to grow as more asteroids are studied.     
	   P-type: reddish, unknown composition
	   R-type asteroids - The R stands for red.     
	   S-type asteroids - This type of asteroids represents about 17% of known asteroids. The S stands for silicaceous. They are relatively bright objects (albedo .10-.22). They have a metallic composition (mainly nickel, iron and magnesium-silicates). The spectra of this class are reddish and similar to those of stony-iron meteorites.  Contain Pyroxene, Olivine. 
	   
	   I-Type: Icy: comets: water, dust, rock, frozen gases such as ammonia, methane
	*/
	
    protected:
	char type;
	int mass;
	int mean_radius;
	float albedo;
	int mineral_type;
    public:
	Asteroid();
	void apply_simplex_effect();
	void init();
	void generate();

    };
    
}
#endif
