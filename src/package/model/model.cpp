#include "model.h"
#include <format>

void Model::loadModel(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << std::format("[Assimp ERR] {}", importer.GetErrorString()) << std::endl;
        return;
    }
    m_directory = filepath.substr(0, filepath.find_last_of("/"));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(this->processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vert;
        vert.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        vert.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
        vert.texcoords = (mesh->mTextureCoords[0])
            ? glm::vec2( mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y ) 
            : glm::vec2( 0.0f, 0.0f );
        vertices.push_back(vert);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace f = mesh->mFaces[i];
        for (unsigned int j = 0; j < f.mNumIndices; ++j) {
            indices.push_back(f.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffMaps = this->loadMaterialTextures(mat, aiTextureType_DIFFUSE, Texture::Type::Diffuse);
        std::vector<Texture> specMaps = this->loadMaterialTextures(mat, aiTextureType_SPECULAR, Texture::Type::Specular);
        for (auto& m : diffMaps) textures.push_back(m);
        for (auto& m : specMaps) textures.push_back(m);
    }

    return Mesh(vertices, indices, textures);
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, Texture::Type txType)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); ++i)
    {
        aiString str;
        mat->GetTexture(aiType, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < m_loadedTexturesCache.size(); ++j) {
            if (m_loadedTexturesCache[j].getFilepath() == std::string(str.C_Str())) {
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture tex(m_directory + "/" + std::string(str.C_Str()), txType);
            textures.push_back(tex);
            m_loadedTexturesCache.push_back(tex);
        }
    }
    return textures;
}

Model::Model(const std::string &filepath)
{
    this->loadModel(filepath);
}

void Model::draw(Shader& shader)
{
    for (auto& m : m_meshes) {
        m.draw(shader);
    }
}
