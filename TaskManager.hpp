#pragma once

#include"common.hpp"

//任务管理器类
class TaskManager {
private:
    std::queue<std::shared_ptr<Task>> tasks; // 待处理任务队列
    std::vector<std::thread> workers; // 工作线程容器
    std::mutex queueMutex; // 保护任务队列的互斥锁
    condition_variable condition;//一个通知线程处理任务的条件变量
    bool stopAll; // 控制所有线程停止的标志
public:
    TaskManager(size_t threads); // 构造函数，初始化成员变量
    ~TaskManager(); // 析构函数，用来停止所有线程并清理资源
    void addTask(std::shared_ptr<Task> task); // 添加任务到队列
    void start(); // 启动线程池中的线程
    void stop(); // 停止线程池中的线程
    void workerFunction(); // 线程池中每个线程执行的函数
};