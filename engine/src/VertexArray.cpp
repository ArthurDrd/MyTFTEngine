#include "VertexArray.h"
#include <glad/glad.h>

namespace MyTFTEngine {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:    return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:    return GL_INT;
        case ShaderDataType::Bool:    return GL_BOOL;
        default: break;
        }
        return 0;
    }

    VertexArray::VertexArray() {
        glCreateVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
        Bind();
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        unsigned int index = 0;

        for (const auto& element : layout) {
            switch (element.Type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4: {
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(
                    index,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (const void*)element.Offset
                );
                index++;
                break;
            }
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
            case ShaderDataType::Bool: {
                glEnableVertexAttribArray(index);
                glVertexAttribIPointer(
                    index,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    layout.GetStride(),
                    (const void*)element.Offset
                );
                index++;
                break;
            }
            default: break;
            }
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
        Bind();
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }

}