#pragma once

class CosObserver {
public:
    virtual ~CosObserver() = default;
    virtual void updateCos() = 0;
};