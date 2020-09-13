#include "config.h"

#include <fstream>

namespace {{ cookiecutter.project_slug }} {

std::unique_ptr<config> config::singleton_ = nullptr;

config* config::singleton() {
    if (singleton_ == nullptr) {
        singleton_ = std::make_unique<config>();
    }
    return singleton_.get();
}

void config::parse(const std::string& filepath) {
    std::ifstream config_in{filepath};
    std::string line;
    while (std::getline(config_in, line)) {
        const char* line_data = line.c_str();
        auto delim_pos = line.find('=');
        if (delim_pos == std::string_view::npos) {
            continue;
        }

        std::string_view key{line_data, delim_pos};
        std::string value{line_data + delim_pos + 1};

        if (key == "logging.level") {
            logging_level_ = value;
        } else if (key == "server.host") {
            server_host_ = value;
        } else if (key == "server.port") {
            server_port_ = static_cast<unsigned short>(std::stoul(value));
        } else if (key == "server.threads") {
            server_threads_ = std::stoi(value);
        }
    }
}

[[nodiscard]] std::string config::logging_level() const {
    return logging_level_;
}

[[nodiscard]] std::string config::server_host() const {
    return server_host_;
}

[[nodiscard]] unsigned short config::server_port() const {
    return server_port_;
}

[[nodiscard]] int config::server_threads() const {
    return server_threads_;
}

}  // namespace {{ cookiecutter.project_slug }}
