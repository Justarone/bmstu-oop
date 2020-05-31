#pragma once

class BaseManager;

class BaseManagerCommand {
public:
    virtual void execute(BaseManager &);
};
