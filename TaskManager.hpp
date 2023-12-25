#pragma once

#include"common.hpp"

//�����������
class TaskManager {
private:
    std::queue<std::shared_ptr<Task>> tasks; // �������������
    std::vector<std::thread> workers; // �����߳�����
    std::mutex queueMutex; // ����������еĻ�����
    condition_variable condition;//һ��֪ͨ�̴߳����������������
    bool stopAll; // ���������߳�ֹͣ�ı�־
public:
    TaskManager(size_t threads); // ���캯������ʼ����Ա����
    ~TaskManager(); // ��������������ֹͣ�����̲߳�������Դ
    void addTask(std::shared_ptr<Task> task); // ������񵽶���
    void start(); // �����̳߳��е��߳�
    void stop(); // ֹͣ�̳߳��е��߳�
    void workerFunction(); // �̳߳���ÿ���߳�ִ�еĺ���
};