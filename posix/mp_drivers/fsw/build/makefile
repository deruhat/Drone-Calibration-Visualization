####################################################################################################

ROOT = ..
FSW = $(ROOT)/fsw
EIGEN = $(ROOT)/..
ROSSERIAL = $(ROOT)/../rosserial
UTILITIES = $(ROOT)/../utilities
COMM = $(ROOT)/../comm

EXEC = $(FSW)/exec
GLOBALS = $(FSW)/globals
HARDWARE = $(FSW)/hardware
CONTROL = $(FSW)/control
API = $(FSW)/api
####################################################################################################

CC = arm-linux-gnueabi-g++
CPP_FLAGS += -static-libstdc++
CPP_FLAGS += -O3
#CPP_FLAGS += -Wall
#CPP_FLAGS += -Wextra
CPP_FLAGS += -D POSIX_ENV
CPP_FLAGS += -D PRECOMPILE_COMM_LIB
CPP_FLAGS += -I $(ROOT)
CPP_FLAGS += -I $(EIGEN)
CPP_FLAGS += -I $(ROSSERIAL)
CPP_FLAGS += -I $(UTILITIES)
CPP_FLAGS += -I $(COMM)
CPP_FLAGS += -std=c++11
CPP_FLAGS += -Wno-write-strings

####################################################################################################

FSW_EXEC_SOURCES += drivers_example.cpp

FSW_GLOBALS_SOURCES += globals.cpp
FSW_GLOBALS_SOURCES += module.cpp
FSW_GLOBALS_SOURCES += object.cpp

FSW_HARDWARE_SOURCES += hmc5883l.cpp
#FSW_HARDWARE_SOURCES += max11644eua.cpp
FSW_HARDWARE_SOURCES += mp_ap_board.cpp
FSW_HARDWARE_SOURCES += mpu6050.cpp
FSW_HARDWARE_SOURCES += overo.cpp
FSW_HARDWARE_SOURCES += pca9685.cpp
FSW_HARDWARE_SOURCES += sc18is602b.cpp

FSW_CONTROL_SOURCES += MatricesAndVectors.cpp
FSW_CONTROL_SOURCES += QuatRotEuler.cpp
FSW_CONTROL_SOURCES += MathFuncs.cpp
FSW_CONTROL_SOURCES += AttitudeControl.cpp
FSW_CONTROL_SOURCES += pevents.cpp

COMM_LIB = $(COMM)/build/lib_mikipilot_comm.a
UTILITIES_LIB = $(UTILITIES)/build/lib_mikipilot_utilities.a

FSW_VERSION_SOURCES += version.cpp


####################################################################################################

EXEC_OBJS = $(addprefix exec_,$(FSW_EXEC_SOURCES:.cpp=.o))
FSW_GLOBALS_OBJS = $(addprefix fsw_globals_,$(FSW_GLOBALS_SOURCES:.cpp=.o))
FSW_HARDWARE_OBJS = $(addprefix fsw_hardware_,$(FSW_HARDWARE_SOURCES:.cpp=.o))
FSW_CONTROL_OBJS = $(addprefix fsw_control_,$(FSW_CONTROL_SOURCES:.cpp=.o))
FSW_VERSION_OBJS = $(addprefix fsw_,$(FSW_VERSION_SOURCES:.cpp=.o))

DEPS_OBJS += $(FSW_GLOBALS_OBJS)
DEPS_OBJS += $(FSW_HARDWARE_OBJS)
DEPS_OBJS += $(FSW_CONTROL_OBJS)
DEPS_OBJS += $(FSW_VERSION_OBJS)

ALL_OBJS += $(EXEC_OBJS)
ALL_OBJS += $(DEPS_OBJS)

####################################################################################################

# Targets.
default: exec_drivers_example
all: exec_drivers_example
deps: globals hardware control version
exec: $(EXEC_OBJS)
globals: $(FSW_GLOBALS_OBJS)
hardware: $(FSW_HARDWARE_OBJS)
control: $(FSW_CONTROL_OBJS)
version: $(FSW_VERSION_OBJS)

lib_comm:
	@ make -s -C $(COMM)/build
lib_utilities:
	@ make -s -C $(UTILITIES)/build

####################################################################################################

# Build MIKIPILOT_FSW EXEC.
exec_drivers_example: lib_utilities lib_comm deps exec_drivers_example.o
	@ echo
	@ echo " BUILDING EXEC:" $@
	@ $(CC) $(CPP_FLAGS) -o $@ $@.o $(DEPS_OBJS) $(COMM_LIB) $(UTILITIES_LIB) -lrt -lpthread
	@ echo " DONE:" $@
	@ echo

####################################################################################################

# Build EXEC object files.
exec_%.o: $(EXEC)/%.cpp
	@ echo " building obj:" $@
	@ $(CC) $(CPP_FLAGS) -c $< -o $@

####################################################################################################

# Build FSW GLOBALS object files.
fsw_globals_%.o: $(GLOBALS)/%.cpp $(GLOBALS)/%.h
	@ echo " building obj:" $@
	@ $(CC) $(CPP_FLAGS) -c $< -o $@

####################################################################################################

# Build FSW HARDWARE object files.
fsw_hardware_%.o: $(HARDWARE)/%.cpp $(HARDWARE)/%.h
	@ echo " building obj:" $@
	@ $(CC) $(CPP_FLAGS) -c $< -o $@

####################################################################################################

# Build FSW Control object files.
fsw_control_%.o: $(CONTROL)/%.cpp $(CONTROL)/%.h
	@ echo " building obj:" $@
	@ $(CC) $(CPP_FLAGS) -c $< -o $@

####################################################################################################

# Build FSW VERSION object files.
fsw_version.o: fsw_version.cpp
	@ echo " building obj:" fsw_version.o
	@ $(CC) $(CPP_FLAGS) -c $< -o $@
	@ rm -f $<
	
# Generate FSW VERSION source files.
fsw_version.cpp:
	@ printf '%s\n%s\nconst string fsw::globals::version::string = "%s";' \
	  '#include "fsw/globals/globals.h"' \
		'using std::string;' \
		N/A \
		>> $@

####################################################################################################

# Clean all files.
clean:
	@ rm -f exec_*
	@ rm -f $(ALL_OBJS)
	@ make -s clean -C $(COMM)/build
	@ make -s clean -C $(UTILITIES)/build

####################################################################################################
