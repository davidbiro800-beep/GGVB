#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <pthread.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <jni.h>
#include <unistd.h>
#include <sys/mman.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <atomic>
#include <mutex>

#define FLBOOL              JKLDDDOJJKSDD
#define FLINT               KKJSDIOQEOLSD
#define FLFLOAT             LKJSDWQEKLMSD
#define MemoryGuard         QQWERTYLKJHGF
#define EncryptedMeta       AZSXDCFVGBHNS
#define Vector2             PLMOKNIJBUHVS
#define Vector3             QAZWSXEDCRFVT
#define Color               TGBYHNUJMIKOL
#define Texture             RFVTGBYHNUJSD
#define Transform           EDCRFVTGBYHNM
#define Shader              WSXEDCRFVTGBS
#define Material            QAZWSXEDCMATS
#define Object              PLMOKNIJBOBJS
#define Weapon              OKMNBVCXZWEPS
#define Player              LKJHGFDSAPLYS
#define Zombie              MNBVCXZASZMBS
#define MapTile             POIUYTREWQTLS
#define GameMap             ASDFGHJKLGMPS
#define Camera              ZXCVBNMQWECMS
#define RenderBatch         QWERTYUIOPRBS
#define Game                ASDFQWERZXCGS
#define Projectile          ZAQWSXCDERFVB
#define WaveManager         TGBNHYMJUKILP
#define InputState          OLPKMIJNUHBYG
#define ParticleEffect      VFTCRDXESZWAQ
#define CollisionResult     MNBVGTRFCDESX

#define get_transform       JJKKLLMMNNOOP
#define set_transform       QQRRSSTTAABBC
#define get_position        CCDDEEFFGGHHI
#define set_position        JJKKLLMMNNOQP
#define get_health          RRSSTTAABBCCD
#define set_health          EEFFGGHHIIJJK
#define get_damage          LLMMNNOOPPQQR
#define set_damage          SSTTUUVVWWXXY
#define get_speed           ZZAABBCCDDEEF
#define set_speed           GGHHIIJJKKLLM
#define get_instance        NNOOPPQQRRSSA
#define get_material        TTAABBCCDDEEG
#define set_material        FFGGHHIIJJKKL
#define get_shader          MMNNOOPPQQRRS
#define set_shader          TTUUVVWWXXYYZ
#define get_color           AABBCCDDEEFFH
#define set_color           GGHHIIJJKKLLI
#define get_texture         MMNNOOPPQQRRJ
#define set_texture         SSTTUUVVWWXXK
#define get_active          YYZZAABBCCDDL
#define set_active          EEFFGGHHIIJJM
#define get_alive           KKLLMMNNOOPPN
#define set_alive           QQRRSSTTAABBO
#define get_score           UUVVWWXXYYZAP
#define set_score           BBCCDDEEFFGGQ
#define get_ammo            HHIIJJKKLLMMR
#define set_ammo            NNOOPPQQRRSSS
#define get_max_ammo        TTUUVVWWXXYYT
#define set_max_ammo        ZZAABBCCDDEEU
#define get_fire_rate       FFGGHHIIJJKKV
#define set_fire_rate       LLMMNNOOPPQQW
#define get_range           RRSSTTAABBCCX
#define set_range           DDEEFFGGHHIIY
#define get_reload_time     JJKKLLMMNNOZZ
#define set_reload_time     PPQQRRSSTTAAA
#define get_spread          BBCCDDEEFFBBB
#define set_spread          GGHHIIJJKKCCC
#define get_pellets         LLMMNNOOPPDDD
#define set_pellets         QQRRSSTTAAEEE
#define get_size            UUVVWWXXYFFF
#define set_size            ZZAABBCCDGGGG
#define get_rotation        EEFFGGHHIHHH
#define set_rotation        JJKKLLMMNJJJ
#define get_scale           OOPPQQRRSKKK
#define set_scale           TTAABBCCDLLL
#define get_width           FFGGHHIIJMMM
#define set_width           KKLLMMNOONNNN
#define get_height          PPQQRRSSTOOOO
#define set_height          UUVVWWXXYPPP
#define get_walkable        ZZAABBCCDQQQQ
#define set_walkable        EEFFGGHHRRRR
#define get_type            IIJJKKLLSSSS
#define set_type            MMNNOPQQTTTT
#define get_tag             RRSSTUUVUUUU
#define set_tag             WWXXYZZAVVVV
#define get_zoom            BBCCDEEFWWWW
#define set_zoom            GGHIJJKKXXXX
#define get_target          LLMNNOOPYYYY
#define set_target          QQRSTTUUZZZZ
#define get_weapon          VVWXYYZA1111
#define set_weapon          BBCDEFGH2222
#define get_direction       IIJKLMNO3333
#define set_direction       PPQRSTUV4444
#define get_cooldown        WWXYZABC5555
#define set_cooldown        DDEFGHIJ6666
#define get_wave            KKLMNOPR7777
#define set_wave            SSTUVWXY8888
#define get_opacity         ZZABCDEF9999
#define set_opacity         GGHIJKLM0000
#define init_game           NNOPQRSTAAAB
#define update_game         UUVWXYZABBBC
#define render_game         CCDEFGHIAAAD
#define cleanup_game        JJKLMNOPAAAE
#define spawn_zombie        QQRSTUVWAAAF
#define check_collision     XXYYZABCAAAG
#define fire_weapon         DDEEFGHIAAAH
#define take_damage_p       JJKKLLMMAAAI
#define take_damage_z       NNOOPPQQAAAJ
#define move_player         RRSSTTUVAAAK
#define move_zombie         WWXXYYZZAAAL
#define reload_weapon       AABBCCDDEAAM
#define next_wave           FFGGHHIIJAAN
#define apply_force         KKLLMMNNOAAO
#define check_line_sight    PPQQRRSSAAAP
#define process_input       TTUUVVWWAAAQ
#define render_quad         XXYYZAABAAAR
#define render_circle       BBCCDDEEFAAS
#define render_line         GGHHIIJJKAAT
#define render_text_gl      LLMMNNOOPQAU
#define render_healthbar    QQRRSSTTUVAV
#define compile_shader_fn   WWXXYYZZABAW
#define link_program_fn     CCDDEEFFGHAX
#define setup_buffers       IIJJKKLLMNAY
#define destroy_buffers     OOPPQQRRSSAZ
#define memory_check_fn     TTUUVVWWXYBA
#define integrity_thread    ZZAABBCCDDBB
#define decrypt_meta_fn     EEFFGGHHIIBC
#define encrypt_meta_fn     JJKKLLMMNNBD

static uint32_t _fl_xor_seed = 0x5A3C9E7D;

static inline uint32_t _fl_next_key() {
    _fl_xor_seed ^= _fl_xor_seed << 13;
    _fl_xor_seed ^= _fl_xor_seed >> 17;
    _fl_xor_seed ^= _fl_xor_seed << 5;
    return _fl_xor_seed;
}

static inline uint32_t _fl_crc32(const void* data, size_t len) {
    const uint8_t* buf = (const uint8_t*)data;
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= buf[i];
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
        }
    }
    return ~crc;
}

