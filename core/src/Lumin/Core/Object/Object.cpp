/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#include "Lumin/Core/Object/Object.h"
#include "Lumin/Core/Renderer/Renderer.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <filesystem>
#include <glm/glm.hpp>

namespace Lumin {
namespace Object {

Object::Object(const std::string& name, const float* vertices, size_t vertexCount, const float* colors, size_t colorCount, const unsigned int* indices, size_t indexCount, const float* uvs, size_t uvCount, const float* normals, size_t normalCount, ObjectShaderProgram objectShaderProgram)
    : name(name), vertexCount(vertexCount), colorCount(colorCount), indexCount(indexCount), uvCount(uvCount), normalCount(normalCount), objectShaderProgram(objectShaderProgram), texture(nullptr)
{
    this->vertices = new float[vertexCount];
    std::memcpy(this->vertices, vertices, vertexCount * sizeof(float));
    this->colors = new float[colorCount];
    std::memcpy(this->colors, colors, colorCount * sizeof(float));
    this->indices = new unsigned int[indexCount];
    std::memcpy(this->indices, indices, indexCount * sizeof(unsigned int));
    this->uvs = new float[uvCount];
    std::memcpy(this->uvs, uvs, uvCount * sizeof(float));
    this->normals = new float[normalCount];
    std::memcpy(this->normals, normals, normalCount * sizeof(float));
    Init();
    ObjectsManager::AddObject(this);
}

Object::~Object()
{
    delete[] vertices;
    delete[] colors;
    delete[] indices;
    delete[] uvs;
    delete[] normals;
}

GLuint Object::GetVAO()
{
    return VAO;
}

void Object::Init()
{
    shaderProgram = Lumin::Renderer::CreateShaderProgram(objectShaderProgram.vertexShader, objectShaderProgram.fragmentShader);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(4, VBO); // 0: vertices, 1: colors, 2: uvs, 3: normals
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // VBO 0: vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // VBO 1: colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorCount * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    // VBO 2: uvs
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, uvCount * sizeof(float), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    // VBO 3: normals
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, normalCount * sizeof(float), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static std::map<std::string, Lumin::Object::OBJMaterial> LoadMTL(const std::string& mtlPath, const std::string& baseDir) {
    std::map<std::string, Lumin::Object::OBJMaterial> materials;
    std::ifstream file(mtlPath);
    if (!file.is_open()) return materials;
    std::string line, current;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "newmtl") {
            iss >> current;
            materials[current] = Lumin::Object::OBJMaterial();
            materials[current].name = current;
        } else if (prefix == "Kd" && !current.empty()) {
            float r, g, b; iss >> r >> g >> b;
            materials[current].diffuseColor = glm::vec3(r, g, b);
        } else if (prefix == "map_Kd" && !current.empty()) {
            std::string tex; iss >> tex;
            materials[current].diffuseTexPath = baseDir + "/" + tex;
        }
    }
    return materials;
}

static std::string GetBaseDir(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) return ".";
    return path.substr(0, pos);
}

