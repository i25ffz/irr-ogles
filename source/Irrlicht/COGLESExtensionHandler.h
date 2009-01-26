// Copyright (C) 2008 Christian Stehno
// Heavily based on the OpenGL driver implemented by Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#ifndef __C_OGLES_EXTENSION_HANDLER_H_INCLUDED__
#define __C_OGLES_EXTENSION_HANDLER_H_INCLUDED__

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_OGLES1_
#if defined(_IRR_USE_IPHONE_DEVICE_)
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#else
#include <GLES/egl.h>
#include <GLES/gl.h>
#include "gles-ext.h"
#endif
#include "os.h"
#include "EDriverFeatures.h"

#ifndef GL_BGRA
// we need to do this for the IMG_BGRA8888 extension
extern int GL_BGRA;
#endif

namespace irr
{
namespace video
{

	class COGLES1ExtensionHandler
	{
	protected:
	enum EOGLESFeatures {
		IRR_AMD_compressed_3DC_texture,
		IRR_AMD_compressed_ATC_texture,
		IRR_ARB_texture_env_combine,
		IRR_ARB_texture_env_dot3,
		IRR_EXT_multi_draw_arrays,
		IRR_EXT_texture_filter_anisotropic,
		IRR_IMG_read_format,
		IRR_IMG_texture_compression_pvrtc,
		IRR_IMG_texture_env_enhanced_fixed_function,
		IRR_IMG_texture_format_BGRA8888,
		IRR_IMG_user_clip_planes,
		IRR_IMG_vertex_program,
		IRR_OES_blend_equation_separate,
		IRR_OES_blend_func_separate,
		IRR_OES_blend_subtract,
		IRR_OES_byte_coordinates,
		IRR_OES_compressed_ETC1_RGB8_texture,
		IRR_OES_compressed_paletted_texture,
		IRR_OES_depth24,
		IRR_OES_depth32,
		IRR_OES_draw_texture,
		IRR_OES_EGL_image,
		IRR_OES_element_index_uint,
		IRR_OES_extended_matrix_palette,
		IRR_OES_fbo_render_mipmap,
		IRR_OES_fixed_point,
		IRR_OES_framebuffer_object,
		IRR_OES_mapbuffer,
		IRR_OES_matrix_get,
		IRR_OES_matrix_palette,
		IRR_OES_point_size_array,
		IRR_OES_point_sprite,
		IRR_OES_query_matrix,
		IRR_OES_read_format,
		IRR_OES_rgb8_rgba8,
		IRR_OES_single_precision,
		IRR_OES_stencil1,
		IRR_OES_stencil4,
		IRR_OES_stencil8,
		IRR_OES_stencil_wrap,
		IRR_OES_texture_cube_map,
		IRR_OES_texture_env_crossbar,
		IRR_OES_texture_mirrored_repeat,

		IRR_OGLES_Feature_Count
	};

		COGLES1ExtensionHandler();

		bool queryFeature(video::E_VIDEO_DRIVER_FEATURE feature) const
		{
			switch (feature)
			{
				case EVDF_RENDER_TO_TARGET:
					return true;
				case EVDF_MULTITEXTURE:
					return MultiTextureExtension;
				case EVDF_BILINEAR_FILTER:
					return true;
				case EVDF_MIP_MAP:
					return true;
				case EVDF_MIP_MAP_AUTO_UPDATE:
					return Version>100; // Supported in version 1.1
				case EVDF_STENCIL_BUFFER:
					return StencilBuffer;
				case EVDF_TEXTURE_NSQUARE:
					return true; // non-square is always supported
				default:
					return false;
			}
		}

		void dump() const;

		void initExtensions(
#ifdef EGL_VERSION_1_0
				EGLDisplay display,
#endif
				bool withStencil);

	public:
		void COGLES1ExtensionHandler::extGlBindFramebuffer(GLenum target, GLuint framebuffer)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlBindFramebufferOES)
				pGlBindFramebufferOES(target, framebuffer);
#elif defined(GL_OES_framebuffer_object)
			glBindFramebufferOES(target, framebuffer);
#else
			os::Printer::log("glBindFramebuffer not supported", ELL_ERROR);
#endif
		}

		void COGLES1ExtensionHandler::extGlDeleteFramebuffers(GLsizei n, const GLuint *framebuffers)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlDeleteFramebuffersOES)
				pGlDeleteFramebuffersOES(n, framebuffers);
#elif defined(GL_OES_framebuffer_object)
			glDeleteFramebuffersOES(n, framebuffers);
#else
			os::Printer::log("glDeleteFramebuffers not supported", ELL_ERROR);
#endif
		}

		void COGLES1ExtensionHandler::extGlGenFramebuffers(GLsizei n, GLuint *framebuffers)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlGenFramebuffersOES)
				pGlGenFramebuffersOES(n, framebuffers);
