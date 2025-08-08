/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <string>
#include <glad/glad.h>

#include "Lumin/Core/stb_image.h"

namespace Lumin {
namespace Renderer {
class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int unit = 0) const;
    GLuint GetID() const { return m_ID; }
private:
    GLuint m_ID;
};

}
}