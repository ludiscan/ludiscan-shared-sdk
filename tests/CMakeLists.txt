# テストプロジェクト用のCMake設定
add_executable(SDKTests main.cpp)
target_link_libraries(SDKTests SDK)