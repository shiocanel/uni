#pragma once

class ActiuneUndo {
public:
    virtual ~ActiuneUndo() = default;
    virtual void doUndo() = 0;
};