#elif defined(GL_OES_framebuffer_object)
			glGenFramebuffersOES(n, framebuffers);
#else
			os::Printer::log("glGenFramebuffers not supported", ELL_ERROR);
#endif
		}

		GLenum COGLES1ExtensionHandler::extGlCheckFramebufferStatus(GLenum target)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlCheckFramebufferStatusOES)
				return pGlCheckFramebufferStatusOES(target);
			else
				return 0;
#elif defined(GL_OES_framebuffer_object)
			return glCheckFramebufferStatusOES(target);
#else
			os::Printer::log("glCheckFramebufferStatus not supported", ELL_ERROR);
			return 0;
#endif
		}

		void COGLES1ExtensionHandler::extGlFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlFramebufferTexture2DOES)
				pGlFramebufferTexture2DOES(target, attachment, textarget, texture, level);
#elif defined(GL_OES_framebuffer_object)
			glFramebufferTexture2DOES(target, attachment, textarget, texture, level);
#else
			os::Printer::log("glFramebufferTexture2D not supported", ELL_ERROR);
#endif
		}

		void COGLES1ExtensionHandler::extGlBindRenderbuffer(GLenum target, GLuint renderbuffer)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlBindRenderbufferOES)
				pGlBindRenderbufferOES(target, renderbuffer);
#elif defined(GL_OES_framebuffer_object)
			glBindRenderbufferOES(target, renderbuffer);
#else
			os::Printer::log("glBindRenderbuffer not supported", ELL_ERROR);
#endif
		}

		void COGLES1ExtensionHandler::extGlDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlDeleteRenderbuffersOES)
				pGlDeleteRenderbuffersOES(n, renderbuffers);
#elif defined(GL_OES_framebuffer_object)
			glDeleteRenderbuffersOES(n, renderbuffers);
#else
			os::Printer::log("glDeleteRenderbuffers not supported", ELL_ERROR);
#endif
		}

		void COGLES1ExtensionHandler::extGlGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlGenRenderbuffersOES)
				pGlGenRenderbuffersOES(n, renderbuffers);
#elif defined(GL_OES_framebuffer_object)
			glGenRenderbuffersOES(n, renderbuffers);
#else
			os::Printer::log("glGenRenderbuffers not supported", ELL_ERROR);
#endif
		}

		void COGLES1ExtensionHandler::extGlRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlRenderbufferStorageOES)
				pGlRenderbufferStorageOES(target, internalformat, width, height);
#elif defined(GL_OES_framebuffer_object)
			glRenderbufferStorageOES(target, internalformat, width, height);
#else
			os::Printer::log("glRenderbufferStorage not supported", ELL_ERROR);
#endif
		}

		void COGLES1ExtensionHandler::extGlFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
		{
#ifdef _IRR_OGLES1_USE_EXTPOINTER_
			if (pGlFramebufferRenderbufferOES)
				pGlFramebufferRenderbufferOES(target, attachment, renderbuffertarget, renderbuffer);
#elif defined(GL_OES_framebuffer_object)
			glFramebufferRenderbufferOES(target, attachment, renderbuffertarget, renderbuffer);
#else
			os::Printer::log("glFramebufferRenderbuffer not supported", ELL_ERROR);
#endif
		}

		void extGlDrawTex(GLfloat X, GLfloat Y, GLfloat Z, GLfloat W, GLfloat H)
		{
#if defined(_IRR_OGLES1_USE_EXTPOINTER_)
			if (pGlDrawTexfOES)
				pGlDrawTexfOES(X, Y, Z, W, H);
#elif defined(GL_OES_draw_texture)
			glDrawTexfOES(X, Y, Z, W, H);
#else
			os::Printer::log("glDrawTexture not supported", ELL_ERROR);
#endif
		}

		void extGlDrawTex(GLint X, GLint Y, GLint Z, GLint W, GLint H)
		{
#if defined(_IRR_OGLES1_USE_EXTPOINTER_)
			if (pGlDrawTexiOES)
				pGlDrawTexiOES(X, Y, Z, W, H);
#elif defined(GL_OES_draw_texture)
			glDrawTexiOES(X, Y, Z, W, H);
#else
			os::Printer::log("glDrawTexture not supported", ELL_ERROR);
#endif
		}

		void extGlDrawTex(GLfloat* coords)
		{
#if defined(_IRR_OGLES1_USE_EXTPOINTER_)
			if (pGlDrawTexfvOES)
				pGlDrawTexfvOES(coords);
#elif defined(GL_OES_draw_texture)
			glDrawTexfvOES(coords);
#else
			os::Printer::log("glDrawTexture not supported", ELL_ERROR);
#endif
		}

		void extGlDrawTex(GLint* coords)
		{
#if defined(_IRR_OGLES1_USE_EXTPOINTER_)
			if (pGlDrawTexivOES)
				pGlDrawTexivOES(coords);
#elif defined(GL_OES_draw_texture)
			glDrawTexivOES(coords);
#else
			os::Printer::log("glDrawTexture not supported", ELL_ERROR);
#endif
		}

		// we need to implement some methods which have been extensions in the original OpenGL driver
		void extGlActiveTexture(GLenum texture)
		{
			glActiveTexture(texture);
		}
		void extGlClientActiveTexture(GLenum texture)
		{
			glClientActiveTexture(texture);
		}
		void extGlGenBuffers(GLsizei n, GLuint *buffers)
		{
			glGenBuffers(n, buffers);
		}
		void extGlBindBuffer(GLenum target, GLuint buffer)
		{
			glBindBuffer(target, buffer);
		}
		void extGlBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
		{
			glBufferData(target, size, data, usage);
		}
		void extGlBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
		{
			glBufferSubData(target, offset, size, data);
		}
		void extGlDeleteBuffers(GLsizei n, const GLuint *buffers)
		{
			glDeleteBuffers(n, buffers);
		}
		void extGlPointParameterf(GLint loc, GLfloat f)
		{
			glPointParameterf(loc, f);
		}
		void extGlPointParameterfv(GLint loc, const GLfloat *v)
		{
			glPointParameterfv(loc, v);
		}

