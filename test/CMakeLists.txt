enable_testing()

add_executable(
  unit_tests

  ADC_tests.cpp
  AND_tests.cpp
  ASL_tests.cpp
  BCC_tests.cpp
  BCS_tests.cpp
  BEQ_tests.cpp
  BIT_tests.cpp
  BMI_tests.cpp
  BNE_tests.cpp
  BPL_tests.cpp
  BVC_tests.cpp
  BVS_tests.cpp
  CLC_tests.cpp
  CLD_tests.cpp
  CLI_tests.cpp
  CLV_tests.cpp
  SEC_tests.cpp
  SED_tests.cpp
  SEI_tests.cpp
  TAX_tests.cpp
)

# include the gtest and em6502 lib
target_link_libraries(unit_tests em6502 GTest::gtest_main)

target_include_directories(unit_tests PUBLIC ${CMAKE_SOURCE_DIR}/include)

include(GoogleTest)

gtest_discover_tests(unit_tests)