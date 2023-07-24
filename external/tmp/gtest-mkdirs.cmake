# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/brabo/Projetos/genetic_algorithm_cpp/external/src/gtest"
  "/home/brabo/Projetos/genetic_algorithm_cpp/external/src/gtest-build"
  "/home/brabo/Projetos/genetic_algorithm_cpp/external"
  "/home/brabo/Projetos/genetic_algorithm_cpp/external/tmp"
  "/home/brabo/Projetos/genetic_algorithm_cpp/external/src/gtest-stamp"
  "/home/brabo/Projetos/genetic_algorithm_cpp/external/src"
  "/home/brabo/Projetos/genetic_algorithm_cpp/external/src/gtest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/brabo/Projetos/genetic_algorithm_cpp/external/src/gtest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/brabo/Projetos/genetic_algorithm_cpp/external/src/gtest-stamp${cfgdir}") # cfgdir has leading slash
endif()
