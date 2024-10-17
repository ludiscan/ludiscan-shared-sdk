//
// Created by matuyuhi on 2024/10/17.
//

#ifndef BINARYBODY_H
#define BINARYBODY_H

#include "CppRestOpenAPIClient/IHttpBody.h"
#include <memory>
#include <istream>

namespace org {
    namespace openapitools {
        namespace client {
            namespace model {

                class BinaryBody : public IHttpBody
                {
                public:
                    BinaryBody(std::shared_ptr<std::istream> stream)
                        : m_Stream(stream)
                    {}

                    virtual void write_to(std::ostream& outputStream) const {
                        if(m_Stream && *m_Stream)
                        {
                            outputStream << m_Stream->rdbuf();
                        }
                    }

                    virtual size_t length() const {
                        // 必要に応じて実装
                        return 0;
                    }

                    virtual bool isBinary() const {
                        return true;
                    }

                private:
                    std::shared_ptr<std::istream> m_Stream;
                };

            }
        }
    }
}

#endif //BINARYBODY_H
