cmake_minimum_required(VERSION 3.24)
project(Projet_2_en_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projet_2_en_C
        gestion_fonction.c
        Headers.h
        main.c)