//	private:
#if defined(_IRR_OGLES1_USE_EXTPOINTER_)
		typedef void (APIENTRY * PFNGLDRAWTEXIOES) (GLint x, GLint y, GLint z, GLint width, GLint height);
		typedef void (APIENTRY * PFNGLDRAWTEXIVOES) (const GLint* coords);
		typedef void (APIENTRY * PFNGLDRAWTEXFOES) (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
		typedef void (APIENTRY * PFNGLDRAWTEXFVOES) (const GLfloat* coords);
		typedef GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROES) (GLuint renderbuffer);
		typedef void (GL_APIENTRYP PFNGLBINDRENDERBUFFEROES) (GLenum target, GLuint renderbuffer);
		typedef void (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOES) (GLsizei n, const GLuint* renderbuffers);
		typedef void (GL_APIENTRYP PFNGLGENRENDERBUFFERSOES) (GLsizei n, GLuint* renderbuffers);
		typedef void (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOES) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
		typedef void (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOES) (GLenum target, GLenum pname, GLint* params);
		typedef GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROES) (GLuint framebuffer);
		typedef void (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROES) (GLenum target, GLuint framebuffer);
		typedef void (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOES) (GLsizei n, const GLuint* framebuffers);
		typedef void (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOES) (GLsizei n, GLuint* framebuffers);
		typedef GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOES) (GLenum target);
		typedef void (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROES) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		typedef void (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOES) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		typedef void (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOES) (GLenum target, GLenum attachment, GLenum pname, GLint* params);
		typedef void (GL_APIENTRYP PFNGLGENERATEMIPMAPOES) (GLenum target);

		PFNGLDRAWTEXIOES pGlDrawTexiOES;
		PFNGLDRAWTEXFOES pGlDrawTexfOES;
		PFNGLDRAWTEXIVOES pGlDrawTexivOES;
		PFNGLDRAWTEXFVOES pGlDrawTexfvOES;
		PFNGLBINDRENDERBUFFEROES pGlBindRenderbufferOES;
		PFNGLDELETERENDERBUFFERSOES pGlDeleteRenderbuffersOES;
		PFNGLGENRENDERBUFFERSOES pGlGenRenderbuffersOES;
		PFNGLRENDERBUFFERSTORAGEOES pGlRenderbufferStorageOES;
		PFNGLBINDFRAMEBUFFEROES pGlBindFramebufferOES;
		PFNGLDELETEFRAMEBUFFERSOES pGlDeleteFramebuffersOES;
		PFNGLGENFRAMEBUFFERSOES pGlGenFramebuffersOES;
		PFNGLCHECKFRAMEBUFFERSTATUSOES pGlCheckFramebufferStatusOES;
		PFNGLFRAMEBUFFERRENDERBUFFEROES pGlFramebufferRenderbufferOES;
		PFNGLFRAMEBUFFERTEXTURE2DOES pGlFramebufferTexture2DOES;
		PFNGLGENERATEMIPMAPOES pGlGenerateMipMapOES;
#endif

	protected:
		u16 EGLVersion;
		u16 Version;
		u8 MaxTextureUnits;
		u8 MaxLights;
		u8 MaxAnisotropy;
		u8 MaxUserClipPlanes;
		bool CommonProfile;
		bool MultiTextureExtension;
		bool MultiSamplingExtension;
		bool StencilBuffer;
		bool FeatureAvailable[IRR_OGLES_Feature_Count];
	};

} // end namespace video
} // end namespace irr


#endif // _IRR_COMPILE_WITH_OGLES1_
#endif
