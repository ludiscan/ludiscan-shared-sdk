//
// Created by matuyuhi on 2024/10/08.
//
#include "SDK/SDKCore.h"
#include "CppRestOpenAPIClient/api/V0Api.h"
#include "CppRestOpenAPIClient/model/CreatePlaySessionDto.h"
#include "CppRestOpenAPIClient/ApiClient.h"
#include <pplx/pplxtasks.h>

using org::openapitools::client::api::V0Api;
using org::openapitools::client::model::CreatePlaySessionDto;
using org::openapitools::client::api::ApiClient;
using org::openapitools::client::api::ApiConfiguration;

bool SDKCore::CreatePlaySession(const std::string& projectId, const std::string& userId)
{
    // ApiClientの作成
    std::shared_ptr<ApiClient> apiClient = std::make_shared<ApiClient>();
    std::shared_ptr<ApiConfiguration> configuration = std::make_shared<ApiConfiguration>();
    configuration->setBaseUrl("http://localhost:3000");
    apiClient->setConfiguration(configuration);

    // V0Apiのインスタンス作成
    V0Api api(apiClient);

    // CreatePlaySessionDtoの設定
    std::shared_ptr<CreatePlaySessionDto> sessionDto = std::make_shared<CreatePlaySessionDto>();
    sessionDto->setName("name");
    sessionDto->setPlatform("Windows");
    sessionDto->setAppVersion("1.0.0");
    sessionDto->setDeviceId("device-id");

    // 非同期でAPI呼び出し
    const auto task = api.playSessionControllerCreate(projectId, sessionDto);

    // 結果を待機
    try {
        task.wait();  // 非同期タスクの完了を待つ
        // メモリ解放
        sessionDto.reset();
        apiClient.reset();
        configuration.reset();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error during play session creation: " << e.what() << std::endl;
        sessionDto.reset();
        apiClient.reset();
        configuration.reset();
        return false;  // 失敗
    }
}
