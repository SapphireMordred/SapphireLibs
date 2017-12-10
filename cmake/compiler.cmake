if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Werror")
else()
  add_definitions(-D_WIN32_WINNT=0x601)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /W3 /WX")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # incremental linking
    message(STATUS "Enabling Incremental Linking..")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL")

    # disabling SAFESEH
    message(STATUS "Disabling Safe Exception Handlers..")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")

    # edit and continue
    message(STATUS "Enabling Edit and Continue..")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /ZI")
  endif()
endif()