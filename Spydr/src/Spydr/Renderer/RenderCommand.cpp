#include "sppch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Spydr
{
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI;
}