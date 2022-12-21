#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "Greet.pb.h"
#include "Greet.grpc.pb.h"

class GreeterServiceImpl final : public Greeter::Service {
    grpc::Status SayHello(grpc::ServerContext *context, const HelloRequest *request, HelloReply *reply) override {
        const std::string &name{request->name()};
        std::cout << "New client request with name: " << name << std::endl;
        std::string message{"Hello, " + name + "!"};
        reply->set_message(message);
        return grpc::Status::OK;
    }
};

int main() {
    GreeterServiceImpl service{};
    grpc::ServerBuilder builder{};
    builder.AddListeningPort("127.0.0.1:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server{builder.BuildAndStart()};
    std::cout << "Server listening on port: 50051" << std::endl;
    server->Wait();
    return 0;
}
