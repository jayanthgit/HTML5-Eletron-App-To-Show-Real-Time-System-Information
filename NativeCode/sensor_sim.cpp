#include <iostream>
#include <cstdio>
#include <chrono>
#include <string>
#include <random>
#include <thread>
#include "streaming-worker.h"
#include "json.hpp"  //https://github.com/nlohmann/json
#include <stdio.h>

using namespace std;
using json = nlohmann::json;

class Sensor : public StreamingWorker {
public:
	Sensor(Callback *data, Callback *complete, Callback *error_callback, v8::Local<v8::Object> & options)
		: StreamingWorker(data, complete, error_callback) {
	}

	void SendLog(const AsyncProgressWorker::ExecutionProgress& progress, string data)
	{
		Message tosend("log", data);
		writeToNode(progress, tosend);
	}

	void SendSystemData(const AsyncProgressWorker::ExecutionProgress& progress, string data)
	{
		Message tosend("systemData", data);
		writeToNode(progress, tosend);
	}

	void Execute(const AsyncProgressWorker::ExecutionProgress& progress) {
		SendLog(progress, "Execute Started");
		
		std::random_device rd;
		std::uniform_real_distribution<double> pos_dist(-10000, 10000);
		while (!closed()) {
			
			json sample;

            //dummy data
			//replace this with reading system manager from the system
			for (ULONG ul = 0; ul < 20; ul++)
			{
				sample[ul]["a"] = pos_dist(rd);
				sample[ul]["b"] = pos_dist(rd);
				sample[ul]["c"] = pos_dist(rd);
				sample[ul]["d"] = pos_dist(rd);
				sample[ul]["e"] = pos_dist(rd);
				sample[ul]["f"] = pos_dist(rd);
				sample[ul]["g"] = pos_dist(rd);
				sample[ul]["h"] = pos_dist(rd);
				sample[ul]["i"] = pos_dist(rd);
				sample[ul]["j"] = pos_dist(rd);
				sample[ul]["k"] = pos_dist(rd);
				sample[ul]["l"] = pos_dist(rd);					
				sample[ul]["m"] = pos_dist(rd);
				sample[ul]["n"] = pos_dist(rd);
				sample[ul]["o"] = pos_dist(rd);
				sample[ul]["p"] = pos_dist(rd);
				sample[ul]["q"] = pos_dist(rd);
				sample[ul]["r"] = pos_dist(rd);
				sample[ul]["s"] = pos_dist(rd);
				sample[ul]["t"] = pos_dist(rd);
				sample[ul]["u"] = pos_dist(rd);
				sample[ul]["v"] = pos_dist(rd);
				sample[ul]["w"] = pos_dist(rd);
				sample[ul]["x"] = pos_dist(rd);
				sample[ul]["y"] = pos_dist(rd);
				sample[ul]["z"] = pos_dist(rd);
			}
			
			SendSystemData(progress, sample.dump());
			std::this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
private:
	string name;
};

StreamingWorker * create_worker(Callback *data
	, Callback *complete
	, Callback *error_callback, v8::Local<v8::Object> & options) {
	return new Sensor(data, complete, error_callback, options);
}

NODE_MODULE(sensor_sim, StreamWorkerWrapper::Init)
