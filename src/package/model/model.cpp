#include "model.h"
#include <format>
#include "../../vendor/stb/stb_image.h"

void Model::loadModel(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or !scene->mRootNode)
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
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) 
    {
        Vertex vert;
        vert.position.x = mesh->mVertices[i].x;
        vert.position.y = mesh->mVertices[i].y;
        vert.position.z = mesh->mVertices[i].z;
        
        if (mesh->HasNormals()) {
            vert.normal.x = mesh->mNormals[i].x;
            vert.normal.y = mesh->mNormals[i].y;
            vert.normal.z = mesh->mNormals[i].z;
        }

        if (mesh->mTextureCoords[0]) {
            vert.texCoords.x = mesh->mTextureCoords[0][i].x;
            vert.texCoords.y = mesh->mTextureCoords[0][i].y;
            if (mesh->HasTangentsAndBitangents()) {

            vert.tangent.x = mesh->mTangents[i].x;
            vert.tangent.y = mesh->mTangents[i].y; 
            vert.tangent.z = mesh->mTangents[i].z; 

            vert.bitangent.x = mesh->mBitangents[i].x;
            vert.bitangent.y = mesh->mBitangents[i].y; 
            vert.bitangent.z = mesh->mBitangents[i].z; 
            }
        } else vert.texCoords = glm::vec2( 0.0f, 0.0f );

        vertices.push_back(vert);
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
    {
        aiFace f = mesh->mFaces[i];
        for (unsigned int j = 0; j < f.mNumIndices; ++j) {
            indices.push_back(f.mIndices[j]);
        }
    }
    
    aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
    aiColor3D color;
    mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);

    std::vector<Texture2D*> diffMaps   = this->loadMaterialTextures_Texture2D(mat, aiTextureType_DIFFUSE);
    std::vector<Texture2D*> specMaps   = this->loadMaterialTextures_Texture2D(mat, aiTextureType_SPECULAR);
    // std::vector<Texture2D*> normalMaps = this->loadMaterialTextures_Texture2D(mat, aiTextureType_NORMALS);
    // std::vector<Texture2D*> heihtMaps  = this->loadMaterialTextures_Texture2D(mat, aiTextureType_HEIGHT);

    std::vector<Texture2D*> textures;
    textures.insert(textures.end(), diffMaps.begin(), diffMaps.end());
    textures.insert(textures.end(), specMaps.begin(), specMaps.end());
    // textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // textures.insert(textures.end(), heihtMaps.begin(), heihtMaps.end());

    return new Mesh(vertices, indices, textures);
}

std::vector<Texture2D*> Model::loadMaterialTextures_Texture2D(aiMaterial* mat, aiTextureType aiType)
{
    std::vector<Texture2D*> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); ++i)
    {
        aiString file;
        mat->GetTexture(aiType, i, &file);
        std::string filepath = m_directory + "/" + std::string(file.C_Str());

        bool skip = false;
        if (m_loadedTexture2DCache.find(filepath) != m_loadedTexture2DCache.end()) {
            skip = true;
        }

        if (!skip) {
            Texture2D::Type type = [aiType] {
                switch (aiType) {
                    case aiTextureType::aiTextureType_DIFFUSE: return Texture2D::Type::Diffuse;
                    case aiTextureType::aiTextureType_SPECULAR: return Texture2D::Type::Specular;
                    // case aiTextureType::aiTextureType_NORMALS: return Texture2D::Type::Normal;
                    // case aiTextureType::aiTextureType_HEIGHT: return Texture2D::Type::Height;
                    default: throw std::runtime_error(std::format("Unsupported aiTextureType {}", (int)aiType));
                }
            }();
            Texture2D* tex = new Texture2D(filepath, type);
            textures.push_back(tex);
            m_loadedTexture2DCache[filepath] = tex;
            // std::cout << "[Model loadMatTex Texture2D] [INFO] " << tex->getId() << " " << (int)tex->getType() << ", " << tex->getFilepath() << std::endl;
        }
    }
    return textures;
}

Model::Model()
{
}

Model::Model(const std::string &filepath)
    : m_filepath(filepath), m_directory(filepath.substr(0, filepath.find_last_of("/")))
{
    this->loadModel(filepath);
}

Model::~Model()
{
    for (auto& m : m_meshes) {
        delete m;
    }
}

void Model::draw(Shader& shader)
{
    for (auto& m : m_meshes) {
        m->draw(shader);
    }
}
