#include "Framework/TileGridRenderer.h"

#include "Framework/Gl/ShaderProgram.h"
#include "Framework/TileSet.h"

#include "Framework/Gl/Shader.h"

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
			&m_colorTexCoordBuffer, offsetof(DynVertexAttribs, fgColor), sizeof(DynVertexAttribs), true);
	m_vao.attachVertexBuffer(3, 4, gl::VertexBufferObject::ComponentType::UByte,
			&m_colorTexCoordBuffer, offsetof(DynVertexAttribs, bgColor), sizeof(DynVertexAttribs), true);
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
	fillDynamicAttributeBuffer();

	m_shader->bind();
	m_vao.bind();
	m_shader->setUniformValue("transform", transform);
	m_shader->setUniformValue("texSampler", 0);
	m_context->drawIndexedPrimitives(gl::PrimitiveType::Triangles, 6 * gridWidth * gridHeight,
			gl::IndexFormat::UInt, 0);
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

void TileGridRenderer::fillDynamicAttributeBuffer()
{
	const int gridWidth = m_grid->width();
	const int gridHeight = m_grid->height();

	auto dynBufferMapping = m_colorTexCoordBuffer.map<DynVertexAttribs>(gl::BufferObject::MappingOptions::Write);
	for(int y = 0; y < gridWidth; ++y)
	{
		for(int x = 0; x < gridHeight; ++x)
		{
			int index = x + y * gridWidth;
			int vertexIndex = index * 4;
			const Tile& tile = m_grid->getTile(index);
			TileSet::TileLocation loc = m_tileSet->getTileLocation(tile.tileIndex());
			uint32_t fgColor = tile.foregroundColor().toRGBAEndianAware();
			uint32_t bgColor = tile.backgroundColor().toRGBAEndianAware();
			if(x == 0 && y == 0)
			{
				m_context->setActiveTextureUnit(0);
				loc.texture->bind();
			}

			dynBufferMapping[vertexIndex].ux = loc.bottomLeft.x;
			dynBufferMapping[vertexIndex].uy = loc.bottomLeft.y;
			dynBufferMapping[vertexIndex].uz = loc.layer;
			dynBufferMapping[vertexIndex].fgColor = fgColor;
			dynBufferMapping[vertexIndex].bgColor = bgColor;
			vertexIndex += 1;
			dynBufferMapping[vertexIndex].ux = loc.bottomLeft.x;
			dynBufferMapping[vertexIndex].uy = loc.topRight.y;
			dynBufferMapping[vertexIndex].uz = loc.layer;
			dynBufferMapping[vertexIndex].fgColor = fgColor;
			dynBufferMapping[vertexIndex].bgColor = bgColor;
			vertexIndex += 1;
			dynBufferMapping[vertexIndex].ux = loc.topRight.x;
			dynBufferMapping[vertexIndex].uy = loc.topRight.y;
			dynBufferMapping[vertexIndex].uz = loc.layer;
			dynBufferMapping[vertexIndex].fgColor = fgColor;
			dynBufferMapping[vertexIndex].bgColor = bgColor;
			vertexIndex += 1;
			dynBufferMapping[vertexIndex].ux = loc.topRight.x;
			dynBufferMapping[vertexIndex].uy = loc.bottomLeft.y;
			dynBufferMapping[vertexIndex].uz = loc.layer;
			dynBufferMapping[vertexIndex].fgColor = fgColor;
			dynBufferMapping[vertexIndex].bgColor = bgColor;
		}
	}
}

std::shared_ptr<gl::ShaderProgram> TileGridRenderer::createDefaultShaders(gl::Context* context)
{
	std::string vertexShaderSource =
		R"(
		#version 140

		uniform mat3 transform;

		in vec2 position;
		in vec3 tex;
		in vec4 fgColor;
	    in vec4 bgColor;

	    out vec3 texCoord;
	    out vec4 foregroundColor;
	    out vec4 backgroundColor;
		
		void main()
		{
		    texCoord = tex;
	        foregroundColor = fgColor;
	        backgroundColor = bgColor;
			gl_Position = vec4((transform * vec3(position, 1)).xy, 1, 1);
		}
		)";

		std::string fragmentShaderSource =
		R"(
		#version 140

		uniform sampler2DArray texSampler;

		in vec3 texCoord;
	    in vec4 foregroundColor;
	    in vec4 backgroundColor;

		out vec4 colorOut;

		void main()
		{
	        vec4 texColor = texture(texSampler, texCoord);
	        vec4 fgColor = texColor * foregroundColor;
	        colorOut = vec4(fgColor.rgb * fgColor.a + backgroundColor.rgb 
	                   * backgroundColor.a * (1.0 - fgColor.a), 1);
		}
		)";

		std::shared_ptr<rf::gl::Shader> vertexShader = std::make_shared<gl::Shader>(rf::gl::Shader::ShaderType::Vertex, context);
		vertexShader->compileSource(vertexShaderSource);
		std::shared_ptr<rf::gl::Shader> fragmentShader = std::make_shared<gl::Shader>(rf::gl::Shader::ShaderType::Fragment, context);
		fragmentShader->compileSource(fragmentShaderSource);
		std::shared_ptr<rf::gl::ShaderProgram> shaderProg = std::make_shared<gl::ShaderProgram>(context);
		shaderProg->attachShader(std::move(vertexShader));
		shaderProg->attachShader(std::move(fragmentShader));
		shaderProg->bindAttributeLocation("position", 0);
		shaderProg->bindAttributeLocation("tex", 1);
		shaderProg->bindAttributeLocation("fgColor", 2);
		shaderProg->bindAttributeLocation("bgColor", 3);
		shaderProg->link();
		return shaderProg;
}

}


