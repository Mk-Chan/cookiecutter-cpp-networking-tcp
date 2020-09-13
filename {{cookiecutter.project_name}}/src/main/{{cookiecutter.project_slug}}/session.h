#ifndef {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_SESSION_H
#define {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_SESSION_H

#include <array>
#include <memory>

#include "boost/asio.hpp"

#include "nlohmann/json.hpp"

namespace {{ cookiecutter.project_slug }} {

class session : public std::enable_shared_from_this<session> {
   public:
    explicit session(boost::asio::ip::tcp::socket&& socket);

    void start();

   private:
    void on_read(boost::system::error_code ec, std::size_t bytes_transferred);
    void on_write(boost::system::error_code ec, std::size_t bytes_transferred);

    void do_read();
    void do_write(const std::string& data);

    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf input_buffer_;
    boost::asio::streambuf output_buffer_;
};

}  // namespace {{ cookiecutter.project_slug }}

#endif  // {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_SESSION_H
