cmake_minimum_required (VERSION 3.15)

project ("test_socket" LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -pthread -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Add source to this project's executable.
add_executable (server server.cpp)
add_executable (client client.cpp)
