libscryptcpp
============

Copywrite (c) 2018, Josh Baldwin

https://github.com/jbaldwin/libscriptcpp

Original algorithm designer and example code from Colin Percival here: http://www.tarsnap.com/scrypt.html
Thanks to wrapped C library 'libscrypt', much easier to understand, here: https://github.com/technion/libscrypt

# Overview #
libscryptcpp is a simple C++17 interface around the scrypt library.  It provides an easy to use cmake file for adding to your projects.

## Requirements
    Linux [tested on Fedora and CentOS]
    C++17 compiler (g++/clang++)
    CMake 3.0.2+

## Instructions
If you git clone this repository you also need to init/update the submodule it requires.
    git submodule update --init --recursive

### Building
    # To include in your CMakeLists.txt:
    add_subdirectory(./path/libscryptcpp)
    # Link headers and libscrypt.a library via target name
    target_link_libraries(${PROJECT_NAME} PRIVATE libscryptcpp)

    # To simply build a libscrypt.a static library:
    mkdir Release && cd Release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . -- -j4 # change to number of cores available

## Examples

### Hash password

    auto mcf_opt = scrypt::hash("password");
    if(mcf_opt.has_value())
    {
        // store mcf.value() into database
    }
    else
    {
        // scrypt hash failed
    }

### Check password

    std::string mcf = load_mcf_from_database(user);

    switch(scrypt::check(std::move(mcf), "password"))
    {
        case scrypt::ResultEnum::PASSWORD_MATCH:
            // Do something if the password matches
            break;
        case scrypt::ResultEnum::PASSWORD_DOES_NOT_MATCH:
            // Do something if the password doesn't match
            break;
        case scrypt::ResultEnum::ERROR_DECRYPT_FAILURE:
            // Internal libscrypt decrypt error, 
            // possibly malformed MCF.
            break;
    }
