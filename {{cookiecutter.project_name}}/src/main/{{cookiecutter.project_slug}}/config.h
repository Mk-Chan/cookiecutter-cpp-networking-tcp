#ifndef {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_CONFIG_H
#define {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_CONFIG_H

#include <memory>
#include <string>

namespace {{ cookiecutter.project_slug }} {

class config {
   public:
    static config* singleton();

    void parse(const std::string& filepath);

    [[nodiscard]] std::string logging_level() const;
    [[nodiscard]] std::string server_host() const;
    [[nodiscard]] unsigned short server_port() const;
    [[nodiscard]] int server_threads() const;

   private:
    static std::unique_ptr<config> singleton_;

    std::string logging_level_;
    std::string server_host_;
    unsigned short server_port_;
    int server_threads_;
};

}  // namespace {{ cookiecutter.project_slug }}

#endif  // {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_SERVICE_CONFIG_H
