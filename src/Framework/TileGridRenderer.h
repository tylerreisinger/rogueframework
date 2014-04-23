#ifndef TILEGRIDRENDERER_H_
#define TILEGRIDRENDERER_H_

#include "TileGrid.h"

#include "Framework/Gl/VertexArrayObject.h"
#include "Framework/Gl/VertexBufferObject.h"
#include "Framework/Gl/IndexBufferObject.h"
#include "Framework/Matrix3.h"

namespace rf
{
class TileSet;
namespace gl
{
class ShaderProgram;
}


class TileGridRenderer
{
public:
	TileGridRenderer(std::shared_ptr<gl::ShaderProgram> shader, gl::Context* context,
			const Matrix3f& transform, const TileGrid* grid, TileSet* tileSet);
	~TileGridRenderer() = default;

	TileGridRenderer(const TileGridRenderer&) = delete;
	TileGridRenderer(TileGridRenderer&&) = delete;
	TileGridRenderer& operator =(const TileGridRenderer&) = delete;
	TileGridRenderer& operator =(TileGridRenderer&&) = delete;

	void render(const Vector2i& location);

	static std::shared_ptr<gl::ShaderProgram> createDefaultShaders(gl::Context* context);

protected:

	struct DynVertexAttribs
	{
		float ux;
		float uy;
		float uz;

		uint32_t fgColor;
		uint32_t bgColor;
	};

	void initializeStaticBuffers();
	void fillDynamicAttributeBuffer();
	void createVertexArrayObject();

	gl::Context* m_context;

	const TileGrid* m_grid;
	TileSet* m_tileSet;

	gl::VertexArrayObject m_vao;
	gl::VertexBufferObject m_vertexBuffer;
	gl::VertexBufferObject m_colorTexCoordBuffer;
	gl::IndexBufferObject m_indexBuffer;

	Matrix3f m_projectionTransform;

	std::shared_ptr<gl::ShaderProgram> m_shader;

	static constexpr int dynComponentsPerVertex = 7;
	static constexpr int staticComponentsPerVertex = 2;
	static constexpr int verticesPerTile = 4;




};

}

#endif
