#include "renderCommand.h"
#include "openGLRendererAPI.h"

namespace GraphicEngine
{

    Scope<RendererAPI> RenderCommand::_rendererAPI = CreateScope<OpenGLRendererAPI>();

}