struct FLBOOL {
    uint32_t _sig;
    uint32_t _enc;
    uint32_t _key;
    uint32_t _check;

    FLBOOL() : _sig(0xFB001D), _key(_fl_next_key()) {
        _enc = (uint32_t)false ^ _key;
        _check = _sig ^ _enc ^ _key;
    }

    FLBOOL(bool v) : _sig(0xFB001D), _key(_fl_next_key()) {
        _enc = (uint32_t)v ^ _key;
        _check = _sig ^ _enc ^ _key;
    }

    bool get() const {
        if (_sig != 0xFB001D) return false;
        if (_check != (_sig ^ _enc ^ _key)) return false;
        return (bool)(_enc ^ _key);
    }

    void set(bool v) {
        _enc = (uint32_t)v ^ _key;
        _check = _sig ^ _enc ^ _key;
    }

    bool is_valid() const {
        return _sig == 0xFB001D && _check == (_sig ^ _enc ^ _key);
    }

    operator bool() const { return get(); }
    FLBOOL& operator=(bool v) { set(v); return *this; }
    bool operator!() const { return !get(); }
    bool operator==(bool v) const { return get() == v; }
    bool operator!=(bool v) const { return get() != v; }
    bool operator==(const FLBOOL& o) const { return get() == o.get(); }
    bool operator!=(const FLBOOL& o) const { return get() != o.get(); }
};

struct FLINT {
    uint32_t _sig;
    int32_t _enc;
    uint32_t _key;
    uint32_t _check;

    FLINT() : _sig(0xF1417D), _key(_fl_next_key()) {
        _enc = 0 ^ (int32_t)_key;
        _check = _sig ^ (uint32_t)_enc ^ _key;
    }

    FLINT(int v) : _sig(0xF1417D), _key(_fl_next_key()) {
        _enc = v ^ (int32_t)_key;
        _check = _sig ^ (uint32_t)_enc ^ _key;
    }

    int get() const {
        if (_sig != 0xF1417D) return 0;
        if (_check != (_sig ^ (uint32_t)_enc ^ _key)) return 0;
        return _enc ^ (int32_t)_key;
    }

    void set(int v) {
        _enc = v ^ (int32_t)_key;
        _check = _sig ^ (uint32_t)_enc ^ _key;
    }

    bool is_valid() const {
        return _sig == 0xF1417D && _check == (_sig ^ (uint32_t)_enc ^ _key);
    }

    operator int() const { return get(); }
    FLINT& operator=(int v) { set(v); return *this; }
    FLINT operator+(const FLINT& o) const { return FLINT(get() + o.get()); }
    FLINT operator-(const FLINT& o) const { return FLINT(get() - o.get()); }
    FLINT operator*(const FLINT& o) const { return FLINT(get() * o.get()); }
    FLINT operator/(const FLINT& o) const { return FLINT(get() / o.get()); }
    FLINT operator+(int v) const { return FLINT(get() + v); }
    FLINT operator-(int v) const { return FLINT(get() - v); }
    FLINT operator*(int v) const { return FLINT(get() * v); }
    FLINT operator/(int v) const { return FLINT(get() / v); }
    FLINT& operator+=(int v) { set(get() + v); return *this; }
    FLINT& operator-=(int v) { set(get() - v); return *this; }
    FLINT& operator+=(const FLINT& o) { set(get() + o.get()); return *this; }
    FLINT& operator-=(const FLINT& o) { set(get() - o.get()); return *this; }
    FLINT& operator++() { set(get() + 1); return *this; }
    FLINT& operator--() { set(get() - 1); return *this; }
    bool operator==(int v) const { return get() == v; }
    bool operator!=(int v) const { return get() != v; }
    bool operator<(int v) const { return get() < v; }
    bool operator>(int v) const { return get() > v; }
    bool operator<=(int v) const { return get() <= v; }
    bool operator>=(int v) const { return get() >= v; }
    bool operator==(const FLINT& o) const { return get() == o.get(); }
    bool operator!=(const FLINT& o) const { return get() != o.get(); }
    bool operator<(const FLINT& o) const { return get() < o.get(); }
    bool operator>(const FLINT& o) const { return get() > o.get(); }
    bool operator<=(const FLINT& o) const { return get() <= o.get(); }
    bool operator>=(const FLINT& o) const { return get() >= o.get(); }
};

struct FLFLOAT {
    uint32_t _sig;
    uint32_t _enc;
    uint32_t _key;
    uint32_t _check;

    FLFLOAT() : _sig(0xFF104D), _key(_fl_next_key()) {
        float z = 0.0f;
        uint32_t bits;
        memcpy(&bits, &z, sizeof(float));
        _enc = bits ^ _key;
        _check = _sig ^ _enc ^ _key;
    }

    FLFLOAT(float v) : _sig(0xFF104D), _key(_fl_next_key()) {
        uint32_t bits;
        memcpy(&bits, &v, sizeof(float));
        _enc = bits ^ _key;
        _check = _sig ^ _enc ^ _key;
    }

    float get() const {
        if (_sig != 0xFF104D) return 0.0f;
        if (_check != (_sig ^ _enc ^ _key)) return 0.0f;
        uint32_t bits = _enc ^ _key;
        float v;
        memcpy(&v, &bits, sizeof(float));
        return v;
    }

    void set(float v) {
        uint32_t bits;
        memcpy(&bits, &v, sizeof(float));
        _enc = bits ^ _key;
        _check = _sig ^ _enc ^ _key;
    }

    bool is_valid() const {
        return _sig == 0xFF104D && _check == (_sig ^ _enc ^ _key);
    }

    operator float() const { return get(); }
    FLFLOAT& operator=(float v) { set(v); return *this; }
    FLFLOAT operator+(const FLFLOAT& o) const { return FLFLOAT(get() + o.get()); }
    FLFLOAT operator-(const FLFLOAT& o) const { return FLFLOAT(get() - o.get()); }
    FLFLOAT operator*(const FLFLOAT& o) const { return FLFLOAT(get() * o.get()); }
    FLFLOAT operator/(const FLFLOAT& o) const { return FLFLOAT(get() / o.get()); }
    FLFLOAT operator+(float v) const { return FLFLOAT(get() + v); }
    FLFLOAT operator-(float v) const { return FLFLOAT(get() - v); }
    FLFLOAT operator*(float v) const { return FLFLOAT(get() * v); }
    FLFLOAT operator/(float v) const { return FLFLOAT(get() / v); }
    FLFLOAT& operator+=(float v) { set(get() + v); return *this; }
    FLFLOAT& operator-=(float v) { set(get() - v); return *this; }
    FLFLOAT& operator+=(const FLFLOAT& o) { set(get() + o.get()); return *this; }
    FLFLOAT& operator-=(const FLFLOAT& o) { set(get() - o.get()); return *this; }
    bool operator==(float v) const { return fabsf(get() - v) < 0.0001f; }
    bool operator!=(float v) const { return fabsf(get() - v) >= 0.0001f; }
    bool operator<(float v) const { return get() < v; }
    bool operator>(float v) const { return get() > v; }
    bool operator<=(float v) const { return get() <= v; }
    bool operator>=(float v) const { return get() >= v; }
    bool operator<(const FLFLOAT& o) const { return get() < o.get(); }
    bool operator>(const FLFLOAT& o) const { return get() > o.get(); }
};

