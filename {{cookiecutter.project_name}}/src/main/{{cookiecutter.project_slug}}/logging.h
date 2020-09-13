#ifndef {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_LOGGING_H
#define {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_LOGGING_H

#include <string>

#include "spdlog/spdlog.h"

namespace {{ cookiecutter.project_slug }} {

inline void log_info(const std::string& what_failed, const std::string& message) {
    spdlog::info("{}: {}", what_failed, message);
}

inline void log_warn(const std::string& what_failed, const std::string& message) {
    spdlog::warn("{}: {}", what_failed, message);
}

inline void log_error(const std::string& what_failed, const std::string& message) {
    spdlog::error("{}: {}", what_failed, message);
}

}  // namespace {{ cookiecutter.project_slug }}

#endif  // {{ cookiecutter.project_name.upper()|replace(' ', '_')|replace('-', '_')|replace('.', '_')|trim() }}_LOGGING_H
