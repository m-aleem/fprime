####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Health.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/HealthComponentImpl.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Stub/HealthComponentStubChecks.cpp"
)

register_fprime_module()
# ### UTs ###
set(UT_SOURCE_FILES
  "${FPRIME_FRAMEWORK_PATH}/Svc/Health/Health.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/HealthTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/HealthTestMain.cpp"
)
register_fprime_ut()
set (UT_TARGET_NAME "${FPRIME_CURRENT_MODULE}_ut_exe")
if (TARGET "${UT_TARGET_NAME}")
    target_compile_options("${UT_TARGET_NAME}" PRIVATE -Wno-conversion)
endif()
