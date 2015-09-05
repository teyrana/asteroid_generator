# *nix makefile
# procedural project

# ==== ==== ==== ==== ==== ==== ==== ====

# define locations
DIST_DIR        = .
DATA_DIR        = .
CPP_SOURCE_DIR  = .
BUILD_DIR       = build
MESH_DIR        = .

# files
SRC_EXT         =cpp
HDR_EXT         =hpp
SOURCE_LIST     =$(shell find $(CPP_SOURCE_DIR) -type f -name '*.$(SRC_EXT)')
HEADER_LIST     =$(shell find $(CPP_SOURCE_DIR) -type f -name '*.$(HDR_EXT)')
OBJ_LIST        =$(SOURCE_LIST:$(CPP_SOURCE_DIR)/%.$(SRC_EXT)=$(BUILD_DIR)/%.o)
EXIST_LIST      =$(shell find $(BUILD_DIR) -type f -name '*.o')
MESH_FILE       =$(MESH_DIR)/transfer.obj
EXE_FILE        =proc
EXE 		=$(DIST_DIR)/$(EXE_FILE)
LOGS            =out.log test.log

# # ===== C compiler/linker options =====
# external programs
CXX	    = g++
DOXYGEN     = $(shell which doxygen)
RM          = rm -f

FLAGS_INCL_BASE     = 
FLAGS_CMPL_DBG_BASE = -pedantic -Wall -g -DDEBUG -DUNIT_TEST -ansi -Wextra
FLAGS_CMPL_REL_BASE = -O2
FLAGS_LINK_BASE     =

FLAGS_CMPL_LINUX    =
FLAGS_LINK_LINUX    = -lGL -lm

FLAGS_CMPL_DARWIN   = -I/usr/include/ -std=c++11 -Wall -Wno-c++11-extensions -I/opt/local/include/
FLAGS_LINK_DARWIN   = -framework OpenGL -framework GLUT 


#(MINGW format).  # use visual studio instead :/
#WIN_FLAGS	     = -D__WINDOWS__ -I"C:/Program Files/Microsoft SDKs/Windows/v7.1/Include"

# use visual studio instead :/
#WIN_LINK_FLAGS  = -lGL -lGLU -lglut -L"C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib"


# ===== ===== Detect Platform ===== =====
SYSTEM_NAME := $(shell uname -s)

ifeq ($(SYSTEM_NAME), Linux)
#	# aimed at Linux Mint, Debian Edition (LMDE)
	PLATFORM_DETECTED = LINUX
	FLAGS_INCL_PLATFORM = $(FLAGS_COMP_LINUX)
	OBJ_VIEWER = g3dviewer
	FLAGS_CMPL_DBG    = $(FLAGS_CMPL_DBG_BASE) -D__$(PLATFORM_DETECTED)__ $(FLAGS_CMPL_LINUX)
	FLAGS_CMPL_REL    = $(FLAGS_CMPL_REL_BASE) -D__$(PLATFORM_DETECTED)__  $(FLAGS_CMPL_LINUX)
	FLAGS_LINK        = $(FLAGS_LINK_BASE) $(FLAGS_LINK_LINUX)

endif
ifeq ($(SYSTEM_NAME), Darwin)
	PLATFORM_DETECTED = MAC_OSX
	FLAGS_COMP_PLATFORM = $(FLAGS_COMP_MACOSX)
	OBJ_VIEWER = /Applications/OBJ\ Viewer.app/Contents/MacOS/OBJ\ Viewer
	FLAGS_CMPL_DBG    = $(FLAGS_CMPL_DBG_BASE) -D__$(PLATFORM_DETECTED)__ $(FLAGS_CMPL_DARWIN)
	FLAGS_CMPL_REL    = $(FLAGS_CMPL_REL_BASE) -D__$(PLATFORM_DETECTED)__  $(FLAGS_CMPL_DARWIN)
	FLAGS_LINK        = $(FLAGS_LINK_BASE) $(FLAGS_LINK_DARWIN)
endif
ifeq ($(SYSTEM_NAME), Windows_NT)
#	# not supported. Please use visual studio
#	#PLATFORM_DETECTED = WINDOWS_64 # currently no difference, anyway
	PLATFORM_DETECTED = WINDOWS
endif

# flags used here:
CPPFLAGS  = 
CXXFLAGS  += $(FLAGS_CMPL_DBG)
LDFLAGS   += $(FLAGS_LINK)

FLAGS_RELEASE   =$(FLAGS_BASE_RELEASE) -D__$(PLATFORM_DETECTED)__  $(FLAGS_COMP_PLATFORM)
FLAGS_DEBUG     =$(FLAGS_BASE_DEBUG) -D__$(PLATFORM_DETECTED)__ $(FLAGS_COMP_PLATFORM)

# ==== ==== ==== ==== ==== ==== ==== ====

# default target
.PHONY:run
run: debug

.PHONY: makefile

#%.o : %.cpp

$(BUILD_DIR)/%.o : ./%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -c -o $@

#$(BUILD_DIR)/%.o: $(CPP_SOURCE_DIR)%.$(SRC_EXT) $(BUILD_DIR)
#	$(CXX) $(CMPL_FLAGS) $< -c -o $@

# do not combine-- '$^' variable will break
$(EXE): $(OBJ_LIST)
	$(CXX) $(LINK_FLAGS) $^ -o $(DIST_DIR)/$(EXE_FILE) 

# use these to debug file
.PHONY: env
env:
	@echo SYSTEM NAME = '$(SYSTEM_NAME)'
	@echo PLATFORM DETECTED = '$(PLATFORM_DETECTED)'
	@echo ''
	@echo SOURCE_LIST = '$(SOURCE_LIST)'	
	@echo ''
	@echo HEADER_LIST = '$(HEADER_LIST)'
	@echo ''
	@echo OBJ_LIST = '$(OBJ_LIST)'
	@echo ''
	@echo EXISTS='$(EXIST_LIST)'
	@echo ''

	@echo FLAGS_CMPL_DBG = $(FLAGS_CMPL_DBG)
	@echo FLAGS_CMPL_REL = $(FLAGS_CMPL_REL)
	@echo LINK_FLAGS = $(FLAGS_LINK)


#.PHONY:debug
debug: $(EXE) 
	$(DIST_DIR)/$(EXE_FILE) $(MESH_FILE)
#	sdiff -b -l $(MESH_FILE) ../data/mesh/bak.obj
#	@echo "\n\n"
	$(OBJ_VIEWER) $(MESH_FILE)

# documentation generation
#doc: doxygen
#doxygen: 
#	$(DOXYGEN) $(DOXYGEN_CFG)

# enable debugging mode
#debug:

# clean up object/error files and executables
.PHONY : clean
clean:
	$(RM) $(OBJ_LIST) core $(LOGS) $(SRC_DIR)/*.orig

.PHONY : tidy
tidy:
	$(RM) $(EXE) *.o

# ==== ==== ensure directories ==== ====
$(DIST_DIR):
	mkdir $(DIST_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	mkdir $(BUILD_DIR)/effects/