Object* Object::FromOBJ(const std::string& path, ObjectShaderProgram objectShaderProgram) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[OBJ] Failed to open file: " << path << std::endl;
        return nullptr;
    }
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    struct Index { int v, vt, vn; };
    std::vector<Index> indices;
    std::vector<int> faceMaterialIndices;
    std::vector<Lumin::Object::OBJMaterial> materialsVec;
    std::map<std::string, Lumin::Object::OBJMaterial> materialsMap;
    std::string currentMtl;
    std::string baseDir = GetBaseDir(path);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "mtllib") {
            std::string mtlFile; iss >> mtlFile;
            std::string mtlPath = baseDir + "/" + mtlFile;
            materialsMap = LoadMTL(mtlPath, baseDir);
        } else if (prefix == "usemtl") {
            iss >> currentMtl;
            if (materialsMap.count(currentMtl) &&
                (materialsVec.empty() || materialsVec.back().name != currentMtl)) {
                materialsVec.push_back(materialsMap[currentMtl]);
            }
        } else if (prefix == "v") {
            glm::vec3 v; iss >> v.x >> v.y >> v.z;
            temp_vertices.push_back(v);
        } else if (prefix == "vt") {
            glm::vec2 uv; iss >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        } else if (prefix == "vn") {
            glm::vec3 n; iss >> n.x >> n.y >> n.z;
            temp_normals.push_back(n);
        } else if (prefix == "f") {
            std::vector<Index> face;
            std::string vert;
            while (iss >> vert) {
                Index idx = {0, -1, -1};
                size_t firstSlash = vert.find('/');
                size_t secondSlash = vert.find('/', firstSlash + 1);
                idx.v = std::stoi(vert.substr(0, firstSlash)) - 1;
                if (firstSlash != std::string::npos) {
                    if (secondSlash == std::string::npos) {
                        idx.vt = std::stoi(vert.substr(firstSlash + 1)) - 1;
                    } else {
                        if (secondSlash > firstSlash + 1)
                            idx.vt = std::stoi(vert.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
                        if (vert.length() > secondSlash + 1)
                            idx.vn = std::stoi(vert.substr(secondSlash + 1)) - 1;
                    }
                }
                face.push_back(idx);
            }
            for (size_t i = 1; i + 1 < face.size(); ++i) {
                indices.push_back(face[0]);
                indices.push_back(face[i]);
                indices.push_back(face[i+1]);
                int matIdx = 0;
                for (size_t m = 0; m < materialsVec.size(); ++m) {
                    if (materialsVec[m].name == currentMtl) { matIdx = (int)m; break; }
                }
                faceMaterialIndices.push_back(matIdx);
            }
        }
    }
    if (indices.empty()) {
        std::cerr << "[OBJ] No faces found in: " << path << std::endl;
        return nullptr;
    }
    for (auto& mat : materialsVec) {
        if (!mat.diffuseTexPath.empty()) {
            mat.texture = new Lumin::Renderer::Texture(mat.diffuseTexPath);
        }
    }
    std::vector<float> vertices, colors, uvs, normals;
    std::vector<unsigned int> out_indices;
    std::vector<int> out_materialIndices;
    for (size_t i = 0; i < indices.size(); ++i) {
        const Index& idx = indices[i];
        glm::vec3 v = temp_vertices[idx.v];
        glm::vec2 uv = (idx.vt >= 0 && idx.vt < (int)temp_uvs.size()) ? temp_uvs[idx.vt] : glm::vec2(0.0f);
        glm::vec3 n = (idx.vn >= 0 && idx.vn < (int)temp_normals.size()) ? temp_normals[idx.vn] : glm::vec3(0.0f, 1.0f, 0.0f);
        vertices.push_back(v.x); vertices.push_back(v.y); vertices.push_back(v.z);
        colors.push_back(1.0f); colors.push_back(1.0f); colors.push_back(1.0f);
        uvs.push_back(uv.x); uvs.push_back(uv.y);
        normals.push_back(n.x); normals.push_back(n.y); normals.push_back(n.z);
        out_indices.push_back((unsigned int)i);
    }
    out_materialIndices = faceMaterialIndices;
    Object* obj = new Object(path, vertices.data(), vertices.size(), colors.data(), colors.size(), out_indices.data(), out_indices.size(), uvs.data(), uvs.size(), normals.data(), normals.size(), objectShaderProgram);
    obj->materials = materialsVec;
    obj->materialIndices = out_materialIndices;
    return obj;
}

void Object::SetTexture(Lumin::Renderer::Texture* texture) {
    this->texture = texture;
}

void Object::SetMaterialUniforms(int materialIdx) {
    OBJMaterial& mat = materials[materialIdx];
    GLuint program = shaderProgram.getId();
    GLint useTextureLoc = glGetUniformLocation(program, "useTexture");
    GLint matColorLoc = glGetUniformLocation(program, "materialColor");
    if (mat.texture) {
        mat.texture->Bind(0);
        glUniform1i(glGetUniformLocation(program, "texture1"), 0);
        glUniform1i(useTextureLoc, 1);
    } else {
        glUniform1i(useTextureLoc, 0);
        glUniform3fv(matColorLoc, 1, &mat.diffuseColor[0]);
    }
}

glm::mat4 Object::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0,0,1));
    model = glm::scale(model, scale);
    return model;
}

void Object::Draw()
{
    Lumin::Renderer::UpdateMVP();
    glUseProgram(shaderProgram.getId());
    Lumin::Renderer::SetLightsUniforms(shaderProgram);
    glm::mat4 model = GetModelMatrix();
    GLuint modelLoc = glGetUniformLocation(shaderProgram.getId(), "Model");
    if (modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    GLuint mvpLoc = glGetUniformLocation(shaderProgram.getId(), "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &Lumin::Renderer::MVP[0][0]);
    if (!materials.empty() && !materialIndices.empty()) {
        glBindVertexArray(VAO);
        size_t triCount = materialIndices.size();
        for (size_t i = 0; i < triCount; ++i) {
            SetMaterialUniforms(materialIndices[i]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * 3 * sizeof(unsigned int)));
        }
        glBindVertexArray(0);
    } else {
        GLuint useTextureLoc = glGetUniformLocation(shaderProgram.getId(), "useTexture");
        glUniform1i(useTextureLoc, texture ? 1 : 0);
        if (texture) {
            texture->Bind(0);
            glUniform1i(glGetUniformLocation(shaderProgram.getId(), "texture1"), 0);
        }
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

}
}