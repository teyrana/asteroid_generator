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

#include "common.hpp"
using namespace std;

#include "Terrain.hpp"
#include "asteroid.hpp"

#include "effects/simplex_effect.hpp"
#include "effects/bombardment_effect.hpp"
using namespace MeshGen;

FILE* logfile;

extern "C" {

    void initialize_logging();
    void shutdown_logging();

    void initialize_logging(){
#ifdef LOGGING
	time_t rawtime;
	char* time_str=NULL;
	logfile=0;
	
	time(&rawtime);

#ifdef __WINDOWS_MSVC__
	const int time_str_len=32;
	fopen_s(&logfile, "meshgen.log", "w");
	time_str=(char*)malloc(time_str_len);
	ctime_s(time_str, time_str_len, &rawtime);
	time_str[strlen(time_str)-1]='\0';  // strip the trailing newline
	fprintf(stderr, "====== Log Started: %s ======\n", time_str);
	fprintf(logfile, "====== Log Started: %s ======\n", time_str );
	free(time_str);
#else
	logfile = fopen("meshgen.log", "w");
	time_str = ctime( &rawtime);
	time_str[strlen(time_str)-1]='\0';  // strip the trailing newline
	fprintf(stderr, "====== Log Started: %s ======\n", time_str );
	fprintf(logfile, "====== Log Started: %s ======\n", time_str );
#endif // #ifndef __WINDOWS_MSVC__
#endif  // #ifdef LOGGING
    }

    void shutdown_logging(){
	time_t rawtime;
	char* time_str=NULL;
	
	time(&rawtime);
	time_str = ctime( &rawtime);
	time_str[strlen(time_str)-1]='\0';  // strip the trailing newline

	fprintf(stderr, "====== Finished: %s ======\n", time_str );
	fprintf(logfile, "====== Finished: %s ======\n", time_str );
	fclose(logfile);

    }

    int main(int argc, char *argv[]) {

	initialize_logging();

	char* mesh_filename=NULL;
	if ( argc > 1 ){
	    mesh_filename = argv[1];
	}else{
	    mesh_filename = strdup("./output.obj");
	}
	
	const bool generate_grid=false;
	const bool generate_asteroid=true;
	const bool generate_simplex_hills = false; //false;
	const bool apply_impacts = true;

	Mesh* gen= new Terrain();

	if (generate_grid){
	    // 1000^2 takes 30 second to render :P
	    gen->load_grid( 200, 200, 250);
	    //gen->load_grid( 80, 80, 250);
	    gen->dump_summary( stderr);
	}
	if (generate_asteroid){
	    gen->load_sphere_81920();
	    gen->set_scale( 1000 );
	    fprintf(stderr, "..>> Asteroid loaded.\n");

	    SimplexEffect simplex;
	    simplex.setMesh( gen);
	    simplex.set_persistence( 0.95);
	    simplex.set_frequency( 0.28/gen->scale);
	    simplex.apply_effect( 2, 0.8*gen->scale, 6*gen->scale);
	    

	    fprintf(stderr, "..>> Finished Generating Asteroid\n");
	}

	if (generate_simplex_hills){	    
	    gen->load_grid( 200, 200, 250);
	    SimplexEffect simplex;
	    simplex.setMesh( gen);
	    simplex.set_persistence( 0.8);
	    simplex.set_frequency( 0.95/gen->scale);
	    simplex.apply_effect( 4, 0, 50);
	}
	if (apply_impacts){
	    //((Terrain*)gen)->generate_topology_cliff( 23);

	    BombardmentEffect bomb;
	    bomb.setMesh( gen);
	    fprintf(stderr, "    set effect mesh.\n");

	    // ApplyMeteorImpacts
	    //bomb.apply_effect( 1, 10, 1000);
	    //bomb.apply_effect( 1, 0.1, 0.25);
	    bomb.apply_effect( 1000, 0.9, 23);
	    bomb.apply_effect( 540, 0.1, 12);
	    fprintf(stderr, "    Effect applied.\n");
	}


	// ************************************************
	
	// // for generating meshes...
	// gen->load_icosahedron();
	// gen->center_mass();
	// gen->dump_summary( stderr);

	// fprintf( stderr, ">> Applying subdivision...\n");
	// gen->subdivide( 3);
	// gen->normalize_vn();

	// fprintf( stderr, ">> Consolidating Vertices...\n");
	// gen->consolidate_vertices();
	// gen->dump_summary( stderr);

	// load cached mesh
	
	// fprintf( logfile, "  >> terrain initialized.\n");
	// fprintf( stderr, "  >> terrain initialized.\n");

	gen->dump_summary( stderr);
	fprintf(stderr, "    Summary Dumped.\n");
	//gen->write_to_header( "grid" );
	gen->write_to_obj_vf( mesh_filename);
	fprintf(stderr, "    File written.\n");
	return 0;
    }
    
}
