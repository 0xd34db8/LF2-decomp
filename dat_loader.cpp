#include "dat_loader.h"
#include "cipher.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>

namespace lf2 {

static std::string to_lower(std::string_view s) {
    std::string res;
    res.reserve(s.size());
    for (char c : s) {
        res.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    return res;
}

void dat_loader_t::init_file(file_t* file, uint32_t id, uint32_t type) {
    std::memset(file, 0, sizeof(file_t));
    file->id = id;
    file->type = type;
    file->weapon_hit_sound_id = -1;
    file->weapon_drop_sound_id = -1;
    file->weapon_broken_sound_id = -1;

    file->walking_frame_rate = 3;
    file->walking_speed = 3000.0;
    file->walking_speedz = 3000.0;
    file->running_frame_rate = 3;
    file->running_speed = 3000.0;
    file->running_speedz = 3000.0;
    file->heavy_walking_speed = 3000.0;
    file->heavy_walking_speedz = 3000.0;
    file->heavy_running_speed = 3000.0;
    file->heavy_running_speedz = 3000.0;

    std::strncpy(file->head, "none", sizeof(file->head) - 1);
    std::strncpy(file->small, "none", sizeof(file->small) - 1);
    std::strncpy(file->name, "none", sizeof(file->name) - 1);

    for (size_t i = 0; i < MAX_FRAMES; ++i) {
        file->frames[i].wait = 1;
        file->frames[i].next = 0;
        file->frames[i].state = 0;
        file->frames[i].itrs = nullptr;
        file->frames[i].bdys = nullptr;
        file->frames[i].itrs_size = 0;
        file->frames[i].bdys_size = 0;
    }
}

void dat_loader_t::free_file_resources(file_t* file) {
    if (!file) return;
    for (size_t i = 0; i < MAX_FRAMES; ++i) {
        if (file->frames[i].itrs) {
            delete[] file->frames[i].itrs;
            file->frames[i].itrs = nullptr;
            file->frames[i].itrs_size = 0;
        }
        if (file->frames[i].bdys) {
            delete[] file->frames[i].bdys;
            file->frames[i].bdys = nullptr;
            file->frames[i].bdys_size = 0;
        }
    }
}

bool dat_loader_t::load_file(file_t* file, const std::string& path, uint32_t id, uint32_t type) {
    if (!file) return false;

    std::string plaintext;
    std::string lower_path = to_lower(path);

    if (lower_path.size() >= 4 && lower_path.compare(lower_path.size() - 4, 4, ".dat") == 0) {
        if (!cipher_t::decrypt_file(path, plaintext)) {
            // Try fallback: sometimes a .dat file might be unencrypted plain text
            std::ifstream raw(path);
            if (!raw.is_open()) return false;
            std::stringstream ss;
            ss << raw.rdbuf();
            plaintext = ss.str();
        }
    } else {
        std::ifstream raw(path);
        if (!raw.is_open()) return false;
        std::stringstream ss;
        ss << raw.rdbuf();
        plaintext = ss.str();
    }

    return parse_content(file, plaintext, id, type);
}

bool dat_loader_t::parse_content(file_t* file, const std::string& content, uint32_t id, uint32_t type) {
    if (!file) return false;

    init_file(file, id, type);

    std::istringstream stream(content);
    std::string token;

    while (stream >> token) {
        // Comments
        if (!token.empty() && token[0] == '#') {
            std::string dummy;
            std::getline(stream, dummy);
            continue;
        }

        if (token == "<bmp_begin>") {
            while (stream >> token && token != "<bmp_end>") {
                if (!token.empty() && token[0] == '#') {
                    std::string dummy;
                    std::getline(stream, dummy);
                    continue;
                }

                if (token == "name:") {
                    std::string val;
                    stream >> val;
                    std::strncpy(file->name, val.c_str(), sizeof(file->name) - 1);
                } else if (token == "head:") {
                    std::string val;
                    stream >> val;
                    std::strncpy(file->head, val.c_str(), sizeof(file->head) - 1);
                } else if (token == "small:") {
                    std::string val;
                    stream >> val;
                    std::strncpy(file->small, val.c_str(), sizeof(file->small) - 1);
                } else if (token.rfind("file(", 0) == 0) {
                    // Sprite sheet entry: file(0-69): sprite\sys\davis_0.bmp w: 79 h: 79 row: 10 col: 7
                    std::string path_val;
                    stream >> path_val;
                    file->bmp_count++;
                } else if (token == "walking_frame_rate") {
                    stream >> file->walking_frame_rate;
                } else if (token == "walking_speed") {
                    stream >> file->walking_speed;
                } else if (token == "walking_speedz") {
                    stream >> file->walking_speedz;
                } else if (token == "running_frame_rate") {
                    stream >> file->running_frame_rate;
                } else if (token == "running_speed") {
                    stream >> file->running_speed;
                } else if (token == "running_speedz") {
                    stream >> file->running_speedz;
                } else if (token == "heavy_walking_speed") {
                    stream >> file->heavy_walking_speed;
                } else if (token == "heavy_walking_speedz") {
                    stream >> file->heavy_walking_speedz;
                } else if (token == "heavy_running_speed") {
                    stream >> file->heavy_running_speed;
                } else if (token == "heavy_running_speedz") {
                    stream >> file->heavy_running_speedz;
                } else if (token == "jump_height") {
                    stream >> file->jump_height;
                } else if (token == "jump_distance") {
                    stream >> file->jump_distance;
                } else if (token == "jump_distancez") {
                    stream >> file->jump_distancez;
                } else if (token == "dash_height") {
                    stream >> file->dash_height;
                } else if (token == "dash_distance") {
                    stream >> file->dash_distance;
                } else if (token == "dash_distancez") {
                    stream >> file->dash_distancez;
                } else if (token == "rowing_height") {
                    stream >> file->rowing_height;
                } else if (token == "rowing_distance") {
                    stream >> file->rowing_distance;
                } else if (token == "weapon_hp:") {
                    stream >> file->weapon_hp;
                } else if (token == "weapon_drop_hurt:") {
                    stream >> file->weapon_drop_hurt;
                } else if (token == "weapon_hit_sound:") {
                    stream >> file->weapon_hit_sound;
                } else if (token == "weapon_drop_sound:") {
                    stream >> file->weapon_drop_sound;
                } else if (token == "weapon_broken_sound:") {
                    stream >> file->weapon_broken_sound;
                }
            }
        } else if (token == "<frame>") {
            int frame_id = -1;
            std::string frame_name;
            stream >> frame_id >> frame_name;

            if (frame_id >= 0 && frame_id < static_cast<int>(MAX_FRAMES)) {
                frame_t& frame = file->frames[frame_id];
                frame.present = 1;
                std::strncpy(frame.name, frame_name.c_str(), sizeof(frame.name) - 1);

                while (stream >> token && token != "<frame_end>") {
                    if (!token.empty() && token[0] == '#') {
                        std::string dummy;
                        std::getline(stream, dummy);
                        continue;
                    }

                    if (token == "pic:") {
                        stream >> frame.pic;
                    } else if (token == "state:") {
                        stream >> frame.state;
                    } else if (token == "wait:") {
                        stream >> frame.wait;
                    } else if (token == "next:") {
                        stream >> frame.next;
                    } else if (token == "dvx:") {
                        stream >> frame.dvx;
                    } else if (token == "dvy:") {
                        stream >> frame.dvy;
                    } else if (token == "dvz:") {
                        stream >> frame.dvz;
                    } else if (token == "centerx:") {
                        stream >> frame.centerx;
                    } else if (token == "centery:") {
                        stream >> frame.centery;
                    } else if (token == "hit_a:") {
                        stream >> frame.hit_a;
                    } else if (token == "hit_d:") {
                        stream >> frame.hit_d;
                    } else if (token == "hit_j:") {
                        stream >> frame.hit_j;
                    } else if (token == "hit_Fa:") {
                        stream >> frame.hit_Fa;
                    } else if (token == "hit_Ua:") {
                        stream >> frame.hit_Ua;
                    } else if (token == "hit_Da:") {
                        stream >> frame.hit_Da;
                    } else if (token == "hit_Fj:") {
                        stream >> frame.hit_Fj;
                    } else if (token == "hit_Uj:") {
                        stream >> frame.hit_Uj;
                    } else if (token == "hit_Dj:") {
                        stream >> frame.hit_Dj;
                    } else if (token == "hit_ja:") {
                        stream >> frame.hit_ja;
                    } else if (token == "mp:") {
                        stream >> frame.mp;
                    } else if (token == "sound:") {
                        stream >> frame.sound;
                    } else if (token == "bpoint:") {
                        while (stream >> token && token != "bpoint_end:") {
                            if (token == "x:") stream >> frame.bpoint.x;
                            else if (token == "y:") stream >> frame.bpoint.y;
                        }
                    } else if (token == "wpoint:") {
                        while (stream >> token && token != "wpoint_end:") {
                            if (token == "kind:") stream >> frame.wpoint.kind;
                            else if (token == "x:") stream >> frame.wpoint.x;
                            else if (token == "y:") stream >> frame.wpoint.y;
                            else if (token == "weaponact:") stream >> frame.wpoint.weaponact;
                            else if (token == "attacking:") stream >> frame.wpoint.attacking;
                            else if (token == "cover:") stream >> frame.wpoint.cover;
                            else if (token == "dvx:") stream >> frame.wpoint.dvx;
                            else if (token == "dvy:") stream >> frame.wpoint.dvy;
                            else if (token == "dvz:") stream >> frame.wpoint.dvz;
                        }
                    } else if (token == "cpoint:") {
                        while (stream >> token && token != "cpoint_end:") {
                            if (token == "kind:") stream >> frame.cpoint.kind;
                            else if (token == "x:") stream >> frame.cpoint.x;
                            else if (token == "y:") stream >> frame.cpoint.y;
                            else if (token == "throwvx:") stream >> frame.cpoint.throwv_x;
                            else if (token == "throwvy:") stream >> frame.cpoint.throwv_y;
                            else if (token == "throwinjury:") stream >> frame.cpoint.throw_injury;
                            else if (token == "vaction:") stream >> frame.cpoint.v_action;
                            else if (token == "taction:") stream >> frame.cpoint.throw_a;
                            else if (token == "aaction:") stream >> frame.cpoint.throw_d;
                            else if (token == "jaction:") stream >> frame.cpoint.throw_j;
                            else if (token == "fronthurtact:") stream >> frame.cpoint.front_hurt_act;
                            else if (token == "backhurtact:") stream >> frame.cpoint.back_hurt_act;
                        }
                    } else if (token == "opoint:") {
                        while (stream >> token && token != "opoint_end:") {
                            if (token == "kind:") stream >> frame.opoint.kind;
                            else if (token == "x:") stream >> frame.opoint.x;
                            else if (token == "y:") stream >> frame.opoint.y;
                            else if (token == "action:") stream >> frame.opoint.action;
                            else if (token == "dvx:") stream >> frame.opoint.dvx;
                            else if (token == "dvy:") stream >> frame.opoint.dvy;
                            else if (token == "oid:") stream >> frame.opoint.oid;
                            else if (token == "facing:") stream >> frame.opoint.facing;
                        }
                    } else if (token == "bdy:") {
                        if (!frame.bdys) {
                            frame.bdys = new bdy_t[5]();
                        }
                        if (frame.bdys_size < 5) {
                            bdy_t& b = frame.bdys[frame.bdys_size++];
                            while (stream >> token && token != "bdy_end:") {
                                if (token == "kind:") stream >> b.kind;
                                else if (token == "x:") stream >> b.x;
                                else if (token == "y:") stream >> b.y;
                                else if (token == "w:") stream >> b.w;
                                else if (token == "h:") stream >> b.h;
                            }
                        } else {
                            while (stream >> token && token != "bdy_end:") {}
                        }
                    } else if (token == "itr:") {
                        if (!frame.itrs) {
                            frame.itrs = new itr_t[5]();
                        }
                        if (frame.itrs_size < 5) {
                            itr_t& it = frame.itrs[frame.itrs_size++];
                            while (stream >> token && token != "itr_end:") {
                                if (token == "kind:") stream >> it.kind;
                                else if (token == "x:") stream >> it.x;
                                else if (token == "y:") stream >> it.y;
                                else if (token == "w:") stream >> it.w;
                                else if (token == "h:") stream >> it.h;
                                else if (token == "dvx:") stream >> it.dvx;
                                else if (token == "dvy:") stream >> it.dvy;
                                else if (token == "fall:") stream >> it.fall;
                                else if (token == "arest:") stream >> it.arest;
                                else if (token == "vrest:") stream >> it.vrest;
                                else if (token == "bdefend:") stream >> it.bdefend;
                                else if (token == "injury:") stream >> it.injury;
                                else if (token == "zwidth:") stream >> it.zwidth;
                                else if (token == "effect:") stream >> it.effect;
                                else if (token == "catchingact:") {
                                    stream >> it.catching_act_1 >> it.catching_act_2;
                                } else if (token == "caughtact:") {
                                    stream >> it.caught_act_1 >> it.caught_act_2;
                                }
                            }
                        } else {
                            while (stream >> token && token != "itr_end:") {}
                        }
                    }
                }
            }
        }
    }

    return true;
}

std::string dat_loader_t::serialize_to_string(const file_t* file) {
    if (!file) return {};

    std::ostringstream ss;
    ss << "<bmp_begin>\n";
    ss << "name: " << file->name << "\n";
    ss << "head: " << file->head << "\n";
    ss << "small: " << file->small << "\n";

    ss << "walking_frame_rate " << file->walking_frame_rate << "\n";
    ss << "walking_speed " << file->walking_speed << "\n";
    ss << "walking_speedz " << file->walking_speedz << "\n";
    ss << "running_frame_rate " << file->running_frame_rate << "\n";
    ss << "running_speed " << file->running_speed << "\n";
    ss << "running_speedz " << file->running_speedz << "\n";
    ss << "heavy_walking_speed " << file->heavy_walking_speed << "\n";
    ss << "heavy_walking_speedz " << file->heavy_walking_speedz << "\n";
    ss << "heavy_running_speed " << file->heavy_running_speed << "\n";
    ss << "heavy_running_speedz " << file->heavy_running_speedz << "\n";
    ss << "jump_height " << file->jump_height << "\n";
    ss << "jump_distance " << file->jump_distance << "\n";
    ss << "jump_distancez " << file->jump_distancez << "\n";
    ss << "dash_height " << file->dash_height << "\n";
    ss << "dash_distance " << file->dash_distance << "\n";
    ss << "dash_distancez " << file->dash_distancez << "\n";
    ss << "rowing_height " << file->rowing_height << "\n";
    ss << "rowing_distance " << file->rowing_distance << "\n";
    ss << "<bmp_end>\n\n";

    for (size_t i = 0; i < MAX_FRAMES; ++i) {
        const frame_t& f = file->frames[i];
        if (f.present == 0) continue;

        ss << "<frame> " << i << " " << f.name << "\n";
        ss << "   pic: " << f.pic << "  state: " << f.state << "  wait: " << f.wait
           << "  next: " << f.next << "  dvx: " << f.dvx << "  dvy: " << f.dvy
           << "  dvz: " << f.dvz << "  centerx: " << f.centerx << "  centery: " << f.centery
           << "  hit_a: " << f.hit_a << "  hit_d: " << f.hit_d << "  hit_j: " << f.hit_j;
        if (f.hit_Fa) ss << " hit_Fa: " << f.hit_Fa;
        if (f.hit_Ua) ss << " hit_Ua: " << f.hit_Ua;
        if (f.hit_Da) ss << " hit_Da: " << f.hit_Da;
        if (f.hit_Fj) ss << " hit_Fj: " << f.hit_Fj;
        if (f.hit_Uj) ss << " hit_Uj: " << f.hit_Uj;
        if (f.hit_Dj) ss << " hit_Dj: " << f.hit_Dj;
        if (f.hit_ja) ss << " hit_ja: " << f.hit_ja;
        if (f.mp) ss << " mp: " << f.mp;
        ss << "\n";

        if (f.bpoint.x || f.bpoint.y) {
            ss << "   bpoint:\n      x: " << f.bpoint.x << "  y: " << f.bpoint.y << "\n   bpoint_end:\n";
        }

        if (f.wpoint.kind) {
            ss << "   wpoint:\n      kind: " << f.wpoint.kind << "  x: " << f.wpoint.x
               << "  y: " << f.wpoint.y << "  weaponact: " << f.wpoint.weaponact
               << "  attacking: " << f.wpoint.attacking << "  cover: " << f.wpoint.cover
               << "  dvx: " << f.wpoint.dvx << "  dvy: " << f.wpoint.dvy << "  dvz: " << f.wpoint.dvz
               << "\n   wpoint_end:\n";
        }

        if (f.itrs && f.itrs_size > 0) {
            for (uint32_t j = 0; j < f.itrs_size; ++j) {
                const itr_t& it = f.itrs[j];
                ss << "   itr:\n      kind: " << it.kind << "  x: " << it.x << "  y: " << it.y
                   << "  w: " << it.w << "  h: " << it.h << "  dvx: " << it.dvx << "  dvy: " << it.dvy
                   << "  fall: " << it.fall << "  arest: " << it.arest << "  vrest: " << it.vrest
                   << "  bdefend: " << it.bdefend << "  injury: " << it.injury << "  zwidth: " << it.zwidth
                   << "  effect: " << it.effect << "\n   itr_end:\n";
            }
        }

        if (f.bdys && f.bdys_size > 0) {
            for (uint32_t j = 0; j < f.bdys_size; ++j) {
                const bdy_t& b = f.bdys[j];
                ss << "   bdy:\n      kind: " << b.kind << "  x: " << b.x << "  y: " << b.y
                   << "  w: " << b.w << "  h: " << b.h << "\n   bdy_end:\n";
            }
        }

        ss << "<frame_end>\n\n";
    }

    return ss.str();
}

bool dat_loader_t::save_file(const file_t* file, const std::string& path, bool encrypt) {
    if (!file) return false;

    std::string text = serialize_to_string(file);
    if (encrypt) {
        std::vector<uint8_t> encrypted = cipher_t::encrypt(text);
        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) return false;
        out.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());
        return true;
    } else {
        std::ofstream out(path);
        if (!out.is_open()) return false;
        out.write(text.data(), text.size());
        return true;
    }
}

} // namespace lf2
