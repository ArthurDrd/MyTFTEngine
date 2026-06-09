#pragma once

#include "Buffer.h"
#include <memory>

namespace MyTFTEngine {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) const;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        unsigned int m_RendererID;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };

}