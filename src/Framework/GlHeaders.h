#ifndef GLHEADERS_H_
#define GLHEADERS_H_

#define GL_TARGET_VERSION 301

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GL_DEBUG

#ifdef GL_DEBUG
#define CHECK_GL_ERROR(fn) {GLenum err = glGetError(); \
	if(err != GL_NO_ERROR) {throw GlException(#fn, err);}}
#else
#define CHECK_GL_ERROR(fn)
#endif

#ifdef GL_CHECK_BIND_CORRECTNESS
#define CHECK_GL_BINDING(type, obj) {\
int val = 0; \
glGetIntegerv(<>, &val); \
if(val != (obj)->handle()) \
{\
	throw GlBindingError(#type); \
}}
#else
#define CHECK_GL_BINDING(type, obj)
#endif

#endif
