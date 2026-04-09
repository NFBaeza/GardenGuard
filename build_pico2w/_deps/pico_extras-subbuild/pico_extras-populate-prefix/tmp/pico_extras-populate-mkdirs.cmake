# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-src"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-build"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-subbuild/pico_extras-populate-prefix"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-subbuild/pico_extras-populate-prefix/tmp"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-subbuild/pico_extras-populate-prefix/src/pico_extras-populate-stamp"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-subbuild/pico_extras-populate-prefix/src"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-subbuild/pico_extras-populate-prefix/src/pico_extras-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-subbuild/pico_extras-populate-prefix/src/pico_extras-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_extras-subbuild/pico_extras-populate-prefix/src/pico_extras-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
