//
// Created by matuyuhi on 2024/10/08.
//

#ifndef SDKCORE_H
#define SDKCORE_H

#include <string>

class SDKCore {
public:
    static bool CreatePlaySession(const std::string& projectId, const std::string& userId);

    static bool PostPlayersPositionLog(const std::string &projectId, const std::string &sessionId);
};

#endif //SDKCORE_H
