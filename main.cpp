#include"common.hpp"


using namespace std;

int main() {
	
	//创建一个最多同时存在并能管理3个线程的的任务管理器
	size_t x = 3;
	TaskManager TM(x);
	shared_ptr<Task> task1 = make_shared<FactorialTask>(3);
	shared_ptr<Task> task2 = make_shared<FactorialTask>(4);
	shared_ptr<Task> task3 = make_shared<FactorialTask>(5);
	shared_ptr<Task> task4 = make_shared<FibonacciTask>(6);
	shared_ptr<Task> task5 = make_shared<FibonacciTask>(7);
	shared_ptr<Task> task6 = make_shared<FibonacciTask>(8);
	shared_ptr<Task> task7 = make_shared<SleepTask>(3);
	shared_ptr<Task> task8 = make_shared<SleepTask>(3);
	shared_ptr<Task> task9 = make_shared<SleepTask>(3);


	TM.addTask(task1);
	TM.addTask(task7);
	TM.addTask(task3);
	TM.addTask(task8);
	TM.addTask(task5);
	TM.addTask(task9);
	TM.addTask(task2);
	TM.addTask(task4);
	TM.addTask(task6);

	return 0;
}