#include <memory>

namespace GraphicEngine
{
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}