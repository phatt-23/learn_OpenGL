#include "model.h"
#include <format>
#include "../../vendor/stb/stb_image.h"

void Model::loadModel(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << std::format("[Assimp ERR] {}", importer.GetErrorString()) << std::endl;
        return;
    }
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

Mesh* Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vert;
        vert.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        vert.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
        vert.texcoords = (mesh->mTextureCoords[0])
            ? glm::vec2( mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y ) 
            : glm::vec2( 0.0f, 0.0f );
        vertices.push_back(vert);
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace f = mesh->mFaces[i];
        for (unsigned int j = 0; j < f.mNumIndices; ++j) {
            indices.push_back(f.mIndices[j]);
        }
    }

    aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
    
    if (true) 
    {
        std::vector<Texture2D> textures;
        std::vector<Texture2D> diffMaps = this->loadMaterialTextures_Texture2D(mat, aiTextureType_DIFFUSE, Texture::Type::Diffuse);
        std::vector<Texture2D> specMaps = this->loadMaterialTextures_Texture2D(mat, aiTextureType_SPECULAR, Texture::Type::Specular);
        for (auto& m : diffMaps) textures.push_back(m);
        for (auto& m : specMaps) textures.push_back(m);
        return new Mesh(vertices, indices, textures);
    }
    else 
    {
        std::vector<Texture> textures;
        std::vector<Texture> diffMaps = this->loadMaterialTextures_Texture(mat, aiTextureType_DIFFUSE, Texture::Type::Diffuse);
        std::vector<Texture> specMaps = this->loadMaterialTextures_Texture(mat, aiTextureType_SPECULAR, Texture::Type::Specular);
        for (auto& m : diffMaps) textures.push_back(m);
        for (auto& m : specMaps) textures.push_back(m);
        return new Mesh(vertices, indices, textures);
    }
}

std::vector<Texture2D> Model::loadMaterialTextures_Texture2D(aiMaterial* mat, aiTextureType aiType, Texture::Type txType)
{
    std::vector<Texture2D> textures;
    // std::cout << ((aiType == aiTextureType_DIFFUSE)? "[diffuse] " : "[specular] ") << mat->GetTextureCount(aiType) << std::endl;
    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); ++i)
    {
        aiString file;
        mat->GetTexture(aiType, i, &file);
        std::string filepath = m_directory + "/" + std::string(file.C_Str());

        bool skip = false;
        for (unsigned int j = 0; j < m_loadedTexture2DCache.size(); ++j) {
            // std::cout << m_loadedTexturesCache[j].path << " <compare> " << filepath << std::endl;
            if (m_loadedTexture2DCache[j].path == filepath) {
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture2D tex(filepath, txType);
            std::cout << "[Model loadMatTex Texture2D] [INFO] " << tex.id << " " << (int)tex.type << ", " << tex.path << std::endl;
            textures.push_back(tex);
            m_loadedTexture2DCache.push_back(tex);
        }
    }
    return textures;
}

std::vector<Texture> Model::loadMaterialTextures_Texture(aiMaterial *mat, aiTextureType aiType, Texture::Type txType)
{
    std::vector<Texture> textures;
    // std::cout << ((aiType == aiTextureType_DIFFUSE)? "[diffuse] " : "[specular] ") << mat->GetTextureCount(aiType) << std::endl;
    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); ++i)
    {
        aiString file;
        mat->GetTexture(aiType, i, &file);
        std::string filepath = m_directory + "/" + std::string(file.C_Str());

        bool skip = false;
        for (unsigned int j = 0; j < m_loadedTextureCache.size(); ++j) {
            // std::cout << m_loadedTexturesCache[j].path << " <compare> " << filepath << std::endl;
            if (m_loadedTextureCache[j].getFilepath() == filepath) {
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture tex(filepath, txType);
            std::cout << "[Model loadMatTex Texture] [INFO] " << tex.getId() << ", " << (int)tex.getType() << ", " << tex.getFilepath() << std::endl;
            textures.push_back(tex);
            m_loadedTextureCache.push_back(tex);
        }
    }
    return textures;
}

Model::Model(const std::string &filepath)
    : m_filepath(filepath)
    , m_directory(filepath.substr(0, filepath.find_last_of("/")))
{
    this->loadModel(filepath);
}

Model::~Model()
{
    for (auto& m : m_meshes) delete m;
}

void Model::draw(Shader& shader)
{
    for (auto& m : m_meshes) {
        m->draw(shader);
    }
}
