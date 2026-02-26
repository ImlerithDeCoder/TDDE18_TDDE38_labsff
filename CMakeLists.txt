# 1. Sätt lägsta version av CMake
cmake_minimum_required(VERSION 3.12)

# 2. Namnge ditt projekt
project(MinaMangaProgram)

# ger intellisence hihihi
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 3. Hitta alla .cpp-filer i projektet (och i undermappar)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")

# 4. Loopa igenom listan av filer vi hittade
foreach(CPP_FILE IN LISTS SOURCES)
    
    # Plocka ut filnamnet utan ändelsen (.cpp)
    # Exempel: Har vi filen "src/dag_01.cpp" blir TARGET_NAME "dag_01"
    #get_filename_component(TARGET_NAME "${CPP_FILE}" NAME_WE)
    
    # Skapa en körbar fil (.exe) för just denna specifika cpp-fil
    #add_executable(${TARGET_NAME} "${CPP_FILE}")
    # Hämta filnamnet utan ändelse (t.ex. "main")
    get_filename_component(FILE_NAME "${CPP_FILE}" NAME_WE)
    
    # Hämta sökvägen till mappen där filen ligger
    get_filename_component(DIR_PATH "${CPP_FILE}" DIRECTORY)
    
    # Plocka ut sista namnet i sökvägen (mappnamnet, t.ex. "labb2")
    get_filename_component(DIR_NAME "${DIR_PATH}" NAME)
    
    # Skapa det nya namnet: labb2_main
    set(TARGET_NAME "${DIR_NAME}_${FILE_NAME}")
    
    # Skapa en körbar fil
    add_executable(${TARGET_NAME} "${CPP_FILE}")
    
    # Bonus: Skriv ut i terminalen så du ser vad som händer när du kör cmake
    message(STATUS "Skapar target: ${TARGET_NAME}")
    
endforeach()