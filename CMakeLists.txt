cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 17)

project(libscryptcpp)

# Create a Debug/lib or Release/lib output directory.
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib)

option(D_GLIBCXX_DEBUG "Use D_GLIBCXX_DEBUG when building Debug" ON)
message("${PROJECT_NAME} D_GLIBCXX_DEBUG=${D_GLIBCXX_DEBUG}")

set(LIBSCRIPTCPP_SOURCE_FILES
    inc/scryptcpp/scrypt.h src/scrypt.cpp

    vendor/libscrypt/b64.h vendor/libscrypt/b64.c
    vendor/libscrypt/crypto-mcf.c
    vendor/libscrypt/crypto-scrypt-saltgen.c
    vendor/libscrypt/crypto_scrypt-check.c
    vendor/libscrypt/crypto_scrypt-hash.c
    vendor/libscrypt/crypto_scrypt-hexconvert.h vendor/libscrypt/crypto_scrypt-hexconvert.c
    vendor/libscrypt/crypto_scrypt-nosse.c
    vendor/libscrypt/libscrypt.h
    vendor/libscrypt/sha256.h vendor/libscrypt/sha256.c
    vendor/libscrypt/slowequals.h vendor/libscrypt/slowequals.c
    vendor/libscrypt/sysendian.h
)

add_library(${PROJECT_NAME} STATIC ${LIBSCRIPTCPP_SOURCE_FILES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("${PROJECT_NAME} is building Debug")
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        -O0
        -g
        -gdwarf-2
    )
    if(D_GLIBCXX_DEBUG)
        message("${PROJECT_NAME} D_GLIBCXX_DEBUG is ON")
        target_compile_options(${PROJECT_NAME} PRIVATE -D_GLIBCXX_DEBUG)
    else()
        message("${PROJECT_NAME} D_GLIBCXX_DEBUG is OFF")
    endif()

else() # "Release"
    message("${PROJECT_NAME} is building Release")
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        -O2
        -g
        -gdwarf-2
    )
endif()