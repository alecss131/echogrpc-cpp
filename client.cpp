#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "Greet.pb.h"
#include "Greet.grpc.pb.h"

int main(int argc, char **argv) {
    std::string name{"World"};
    if (argc == 2) {
        name = argv[1];
    }
    auto channel{grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials())};
    auto stub{Greeter::NewStub(channel)};
    grpc::ClientContext context{};
    HelloRequest request{};
    request.set_name(name);
    HelloReply reply{};
    grpc::Status status{stub->SayHello(&context, request, &reply)};
    if (status.ok()) {
        std::cout << "Server response: " << reply.message() << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }
    return 0;
}