struct MemoryGuard {
    struct Region {
        void* _ptr;
        void* _copy;
        size_t _size;
        uint32_t _crc;
    };

    std::vector<Region> _regions;
    std::mutex _mtx;
    std::atomic<bool> _tampered;
    std::atomic<bool> _running;
    pthread_t _thread;

    MemoryGuard() : _tampered(false), _running(false), _thread(0) {}

    ~MemoryGuard() {
        stop();
        for (auto& r : _regions) {
            if (r._copy) free(r._copy);
        }
    }

    void register_region(void* ptr, size_t size) {
        std::lock_guard<std::mutex> lock(_mtx);
        Region r;
        r._ptr = ptr;
        r._size = size;
        r._copy = malloc(size);
        memcpy(r._copy, ptr, size);
        r._crc = _fl_crc32(r._copy, size);
        _regions.push_back(r);
    }

    void update_region(void* ptr) {
        std::lock_guard<std::mutex> lock(_mtx);
        for (auto& r : _regions) {
            if (r._ptr == ptr) {
                memcpy(r._copy, r._ptr, r._size);
                r._crc = _fl_crc32(r._copy, r._size);
                break;
            }
        }
    }

    void update_all() {
        std::lock_guard<std::mutex> lock(_mtx);
        for (auto& r : _regions) {
            memcpy(r._copy, r._ptr, r._size);
            r._crc = _fl_crc32(r._copy, r._size);
        }
    }

    bool verify() {
        std::lock_guard<std::mutex> lock(_mtx);
        for (auto& r : _regions) {
            uint32_t copy_crc = _fl_crc32(r._copy, r._size);
            if (copy_crc != r._crc) {
                _tampered = true;
                return false;
            }
            if (memcmp(r._ptr, r._copy, r._size) != 0) {
                _tampered = true;
                return false;
            }
        }
        return true;
    }

    bool is_tampered() const { return _tampered.load(); }

    static void* _check_thread(void* arg) {
        MemoryGuard* self = (MemoryGuard*)arg;
        while (self->_running.load()) {
            if (!self->verify()) {
                break;
            }
            usleep(50000);
        }
        return nullptr;
    }

    void start() {
        _running = true;
        pthread_create(&_thread, nullptr, _check_thread, this);
    }

    void stop() {
        _running = false;
        if (_thread) {
            pthread_join(_thread, nullptr);
            _thread = 0;
        }
    }
};

struct EncryptedMeta {
    static const uint8_t _meta_key = 0xA7;
    static const size_t META_MAX = 4096;

    uint8_t _data[META_MAX];
    size_t _len;
    uint32_t _crc;

    EncryptedMeta() : _len(0), _crc(0) {
        memset(_data, 0, META_MAX);
    }

    void store(const void* src, size_t len) {
        if (len > META_MAX) len = META_MAX;
        _len = len;
        const uint8_t* s = (const uint8_t*)src;
        for (size_t i = 0; i < len; i++) {
            _data[i] = s[i] ^ (_meta_key + (uint8_t)(i * 37));
        }
        _crc = _fl_crc32(_data, _len);
    }

    bool load(void* dst, size_t len) const {
        if (len > _len) len = _len;
        if (_fl_crc32(_data, _len) != _crc) return false;
        uint8_t* d = (uint8_t*)dst;
        for (size_t i = 0; i < len; i++) {
            d[i] = _data[i] ^ (_meta_key + (uint8_t)(i * 37));
        }
        return true;
    }

    bool is_valid() const {
        return _fl_crc32(_data, _len) == _crc;
    }

    void store_int(int val) { store(&val, sizeof(int)); }
    void store_float(float val) { store(&val, sizeof(float)); }
    void store_string(const char* str) { store(str, strlen(str) + 1); }

    int load_int() const {
        int v = 0;
        load(&v, sizeof(int));
        return v;
    }

    float load_float() const {
        float v = 0.0f;
        load(&v, sizeof(float));
        return v;
    }

    bool load_string(char* dst, size_t max_len) const {
        return load(dst, max_len);
    }
};

struct Vector2 {
    FLFLOAT x;
    FLFLOAT y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    float get_x() const { return x.get(); }
    void set_x(float v) { x.set(v); }
    float get_y() const { return y.get(); }
    void set_y(float v) { y.set(v); }

    Vector2 operator+(const Vector2& o) const { return Vector2(x.get() + o.x.get(), y.get() + o.y.get()); }
    Vector2 operator-(const Vector2& o) const { return Vector2(x.get() - o.x.get(), y.get() - o.y.get()); }
    Vector2 operator*(float s) const { return Vector2(x.get() * s, y.get() * s); }

    float length() const {
        float lx = x.get(), ly = y.get();
        return sqrtf(lx * lx + ly * ly);
    }

    Vector2 normalized() const {
        float l = length();
        if (l < 0.0001f) return Vector2(0.0f, 0.0f);
        return Vector2(x.get() / l, y.get() / l);
    }

    float distance(const Vector2& o) const {
        return (*this - o).length();
    }

    float dot(const Vector2& o) const {
        return x.get() * o.x.get() + y.get() * o.y.get();
    }

    bool is_valid() const { return x.is_valid() && y.is_valid(); }
};

struct Vector3 {
    FLFLOAT x;
    FLFLOAT y;
    FLFLOAT z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    float get_x() const { return x.get(); }
    void set_x(float v) { x.set(v); }
    float get_y() const { return y.get(); }
    void set_y(float v) { y.set(v); }
    float get_z() const { return z.get(); }
    void set_z(float v) { z.set(v); }

    Vector3 operator+(const Vector3& o) const { return Vector3(x.get() + o.x.get(), y.get() + o.y.get(), z.get() + o.z.get()); }
    Vector3 operator-(const Vector3& o) const { return Vector3(x.get() - o.x.get(), y.get() - o.y.get(), z.get() - o.z.get()); }
    Vector3 operator*(float s) const { return Vector3(x.get() * s, y.get() * s, z.get() * s); }

    float length() const {
        float lx = x.get(), ly = y.get(), lz = z.get();
        return sqrtf(lx * lx + ly * ly + lz * lz);
    }

    Vector3 normalized() const {
        float l = length();
        if (l < 0.0001f) return Vector3(0.0f, 0.0f, 0.0f);
        return Vector3(x.get() / l, y.get() / l, z.get() / l);
    }

    bool is_valid() const { return x.is_valid() && y.is_valid() && z.is_valid(); }
};

struct Color {
    FLFLOAT r;
    FLFLOAT g;
    FLFLOAT b;
    FLFLOAT a;

    Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}

    float get_r() const { return r.get(); }
    void set_r(float v) { r.set(v); }
    float get_g() const { return g.get(); }
    void set_g(float v) { g.set(v); }
    float get_b() const { return b.get(); }
    void set_b(float v) { b.set(v); }
    float get_a() const { return a.get(); }
    void set_a(float v) { a.set(v); }

    bool is_valid() const { return r.is_valid() && g.is_valid() && b.is_valid() && a.is_valid(); }

    static Color red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
    static Color green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
    static Color blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
    static Color white() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
    static Color black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
    static Color yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
    static Color brown() { return Color(0.6f, 0.3f, 0.1f, 1.0f); }
    static Color gray() { return Color(0.5f, 0.5f, 0.5f, 1.0f); }
    static Color dark_gray() { return Color(0.3f, 0.3f, 0.3f, 1.0f); }
    static Color dark_green() { return Color(0.0f, 0.5f, 0.0f, 1.0f); }
    static Color dark_red() { return Color(0.5f, 0.0f, 0.0f, 1.0f); }
};

