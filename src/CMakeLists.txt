cmake_minimum_required(VERSION 3.12)

project(TransactionManagementProgram CXX)

set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)

add_executable(txmp txmp.cpp transaction.cpp)

add_executable(add_tx add_tx.cpp transaction.cpp)

add_executable(print_transactions print_transactions.cpp transaction.cpp)

target_include_directories(txmp PRIVATE ${CURSES_INCLUDE_DIRS})

target_link_libraries(txmp PRIVATE ${CURSES_LIBRARIES})
