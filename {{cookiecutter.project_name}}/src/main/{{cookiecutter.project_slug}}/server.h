#ifndef {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_SERVER_H
#define {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_SERVER_H

#include "boost/asio.hpp"

namespace {{ cookiecutter.project_slug }} {

class server {
   public:
    server(boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint endpoint);

    void start();

   private:
    void on_accept(boost::system::error_code ec, boost::asio::ip::tcp::socket socket);

    void do_accept();

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

}  // namespace {{ cookiecutter.project_slug }}

#endif  // {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_SERVER_H