struct Texture {
    FLINT _id;
    FLINT _width;
    FLINT _height;
    FLINT _channels;
    FLBOOL _loaded;

    Texture() : _id(0), _width(0), _height(0), _channels(4), _loaded(false) {}

    int get_id() const { return _id.get(); }
    void set_id(int v) { _id.set(v); }
    int get_width() const { return _width.get(); }
    void set_width(int v) { _width.set(v); }
    int get_height() const { return _height.get(); }
    void set_height(int v) { _height.set(v); }
    int get_channels() const { return _channels.get(); }
    void set_channels(int v) { _channels.set(v); }
    bool get_loaded() const { return _loaded.get(); }
    void set_loaded(bool v) { _loaded.set(v); }

    bool is_valid() const {
        return _id.is_valid() && _width.is_valid() && _height.is_valid() &&
               _channels.is_valid() && _loaded.is_valid();
    }
};

struct Transform {
    Vector2 _position;
    FLFLOAT _rotation;
    Vector2 _scale;

    Transform() : _rotation(0.0f), _scale(1.0f, 1.0f) {}
    Transform(float x, float y) : _position(x, y), _rotation(0.0f), _scale(1.0f, 1.0f) {}
    Transform(float x, float y, float rot) : _position(x, y), _rotation(rot), _scale(1.0f, 1.0f) {}
    Transform(float x, float y, float rot, float sx, float sy) : _position(x, y), _rotation(rot), _scale(sx, sy) {}

    Vector2 get_position() const { return _position; }
    void set_position(const Vector2& v) { _position = v; }
    void set_position(float x, float y) { _position.set_x(x); _position.set_y(y); }
    float get_rotation() const { return _rotation.get(); }
    void set_rotation(float v) { _rotation.set(v); }
    Vector2 get_scale() const { return _scale; }
    void set_scale(const Vector2& v) { _scale = v; }
    void set_scale(float x, float y) { _scale.set_x(x); _scale.set_y(y); }

    float get_x() const { return _position.get_x(); }
    float get_y() const { return _position.get_y(); }
    void set_x(float v) { _position.set_x(v); }
    void set_y(float v) { _position.set_y(v); }

    void translate(float dx, float dy) {
        _position.set_x(_position.get_x() + dx);
        _position.set_y(_position.get_y() + dy);
    }

    void translate(const Vector2& delta) {
        translate(delta.get_x(), delta.get_y());
    }

    bool is_valid() const {
        return _position.is_valid() && _rotation.is_valid() && _scale.is_valid();
    }
};

struct Shader {
    FLINT _program;
    FLINT _vertex_shader;
    FLINT _fragment_shader;
    FLBOOL _compiled;
    FLINT _uniform_proj;
    FLINT _uniform_color;
    FLINT _uniform_model;

    Shader() : _program(0), _vertex_shader(0), _fragment_shader(0), _compiled(false),
               _uniform_proj(-1), _uniform_color(-1), _uniform_model(-1) {}

    int get_program() const { return _program.get(); }
    void set_program(int v) { _program.set(v); }
    int get_vertex_shader() const { return _vertex_shader.get(); }
    void set_vertex_shader(int v) { _vertex_shader.set(v); }
    int get_fragment_shader() const { return _fragment_shader.get(); }
    void set_fragment_shader(int v) { _fragment_shader.set(v); }
    bool get_compiled() const { return _compiled.get(); }
    void set_compiled(bool v) { _compiled.set(v); }
    int get_uniform_proj() const { return _uniform_proj.get(); }
    void set_uniform_proj(int v) { _uniform_proj.set(v); }
    int get_uniform_color() const { return _uniform_color.get(); }
    void set_uniform_color(int v) { _uniform_color.set(v); }
    int get_uniform_model() const { return _uniform_model.get(); }
    void set_uniform_model(int v) { _uniform_model.set(v); }

    bool is_valid() const {
        return _program.is_valid() && _vertex_shader.is_valid() &&
               _fragment_shader.is_valid() && _compiled.is_valid();
    }
};

struct Material {
    Color _color;
    Texture _texture;
    Shader* _shader;
    FLFLOAT _opacity;
    FLBOOL _use_texture;

    Material() : _shader(nullptr), _opacity(1.0f), _use_texture(false) {}

    Color get_color() const { return _color; }
    void set_color(const Color& c) { _color = c; }
    Texture get_texture() const { return _texture; }
    void set_texture(const Texture& t) { _texture = t; _use_texture = true; }
    Shader* get_shader() const { return _shader; }
    void set_shader(Shader* s) { _shader = s; }
    float get_opacity() const { return _opacity.get(); }
    void set_opacity(float v) { _opacity.set(v); }
    bool get_use_texture() const { return _use_texture.get(); }
    void set_use_texture(bool v) { _use_texture.set(v); }

    bool is_valid() const {
        return _color.is_valid() && _opacity.is_valid() && _use_texture.is_valid();
    }
};

struct Object {
    Transform _transform;
    Material _material;
    Vector2 _size;
    FLBOOL _active;
    FLINT _tag;
    FLINT _layer;
    FLINT _id;
    FLBOOL _visible;
    FLBOOL _collidable;

    static FLINT _next_id;

    Object() : _size(1.0f, 1.0f), _active(true), _tag(0), _layer(0), _visible(true), _collidable(true) {
        _id = _next_id.get();
        _next_id += 1;
    }

    Transform get_transform() const { return _transform; }
    void set_transform(const Transform& t) { _transform = t; }
    Material get_material() const { return _material; }
    void set_material(const Material& m) { _material = m; }
    Vector2 get_size() const { return _size; }
    void set_size(const Vector2& s) { _size = s; }
    void set_size(float w, float h) { _size = Vector2(w, h); }
    bool get_active() const { return _active.get(); }
    void set_active(bool v) { _active.set(v); }
    int get_tag() const { return _tag.get(); }
    void set_tag(int v) { _tag.set(v); }
    int get_layer() const { return _layer.get(); }
    void set_layer(int v) { _layer.set(v); }
    int get_id() const { return _id.get(); }
    bool get_visible() const { return _visible.get(); }
    void set_visible(bool v) { _visible.set(v); }
    bool get_collidable() const { return _collidable.get(); }
    void set_collidable(bool v) { _collidable.set(v); }

    float get_x() const { return _transform.get_x(); }
    float get_y() const { return _transform.get_y(); }
    void set_x(float v) { _transform.set_x(v); }
    void set_y(float v) { _transform.set_y(v); }

    float get_width() const { return _size.get_x(); }
    float get_height() const { return _size.get_y(); }
    void set_width(float v) { _size.set_x(v); }
    void set_height(float v) { _size.set_y(v); }

