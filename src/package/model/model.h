#ifndef __MODEL_MODEL_H
#define __MODEL_MODEL_H

#include <string>
#include <vector>
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
    private:
        // var
        std::string m_filepath;
        std::string m_directory;
        std::vector<Mesh*> m_meshes;
        std::vector<Texture2D> m_loadedTexturesCache;

        // fn
        void loadModel(const std::string& filepath);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture2D> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, Texture::Type txType);

    public:
        Model(const std::string& filepath);
        ~Model();

        void draw(Shader& shader);
};

#endif//__MODEL_MODEL_H