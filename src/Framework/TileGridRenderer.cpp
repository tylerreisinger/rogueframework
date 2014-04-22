#include "Framework/TileGridRenderer.h"

#include "Framework/Gl/ShaderProgram.h"
#include "Framework/TileSet.h"

namespace rf
{

TileGridRenderer::TileGridRenderer(std::shared_ptr<gl::ShaderProgram> shader,
		gl::Context* context, const TileGrid* grid, TileSet* tileSet):
	m_shader(std::move(shader)),
	m_context(context), m_grid(grid), m_tileSet(tileSet),
	m_vertexBuffer(gl::VertexBufferObject::UsageType::StaticDraw, context),
	m_colorTexCoordBuffer(gl::VertexBufferObject::UsageType::StreamDraw, context),
	m_indexBuffer(gl::BufferObject::UsageType::StaticDraw, gl::IndexBufferObject::IndexFormat::UInt, context),
	m_vao(context)
{
	m_colorTexCoordBuffer.bind();
	m_colorTexCoordBuffer.allocate(m_grid->width() * m_grid->height() * verticesPerTile * sizeof(DynVertexAttribs));

	initializeStaticBuffers();

	m_vao.bind();
	m_vao.attachVertexBuffer(0, 2, gl::VertexBufferObject::ComponentType::Float,
			&m_vertexBuffer, 0, 0, false);
	m_vao.attachVertexBuffer(1, 3, gl::VertexBufferObject::ComponentType::Float,
			&m_colorTexCoordBuffer, offsetof(DynVertexAttribs, ux), sizeof(DynVertexAttribs), false);
	m_vao.attachVertexBuffer(2, 4, gl::VertexBufferObject::ComponentType::UByte,
			&m_colorTexCoordBuffer, offsetof(DynVertexAttribs, color), sizeof(DynVertexAttribs), true);
	m_vao.setIndexBuffer(&m_indexBuffer);
	context->unbindVertexArray();

	m_projectionTransform = Matrix3f::orthographicProjection(0, 800, 600, 0);
}

void TileGridRenderer::render(const Vector2i& location)
{
	const int gridWidth = m_grid->width();
	const int gridHeight = m_grid->height();
	const int tileWidth = m_tileSet->tileWidth();
	const int tileHeight = m_tileSet->tileHeight();

	Matrix3f transform = m_projectionTransform * Matrix3f::translation(location.x, location.y);

	m_colorTexCoordBuffer.invalidate();
	{
		auto dynBufferMapping = m_colorTexCoordBuffer.map<DynVertexAttribs>(gl::BufferObject::MappingOptions::Write);
		for(int y = 0; y < gridWidth; ++y)
		{
			for(int x = 0; x < gridHeight; ++x)
			{
				int index = x + y * gridWidth;
				int vertexIndex = index * 4;
				const Tile& tile = m_grid->getTile(index);
				TileSet::TileLocation loc = m_tileSet->getTileLocation(tile.tileIndex());
				uint32_t color = tile.foregroundColor().toRGBAEndianAware();
				if(x == 0 && y == 0)
				{
					glActiveTexture(GL_TEXTURE0);
					loc.texture->bind();
				}

				dynBufferMapping[vertexIndex].ux = loc.bottomLeft.x;
				dynBufferMapping[vertexIndex].uy = loc.bottomLeft.y;
				dynBufferMapping[vertexIndex].uz = loc.layer;
				dynBufferMapping[vertexIndex].color = color;
				vertexIndex += 1;
				dynBufferMapping[vertexIndex].ux = loc.bottomLeft.x;
				dynBufferMapping[vertexIndex].uy = loc.topRight.y;
				dynBufferMapping[vertexIndex].uz = loc.layer;
				dynBufferMapping[vertexIndex].color = color;
				vertexIndex += 1;
				dynBufferMapping[vertexIndex].ux = loc.topRight.x;
				dynBufferMapping[vertexIndex].uy = loc.topRight.y;
				dynBufferMapping[vertexIndex].uz = loc.layer;
				dynBufferMapping[vertexIndex].color = color;
				vertexIndex += 1;
				dynBufferMapping[vertexIndex].ux = loc.topRight.x;
				dynBufferMapping[vertexIndex].uy = loc.bottomLeft.y;
				dynBufferMapping[vertexIndex].uz = loc.layer;
				dynBufferMapping[vertexIndex].color = color;
			}
		}
	}

	m_shader->bind();
	m_vao.bind();
	m_shader->setUniformValue("transform", transform);
	m_shader->setUniformValue("texSampler", 0);
	glDrawElements(GL_TRIANGLES, 6 * gridWidth * gridHeight, GL_UNSIGNED_INT, nullptr);
}

void TileGridRenderer::initializeStaticBuffers()
{
	m_vertexBuffer.bind();
	m_vertexBuffer.allocate(m_grid->width() * m_grid->height() * verticesPerTile * staticComponentsPerVertex * sizeof(float));
	m_indexBuffer.bind();
	m_indexBuffer.allocate(m_grid->width() * m_grid->height() * 6 * sizeof(int));
	m_vertexBuffer.bind();
	auto map = m_vertexBuffer.map<float>(gl::BufferObject::MappingOptions::Write);
	m_indexBuffer.bind();
	auto indexMap = m_indexBuffer.map<unsigned int>(gl::BufferObject::MappingOptions::Write);

	const int gridWidth = m_grid->width();
	const int gridHeight = m_grid->height();
	const int tileWidth = m_tileSet->tileWidth();
	const int tileHeight = m_tileSet->tileHeight();

	for(int y = 0; y < gridHeight; ++y)
	{
		for(int x = 0; x < gridWidth; ++x)
		{
			int quadIndex = x + y * gridWidth;
			int vertIndex = quadIndex * 4;
			int componentIndexStart = vertIndex;
			int componentIndex = vertIndex * 2;
			int indexIndex = quadIndex * 6;

			map[componentIndex++] = x * tileWidth;
			map[componentIndex++] = y * tileHeight;
			map[componentIndex++] = x * tileWidth;
			map[componentIndex++] = (y + 1) * tileHeight;
			map[componentIndex++] = (x + 1) * tileWidth;
			map[componentIndex++] = (y + 1) * tileHeight;
			map[componentIndex++] = (x + 1) * tileWidth;
			map[componentIndex] = y * tileHeight;

			indexMap[indexIndex++] = componentIndexStart;
			indexMap[indexIndex++] = componentIndexStart + 1;
			indexMap[indexIndex++] = componentIndexStart + 2;
			indexMap[indexIndex++] = componentIndexStart + 2;
			indexMap[indexIndex++] = componentIndexStart + 3;
			indexMap[indexIndex] = componentIndexStart;
		}
	}
}

}
