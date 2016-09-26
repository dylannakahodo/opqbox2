//
// Created by tusk on 9/14/16.
//

#include "ZMQTrigger.hpp"
#include "ZMQSerializer.hpp"
#include "Settings.hpp"
#include "opq.pb.h"
#include "util.hpp"
#include <czmq.h>
#include <opqdata.hpp>
#include <string>
#include <boost/log/trivial.hpp>
using namespace opq;

ZMQTrigger::ZMQTrigger(opq::data::AnalysisQueue q) {
    _q = q;
    _running = false;
}

void ZMQTrigger::start() {
    _t = std::thread([this] { readerLoop(); });
}

void ZMQTrigger::stop() {
    _running = false;
    _t.join();

}

void ZMQTrigger::readerLoop() {
    _running = true;
    ZMQSerializer zmq;
    while (_running) {
        auto message = _q->pop();
        zmq << message;
    }
    BOOST_LOG_TRIVIAL(info) << "ZMQ thread done";
}