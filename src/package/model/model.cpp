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
    std::vector<unsigned int> indices;
    std::vector<Texture2D> textures;

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

    aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture2D> diffMaps = this->loadMaterialTextures(mat, aiTextureType_DIFFUSE, Texture::Type::Diffuse);
    std::vector<Texture2D> specMaps = this->loadMaterialTextures(mat, aiTextureType_SPECULAR, Texture::Type::Specular);
    for (auto& m : diffMaps) textures.push_back(m);
    for (auto& m : specMaps) textures.push_back(m);

    return new Mesh(vertices, indices, textures);
}

static unsigned int loadTextureFromFile(const std::string& filepath)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filepath << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

std::vector<Texture2D> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, Texture::Type txType)
{
    std::vector<Texture2D> textures;
    // std::cout << ((aiType == aiTextureType_DIFFUSE)? "[diffuse] " : "[specular] ") << mat->GetTextureCount(aiType) << std::endl;
    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); ++i)
    {
        aiString file;
        mat->GetTexture(aiType, i, &file);
        std::string filepath = m_directory + "/" + std::string(file.C_Str());

        bool skip = false;
        for (unsigned int j = 0; j < m_loadedTexturesCache.size(); ++j) {
            // std::cout << m_loadedTexturesCache[j].path << " <compare> " << filepath << std::endl;
            if (m_loadedTexturesCache[j].path == filepath) {
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture2D tex = {
                .id = loadTextureFromFile(filepath),
                .type = txType,
                .path = filepath
            };
            textures.push_back(tex);
            m_loadedTexturesCache.push_back(tex);
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
