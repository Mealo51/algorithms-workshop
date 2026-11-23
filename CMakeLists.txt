cmake_minimum_required(VERSION 3.24)
project(ModernCppAlgorithmsWorkshop LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
enable_testing()

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "Use the same MSVC runtime as the exercises" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "The exercises use GoogleTest only" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Keep GoogleTest local to the workshop build" FORCE)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
    URL_HASH SHA256=65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    get_filename_component(msvc_bin_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
    get_filename_component(msvc_toolset "${msvc_bin_dir}/../../.." ABSOLUTE)
    set(native_rules "${msvc_toolset}/CodeAnalysis/Rulesets/NativeRecommendedRules.ruleset")
    cmake_path(NATIVE_PATH native_rules NORMALIZE native_rules_path)
endif()

set(workshop_exercises
    ex01_find_first_dead
    ex02_count_poisoned
    ex03_row_walkable
    ex04_total_weight
    ex05_apply_damage
    ex06_remove_inactive_bullets
    ex07_rank_targets
    ex08_partition_near
    ex09_unique_contacts
    ex10_filter_and_label_enemies
    ex11_shuffle_deck
)

foreach(exercise IN LISTS workshop_exercises)
    add_executable(${exercise} exercises/${exercise}.cpp)
    target_link_libraries(${exercise} PRIVATE GTest::gtest)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # In the course's Visual Studio toolchain, CMake maps this to /std:c++latest.
        target_compile_features(${exercise} PRIVATE cxx_std_23)
        target_compile_options(${exercise} PRIVATE
            /W4
            /WX
            /external:env:INCLUDE
            /external:W0
            /analyze
            /analyze:external-
        )
        if(EXISTS "${native_rules}")
            target_compile_options(${exercise} PRIVATE "/analyze:ruleset${native_rules_path}")
        endif()
    else()
        target_compile_features(${exercise} PRIVATE cxx_std_20)
    endif()
    gtest_discover_tests(${exercise} TEST_PREFIX "${exercise}.")
endforeach()
