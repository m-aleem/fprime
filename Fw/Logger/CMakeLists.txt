####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(MOD_DEPS
    Fw/Types
)
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Logger.cpp"
)
register_fprime_module()

# Rules based unit testing
set(UT_MOD_DEPS
    STest
    Fw/Types
)
set(UT_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/FakeLogger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/LoggerRules.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/LoggerMain.cpp"
)
# STest Includes for this UT
register_fprime_ut()
set (UT_TARGET_NAME "${FPRIME_CURRENT_MODULE}_ut_exe")
if (TARGET "${UT_TARGET_NAME}")
    target_compile_options("${UT_TARGET_NAME}" PRIVATE -Wno-conversion)
endif()
