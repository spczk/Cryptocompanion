cmake_minimum_required(VERSION 3.9)
project(CryptoCompanion)

set(CMAKE_CXX_STANDARD 11)

add_executable(CryptoCompanion
        adressbook.cpp
        adressbook.h
        cryptocompanion.cpp
        cryptocompanion.h
        main.cpp
        secdialog.cpp
        secdialog.h
        user.cpp
        user.h)
