# STM32F411CEU6 HAL SAMPLE
A sample project to show how to build a modular STM32 HAL-supported application for the black pill board.

## Setup instructions
**Install dependencies :**
 * `sudo apt install gcc-arm-none-eabi`
 * for uploading the binary to the board
   * `sudo apt install stm32flash` for stm32flash (over uart)
   * OR `sudo apt-get install stlink-tools` for st-flash (over stlink v2)
 * No need to worry about the rest, as they would be managed by submodules.

**Download source code :**
 * `git clone https://github.com/RohanVDvivedi/stm32f411ceu6_hal_sample.git`

**Build from source :**
 * `cd stm32f411ceu6_hal_sample`
 * `make clean all`

**Install from the build :**
 * `make upload` or `make upload-using-uart`
 * ***you may discard the build by*** `make clean`

