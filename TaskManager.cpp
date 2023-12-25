#include"common.hpp"

using namespace std;

//初始化线程池，创建线程并让线程尝试管理任务
TaskManager::TaskManager(size_t threads):stopAll(false) {
	for (size_t i = 0; i < threads; ++i) {
		workers.emplace_back([this] {this->workerFunction(); });
		//等价下面两行
		//thread t(TaskManager::workerFunction, this);
		//workers.push_back(move(t));
	}
}

//析构函数，结束多任务管理器
TaskManager::~TaskManager() {
	stop();
}

//添加任务到任务队列，并通知任意空闲的线程开始执行任务
void TaskManager::addTask(std::shared_ptr<Task> task) {
	//添加任务至队列需要先拿锁，保护任务队列的访问不能被打断或是打断其他正在访问任务队列的线程
	unique_lock<mutex>lock(queueMutex);
	tasks.push(task);
	//通知空闲线程执行任务
	condition.notify_one();
}

//启动线程 
void TaskManager::start() {
	stopAll = false;
}

//结束线程池中的线程
void TaskManager::stop() {
	stopAll = true;
	//通知所有线程可以结束
	condition.notify_all();
	//等待还在执行任务的线程执行完任务;
	for (auto& worker : workers) {
		if (worker.joinable()) {
			worker.join();
		}
	}
}

//线程管理执行任务
void TaskManager::workerFunction() {
	//用while(true)实现线程的复用
	while (true) {
		shared_ptr<Task>task; 
		//
		{	
			//访问任务队列前，拿锁
			unique_lock<mutex>lock(queueMutex);
			//根据条件变量，判断任务队列是否有任务，或者是被通知要结束线程
			condition.wait(lock, [this] {
				return !tasks.empty() || stopAll;
				});
			//如果任务队列为空，并且要结束线程，那就退出
			if (stopAll && tasks.empty()) return;
			//否则继续执行任务
			task = tasks.front();
			tasks.pop();
		}
		string taskName = task->getName();//获取任务名称
		//线程管理执行任务
		cout << "我是线程" << this_thread::get_id() << " 号，开始处理任务:"<<taskName << endl;
		task->execute();
		cout << "我是线程" << this_thread::get_id() << " 任务结束" << endl;
	}
}