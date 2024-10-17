//
// Created by matuyuhi on 2024/10/16.
//

#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include "CppRestOpenAPIClient/HttpContent.h" // 生成されたHttpContentのヘッダー
#include <memory>
#include <sstream>

#include "BinaryBody.h"
#include "CppRestOpenAPIClient/ModelBase.h"

// プレイヤーの座標データ構造体
struct PlayerPosition {
    int32_t player; // プレイヤー識別子
    float x;
    float y;
    float z; // オプション（ここでは必須と仮定）
    uint64_t offsetTimestamp;
};

using org::openapitools::client::model::ModelBase;

class Utilities {
public:
    static std::vector<uint8_t> constructBinaryData(const int players, const int stampCount, const std::vector<std::vector<PlayerPosition>>& allPositions) {
        std::vector<uint8_t> buffer;

        // メタ情報の追加（playersとstampcount）
        buffer.resize(8);
        buffer[0] = players & 0xFF;
        buffer[1] = (players >> 8) & 0xFF;
        buffer[2] = (players >> 16) & 0xFF;
        buffer[3] = (players >> 24) & 0xFF;

        buffer[4] = stampCount & 0xFF;
        buffer[5] = (stampCount >> 8) & 0xFF;
        buffer[6] = (stampCount >> 16) & 0xFF;
        buffer[7] = (stampCount >> 24) & 0xFF;

        // 各タイムスタンプごとのデータを追加
        for (int i = 0; i < stampCount; ++i) {
            for (int p = 0; p < players; ++p) {
                const PlayerPosition& pos = allPositions[i][p];

                // プレイヤー識別子をリトルエンディアンで追加
                int32_t playerLE = pos.player;
                auto* player_ptr = reinterpret_cast<uint8_t*>(&playerLE);
                buffer.insert(buffer.end(), player_ptr, player_ptr + sizeof(int32_t));

                // x, y, zをリトルエンディアンで追加
                float x = pos.x;
                float y = pos.y;
                float z = pos.z;
                auto* x_ptr = reinterpret_cast<uint8_t*>(&x);
                auto* y_ptr = reinterpret_cast<uint8_t*>(&y);
                auto* z_ptr = reinterpret_cast<uint8_t*>(&z);
                buffer.insert(buffer.end(), x_ptr, x_ptr + sizeof(float));
                buffer.insert(buffer.end(), y_ptr, y_ptr + sizeof(float));
                buffer.insert(buffer.end(), z_ptr, z_ptr + sizeof(float));

                // offsetTimestampをリトルエンディアンで追加
                uint64_t tsLE = pos.offsetTimestamp;
                auto* ts_ptr = reinterpret_cast<uint8_t*>(&tsLE);
                buffer.insert(buffer.end(), ts_ptr, ts_ptr + sizeof(uint64_t));
            }
        }

        return buffer;
    }

    static std::shared_ptr<org::openapitools::client::model::HttpContent> toHttpContent(const utility::string_t& name, const std::shared_ptr<std::istream>& data, const utility::string_t& fileName, const utility::string_t& contentType) {
        auto httpContent = std::make_shared<org::openapitools::client::model::HttpContent>();
        httpContent->setName(name);
        httpContent->setFileName(fileName);
        httpContent->setContentType(contentType);
        httpContent->setContentDisposition(U("form-data")); // Content-Disposition を設定
        httpContent->setData(data);
        return httpContent;
    }

    static std::shared_ptr<org::openapitools::client::model::HttpContent> createHttpContent(const std::vector<uint8_t>& binaryData) {
        // バイナリデータをストリームに変換
        auto dataStream = std::make_shared<std::stringstream>();
        dataStream->write(reinterpret_cast<const char*>(binaryData.data()), binaryData.size());
        dataStream->seekg(0); // ストリームの位置を先頭にリセット

        // ModelBase の新しい toHttpContent を使用してファイルコンテンツを作成
        return toHttpContent(
            U("file"),               // フィールド名
            dataStream,              // バイナリデータのストリーム
            U("data.bin"),           // 任意のファイル名
            U("application/octet-stream") // コンテンツタイプ
        );
    }
};



#endif //UTILITIES_H