    bool intersects(const Object& other) const {
        float ax = get_x(), ay = get_y();
        float aw = get_width(), ah = get_height();
        float bx = other.get_x(), by = other.get_y();
        float bw = other.get_width(), bh = other.get_height();
        return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
    }

    bool contains_point(float px, float py) const {
        float ox = get_x(), oy = get_y();
        float ow = get_width(), oh = get_height();
        return px >= ox && px <= ox + ow && py >= oy && py <= oy + oh;
    }

    void start() {
        _active = true;
        _visible = true;
    }

    bool is_valid() const {
        return _transform.is_valid() && _active.is_valid() &&
               _tag.is_valid() && _id.is_valid() && _visible.is_valid() && _collidable.is_valid();
    }
};

struct Weapon {
    FLINT _damage;
    FLINT _ammo;
    FLINT _max_ammo;
    FLFLOAT _fire_rate;
    FLFLOAT _range;
    FLFLOAT _reload_time;
    FLFLOAT _spread;
    FLINT _pellets;
    FLFLOAT _cooldown_timer;
    FLFLOAT _reload_timer;
    FLBOOL _reloading;
    FLINT _type;

    Weapon() : _damage(25), _ammo(8), _max_ammo(8), _fire_rate(0.5f), _range(8.0f),
               _reload_time(2.0f), _spread(0.3f), _pellets(5), _cooldown_timer(0.0f),
               _reload_timer(0.0f), _reloading(false), _type(0) {}

    int get_damage() const { return _damage.get(); }
    void set_damage(int v) { _damage.set(v); }
    int get_ammo() const { return _ammo.get(); }
    void set_ammo(int v) { _ammo.set(v); }
    int get_max_ammo() const { return _max_ammo.get(); }
    void set_max_ammo(int v) { _max_ammo.set(v); }
    float get_fire_rate() const { return _fire_rate.get(); }
    void set_fire_rate(float v) { _fire_rate.set(v); }
    float get_range() const { return _range.get(); }
    void set_range(float v) { _range.set(v); }
    float get_reload_time() const { return _reload_time.get(); }
    void set_reload_time(float v) { _reload_time.set(v); }
    float get_spread() const { return _spread.get(); }
    void set_spread(float v) { _spread.set(v); }
    int get_pellets() const { return _pellets.get(); }
    void set_pellets(int v) { _pellets.set(v); }
    float get_cooldown() const { return _cooldown_timer.get(); }
    void set_cooldown(float v) { _cooldown_timer.set(v); }
    bool get_reloading() const { return _reloading.get(); }
    int get_type() const { return _type.get(); }
    void set_type(int v) { _type.set(v); }

    bool can_fire() const {
        return _ammo.get() > 0 && _cooldown_timer.get() <= 0.0f && !_reloading.get();
    }

    void fire() {
        if (!can_fire()) return;
        _ammo -= 1;
        _cooldown_timer = _fire_rate.get();
    }

    void start_reload() {
        if (_reloading.get()) return;
        if (_ammo.get() == _max_ammo.get()) return;
        _reloading = true;
        _reload_timer = _reload_time.get();
    }

    void update(float dt) {
        if (_cooldown_timer.get() > 0.0f) {
            _cooldown_timer -= dt;
        }
        if (_reloading.get()) {
            _reload_timer -= dt;
            if (_reload_timer.get() <= 0.0f) {
                _ammo = _max_ammo.get();
                _reloading = false;
            }
        }
    }

    bool is_valid() const {
        return _damage.is_valid() && _ammo.is_valid() && _max_ammo.is_valid() &&
               _fire_rate.is_valid() && _range.is_valid() && _reload_time.is_valid() &&
               _spread.is_valid() && _pellets.is_valid() && _reloading.is_valid();
    }
};

struct Player {
    Transform _transform;
    FLINT _health;
    FLINT _max_health;
    FLFLOAT _speed;
    FLFLOAT _direction;
    FLINT _score;
    FLBOOL _alive;
    Weapon _weapon;
    FLFLOAT _invincible_timer;
    Color _color;
    Vector2 _size;
    FLFLOAT _shoot_dir_x;
    FLFLOAT _shoot_dir_y;

    Player() : _health(100), _max_health(100), _speed(5.0f), _direction(0.0f),
               _score(0), _alive(true), _invincible_timer(0.0f),
               _color(0.0f, 0.8f, 0.0f, 1.0f), _size(0.8f, 0.8f),
               _shoot_dir_x(1.0f), _shoot_dir_y(0.0f) {}

    Transform get_transform() const { return _transform; }
    void set_transform(const Transform& t) { _transform = t; }
    int get_health() const { return _health.get(); }
    void set_health(int v) { _health.set(v); }
    int get_max_health() const { return _max_health.get(); }
    void set_max_health(int v) { _max_health.set(v); }
    float get_speed() const { return _speed.get(); }
    void set_speed(float v) { _speed.set(v); }
    float get_direction() const { return _direction.get(); }
    void set_direction(float v) { _direction.set(v); }
    int get_score() const { return _score.get(); }
    void set_score(int v) { _score.set(v); }
    bool get_alive() const { return _alive.get(); }
    void set_alive(bool v) { _alive.set(v); }
    Weapon get_weapon() const { return _weapon; }
    void set_weapon(const Weapon& w) { _weapon = w; }
    float get_x() const { return _transform.get_x(); }
    float get_y() const { return _transform.get_y(); }
    void set_x(float v) { _transform.set_x(v); }
    void set_y(float v) { _transform.set_y(v); }

    void take_damage(int dmg) {
        if (!_alive.get()) return;
        if (_invincible_timer.get() > 0.0f) return;
        int hp = _health.get() - dmg;
        if (hp < 0) hp = 0;
        _health.set(hp);
        _invincible_timer = 0.5f;
        if (hp <= 0) _alive = false;
    }

    void heal(int amount) {
        int hp = _health.get() + amount;
        if (hp > _max_health.get()) hp = _max_health.get();
        _health.set(hp);
    }

    void add_score(int v) {
        _score += v;
    }

    void update(float dt) {
        if (_invincible_timer.get() > 0.0f) {
            _invincible_timer -= dt;
        }
        _weapon.update(dt);
    }

    bool is_valid() const {
        return _transform.is_valid() && _health.is_valid() && _max_health.is_valid() &&
               _speed.is_valid() && _direction.is_valid() && _score.is_valid() &&
               _alive.is_valid() && _weapon.is_valid();
    }
};

struct Zombie {
    Transform _transform;
    FLINT _health;
    FLINT _max_health;
    FLFLOAT _speed;
    FLINT _damage;
    FLBOOL _alive;
    Vector2 _target;
    FLFLOAT _attack_cooldown;
    FLFLOAT _attack_timer;
    FLINT _type;
    Color _color;
    Vector2 _size;
    FLFLOAT _stun_timer;

    Zombie() : _health(50), _max_health(50), _speed(2.0f), _damage(10), _alive(true),
               _attack_cooldown(1.0f), _attack_timer(0.0f), _type(0),
               _color(0.8f, 0.0f, 0.0f, 1.0f), _size(0.7f, 0.7f), _stun_timer(0.0f) {}

