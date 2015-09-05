#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <cfloat>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdint.h>
#include <sstream>
#include <string>

#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <queue>


// ===================== GL Math (GLM) library // =====================
//#define GLM_MESSAGES  // produces VERBOSE messages
#define GLM_FORCE_RADIANS // required on DARWIN to prevent the use of deprecated functions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace glm;


// ===================== Logging // =====================
#define LOGGING

#ifdef LOGGING
extern FILE* logfile;
#endif


// ====== =======  // ====== =======  OS Specific crap // ====== =======// ====== =======
// ====== =======
#ifdef __LINUX__


#endif //__LINUX__


// ====== =======
#ifdef __MAC_OSX__
//...
//#include <gl\GL.h>  // windows
#endif //#ifdef __MAC_OSX__

// ====== =======
#ifdef __WINDOWS_MSVC__
//#define _USE_MATH_DEFINES // works for MSVC
#define strdup _strdup
#pragma comment(lib, "opengl32.lib")
// If you get compiler errors pointing to gl.h, this is because there are some things like WINGDI which are used in gl.h
// but are only defined in some other header files. Include windows.h before including gl.h
// If you have link errors, then you need to figure out how to link with your specific compiler/IDE.
// NOTE: glload library handles this. (at least on windows 7)
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "glfwD.lib")

#ifdef QT_4XX_
#pragma comment(lib, "QtCore4.lib")
#pragma comment(lib, "QtGui4.lib")
#pragma comment(lib, "QtOpenGL4.lib")
#endif

#ifdef QT_5XX_
#pragma comment(lib, "Qt5Core.lib")
#pragma comment(lib, "Qt5Gui.lib")
#pragma comment(lib, "Qt5OpenGL.lib")
#pragma comment(lib, "Qt5Widgets.lib")
#endif

// #pragma warning( disable: 4996)
// float-double auto-cast warnings
#pragma warning( disable: 4244)
//#pragma warning( disable: 4305)

#endif // __WINDOWS_MSVC__

// ====== =======
#ifdef __WINDOWS_MINGW__

#endif // #ifdef__WINDOWS_MINGW__



#endif
