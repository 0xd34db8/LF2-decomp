#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <map>

namespace lf2 {

struct object_entry_t {
    int32_t     id;
    int32_t     type;
    std::string file;
};

struct background_entry_t {
    int32_t     id;
    std::string file;
};

class data_txt_t {
public:
    data_txt_t();

    bool load_from_file(const std::string& path);
    bool load_from_string(const std::string& content);

    const std::vector<object_entry_t>& get_objects() const { return m_objects; }
    const std::vector<background_entry_t>& get_backgrounds() const { return m_backgrounds; }
    const std::string& get_file_editing() const { return m_file_editing; }

    const object_entry_t* find_object(int32_t id) const;
    const background_entry_t* find_background(int32_t id) const;

private:
    std::vector<object_entry_t>     m_objects;
    std::vector<background_entry_t> m_backgrounds;
    std::string                     m_file_editing;
    std::map<int32_t, size_t>       m_object_index;
    std::map<int32_t, size_t>       m_background_index;
};

} // namespace lf2