    Transform get_transform() const { return _transform; }
    void set_transform(const Transform& t) { _transform = t; }
    int get_health() const { return _health.get(); }
    void set_health(int v) { _health.set(v); }
    int get_max_health() const { return _max_health.get(); }
    float get_speed() const { return _speed.get(); }
    void set_speed(float v) { _speed.set(v); }
    int get_damage() const { return _damage.get(); }
    void set_damage(int v) { _damage.set(v); }
    bool get_alive() const { return _alive.get(); }
    void set_alive(bool v) { _alive.set(v); }
    Vector2 get_target() const { return _target; }
    void set_target(const Vector2& t) { _target = t; }
    float get_cooldown() const { return _attack_timer.get(); }
    int get_type() const { return _type.get(); }
    void set_type(int v) { _type.set(v); }
    float get_x() const { return _transform.get_x(); }
    float get_y() const { return _transform.get_y(); }
    void set_x(float v) { _transform.set_x(v); }
    void set_y(float v) { _transform.set_y(v); }

    void take_damage(int dmg) {
        if (!_alive.get()) return;
        int hp = _health.get() - dmg;
        if (hp < 0) hp = 0;
        _health.set(hp);
        _stun_timer = 0.2f;
        if (hp <= 0) _alive = false;
    }

    bool can_attack() const {
        return _attack_timer.get() <= 0.0f && _alive.get();
    }

    void attack() {
        _attack_timer = _attack_cooldown.get();
    }

    void update(float dt) {
        if (_attack_timer.get() > 0.0f) {
            _attack_timer -= dt;
        }
        if (_stun_timer.get() > 0.0f) {
            _stun_timer -= dt;
        }
    }

    void move_toward(const Vector2& dest, float dt, const std::vector<Object>& obstacles) {
        if (!_alive.get()) return;
        if (_stun_timer.get() > 0.0f) return;
        Vector2 pos = _transform.get_position();
        Vector2 dir = (dest - pos).normalized();
        float spd = _speed.get() * dt;
        float nx = pos.get_x() + dir.get_x() * spd;
        float ny = pos.get_y() + dir.get_y() * spd;

        bool blocked = false;
        for (const auto& obs : obstacles) {
            if (!obs.get_active() || !obs.get_collidable()) continue;
            float ox = obs.get_x(), oy = obs.get_y();
            float ow = obs.get_width(), oh = obs.get_height();
            float zw = _size.get_x(), zh = _size.get_y();
            if (nx < ox + ow && nx + zw > ox && ny < oy + oh && ny + zh > oy) {
                blocked = true;
                break;
            }
        }

        if (!blocked) {
            _transform.set_position(nx, ny);
        } else {
            float ax = pos.get_x() + dir.get_x() * spd;
            float ay = pos.get_y();
            blocked = false;
            for (const auto& obs : obstacles) {
                if (!obs.get_active() || !obs.get_collidable()) continue;
                float ox = obs.get_x(), oy = obs.get_y();
                float ow = obs.get_width(), oh = obs.get_height();
                float zw = _size.get_x(), zh = _size.get_y();
                if (ax < ox + ow && ax + zw > ox && ay < oy + oh && ay + zh > oy) {
                    blocked = true;
                    break;
                }
            }
            if (!blocked) {
                _transform.set_x(ax);
            } else {
                float bx = pos.get_x();
                float by = pos.get_y() + dir.get_y() * spd;
                blocked = false;
                for (const auto& obs : obstacles) {
                    if (!obs.get_active() || !obs.get_collidable()) continue;
                    float ox = obs.get_x(), oy = obs.get_y();
                    float ow = obs.get_width(), oh = obs.get_height();
                    float zw = _size.get_x(), zh = _size.get_y();
                    if (bx < ox + ow && bx + zw > ox && by < oy + oh && by + zh > oy) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    _transform.set_y(by);
                }
            }
        }
    }

    bool is_valid() const {
        return _transform.is_valid() && _health.is_valid() && _speed.is_valid() &&
               _damage.is_valid() && _alive.is_valid() && _type.is_valid();
    }
};

struct Projectile {
    Vector2 _position;
    Vector2 _direction;
    FLFLOAT _speed;
    FLINT _damage;
    FLFLOAT _lifetime;
    FLBOOL _active;
    FLFLOAT _range;
    FLFLOAT _traveled;

    Projectile() : _speed(20.0f), _damage(25), _lifetime(2.0f), _active(false), _range(8.0f), _traveled(0.0f) {}

    Vector2 get_position() const { return _position; }
    void set_position(const Vector2& p) { _position = p; }
    Vector2 get_direction() const { return _direction; }
    void set_direction(const Vector2& d) { _direction = d; }
    float get_speed() const { return _speed.get(); }
    int get_damage() const { return _damage.get(); }
    bool get_active() const { return _active.get(); }
    void set_active(bool v) { _active.set(v); }

    void update(float dt) {
        if (!_active.get()) return;
        float spd = _speed.get() * dt;
        float nx = _position.get_x() + _direction.get_x() * spd;
        float ny = _position.get_y() + _direction.get_y() * spd;
        _position.set_x(nx);
        _position.set_y(ny);
        _traveled += spd;
        _lifetime -= dt;
        if (_lifetime.get() <= 0.0f || _traveled.get() >= _range.get()) {
            _active = false;
        }
    }

    bool is_valid() const {
        return _speed.is_valid() && _damage.is_valid() && _active.is_valid();
    }
};

struct ParticleEffect {
    Vector2 _position;
    Color _color;
    FLFLOAT _lifetime;
    FLFLOAT _max_lifetime;
    FLFLOAT _size;
    FLBOOL _active;

    ParticleEffect() : _lifetime(0.0f), _max_lifetime(0.3f), _size(0.2f), _active(false) {}

    void spawn(float x, float y, const Color& c, float life, float sz) {
        _position.set_x(x);
        _position.set_y(y);
        _color = c;
        _lifetime = life;
        _max_lifetime = life;
        _size = sz;
        _active = true;
    }

    void update(float dt) {
        if (!_active.get()) return;
        _lifetime -= dt;
        if (_lifetime.get() <= 0.0f) _active = false;
    }

    float get_alpha() const {
        if (_max_lifetime.get() <= 0.0f) return 0.0f;
        return _lifetime.get() / _max_lifetime.get();
    }

    bool is_valid() const {
        return _lifetime.is_valid() && _size.is_valid() && _active.is_valid();
    }
};

struct MapTile {
    FLINT _type;
    FLBOOL _walkable;
    Vector2 _position;
    Vector2 _size;
    Color _color;

    MapTile() : _type(0), _walkable(true), _size(1.0f, 1.0f) {}

