macro(vlarklib_add_test name srcdir)
    file(GLOB_RECURSE test_src ${srcdir}/*.cpp)
    add_executable(${name}_test ${test_src})
    #wpilib_target_warnings(${name}_test)
    # if(BUILD_SHARED_LIBS)
    #     target_compile_definitions(${name}_test PRIVATE -DGTEST_LINKED_AS_SHARED_LIBRARY)
    # endif()
    if(MSVC)
        target_compile_options(${name}_test PRIVATE /wd4101 /wd4251)
    endif()
    add_test(NAME ${name} COMMAND ${name}_test)
endmacro()




file(GLOB_RECURSE vlk_src ../src/*.cpp)
file(GLOB_RECURSE vlk_h ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h)

if(WITH_TESTS)
    add_library(vlark_lib ${vlk_src} ${vlk_h})
    target_include_directories(vlark_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    #set_target_properties(vlark_lib PROPERTIES DEBUG_POSTFIX "d")

    set_property(TARGET vlark_lib PROPERTY FOLDER "libraries")
    # target_compile_definitions(vlark_lib PRIVATE WPILIB_EXPORTS)

    target_compile_features(vlark_lib PUBLIC cxx_std_20)
    

    vlarklib_add_test(vlark ./ )
    target_include_directories(vlark_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
    target_link_libraries(vlark_test vlark_lib gtest_main gtest)
endif()