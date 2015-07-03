#pragma once

namespace Benchmark
{

class IEventHandler
{
public:
    virtual ~IEventHandler() {}

    void setNextHandler(UniqueResultHandler &&handler)
    {
        if (mNextHandler)
            mNextHandler->setNextHandler(std::forward<UniqueResultHandler>(handler));
        else
            mNextHandler = std::move(handler);
    }

    void handle(ResultEvent const &results)
    {
        handleHook(results);
        if (mNextHandler)
            mNextHandler->handle(results);
    }

protected:
    virtual void handleHook(ResultEvent const &results) = 0;

private:
    UniqueResultHandler mNextHandler;
};

} // Benchmark