    int get_type() const { return _type.get(); }
    void set_type(int v) {
        _type.set(v);
        switch(v) {
            case 0: _walkable = true; _color = Color(0.4f, 0.4f, 0.4f, 1.0f); break;
            case 1: _walkable = false; _color = Color(0.2f, 0.2f, 0.2f, 1.0f); break;
            case 2: _walkable = true; _color = Color(0.35f, 0.35f, 0.35f, 1.0f); break;
            default: _walkable = true; _color = Color(0.4f, 0.4f, 0.4f, 1.0f); break;
        }
    }
    bool get_walkable() const { return _walkable.get(); }
    void set_walkable(bool v) { _walkable.set(v); }
    Vector2 get_position() const { return _position; }
    void set_position(float x, float y) { _position.set_x(x); _position.set_y(y); }
    Vector2 get_size() const { return _size; }
    void set_size(float w, float h) { _size.set_x(w); _size.set_y(h); }
    Color get_color() const { return _color; }
    void set_color(const Color& c) { _color = c; }

    bool is_valid() const {
        return _type.is_valid() && _walkable.is_valid();
    }
};

struct GameMap {
    static const int MAX_WIDTH = 20;
    static const int MAX_HEIGHT = 15;

    MapTile _tiles[MAX_WIDTH][MAX_HEIGHT];
    FLINT _width;
    FLINT _height;
    std::vector<Vector2> _spawn_points;
    std::vector<Object> _obstacles;
    FLFLOAT _tile_size;

    GameMap() : _width(MAX_WIDTH), _height(MAX_HEIGHT), _tile_size(1.0f) {}

    int get_width() const { return _width.get(); }
    void set_width(int v) { _width.set(v); }
    int get_height() const { return _height.get(); }
    void set_height(int v) { _height.set(v); }
    float get_tile_size() const { return _tile_size.get(); }

    MapTile& get_tile(int x, int y) { return _tiles[x][y]; }
    const MapTile& get_tile_const(int x, int y) const { return _tiles[x][y]; }

    void generate() {
        for (int x = 0; x < MAX_WIDTH; x++) {
            for (int y = 0; y < MAX_HEIGHT; y++) {
                _tiles[x][y].set_position((float)x, (float)y);
                _tiles[x][y].set_size(1.0f, 1.0f);
                if (x == 0 || x == MAX_WIDTH - 1 || y == 0 || y == MAX_HEIGHT - 1) {
                    _tiles[x][y].set_type(1);
                } else {
                    _tiles[x][y].set_type(0);
                }
            }
        }

        _spawn_points.clear();
        for (int x = 1; x < MAX_WIDTH - 1; x++) {
            _spawn_points.push_back(Vector2((float)x, 1.0f));
            _spawn_points.push_back(Vector2((float)x, (float)(MAX_HEIGHT - 2)));
        }
        for (int y = 1; y < MAX_HEIGHT - 1; y++) {
            _spawn_points.push_back(Vector2(1.0f, (float)y));
            _spawn_points.push_back(Vector2((float)(MAX_WIDTH - 2), (float)y));
        }

        _obstacles.clear();

        auto add_box = [&](float bx, float by, float bw, float bh) {
            Object box;
            box._transform.set_position(bx, by);
            box.set_size(bw, bh);
            box._material.set_color(Color::brown());
            box.set_tag(1);
            box.set_collidable(true);
            box.start();
            _obstacles.push_back(box);
        };

        add_box(4.0f, 4.0f, 2.0f, 1.0f);
        add_box(4.0f, 5.0f, 1.0f, 2.0f);
        add_box(14.0f, 4.0f, 2.0f, 1.0f);
        add_box(15.0f, 5.0f, 1.0f, 2.0f);
        add_box(4.0f, 10.0f, 2.0f, 1.0f);
        add_box(4.0f, 8.0f, 1.0f, 2.0f);
        add_box(14.0f, 10.0f, 2.0f, 1.0f);
        add_box(15.0f, 8.0f, 1.0f, 2.0f);
        add_box(9.0f, 3.0f, 2.0f, 1.0f);
        add_box(9.0f, 11.0f, 2.0f, 1.0f);
        add_box(9.0f, 7.0f, 1.0f, 1.0f);
        add_box(10.0f, 7.0f, 1.0f, 1.0f);
        add_box(7.0f, 5.0f, 1.0f, 1.0f);
        add_box(12.0f, 9.0f, 1.0f, 1.0f);
        add_box(3.0f, 7.0f, 1.0f, 1.0f);
        add_box(16.0f, 7.0f, 1.0f, 1.0f);
    }

    bool is_walkable(float px, float py, float pw, float ph) const {
        int x0 = (int)px;
        int y0 = (int)py;
        int x1 = (int)(px + pw);
        int y1 = (int)(py + ph);
        if (x0 < 0 || y0 < 0 || x1 >= MAX_WIDTH || y1 >= MAX_HEIGHT) return false;
        for (int x = x0; x <= x1; x++) {
            for (int y = y0; y <= y1; y++) {
                if (!_tiles[x][y].get_walkable()) return false;
            }
        }
        for (const auto& obs : _obstacles) {
            if (!obs.get_active() || !obs.get_collidable()) continue;
            float ox = obs.get_x(), oy = obs.get_y();
            float ow = obs.get_width(), oh = obs.get_height();
            if (px < ox + ow && px + pw > ox && py < oy + oh && py + ph > oy) {
                return false;
            }
        }
        return true;
    }

    Vector2 get_random_spawn() const {
        if (_spawn_points.empty()) return Vector2(1.0f, 1.0f);
        int idx = rand() % _spawn_points.size();
        return _spawn_points[idx];
    }

    bool is_valid() const {
        return _width.is_valid() && _height.is_valid();
    }
};

struct Camera {
    Vector2 _position;
    FLFLOAT _zoom;
    FLFLOAT _screen_width;
    FLFLOAT _screen_height;

    Camera() : _zoom(1.0f), _screen_width(20.0f), _screen_height(15.0f) {}

    Vector2 get_position() const { return _position; }
    void set_position(const Vector2& p) { _position = p; }
    void set_position(float x, float y) { _position.set_x(x); _position.set_y(y); }
    float get_zoom() const { return _zoom.get(); }
    void set_zoom(float v) { _zoom.set(v); }
    float get_screen_width() const { return _screen_width.get(); }
    void set_screen_width(float v) { _screen_width.set(v); }
    float get_screen_height() const { return _screen_height.get(); }
    void set_screen_height(float v) { _screen_height.set(v); }

    void follow(const Vector2& target, float dt) {
        float cx = _position.get_x();
        float cy = _position.get_y();
        float tx = target.get_x() - _screen_width.get() * 0.5f;
        float ty = target.get_y() - _screen_height.get() * 0.5f;
        float lerp = 5.0f * dt;
        if (lerp > 1.0f) lerp = 1.0f;
        _position.set_x(cx + (tx - cx) * lerp);
        _position.set_y(cy + (ty - cy) * lerp);
    }

    void get_ortho_matrix(float* mat) const {
        float l = _position.get_x();
        float r = l + _screen_width.get() / _zoom.get();
        float b = _position.get_y();
        float t = b + _screen_height.get() / _zoom.get();
        float n = -1.0f;
        float f = 1.0f;
        memset(mat, 0, 16 * sizeof(float));
        mat[0] = 2.0f / (r - l);
        mat[5] = 2.0f / (t - b);
        mat[10] = -2.0f / (f - n);
        mat[12] = -(r + l) / (r - l);
        mat[13] = -(t + b) / (t - b);
        mat[14] = -(f + n) / (f - n);
        mat[15] = 1.0f;
    }

