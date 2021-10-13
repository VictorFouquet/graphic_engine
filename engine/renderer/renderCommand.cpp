#include "renderCommand.h"
#include "openGLRendererAPI.h"

namespace GraphicEngine
{

    RendererAPI* RenderCommand::_rendererAPI = new OpenGLRendererAPI;

}