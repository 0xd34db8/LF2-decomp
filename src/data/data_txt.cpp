#include "data_txt.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace lf2 {

data_txt_t::data_txt_t() {}

bool data_txt_t::load_from_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return load_from_string(buffer.str());
}

bool data_txt_t::load_from_string(const std::string& content) {
    m_objects.clear();
    m_backgrounds.clear();
    m_object_index.clear();
    m_background_index.clear();
    m_file_editing.clear();

    std::istringstream stream(content);
    std::string token;

    enum Section {
        SEC_NONE,
        SEC_OBJECT,
        SEC_FILE_EDITING,
        SEC_BACKGROUND
    } section = SEC_NONE;

    while (stream >> token) {
        // Strip line comments if token starts with '#'
        if (token.empty() || token[0] == '#') {
            std::string dummy;
            std::getline(stream, dummy);
            continue;
        }

        if (token == "<object>") {
            section = SEC_OBJECT;
            continue;
        } else if (token == "<object_end>") {
            section = SEC_NONE;
            continue;
        } else if (token == "<file_editing>") {
            section = SEC_FILE_EDITING;
            continue;
        } else if (token == "<file_editing_end>") {
            section = SEC_NONE;
            continue;
        } else if (token == "<background>") {
            section = SEC_BACKGROUND;
            continue;
        } else if (token == "<background_end>") {
            section = SEC_NONE;
            continue;
        }

        if (section == SEC_OBJECT) {
            if (token == "id:") {
                object_entry_t entry;
                stream >> entry.id;

                std::string key;
                while (stream >> key) {
                    if (key[0] == '#') {
                        std::string dummy;
                        std::getline(stream, dummy);
                        break;
                    }
                    if (key == "type:") {
                        stream >> entry.type;
                    } else if (key == "file:") {
                        stream >> entry.file;
                        break;
                    }
                }
                m_object_index[entry.id] = m_objects.size();
                m_objects.push_back(entry);
            }
        } else if (section == SEC_BACKGROUND) {
            if (token == "id:") {
                background_entry_t entry;
                stream >> entry.id;

                std::string key;
                while (stream >> key) {
                    if (key[0] == '#') {
                        std::string dummy;
                        std::getline(stream, dummy);
                        break;
                    }
                    if (key == "file:") {
                        stream >> entry.file;
                        break;
                    }
                }
                m_background_index[entry.id] = m_backgrounds.size();
                m_backgrounds.push_back(entry);
            }
        } else if (section == SEC_FILE_EDITING) {
            m_file_editing = token;
        }
    }

    return !m_objects.empty();
}

const object_entry_t* data_txt_t::find_object(int32_t id) const {
    auto it = m_object_index.find(id);
    if (it != m_object_index.end()) {
        return &m_objects[it->second];
    }
    return nullptr;
}

const background_entry_t* data_txt_t::find_background(int32_t id) const {
    auto it = m_background_index.find(id);
    if (it != m_background_index.end()) {
        return &m_backgrounds[it->second];
    }
    return nullptr;
}

} // namespace lf2

