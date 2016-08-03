####################################################################################################

MP = ../..
EIGEN = $(MP)
MESSAGES = $(MP)/messages
SOURCE = $(MESSAGES)/messages

####################################################################################################

CC = arm-linux-gnueabi-g++
CPP_FLAGS += -O3
CPP_FLAGS += -Wall
CPP_FLAGS += -Wextra
CPP_FLAGS += -D POSIX_ENV
CPP_FLAGS += -I $(EIGEN)
CPP_FLAGS += -I $(MESSAGES)

####################################################################################################

MESSAGES_LIB = lib_mikipilot_messages.a

MESSAGES_SOURCES += ahrs_data_pkt.cpp
MESSAGES_SOURCES += ahrs_gains_pkt.cpp
MESSAGES_SOURCES += ahrs_state_pkt.cpp
MESSAGES_SOURCES += all_messages.cpp
MESSAGES_SOURCES += ctrl_data_pkt.cpp
MESSAGES_SOURCES += ctrl_gains_pkt.cpp
MESSAGES_SOURCES += ctrl_mode_pkt.cpp
MESSAGES_SOURCES += ctrl_state_pkt.cpp
MESSAGES_SOURCES += dyn_cmd_pkt.cpp
MESSAGES_SOURCES += global_defs.cpp
MESSAGES_SOURCES += health_state_pkt.cpp
MESSAGES_SOURCES += imu_pkt.cpp
MESSAGES_SOURCES += imu_state_pkt.cpp
MESSAGES_SOURCES += mag_pkt.cpp
MESSAGES_SOURCES += mag_state_pkt.cpp
MESSAGES_SOURCES += packet.cpp
MESSAGES_SOURCES += pid_data_pkt.cpp
MESSAGES_SOURCES += pid_gains_pkt.cpp
MESSAGES_SOURCES += pos_pkt.cpp
MESSAGES_SOURCES += pwm_pkt.cpp
MESSAGES_SOURCES += .cpp
MESSAGES_SOURCES += ahrs.cpp
MESSAGES_SOURCES += ahrs.cpp
MESSAGES_SOURCES += ahrs.cpp
MESSAGES_SOURCES += ahrs.cpp
MESSAGES_SOURCES += ahrs.cpp


####################################################################################################

MESSAGES_OBJS = $(addprefix messages_,$(MESSAGES_SOURCES:.cpp=.o))

####################################################################################################

# Targets.
default: lib
lib: $(MESSAGES_LIB)

####################################################################################################

# Build library file.
$MESSAGES_LIB): $(MESSAGES_OBJS)
	@ echo " building lib:" $@
	@ ar rcs $(MESSAGES_LIB) $(MESSAGES_OBJS)
	@ echo
	@ echo " FLAGS:" $(OPT_FLAGS)
	@ echo " DONE:" $(MESSAGES_LIB)
	@ echo

####################################################################################################

# Build MESSAGES object files.
messages_%.o: $(SOURCE)/%.cpp $(SOURCE)/%.h
	@ echo " building obj:" $@
	@ $(CC) $(CPP_FLAGS) $(OPT_FLAGS) -c $< -o $@

####################################################################################################

# Clean all files.
clean:
	@ rm -f $(MESSAGES_LIB)
	@ rm -f $(MESSAGES_OBJS)

####################################################################################################
