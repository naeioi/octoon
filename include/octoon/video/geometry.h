#ifndef OCTOON_GEOMETRY_H_
#define OCTOON_GEOMETRY_H_

#include <octoon/video/render_object.h>
#include <octoon/hal/graphics_data.h>

namespace octoon
{
	namespace video
	{
		class OCTOON_EXPORT Geometry final : public RenderObject
		{
			OctoonDeclareSubClass(Geometry, RenderObject)
		public:
			Geometry() noexcept;
			~Geometry() noexcept;

			void setCastShadow(bool enable) noexcept;
			bool getCastShadow() const noexcept;

			void setReceiveShadow(bool enable) noexcept;
			bool getReceiveShadow() const noexcept;

			void setMaterial(MaterialPtr&& material) noexcept;
			void setMaterial(const MaterialPtr& material) noexcept;
			const MaterialPtr& getMaterial() const noexcept;

			void setDrawType(DrawType type) noexcept;
			DrawType getDrawType() const noexcept;

			void setNumVertices(std::uint32_t numVertice) noexcept;
			std::uint32_t getNumVertices() const noexcept;

			void setNumIndices(std::uint32_t numIndices) noexcept;
			std::uint32_t getNumIndices() const noexcept;

			void setVertexBuffer(const hal::GraphicsDataPtr& data) noexcept;
			const hal::GraphicsDataPtr& getVertexBuffer() const noexcept;

			void setIndexBuffer(const hal::GraphicsDataPtr& data) noexcept;
			const hal::GraphicsDataPtr& getIndexBuffer() const noexcept;

		private:

			bool isCastShadow_;
			bool isReceiveShadow_;

			std::uint32_t numVertices_;
			std::uint32_t numIndices_;

			std::intptr_t vertexOffset_;
			std::intptr_t indexOffset_;

			MaterialPtr material_;
			DrawType drawType_;
			GraphicsIndexType indexType_;
			hal::GraphicsDataPtr vertices_;
			hal::GraphicsDataPtr indices_;
		};
	}
}

#endif