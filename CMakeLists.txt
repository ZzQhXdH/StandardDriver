cmake_minimum_required(VERSION 3.14)
project(StandardDriver)

set(CMAKE_CXX_STANDARD 11)

add_executable(StandardDriver main.cpp Standard/Memory.h Standard/Memory.cpp Standard/String.cpp Standard/String.h Standard/TemplateUtil.h Standard/FormatBuilder.h Standard/ByteArray.h Standard/Cryptography.cpp Standard/Cryptography.h Standard/ActionBuilder.h Standard/FlashDrv.h)