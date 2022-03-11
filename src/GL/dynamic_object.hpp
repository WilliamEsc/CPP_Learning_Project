#pragma once

#include <unordered_set>

namespace GL {

class DynamicObject
{
public:
    virtual ~DynamicObject() {}

    virtual void move() = 0;
    virtual bool toDelete() const { return false; }
};

inline std::unordered_set<DynamicObject*> move_queue;

} // namespace GL