    bool is_valid() const {
        return _zoom.is_valid() && _screen_width.is_valid() && _screen_height.is_valid();
    }
};

struct WaveManager {
    FLINT _current_wave;
    FLINT _zombies_per_wave;
    FLINT _zombies_spawned;
    FLINT _zombies_alive;
    FLFLOAT _spawn_interval;
    FLFLOAT _spawn_timer;
    FLFLOAT _wave_delay;
    FLFLOAT _wave_timer;
    FLBOOL _wave_active;
    FLBOOL _waiting;

    WaveManager() : _current_wave(0), _zombies_per_wave(5), _zombies_spawned(0),
                    _zombies_alive(0), _spawn_interval(1.5f), _spawn_timer(0.0f),
                    _wave_delay(3.0f), _wave_timer(0.0f), _wave_active(false), _waiting(true) {}

    int get_wave() const { return _current_wave.get(); }
    void set_wave(int v) { _current_wave.set(v); }
    int get_zombies_alive() const { return _zombies_alive.get(); }
    void set_zombies_alive(int v) { _zombies_alive.set(v); }
    bool get_wave_active() const { return _wave_active.get(); }

    void next_wave() {
        _current_wave += 1;
        _zombies_per_wave = 5 + _current_wave.get() * 3;
        _zombies_spawned = 0;
        _zombies_alive = _zombies_per_wave.get();
        _spawn_timer = 0.0f;
        _wave_active = true;
        _waiting = false;
        float interval = 1.5f - (float)_current_wave.get() * 0.1f;
        if (interval < 0.3f) interval = 0.3f;
        _spawn_interval = interval;
    }

    bool should_spawn(float dt) {
        if (!_wave_active.get()) return false;
        if (_zombies_spawned.get() >= _zombies_per_wave.get()) return false;
        _spawn_timer -= dt;
        if (_spawn_timer.get() <= 0.0f) {
            _spawn_timer = _spawn_interval.get();
            _zombies_spawned += 1;
            return true;
        }
        return false;
    }

    void zombie_killed() {
        _zombies_alive -= 1;
        if (_zombies_alive.get() <= 0 && _zombies_spawned.get() >= _zombies_per_wave.get()) {
            _wave_active = false;
            _waiting = true;
            _wave_timer = _wave_delay.get();
        }
    }

    void update(float dt) {
        if (_waiting.get()) {
            _wave_timer -= dt;
            if (_wave_timer.get() <= 0.0f) {
                next_wave();
            }
        }
    }

    bool is_valid() const {
        return _current_wave.is_valid() && _zombies_per_wave.is_valid() &&
               _zombies_alive.is_valid() && _wave_active.is_valid();
    }
};

struct InputState {
    FLFLOAT _move_x;
    FLFLOAT _move_y;
    FLFLOAT _aim_x;
    FLFLOAT _aim_y;
    FLBOOL _shooting;
    FLBOOL _touch_move;
    FLBOOL _touch_aim;
    FLFLOAT _touch_move_start_x;
    FLFLOAT _touch_move_start_y;
    FLFLOAT _touch_aim_start_x;
    FLFLOAT _touch_aim_start_y;
    FLINT _move_pointer_id;
    FLINT _aim_pointer_id;

    InputState() : _move_x(0.0f), _move_y(0.0f), _aim_x(0.0f), _aim_y(0.0f),
                   _shooting(false), _touch_move(false), _touch_aim(false),
                   _touch_move_start_x(0.0f), _touch_move_start_y(0.0f),
                   _touch_aim_start_x(0.0f), _touch_aim_start_y(0.0f),
                   _move_pointer_id(-1), _aim_pointer_id(-1) {}

    float get_move_x() const { return _move_x.get(); }
    float get_move_y() const { return _move_y.get(); }
    float get_aim_x() const { return _aim_x.get(); }
    float get_aim_y() const { return _aim_y.get(); }
    bool get_shooting() const { return _shooting.get(); }

    void reset() {
        _move_x = 0.0f;
        _move_y = 0.0f;
        _aim_x = 0.0f;
        _aim_y = 0.0f;
        _shooting = false;
        _touch_move = false;
        _touch_aim = false;
        _move_pointer_id = -1;
        _aim_pointer_id = -1;
    }

    bool is_valid() const {
        return _move_x.is_valid() && _move_y.is_valid() && _shooting.is_valid();
    }
};

struct CollisionResult {
    FLBOOL _hit;
    Vector2 _point;
    Vector2 _normal;
    FLFLOAT _distance;

    CollisionResult() : _hit(false), _distance(0.0f) {}

    bool get_hit() const { return _hit.get(); }
    Vector2 get_point() const { return _point; }
    Vector2 get_normal() const { return _normal; }
    float get_distance() const { return _distance.get(); }
};

struct RenderBatch {
    GLuint _vao;
    GLuint _vbo;
    FLINT _vertex_count;
    FLINT _max_vertices;
    float* _vertices;
    FLBOOL _initialized;

    RenderBatch() : _vao(0), _vbo(0), _vertex_count(0), _max_vertices(4096), _vertices(nullptr), _initialized(false) {}

    void init() {
        _vertices = (float*)malloc(_max_vertices.get() * 6 * sizeof(float));
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _max_vertices.get() * 6 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
        _initialized = true;
    }

    void begin() {
        _vertex_count = 0;
    }

    void add_quad(float x, float y, float w, float h, float r, float g, float b, float a) {
        int vc = _vertex_count.get();
        if (vc + 6 > _max_vertices.get()) return;
        int base = vc * 6;
        float verts[] = {
            x, y, r, g, b, a,
            x + w, y, r, g, b, a,
            x, y + h, r, g, b, a,
            x + w, y, r, g, b, a,
            x + w, y + h, r, g, b, a,
            x, y + h, r, g, b, a
        };
        memcpy(_vertices + base, verts, sizeof(verts));
        _vertex_count += 6;
    }

    void end() {
        if (_vertex_count.get() == 0) return;
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, _vertex_count.get() * 6 * sizeof(float), _vertices);
        glDrawArrays(GL_TRIANGLES, 0, _vertex_count.get());
        glBindVertexArray(0);
    }

    void destroy() {
        if (_vertices) { free(_vertices); _vertices = nullptr; }
        if (_vao) { glDeleteVertexArrays(1, &_vao); _vao = 0; }
        if (_vbo) { glDeleteBuffers(1, &_vbo); _vbo = 0; }
        _initialized = false;
    }

    bool is_valid() const {
        return _vertex_count.is_valid() && _initialized.is_valid();
    }
};

static bool _fl_validate_all_types(const Player& p, const std::vector<Zombie>& zombies,
                                    const GameMap& gmap, const WaveManager& wm) {
    if (!p.is_valid()) return false;
    if (!p._weapon.is_valid()) return false;
    if (!gmap.is_valid()) return false;
    if (!wm.is_valid()) return false;
    for (const auto& z : zombies) {
        if (!z.is_valid()) return false;
    }
    for (const auto& obs : gmap._obstacles) {
        if (!obs.is_valid()) return false;
    }
    return true;
}
