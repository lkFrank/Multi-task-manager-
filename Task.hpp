#pragma once

#include"common.hpp"
using namespace std;


//任务类
class Task {
public:
	virtual void execute() = 0;//纯虚函数，在子类中实现具体任务
	virtual ~Task() {}
	virtual string getName() const = 0;//新增虚函数，用于获取任务名称
};

//计算大数阶层的任务
class FactorialTask :public Task {
	int number;
public:
	FactorialTask(int num):number(num){}
	void execute() override {
		unsigned long long factorial = 1;
		for (int i = 1; i <= number; ++i) {
			factorial *= i;
		}
		cout << "Factorial of " << number << " is " << factorial << endl;
	};
	string getName()const override {
		return "FactorialTask";
	}
};

//计算斐波那契数列的任务
class FibonacciTask :public Task {
	int n;
public:
	FibonacciTask(int n):n(n){}
	void execute()override {
		vector<unsigned long long >fib(n + 1, 0);
		fib[1] = 1;
		for (int i = 2; i <= n; ++i) {
			fib[i] = fib[i - 1] + fib[i - 2];
		}
		cout << "Fibonacci number at position " << n << " is " << fib[n] << endl;
	}
	string getName()const override {
		return "FibonacciTask";
	}
};

//休眠任务
class SleepTask : public Task {
	int duration;
public:
	SleepTask(int dur):duration(dur){}
	void execute()override {
		cout << "Sleeping for" << duration << "seconds..."<<endl;
		this_thread::sleep_for(chrono::seconds(duration));
		cout << "Awake after sleeping for " << duration << " seconds" << endl;
	}
	string getName()const override {
		return "SleepTask";
	}
};

//I/O任务
class IOTask :public Task {
	string filename;
public:
	IOTask(const string& fname) :filename(fname) {}
	void execute()override {
		ifstream file(filename);
		if (file.is_open()) {
			cout << "Reading from file: " << filename << endl;
			string line;
			while (getline(file, line)) {
				cout << line << endl;
			}
			file.close();
		}
		else {
			cout << "Unable to open file: " << filename << endl;
		}
	}
	string getName()const override {
		return "IOTask";
	}
};