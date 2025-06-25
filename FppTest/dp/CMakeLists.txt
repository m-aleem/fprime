set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpTest.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/DpTest.fpp"
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpTest.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DpTestTestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DpTestTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DpTestTesterHelpers.cpp"
)
set(UT_MOD_DEPS STest)
register_fprime_ut()
