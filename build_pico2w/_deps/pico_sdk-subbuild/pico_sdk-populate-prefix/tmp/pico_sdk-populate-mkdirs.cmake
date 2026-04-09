# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-src"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-build"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/tmp"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
