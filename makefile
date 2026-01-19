CC:=arm-none-eabi-gcc -c
LD:=arm-none-eabi-gcc #arm-none-eabi-ld
OC:=arm-none-eabi-objcopy

# utility
RM:=rm -f
MK:=mkdir -p

# list of all the directories, in the project
DEPS_DIR:=./deps
INC_DIR:=./inc
OBJ_DIR:=./obj
SRC_DIR:=./src
BIN_DIR:=./bin

# include the name of the dependencies to be built here
# must have the same name submodule directory in ./deps/ and it also must build the library with the same name in it's ./lib directory
# these must also be in the order from most derieved to the least derieved (the parent most library)
DEPS:=capp

# no OS to return to baremetal application
USE_NOHOST:=--specs=nosys.specs

# specify the instruction set to use and the cpu (can not change this)
ARCH_FLAGS:=-mthumb -mcpu=cortex-m4
# optimization for code size, use -O(0,1,2,3) for execution performance
OPTIMIZATION:=-Os
# use hardware FPU
HARD_FPU:=-mfloat-abi=hard
# the final compiler flags
CCFLAGS:=$(ARCH_FLAGS) ${HARD_FPU} ${OPTIMIZATION} -I./inc -fsingle-precision-constant -flto -ffunction-sections -fdata-sections
# I am using only single precission floating point constants

# adding HAL header to include dirs
CCFLAGS += \
  -I$(DEPS_DIR)/STM32CubeF4/Drivers/CMSIS/Include \
  -I$(DEPS_DIR)/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
  -I$(DEPS_DIR)/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc

# adding include dirs from dependencies
CCFLAGS += $(addprefix -I$(DEPS_DIR)/,$(addsuffix /inc,$(DEPENDENCIES)))

# figure out all the static libraries we need to build with
LIBRARIES=$(foreach d,$(DEPS), \
            $(wildcard $(DEPS_DIR)/$(d)/lib/lib*.a))

# add this option to LDFLAGS to build the map file along side the executable elf
MAP:=-Map=./bin/main.map
# introduce the path to the linker script and the name of the linker script
LDSCRIPTS=-L. -T gcc.ld
LDSCRIPTS += $(addprefix -L, $(sort $(dir $(LIBRARIES))))
# remove unused function and data sections
GC:=-Wl,--gc-sections
#the final linker flags
LDFLAGS=$(LDSCRIPTS) $(GC) $(HARD_FPU)

# libraries, all of which we are concerned with
LIB:=-lm
LIB += $(addprefix -l, $(patsubst lib%,%, $(basename $(notdir $(LIBRARIES)))))

# figure out all the sources in the project
SOURCES:=${shell find . -name '*.c'}
SOURCES+=deps/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
# and the required objects ot be built
OBJECTS:=$(patsubst %.c,%.o,${SOURCES})

# rule to make the directory for storing object files, that we create
${OBJ_DIR} :
	${MK} $@

# generate objects from c sources
%.o : %.c
	${CC} $(CCFLAGS) $< -o $@

# generate objects from asm sources
%.o : %.S
	${CC} $(CCFLAGS) $< -o $@

# generate final elf by linking all the object files
main.elf : $(OBJECTS)
	$(LD) $(ARCH_FLAGS) $(LDFLAGS) $(USE_NOHOST) $^ -o $@ $(LIB)

# convert to hex or binary that can be transfered by the corresponding uploader driver
main.bin : main.elf
	${OC} -O binary main.elf main.bin

all : main.bin

clean :


# upload command to upload the code to the microcontroller
upload :
	st-flash write main.bin 0x08000000

upload-using-uart :
	stm32flash -w main.bin /dev/ttyUSB0