# moxie
Non blocking asynchronous IO framework based on epoll, with a fucus on being:
* simple : easily used API, pithy code, no dependence.
* fast : 150000 qps (Echo in single thread).


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
> * Use moxie in single thread.</br>
[moxie/example/Echo.cpp](https://github.com/sxfworks/moxie/blob/master/example/Echo.cpp)
> * Use moxie in multi-thread.</br>
[moxie/example/MultiThreadEcho.cpp](https://github.com/sxfworks/moxie/blob/master/example/MultiThreadEcho.cpp)
> * Use the timer of the moxie.</br>
[moxie/example/TimerExam.cpp](https://github.com/sxfworks/moxie/blob/master/example/TimerExam.cpp)

