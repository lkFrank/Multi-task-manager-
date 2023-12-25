#include"common.hpp"

using namespace std;

//��ʼ���̳߳أ������̲߳����̳߳��Թ�������
TaskManager::TaskManager(size_t threads):stopAll(false) {
	for (size_t i = 0; i < threads; ++i) {
		workers.emplace_back([this] {this->workerFunction(); });
		//�ȼ���������
		//thread t(TaskManager::workerFunction, this);
		//workers.push_back(move(t));
	}
}

//�������������������������
TaskManager::~TaskManager() {
	stop();
}

//�������������У���֪ͨ������е��߳̿�ʼִ������
void TaskManager::addTask(std::shared_ptr<Task> task) {
	//���������������Ҫ������������������еķ��ʲ��ܱ���ϻ��Ǵ���������ڷ���������е��߳�
	unique_lock<mutex>lock(queueMutex);
	tasks.push(task);
	//֪ͨ�����߳�ִ������
	condition.notify_one();
}

//�����߳� 
void TaskManager::start() {
	stopAll = false;
}

//�����̳߳��е��߳�
void TaskManager::stop() {
	stopAll = true;
	//֪ͨ�����߳̿��Խ���
	condition.notify_all();
	//�ȴ�����ִ��������߳�ִ��������;
	for (auto& worker : workers) {
		if (worker.joinable()) {
			worker.join();
		}
	}
}

//�̹߳���ִ������
void TaskManager::workerFunction() {
	//��while(true)ʵ���̵߳ĸ���
	while (true) {
		shared_ptr<Task>task; 
		//
		{	
			//�����������ǰ������
			unique_lock<mutex>lock(queueMutex);
			//���������������ж���������Ƿ������񣬻����Ǳ�֪ͨҪ�����߳�
			condition.wait(lock, [this] {
				return !tasks.empty() || stopAll;
				});
			//����������Ϊ�գ�����Ҫ�����̣߳��Ǿ��˳�
			if (stopAll && tasks.empty()) return;
			//�������ִ������
			task = tasks.front();
			tasks.pop();
		}
		string taskName = task->getName();//��ȡ��������
		//�̹߳���ִ������
		cout << "�����߳�" << this_thread::get_id() << " �ţ���ʼ��������:"<<taskName << endl;
		task->execute();
		cout << "�����߳�" << this_thread::get_id() << " �������" << endl;
	}
}