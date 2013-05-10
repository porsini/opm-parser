add_executable(runParserTests ParserTests.cpp)
add_executable(runParserTestsInternalData ParserTestsInternalData.cpp)
add_executable(runParserKWTests ParserKWTests.cpp)
add_executable(runParserRecordTests ParserRecordTests.cpp)
add_executable(runParserRecordSizeTests ParserRecordSizeTests.cpp)
add_executable(runParserItemTests ParserItemTests.cpp)

target_link_libraries(runParserTests Parser Logger ${Boost_LIBRARIES})
target_link_libraries(runParserTestsInternalData Parser Logger ${Boost_LIBRARIES})
target_link_libraries(runParserKWTests Parser Logger ${Boost_LIBRARIES})
target_link_libraries(runParserRecordSizeTests Parser Logger ${Boost_LIBRARIES})
target_link_libraries(runParserRecordTests Parser Logger ${Boost_LIBRARIES})
target_link_libraries(runParserItemTests Parser Logger ${Boost_LIBRARIES})

add_test(NAME runParserTests WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${EXECUTABLE_OUTPUT_PATH}/runParserTests )
add_test(NAME runParserTestsInternalData WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${EXECUTABLE_OUTPUT_PATH}/runParserTestsInternalData)
add_test(NAME runParserKWTests COMMAND ${EXECUTABLE_OUTPUT_PATH}/runParserKWTests )
add_test(NAME runParserRecordSizeTests COMMAND ${EXECUTABLE_OUTPUT_PATH}/runParserRecordSizeTests )
add_test(NAME runParserRecordTests COMMAND ${EXECUTABLE_OUTPUT_PATH}/runParserRecordTests )
add_test(NAME runParserItemTests COMMAND ${EXECUTABLE_OUTPUT_PATH}/runParserItemTests )

set_tests_properties(runParserTestsInternalData PROPERTIES LABELS Statoil)

set_property(SOURCE ParserRecordTests.cpp PROPERTY COMPILE_FLAGS "-Wno-error")