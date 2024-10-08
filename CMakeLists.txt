cmake_minimum_required(VERSION 3.29)
project(SDK)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

# If build type is not specified, default to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Include necessary modules
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# OpenSSLのパスを明示的に指定
find_package(OpenSSL REQUIRED)
set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
set(OPENSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
set(OPENSSL_LIBRARIES /opt/homebrew/opt/openssl@3/lib)

# Include directories
include_directories(${OPENSSL_INCLUDE_DIR})
link_directories(${OPENSSL_LIBRARIES})

# SDKライブラリの定義
file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# CppRestSDKライブラリのリンク設定
find_package(cpprestsdk REQUIRED)
find_package(Boost REQUIRED)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Boost::headers
        cpprestsdk::cpprest
        OpenSSL::SSL
        OpenSSL::Crypto
)

# コンパイルオプション設定
target_compile_options(${PROJECT_NAME}
        PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wno-unused-variable -Wno-unused-lambda-capture>
)

# パッケージ設定ファイルの生成
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# インストールターゲットの設定
install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# ヘッダーファイルのインストール設定
install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# パッケージ設定ファイルのインストール設定
install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# インストールターゲットのエクスポート
install(
        EXPORT ${PROJECT_NAME}Targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# テストプロジェクトの追加
add_subdirectory(tests)
