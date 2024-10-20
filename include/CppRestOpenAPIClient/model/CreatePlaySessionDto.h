/**
 * API Documentation
 * The API description
 *
 * The version of the OpenAPI document: 0.0.1
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 7.8.0.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */

/*
 * CreatePlaySessionDto.h
 *
 * 
 */

#ifndef ORG_OPENAPITOOLS_CLIENT_MODEL_CreatePlaySessionDto_H_
#define ORG_OPENAPITOOLS_CLIENT_MODEL_CreatePlaySessionDto_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace org {
namespace openapitools {
namespace client {
namespace model {



/// <summary>
/// 
/// </summary>
class  CreatePlaySessionDto
    : public ModelBase
{
public:
    CreatePlaySessionDto();
    virtual ~CreatePlaySessionDto();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// CreatePlaySessionDto members

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getName() const;
    bool nameIsSet() const;
    void unsetName();

    void setName(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getDeviceId() const;
    bool deviceIdIsSet() const;
    void unsetDeviceId();

    void setDeviceId(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getPlatform() const;
    bool platformIsSet() const;
    void unsetPlatform();

    void setPlatform(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getAppVersion() const;
    bool appVersionIsSet() const;
    void unsetAppVersion();

    void setAppVersion(const utility::string_t& value);


protected:
    utility::string_t m_Name;
    bool m_NameIsSet;
    utility::string_t m_DeviceId;
    bool m_DeviceIdIsSet;
    utility::string_t m_Platform;
    bool m_PlatformIsSet;
    utility::string_t m_AppVersion;
    bool m_AppVersionIsSet;
};


}
}
}
}

#endif /* ORG_OPENAPITOOLS_CLIENT_MODEL_CreatePlaySessionDto_H_ */
