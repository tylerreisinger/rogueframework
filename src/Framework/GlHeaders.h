#ifndef GLHEADERS_H_
#define GLHEADERS_H_

#define TARGET_GL_VERSION 301

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GL_DEBUG

#ifdef GL_DEBUG
#define CHECK_GL_ERROR(fn) {GLenum err = glGetError(); \
	if(err != GL_NO_ERROR) {throw GlException("fn", err);}}
#else
#define CHECK_GL_ERROR(fn)
#endif

#endif
