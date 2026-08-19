if(NOT DEFINED ENV{EMSDK})
    message(
        FATAL_ERROR
        "EMSDK is not set. Activate a pinned Emscripten SDK environment first."
    )
endif()

set(
    _sdt_emscripten_toolchain
    "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"
)
cmake_path(NORMAL_PATH _sdt_emscripten_toolchain)

if(NOT EXISTS "${_sdt_emscripten_toolchain}")
    message(
        FATAL_ERROR
        "Emscripten CMake toolchain was not found at "
        "${_sdt_emscripten_toolchain}"
    )
endif()

include("${_sdt_emscripten_toolchain}")

