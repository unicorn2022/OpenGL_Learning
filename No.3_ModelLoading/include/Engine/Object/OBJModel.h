#pragma once
#include "Engine/Basic/Object.h"
#include "Engine/Object/Mesh.h"
#include "Engine/Material/INCLUDE_ALL.h"
#include "Engine/Manager/ShaderManager.h"
#include "Engine/Manager/TextureManager.h"
#include "Engine/Manager/MaterialManager.h"

class OBJModel : public Object {
public:
    /** OBJ模型
     * \param name 模型名称
     * \param parent 父对象
     */
    OBJModel(std::string name, Object* parent) : Object(name, NULL, parent) {
        this->directory = model_root_path + name + "/";
        this->path = directory + name + ".obj";
        this->count = 0;
        RenderInit();        
    }

    ~OBJModel() {
        for (auto mesh : meshs) 
            delete mesh;
        meshs.clear();
    }


public:
    virtual void GameTick() { }
    virtual void RenderTick(Camera* camera) {
        for (auto mesh : meshs) 
            mesh->RenderTick(camera);
    }

private:
    std::string directory;              // 模型目录, 含末尾`/`
    std::string path;                   // 模型路径
    std::vector<Mesh*> meshs;           // 网格体
    int count;

private:
    void GameInit() {}
    
    void RenderInit() {
        /* 加载模型 */
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "[ERROR::OBJModel.h::RenderInit()] 模型加载失败: " << importer.GetErrorString() << std::endl;
            return;
        }
        /* 处理节点 */
        ProcessNode(scene->mRootNode, scene);
    }

    /** 处理 assimp 节点
     * \param node assimp 节点
     * \param scene assimp 场景
     */
    void ProcessNode(aiNode* node, const aiScene* scene) {
        // 1. 处理所有的网格体
        for (int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh, scene);
        }
        // 2. 递归处理子节点
        for (int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    /** 处理 assimp 网格体, 并将其添加到 vector<Mesh*>meshs 中
     * \param ai_mesh assimp 网格体
     * \param scene assimp 场景
     */
    void ProcessMesh(aiMesh* ai_mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // 1. 处理顶点
        for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++) {
            Vertex vertex;
            // 1.1 位置
            vertex.Position.x = ai_mesh->mVertices[i].x;
            vertex.Position.y = ai_mesh->mVertices[i].y;
            vertex.Position.z = ai_mesh->mVertices[i].z;
            // 1.2 法线
            vertex.Normal.x = ai_mesh->mNormals[i].x;
            vertex.Normal.y = ai_mesh->mNormals[i].y;
            vertex.Normal.z = ai_mesh->mNormals[i].z;
            // 1.3 UV坐标
            if (ai_mesh->mTextureCoords[0]) {
                vertex.TexCoords.x = ai_mesh->mTextureCoords[0][i].x;
                vertex.TexCoords.y = ai_mesh->mTextureCoords[0][i].y;
            } else {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }
        // 2. 处理索引
        for (int i = 0; i < ai_mesh->mNumFaces; i++) {
            aiFace face = ai_mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // 3. 处理材质
        Material* material;
        if (ai_mesh->mMaterialIndex >= 0) {
            aiMaterial* mat = scene->mMaterials[ai_mesh->mMaterialIndex];
            Texture* diffuse = ProcessTexture(mat, aiTextureType_DIFFUSE);
            Texture* specular = ProcessTexture(mat, aiTextureType_SPECULAR);
            material = new PhongMaterial(ShaderManager::GetInstance().phong_light_model_shader, diffuse, specular);
            MaterialManager::GetInstance().AddOBJMaterial(material);
        } else {
            material = new BasicMaterial(ShaderManager::GetInstance().basic_shader);
        }
        // 4. 保存到meshs中
        Mesh* mesh = new Mesh(name + std::to_string(count++), material, vertices, indices, this);
        meshs.push_back(mesh);
    }

    /** 处理 assimp 纹理, 并将其添加到 TextureManager 中
     * \param mat assimp 材质
     * \param type assimp 纹理类型
     * \return 材质中, 对应类型的第一张纹理
     */
    Texture* ProcessTexture(aiMaterial* mat, aiTextureType type) {
        Texture* first_texture = NULL;
        for (int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString file_name;
            mat->GetTexture(type, i, &file_name);
            Texture* texture = TextureManager::GetInstance().AddOBJTexture(directory, file_name.C_Str());
            if (first_texture == NULL) first_texture = texture;
        }
        return first_texture;
    }
};