#ifndef GL_ENUMS_H_
#define GL_ENUMS_H_

namespace rf
{
namespace gl
{



enum class ClearFlags : GLbitfield
{
	ColorBuffer = GL_COLOR_BUFFER_BIT,
	DepthBuffer = GL_DEPTH_BUFFER_BIT,
	StencilBuffer = GL_STENCIL_BUFFER_BIT
};

enum class BufferBindTarget
{
	ArrayBuffer = GL_ARRAY_BUFFER,
	IndexBuffer = GL_ELEMENT_ARRAY_BUFFER,
	CopyReadBuffer = GL_COPY_READ_BUFFER,
	CopyWriteBuffer = GL_COPY_WRITE_BUFFER
};

enum class PrimitiveType : GLenum
{
	Points = GL_POINTS,
	LineStrip = GL_LINE_STRIP,
	LineLoop = GL_LINE_LOOP,
	Lines = GL_LINES,
	LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
	LinesAdjacency = GL_LINES_ADJACENCY,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN,
	Triangles = GL_TRIANGLES,
	TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
	Patches = GL_PATCHES
};

enum class IndexFormat : GLenum
{
	UByte = GL_UNSIGNED_BYTE,
	UShort = GL_UNSIGNED_SHORT,
	UInt = GL_UNSIGNED_INT
};

}
}


#endif
