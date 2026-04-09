# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/_deps/pico_sdk-src/tools/pioasm"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pioasm"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pioasm-install"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/miosa/CommonDisk/Projects/GardenGuard/build_pico2w/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
