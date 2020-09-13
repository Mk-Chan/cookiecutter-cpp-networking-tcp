#include "session.h"

#include <iostream>

#include "boost/algorithm/string.hpp"

#include "fmt/format.h"

#include "nlohmann/json.hpp"

#include "spdlog/spdlog.h"

#include "logging.h"

using boost::asio::ip::tcp;
using nlohmann::json;
using std::placeholders::_1;
using std::placeholders::_2;

namespace {{ cookiecutter.project_slug }} {

session::session(tcp::socket&& socket)
    : socket_(std::move(socket)),
      input_buffer_(),
      output_buffer_() {
}

void session::start() {
    do_read();
}

void session::on_read(boost::system::error_code ec, std::size_t) {
    if (ec) {
        return;
    }

    std::istream input_stream{&input_buffer_};
    std::string message_string;
    std::getline(input_stream, message_string);
    boost::trim_right_if(message_string, boost::is_any_of("\n"));
    try {
        json message_json = json::parse(message_string);
        std::string json_dump{message_json.dump()};
        log_info("on_read", fmt::format("received {}", json_dump));
        do_write(json_dump);
    } catch (nlohmann::detail::parse_error& e) {
        log_error("on_read", e.what());
    }

    do_read();
}

void session::on_write(boost::system::error_code ec, std::size_t) {
    if (ec) {
        log_error("write", ec.message());
    }
}

void session::do_read() {
    boost::asio::async_read_until(
        socket_, input_buffer_, "\n", std::bind(&session::on_read, shared_from_this(), _1, _2));
}

void session::do_write(const std::string& data) {
    std::ostream output_stream{&output_buffer_};
    output_stream << data << "\n";
    boost::asio::async_write(
        socket_, output_buffer_, std::bind(&session::on_write, shared_from_this(), _1, _2));
}

}  // namespace {{ cookiecutter.project_slug }}
