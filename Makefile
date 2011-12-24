# This file was automagically generated by mbed.org. For more information, 
# see http://mbed.org/handbook/Exporting-To-GCC

GCC_BIN = 
PROJECT = xbm3pi-ugv
OBJECTS = CommandDispatcher.o TelemetryEncoder.o CommandStreamParser.o XBeeApi.o Gyro.o main.o Accelerometer.o m3pi/m3pi.o XBee/XBee.o 
SYS_OBJECTS = ./mbed/LPC1768/GCC_CS/startup_LPC17xx.o ./mbed/LPC1768/GCC_CS/sys.o ./mbed/LPC1768/GCC_CS/cmsis_nvic.o ./mbed/LPC1768/GCC_CS/core_cm3.o ./mbed/LPC1768/GCC_CS/system_LPC17xx.o 
INCLUDE_PATHS = -I./m3pi -I./XBee -I./mbed -I./mbed/LPC1768 -I./mbed/LPC1768/GCC_CS -I./m3pi -I./XBee 
LIBRARY_PATHS = -L./m3pi -L./XBee -L./mbed -L./mbed/LPC1768 -L./mbed/LPC1768/GCC_CS -L./m3pi -L./XBee 
LIBRARIES = -lmbed -lcapi
LINKER_SCRIPT = mbed/LPC1768/GCC_CS/LPC1768.ld

############################################################################### 
CC = $(GCC_BIN)arm-none-eabi-gcc
CPP = $(GCC_BIN)arm-none-eabi-g++
CC_FLAGS = -c -Os -fno-common -fmessage-length=0 -Wall -fno-exceptions -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections 
ONLY_C_FLAGS = -std=gnu99
ONLY_CPP_FLAGS = -std=gnu++98
CC_SYMBOLS = -DTARGET_LPC1768 -DTOOLCHAIN_GCC_CS -DNDEBUG


AS = $(GCC_BIN)arm-none-eabi-as

LD = $(GCC_BIN)arm-none-eabi-gcc
LD_FLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc

OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy

all: $(PROJECT).bin

clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(OBJECTS)

.s.o:
	$(AS)  $(CC_FLAGS) $(CC_SYMBOLS) -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) $(ONLY_C_FLAGS)   $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) $(ONLY_CPP_FLAGS) $(INCLUDE_PATHS) -o $@ $<


$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@