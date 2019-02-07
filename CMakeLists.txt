cmake_minimum_required(VERSION 3.9)
project(PureMVC)

set(CMAKE_C_STANDARD 99)

set(SOURCES src/core/model.c src/core/controller.c src/core/view.c)
list(APPEND SOURCES src/patterns/command/macro_command.c src/patterns/command/simple_command.c)
list(APPEND SOURCES src/patterns/mediator/mediator.c)
list(APPEND SOURCES src/patterns/observer/notification.c src/patterns/observer/observer.c)
list(APPEND SOURCES src/patterns/proxy/proxy.c)
add_library(PureMVC ${SOURCES})
target_include_directories(PureMVC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(TestController test/core/controller_test.c test/core/controller_test_command.c test/core/controller_test_command2.c test/core/controller_test_vo.c)
target_link_libraries(TestController PureMVC)

add_executable(TestModel test/core/model_test_proxy.c test/core/model_test.c)
target_link_libraries(TestModel PureMVC)

add_executable(TestView test/core/view_test.c test/core/view_test_mediator.c test/core/view_test_mediator4.c)
target_link_libraries(TestView PureMVC)

set(TestMacroCommand test/patterns/command/macro_command_test.c test/patterns/command/macro_command_test.h)
list(APPEND TestMacroCommand test/patterns/command/macro_command_test_command.c)
list(APPEND TestMacroCommand test/patterns/command/macro_command_test_sub1_command.c)
list(APPEND TestMacroCommand test/patterns/command/macro_command_test_sub2_command.c)
list(APPEND TestMacroCommand test/patterns/command/macro_command_test_vo.c)
add_executable(TestMacroCommand ${TestMacroCommand})
target_link_libraries(TestMacroCommand PureMVC)

set(TestSimpleCommand test/patterns/command/simple_command_test.c)
list(APPEND TestSimpleCommand test/patterns/command/simple_command_test_command.c)
list(APPEND TestSimpleCommand test/patterns/command/simple_command_test.c)
list(APPEND TestSimpleCommand test/patterns/command/simple_command_test_vo.c)
add_executable(TestSimpleCommand ${TestSimpleCommand})
target_link_libraries(TestSimpleCommand PureMVC)

add_executable(TestMediator test/patterns/mediator/mediator_test.c)
target_link_libraries(TestMediator PureMVC)

add_executable(TestNotification test/patterns/observer/notification_test.c)
target_link_libraries(TestNotification PureMVC)

add_executable(TestObserver test/patterns/observer/observer_test.c)
target_link_libraries(TestObserver PureMVC)

add_executable(TestProxy test/patterns/proxy/proxy_test.c)
target_link_libraries(TestProxy PureMVC)


