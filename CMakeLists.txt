# 1. Sätt lägsta version av CMake
cmake_minimum_required(VERSION 3.12)

# 2. Namnge ditt projekt
project(MinaMangaProgram)

# ger intellisence hihihi
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 3. Hitta alla .cpp-filer i projektet (och i undermappar)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "tester/*.cpp")


# Aktivera FetchContent
include(FetchContent)

# Definiera var Catch2 ska laddas ner ifrån
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2 # Du kan byta detta till senaste versionen om du vill
)

# Gör Catch2 tillgängligt i ditt projekt
FetchContent_MakeAvailable(Catch2)
# Skapa BARA en körbar fil för ditt testprogram
add_executable(test_labb2 "tester/test_tdde18_lab2.cpp")

# Länka in Catch2
target_link_libraries(test_labb2 PRIVATE Catch2::Catch2WithMain)