# Yêu cầu phiên bản CMake tối thiểu
cmake_minimum_required(VERSION 3.16)

# Đặt tên dự án
project(THUVIEN VERSION 1.0.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Thêm thư mục include để tìm các file header
include_directories(${CMAKE_SOURCE_DIR}/include)

# Định nghĩa các file mã nguồn
set(SOURCE_FILES
    src/main.cpp
    src/Book.cpp
    src/BorrowRecord.cpp
    src/FileManager.cpp
    src/Librarian.cpp
    src/Library.cpp
    src/Menu.cpp
    src/Reader.cpp
    src/User.cpp
    src/Utils.cpp
)

# Tạo file thực thi từ các file mã nguồn
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Liên kết với các thư viện cần thiết dựa trên hệ điều hành
if(WIN32)
    # Trên Windows (sử dụng MinGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
elseif(UNIX)
    # Trên Linux (hoặc macOS)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

# Thiết lập thư mục đầu ra
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)