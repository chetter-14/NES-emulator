include_directories("${NES-emulator_SOURCE_DIR}/include")
add_executable(NES-emulator main.cpp Bus.cpp "olc6502.cpp")