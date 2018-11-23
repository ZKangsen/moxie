# moxie
Non blocking asynchronous IO framework based on epoll in single thread, but it can be used in multi-thread program.

## Getting start
### install moxie
```bash
   git clone https://github.com/sxfworks/moxie.git
   cd moxie
   make
   cd ../
   mv moxie ${your_project_include_path}
```
## How to use moxie
> * Use moxie in single thread.
###[moxie/example/Echo.cpp](https://github.com/sxfworks/moxie/blob/master/example/Echo.cpp)
> * Use moxie in multi-thread
###[moxie/example/MultiThreadEcho.cpp](https://github.com/sxfworks/moxie/blob/master/example/MultiThreadEcho.cpp)
> * Use the thmer of the moxie
###[moxie/example/TimerExam.cpp](https://github.com/sxfworks/moxie/blob/master/example/TimerExam.cpp)

