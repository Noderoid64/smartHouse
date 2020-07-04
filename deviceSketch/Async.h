
#ifndef ASYNCER
#define ASYNCER

//#include <list>
//#include <functional>

void setTimeout(long time, std::function<void()> func);
void asyncTick();

#endif
