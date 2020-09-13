#include "server.h"

#include <memory>

#include "logging.h"
#include "session.h"

using std::placeholders::_1;
using std::placeholders::_2;

namespace {{ cookiecutter.project_slug }} {

server::server(boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint endpoint)
    : io_context_(io_context),
      acceptor_(boost::asio::make_strand(io_context)) {
    boost::system::error_code ec;

    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
        log_error("acceptor_open", ec.message());
        return;
    }

    acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
    if (ec) {
        log_error("acceptor_set_option", ec.message());
        return;
    }

    acceptor_.bind(endpoint, ec);
    if (ec) {
        log_error("acceptor_bind", ec.message());
        return;
    }

    acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
    if (ec) {
        log_error("acceptor_listen", ec.message());
        return;
    }
}

void server::start() {
    do_accept();
}

void server::on_accept(boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
    if (!ec) {
        std::make_shared<session>(std::move(socket))->start();
    } else {
        log_error("accept", ec.message());
    }

    do_accept();
}

void server::do_accept() {
    acceptor_.async_accept(boost::asio::make_strand(io_context_),
                           std::bind(&server::on_accept, this, _1, _2));
}

}  // namespace {{ cookiecutter.project_slug }}
