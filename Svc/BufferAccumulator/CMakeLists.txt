####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
restrict_platforms(Linux Darwin) # Uses sys/time

set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/BufferAccumulator.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/BufferAccumulator.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ArrayFIFOBuffer.cpp"
)

register_fprime_module()

### UTS ###
set(UT_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/BufferAccumulator.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/BufferAccumulatorTester.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/Accumulate.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/Drain.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/Errors.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/Health.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/BufferAccumulatorMain.cpp"
)
register_fprime_ut()

