#include <iostream>
#include <vector>

#include "boost/asio.hpp"

#include "spdlog/spdlog.h"

#include "fmt/format.h"

#include "config.h"
#include "logging.h"
#include "server.h"

using boost::asio::ip::tcp;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: ./{{ cookiecutter.project_slug }} <path-to-config>" << std::endl;
        return 1;
    }

    {{ cookiecutter.project_slug }}::config* config = {{ cookiecutter.project_slug }}::config::singleton();
    config->parse(argv[1]);

    spdlog::set_level(spdlog::level::from_str(config->logging_level()));

    auto host = boost::asio::ip::make_address(config->server_host());
    auto port = config->server_port();
    auto hardware_concurrency = std::thread::hardware_concurrency();
    unsigned int max_threads = hardware_concurrency != 0 ? hardware_concurrency * 2 : 8;
    auto num_threads = std::clamp<int>(config->server_threads(), 1, max_threads);

    boost::asio::io_context server_io_context{num_threads};

    auto endpoint = boost::asio::ip::tcp::endpoint{host, port};
    auto server = std::make_unique<{{ cookiecutter.project_slug }}::server>(server_io_context, endpoint);
    server->start();
    {{ cookiecutter.project_slug }}::log_info(
        "main", fmt::format("listening on {}:{}", endpoint.address().to_string(), endpoint.port()));

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int thread_num = 0; thread_num < num_threads; ++thread_num) {
        threads.emplace_back([&server_io_context] { server_io_context.run(); });
    }

    constexpr static int buffer_size = 1024;
    char buffer[buffer_size];
    while (std::cin.getline(buffer, buffer_size)) {
        std::string cmdline_input{buffer};
        if (cmdline_input == "quit" || cmdline_input == "exit") {
            {{ cookiecutter.project_slug }}::log_info("main", "quitting...");
            break;
        } else {
            {{ cookiecutter.project_slug }}::log_error("main", fmt::format("unknown command: {}", cmdline_input));
        }
    }

    server_io_context.stop();

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}
