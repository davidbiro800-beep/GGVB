#include "struct.h"
#include <EGL/egl.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <cstdio>
#include <cerrno>

FLINT Object::_next_id = FLINT(1);

static const char* _vert_src =
    "#version 300 es\n"
    "layout(location = 0) in vec2 aPos;\n"
    "layout(location = 1) in vec4 aColor;\n"
    "uniform mat4 uProj;\n"
    "out vec4 vColor;\n"
    "void main() {\n"
    "    gl_Position = uProj * vec4(aPos, 0.0, 1.0);\n"
    "    vColor = aColor;\n"
    "}\n";

static const char* _frag_src =
    "#version 300 es\n"
    "precision mediump float;\n"
    "in vec4 vColor;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vColor;\n"
    "}\n";

static const uint8_t _embedded_meta[] = {
    0xA3, 0x7F, 0xE2, 0x91, 0xB4, 0xD8, 0x6C, 0x1A, 0xF5, 0x3E,
    0x82, 0xC7, 0x59, 0x0D, 0xA1, 0x6E, 0xBB, 0x44, 0xF8, 0x23,
    0x97, 0xDA, 0x5F, 0x10, 0xCC, 0x8A, 0x41, 0xE6, 0x7D, 0x2B,
    0xAF, 0x64, 0x18, 0xFC, 0x93, 0x57, 0x0A, 0xDE, 0x75, 0x39,
    0xB0, 0x4C, 0xE1, 0x88, 0x2F, 0xC5, 0x6A, 0x16, 0xFD, 0x90,
    0x53, 0x07, 0xDB, 0x72, 0x36, 0xAD, 0x49, 0xEE, 0x85, 0x2C,
    0xC2, 0x67, 0x13, 0xFA, 0x9E, 0x50, 0x04, 0xD9, 0x7A, 0x33,
    0xAA, 0x46, 0xEB, 0x83, 0x29, 0xBF, 0x65, 0x11, 0xF7, 0x9B,
    0x4E, 0x02, 0xD6, 0x77, 0x31, 0xA8, 0x4D, 0xE8, 0x80, 0x26,
    0xBC, 0x62, 0x0F, 0xF4, 0x98, 0x4B, 0xFF, 0xD3, 0x74, 0x38,
    0xA5, 0x4A, 0xE5, 0x8E, 0x24, 0xBA, 0x60, 0x0C, 0xF1, 0x96,
    0x48, 0xFE, 0xD1, 0x71, 0x35, 0xA2, 0x47, 0xE3, 0x8B, 0x21,
    0xB7, 0x5E, 0x09, 0xEF, 0x94, 0x45, 0xFB, 0xCE, 0x6F, 0x32,
    0xA0, 0x43, 0xDF, 0x89, 0x1F, 0xB5, 0x5B, 0x06, 0xEC, 0x91,
    0x42, 0xF9, 0xCB, 0x6D, 0x30, 0x9D, 0x40, 0xDC, 0x86, 0x1C,
    0xB2, 0x58, 0x03, 0xEA, 0x8F, 0x3F, 0xF6, 0xC8, 0x6B, 0x2E,
    0x9A, 0x3D, 0xDA, 0x84, 0x19, 0xB0, 0x55, 0x01, 0xE7, 0x8C,
    0x3C, 0xF3, 0xC6, 0x68, 0x2D, 0x98, 0x3A, 0xD7, 0x81, 0x17,
    0xAE, 0x52, 0xFE, 0xE4, 0x8A, 0x3A, 0xF0, 0xC3, 0x66, 0x2A,
    0x95, 0x37, 0xD5, 0x7F, 0x14, 0xAB, 0x50, 0xFC, 0xE2, 0x87,
    0x37, 0xED, 0xC1, 0x63, 0x28, 0x92, 0x34, 0xD2, 0x7C, 0x12,
    0xA9, 0x4E, 0xF9, 0xDF, 0x85, 0x34, 0xEB, 0xBE, 0x61, 0x25,
    0x8F, 0x31, 0xD0, 0x7A, 0x0F, 0xA6, 0x4B, 0xF7, 0xDD, 0x82,
    0x32, 0xE8, 0xBC, 0x5E, 0x22, 0x8D, 0x2F, 0xCD, 0x77, 0x0D,
    0xA4, 0x49, 0xF4, 0xDA, 0x80, 0x2F, 0xE6, 0xB9, 0x5C, 0x20,
    0x8B, 0x2C, 0xCB, 0x75, 0x0A, 0xA1
};

struct Game {
    static Game* _instance;

    Player _player;
    std::vector<Zombie> _zombies;
    std::vector<Projectile> _projectiles;
    std::vector<ParticleEffect> _particles;
    GameMap _map;
    Camera _camera;
    WaveManager _wave_mgr;
    InputState _input;
    Shader _shader;
    RenderBatch _batch;
    MemoryGuard _guard;
    EncryptedMeta _meta;

    FLBOOL _initialized;
    FLBOOL _cheat_detected;
    FLBOOL _game_over;
    FLBOOL _paused;
    FLFLOAT _delta_time;
    FLFLOAT _last_time;
    FLINT _screen_w;
    FLINT _screen_h;
    FLFLOAT _game_time;

    JavaVM* _jvm;
    jobject _activity;

    Game() : _initialized(false), _cheat_detected(false), _game_over(false),
             _paused(false), _delta_time(0.016f), _last_time(0.0f),
             _screen_w(1080), _screen_h(1920), _game_time(0.0f),
             _jvm(nullptr), _activity(nullptr) {}

    static Game* get_instance() {
        if (!_instance) {
            _instance = new Game();
        }
        return _instance;
    }

    GLuint compile_shader_fn(GLenum type, const char* src) {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        GLint ok;
        glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char log[512];
            glGetShaderInfoLog(s, 512, nullptr, log);
            __android_log_print(ANDROID_LOG_ERROR, "FL", "%s", log);
        }
        return s;
    }

    GLuint link_program_fn(GLuint vs, GLuint fs) {
        GLuint p = glCreateProgram();
        glAttachShader(p, vs);
        glAttachShader(p, fs);
        glLinkProgram(p);
        GLint ok;
        glGetProgramiv(p, GL_LINK_STATUS, &ok);
        if (!ok) {
            char log[512];
            glGetProgramInfoLog(p, 512, nullptr, log);
            __android_log_print(ANDROID_LOG_ERROR, "FL", "%s", log);
        }
        return p;
    }

    void decrypt_meta_fn() {
        uint8_t decrypted[256];
        size_t meta_len = sizeof(_embedded_meta);
        if (meta_len > 256) meta_len = 256;
        for (size_t i = 0; i < meta_len; i++) {
            decrypted[i] = _embedded_meta[i] ^ (0xA7 + (uint8_t)(i * 37));
        }
        _meta.store(decrypted, meta_len);
    }

    void init_game() {
        srand((unsigned int)time(nullptr));

        GLuint vs = compile_shader_fn(GL_VERTEX_SHADER, _vert_src);
        GLuint fs = compile_shader_fn(GL_FRAGMENT_SHADER, _frag_src);
        GLuint prog = link_program_fn(vs, fs);
        _shader.set_program(prog);
        _shader.set_vertex_shader(vs);
        _shader.set_fragment_shader(fs);
        _shader.set_uniform_proj(glGetUniformLocation(prog, "uProj"));
        _shader.set_compiled(true);

        glDeleteShader(vs);
        glDeleteShader(fs);

        _batch.init();

        _map.generate();

        _player._transform.set_position(10.0f, 7.0f);
        _player._health = 100;
        _player._max_health = 100;
        _player._speed = 5.0f;
        _player._alive = true;
        _player._score = 0;
        _player._weapon._damage = 25;
        _player._weapon._ammo = 8;
        _player._weapon._max_ammo = 8;
        _player._weapon._fire_rate = 0.5f;
        _player._weapon._range = 8.0f;
        _player._weapon._reload_time = 2.0f;
        _player._weapon._spread = 0.3f;
        _player._weapon._pellets = 5;

        _camera.set_screen_width(20.0f);
        _camera.set_screen_height(15.0f);

        _projectiles.resize(64);
        _particles.resize(128);

        decrypt_meta_fn();

        _guard.register_region(&_player, sizeof(Player));
        _guard.register_region(&_wave_mgr, sizeof(WaveManager));
        _guard.start();

        _wave_mgr._wave_timer = 2.0f;
        _wave_mgr._waiting = true;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        _initialized = true;
    }

    void spawn_zombie() {
        Vector2 sp = _map.get_random_spawn();
        float px = _player.get_x();
        float py = _player.get_y();
        float dist = sp.distance(Vector2(px, py));
        if (dist < 3.0f) {
            sp = Vector2(1.0f, 1.0f);
        }

        Zombie z;
        z._transform.set_position(sp.get_x(), sp.get_y());

        int wave = _wave_mgr.get_wave();
        int type_roll = rand() % 100;
        if (wave > 3 && type_roll < 20) {
            z.set_type(2);
            z._health = 150;
            z._max_health = 150;
            z._speed = 1.5f;
            z._damage = 20;
            z._color = Color(0.5f, 0.0f, 0.0f, 1.0f);
            z._size = Vector2(1.0f, 1.0f);
        } else if (wave > 1 && type_roll < 40) {
            z.set_type(1);
            z._health = 30;
            z._max_health = 30;
            z._speed = 4.0f;
            z._damage = 5;
            z._color = Color(1.0f, 0.3f, 0.0f, 1.0f);
            z._size = Vector2(0.5f, 0.5f);
        } else {
            z.set_type(0);
            z._health = 50 + wave * 5;
            z._max_health = 50 + wave * 5;
            z._speed = 2.0f + (float)wave * 0.15f;
            z._damage = 10;
            z._color = Color(0.8f, 0.0f, 0.0f, 1.0f);
            z._size = Vector2(0.7f, 0.7f);
        }

        z._alive = true;
        _zombies.push_back(z);
    }

    void fire_weapon() {
        if (!_player._weapon.can_fire()) return;
        _player._weapon.fire();

        float px = _player.get_x() + _player._size.get_x() * 0.5f;
        float py = _player.get_y() + _player._size.get_y() * 0.5f;
        float aim_x = _player._shoot_dir_x.get();
        float aim_y = _player._shoot_dir_y.get();
        float aim_len = sqrtf(aim_x * aim_x + aim_y * aim_y);
        if (aim_len < 0.001f) { aim_x = 1.0f; aim_y = 0.0f; }
        else { aim_x /= aim_len; aim_y /= aim_len; }

        int pellets = _player._weapon.get_pellets();
        float spread = _player._weapon.get_spread();

        for (int i = 0; i < pellets; i++) {
            float angle = atan2f(aim_y, aim_x);
            float offset = ((float)(rand() % 1000) / 1000.0f - 0.5f) * 2.0f * spread;
            angle += offset;
            float dx = cosf(angle);
            float dy = sinf(angle);

            for (auto& proj : _projectiles) {
                if (!proj.get_active()) {
                    proj._position = Vector2(px, py);
                    proj._direction = Vector2(dx, dy);
                    proj._speed = 20.0f;
                    proj._damage = _player._weapon.get_damage();
                    proj._range = _player._weapon.get_range();
                    proj._traveled = 0.0f;
                    proj._lifetime = 2.0f;
                    proj._active = true;
                    break;
                }
            }
        }

        for (auto& part : _particles) {
            if (!part._active.get()) {
                part.spawn(px + aim_x * 0.5f, py + aim_y * 0.5f,
                          Color::yellow(), 0.15f, 0.4f);
                break;
            }
        }

        if (_player._weapon.get_ammo() <= 0) {
            _player._weapon.start_reload();
        }
    }

    void move_player(float dt) {
        if (!_player.get_alive()) return;
        float mx = _input.get_move_x();
        float my = _input.get_move_y();
        float len = sqrtf(mx * mx + my * my);
        if (len < 0.1f) return;
        mx /= len;
        my /= len;
        float spd = _player.get_speed() * dt;
        float nx = _player.get_x() + mx * spd;
        float ny = _player.get_y() + my * spd;
        float pw = _player._size.get_x();
        float ph = _player._size.get_y();

        if (_map.is_walkable(nx, _player.get_y(), pw, ph)) {
            _player.set_x(nx);
        }
        if (_map.is_walkable(_player.get_x(), ny, pw, ph)) {
            _player.set_y(ny);
        }
    }

    void check_collision() {
        float px = _player.get_x();
        float py = _player.get_y();
        float pw = _player._size.get_x();
        float ph = _player._size.get_y();

        for (auto& z : _zombies) {
            if (!z.get_alive()) continue;
            float zx = z.get_x();
            float zy = z.get_y();
            float zw = z._size.get_x();
            float zh = z._size.get_y();

            if (px < zx + zw && px + pw > zx && py < zy + zh && py + ph > zy) {
                if (z.can_attack()) {
                    _player.take_damage(z.get_damage());
                    z.attack();
                    for (auto& part : _particles) {
                        if (!part._active.get()) {
                            part.spawn(px + pw * 0.5f, py + ph * 0.5f,
                                      Color::red(), 0.3f, 0.3f);
                            break;
                        }
                    }
                }
            }
        }

        for (auto& proj : _projectiles) {
            if (!proj.get_active()) continue;
            float prx = proj._position.get_x();
            float pry = proj._position.get_y();

            for (auto& z : _zombies) {
                if (!z.get_alive()) continue;
                float zx = z.get_x();
                float zy = z.get_y();
                float zw = z._size.get_x();
                float zh = z._size.get_y();
                if (prx >= zx && prx <= zx + zw && pry >= zy && pry <= zy + zh) {
                    z.take_damage(proj.get_damage());
                    proj._active = false;
                    for (auto& part : _particles) {
                        if (!part._active.get()) {
                            part.spawn(prx, pry, Color(1.0f, 0.5f, 0.0f, 1.0f), 0.2f, 0.2f);
                            break;
                        }
                    }
                    if (!z.get_alive()) {
                        _player.add_score(10 * (z.get_type() + 1));
                        _wave_mgr.zombie_killed();
                        for (int p = 0; p < 3; p++) {
                            for (auto& part : _particles) {
                                if (!part._active.get()) {
                                    float ox = ((float)(rand() % 100) / 100.0f - 0.5f) * 0.5f;
                                    float oy = ((float)(rand() % 100) / 100.0f - 0.5f) * 0.5f;
                                    part.spawn(zx + zw * 0.5f + ox, zy + zh * 0.5f + oy,
                                              Color::dark_red(), 0.4f, 0.15f);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
            }

            for (const auto& obs : _map._obstacles) {
                if (!obs.get_active()) continue;
                float ox = obs.get_x(), oy = obs.get_y();
                float ow = obs.get_width(), oh = obs.get_height();
                if (prx >= ox && prx <= ox + ow && pry >= oy && pry <= oy + oh) {
                    proj._active = false;
                    break;
                }
            }
        }
    }

    bool memory_check_fn() {
        if (!_fl_validate_all_types(_player, _zombies, _map, _wave_mgr)) {
            _cheat_detected = true;
            return false;
        }
        if (_guard.is_tampered()) {
            _cheat_detected = true;
            return false;
        }
        return true;
    }

    void notify_cheat_detected() {
        if (!_jvm || !_activity) return;
        JNIEnv* env = nullptr;
        bool attached = false;
        int status = _jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
        if (status == JNI_EDETACHED) {
            _jvm->AttachCurrentThread(&env, nullptr);
            attached = true;
        }
        if (env) {
            jclass cls = env->GetObjectClass(_activity);
            jmethodID mid = env->GetMethodID(cls, "onCheatDetected", "()V");
            if (mid) {
                env->CallVoidMethod(_activity, mid);
            }
            env->DeleteLocalRef(cls);
        }
        if (attached) {
            _jvm->DetachCurrentThread();
        }
    }

    void update_game(float dt) {
        if (_game_over.get() || _paused.get()) return;
        if (_cheat_detected.get()) {
            notify_cheat_detected();
            return;
        }

        _game_time += dt;
        _player.update(dt);

        move_player(dt);

        if (_input.get_shooting() && _player.get_alive()) {
            float ax = _input.get_aim_x();
            float ay = _input.get_aim_y();
            float al = sqrtf(ax * ax + ay * ay);
            if (al > 0.1f) {
                _player._shoot_dir_x = ax / al;
                _player._shoot_dir_y = ay / al;
            }
            fire_weapon();
        }

        _wave_mgr.update(dt);
        if (_wave_mgr.should_spawn(dt)) {
            spawn_zombie();
        }

        Vector2 player_pos = _player._transform.get_position();
        for (auto& z : _zombies) {
            if (!z.get_alive()) continue;
            z.update(dt);
            z.set_target(player_pos);
            z.move_toward(player_pos, dt, _map._obstacles);
        }

        for (auto& proj : _projectiles) {
            proj.update(dt);
        }

        for (auto& part : _particles) {
            part.update(dt);
        }

        check_collision();

        _camera.follow(player_pos, dt);

        if (!_player.get_alive()) {
            _game_over = true;
        }

        _guard.update_region(&_player);
        _guard.update_region(&_wave_mgr);

        if ((int)(_game_time.get() * 10) % 50 == 0) {
            memory_check_fn();
        }
    }

    void render_quad(float x, float y, float w, float h, const Color& c) {
        _batch.add_quad(x, y, w, h, c.get_r(), c.get_g(), c.get_b(), c.get_a());
    }

    void render_game() {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(_shader.get_program());

        float proj[16];
        _camera.get_ortho_matrix(proj);
        glUniformMatrix4fv(_shader.get_uniform_proj(), 1, GL_FALSE, proj);

        _batch.begin();

        for (int x = 0; x < _map.get_width(); x++) {
            for (int y = 0; y < _map.get_height(); y++) {
                const MapTile& tile = _map.get_tile_const(x, y);
                Color tc = tile.get_color();
                render_quad((float)x, (float)y, 1.0f, 1.0f, tc);
            }
        }

        for (const auto& obs : _map._obstacles) {
            if (!obs.get_active() || !obs.get_visible()) continue;
            Color oc = obs._material.get_color();
            render_quad(obs.get_x(), obs.get_y(), obs.get_width(), obs.get_height(), oc);
        }

        for (const auto& z : _zombies) {
            if (!z.get_alive()) continue;
            float zx = z.get_x(), zy = z.get_y();
            float zw = z._size.get_x(), zh = z._size.get_y();
            render_quad(zx, zy, zw, zh, z._color);
            float hp_ratio = (float)z.get_health() / (float)z.get_max_health();
            render_quad(zx, zy + zh + 0.05f, zw * hp_ratio, 0.08f, Color::red());
            render_quad(zx + zw * hp_ratio, zy + zh + 0.05f, zw * (1.0f - hp_ratio), 0.08f, Color::dark_gray());
        }

        for (const auto& proj : _projectiles) {
            if (!proj.get_active()) continue;
            float prx = proj._position.get_x();
            float pry = proj._position.get_y();
            render_quad(prx - 0.05f, pry - 0.05f, 0.1f, 0.1f, Color::yellow());
        }

        for (const auto& part : _particles) {
            if (!part._active.get()) continue;
            float alpha = part.get_alpha();
            float sz = part._size.get();
            Color pc = part._color;
            Color fade(pc.get_r(), pc.get_g(), pc.get_b(), alpha);
            render_quad(part._position.get_x() - sz * 0.5f,
                       part._position.get_y() - sz * 0.5f, sz, sz, fade);
        }

        if (_player.get_alive()) {
            Color pc = _player._color;
            if (_player._invincible_timer.get() > 0.0f) {
                int blink = (int)(_game_time.get() * 20.0f) % 2;
                if (blink) pc = Color(1.0f, 1.0f, 1.0f, 0.7f);
            }
            render_quad(_player.get_x(), _player.get_y(),
                       _player._size.get_x(), _player._size.get_y(), pc);

            float aim_x = _player._shoot_dir_x.get();
            float aim_y = _player._shoot_dir_y.get();
            float cpx = _player.get_x() + _player._size.get_x() * 0.5f;
            float cpy = _player.get_y() + _player._size.get_y() * 0.5f;
            render_quad(cpx + aim_x * 0.5f - 0.08f, cpy + aim_y * 0.5f - 0.08f,
                       0.16f, 0.16f, Color(0.3f, 0.3f, 0.3f, 1.0f));
        }

        _batch.end();

        _batch.begin();

        float ui_left = _camera._position.get_x() + 0.3f;
        float ui_top = _camera._position.get_y() + _camera.get_screen_height() - 0.8f;

        float hp_ratio = (float)_player.get_health() / (float)_player.get_max_health();
        render_quad(ui_left, ui_top, 4.0f * hp_ratio, 0.3f, Color::green());
        render_quad(ui_left + 4.0f * hp_ratio, ui_top, 4.0f * (1.0f - hp_ratio), 0.3f, Color::dark_red());
        render_quad(ui_left - 0.02f, ui_top - 0.02f, 4.04f, 0.34f, Color(1.0f, 1.0f, 1.0f, 0.3f));

        float ammo_y = ui_top - 0.5f;
        int ammo = _player._weapon.get_ammo();
        int max_ammo = _player._weapon.get_max_ammo();
        for (int i = 0; i < max_ammo; i++) {
            Color ac = (i < ammo) ? Color::yellow() : Color::dark_gray();
            render_quad(ui_left + (float)i * 0.35f, ammo_y, 0.25f, 0.2f, ac);
        }

        if (_player._weapon.get_reloading()) {
            float reload_ratio = 1.0f - (_player._weapon._reload_timer.get() / _player._weapon.get_reload_time());
            render_quad(ui_left, ammo_y - 0.3f, 3.0f * reload_ratio, 0.15f, Color(0.0f, 0.7f, 1.0f, 1.0f));
        }

        float wave_x = _camera._position.get_x() + _camera.get_screen_width() - 2.5f;
        float wave_y = ui_top;
        int wave_num = _wave_mgr.get_wave();
        for (int i = 0; i < wave_num && i < 10; i++) {
            render_quad(wave_x + (float)i * 0.2f, wave_y, 0.15f, 0.3f, Color(1.0f, 0.8f, 0.0f, 1.0f));
        }

        int score = _player.get_score();
        int digits = score;
        float score_x = wave_x;
        float score_y = wave_y - 0.5f;
        if (digits == 0) {
            render_quad(score_x, score_y, 0.2f, 0.3f, Color::white());
        } else {
            int d_count = 0;
            int tmp = digits;
            while (tmp > 0) { d_count++; tmp /= 10; }
            for (int i = d_count - 1; i >= 0; i--) {
                int d = digits % 10;
                digits /= 10;
                float bar_h = 0.03f * (float)(d + 1);
                render_quad(score_x + (float)i * 0.22f, score_y, 0.18f, bar_h, Color::white());
            }
        }

        if (_input.get_shooting() || _input._touch_move.get()) {
            float sw2 = (float)_screen_w.get() * 0.5f;
            float screen_to_world_x = _camera.get_screen_width() / (float)_screen_w.get();
            float screen_to_world_y = _camera.get_screen_height() / (float)_screen_h.get();

            if (_input._touch_move.get()) {
                float jx = _camera._position.get_x() + _input._touch_move_start_x.get() * screen_to_world_x;
                float jy = _camera._position.get_y() + (_camera.get_screen_height() - _input._touch_move_start_y.get() * screen_to_world_y);
                render_quad(jx - 0.4f, jy - 0.4f, 0.8f, 0.8f, Color(1.0f, 1.0f, 1.0f, 0.15f));
                float dx = _input.get_move_x();
                float dy = _input.get_move_y();
                render_quad(jx + dx * 0.3f - 0.2f, jy - dy * 0.3f - 0.2f, 0.4f, 0.4f, Color(1.0f, 1.0f, 1.0f, 0.3f));
            }
        }

        if (_game_over.get()) {
            float cx = _camera._position.get_x() + _camera.get_screen_width() * 0.5f;
            float cy = _camera._position.get_y() + _camera.get_screen_height() * 0.5f;
            render_quad(cx - 4.0f, cy - 1.5f, 8.0f, 3.0f, Color(0.0f, 0.0f, 0.0f, 0.8f));
            render_quad(cx - 3.0f, cy - 0.5f, 6.0f, 1.0f, Color::dark_red());
            render_quad(cx - 2.5f, cy - 0.3f, 5.0f, 0.6f, Color::red());
        }

        if (_cheat_detected.get()) {
            float cx = _camera._position.get_x() + _camera.get_screen_width() * 0.5f;
            float cy = _camera._position.get_y() + _camera.get_screen_height() * 0.5f;
            render_quad(cx - 5.0f, cy - 2.0f, 10.0f, 4.0f, Color(0.0f, 0.0f, 0.0f, 0.9f));
            render_quad(cx - 4.0f, cy - 0.5f, 8.0f, 1.0f, Color::red());
            render_quad(cx - 3.5f, cy + 0.8f, 7.0f, 0.5f, Color::yellow());
        }

        _batch.end();
    }

    void process_input(int action, int pointer_id, float x, float y) {
        float half_w = (float)_screen_w.get() * 0.5f;

        if (action == 0) {
            if (x < half_w) {
                _input._touch_move = true;
                _input._move_pointer_id = pointer_id;
                _input._touch_move_start_x = x;
                _input._touch_move_start_y = y;
            } else {
                _input._touch_aim = true;
                _input._aim_pointer_id = pointer_id;
                _input._touch_aim_start_x = x;
                _input._touch_aim_start_y = y;
                _input._shooting = true;
            }
        } else if (action == 2) {
            if (pointer_id == _input._move_pointer_id.get() && _input._touch_move.get()) {
                float dx = x - _input._touch_move_start_x.get();
                float dy = y - _input._touch_move_start_y.get();
                float len = sqrtf(dx * dx + dy * dy);
                float max_dist = (float)_screen_w.get() * 0.08f;
                if (len > max_dist) {
                    dx = dx / len * max_dist;
                    dy = dy / len * max_dist;
                    len = max_dist;
                }
                if (len > 5.0f) {
                    _input._move_x = dx / max_dist;
                    _input._move_y = -dy / max_dist;
                } else {
                    _input._move_x = 0.0f;
                    _input._move_y = 0.0f;
                }
            }
            if (pointer_id == _input._aim_pointer_id.get() && _input._touch_aim.get()) {
                float dx = x - _input._touch_aim_start_x.get();
                float dy = y - _input._touch_aim_start_y.get();
                float len = sqrtf(dx * dx + dy * dy);
                if (len > 5.0f) {
                    _input._aim_x = dx / len;
                    _input._aim_y = -dy / len;
                    _input._shooting = true;
                }
            }
        } else if (action == 1) {
            if (pointer_id == _input._move_pointer_id.get()) {
                _input._touch_move = false;
                _input._move_pointer_id = -1;
                _input._move_x = 0.0f;
                _input._move_y = 0.0f;
            }
            if (pointer_id == _input._aim_pointer_id.get()) {
                _input._touch_aim = false;
                _input._aim_pointer_id = -1;
                _input._shooting = false;
            }
        }
    }

    void cleanup_game() {
        _guard.stop();
        _batch.destroy();
        if (_shader.get_program()) {
            glDeleteProgram(_shader.get_program());
        }
        _zombies.clear();
        _projectiles.clear();
        _particles.clear();
        _initialized = false;
    }

    void restart() {
        _guard.stop();
        _zombies.clear();
        _projectiles.clear();
        _particles.clear();

        _player._transform.set_position(10.0f, 7.0f);
        _player._health = 100;
        _player._alive = true;
        _player._score = 0;
        _player._weapon._ammo = 8;
        _player._weapon._reloading = false;
        _player._invincible_timer = 0.0f;

        _wave_mgr = WaveManager();
        _wave_mgr._wave_timer = 2.0f;
        _wave_mgr._waiting = true;

        _game_over = false;
        _cheat_detected = false;
        _game_time = 0.0f;

        _projectiles.resize(64);
        _particles.resize(128);

        _guard.register_region(&_player, sizeof(Player));
        _guard.register_region(&_wave_mgr, sizeof(WaveManager));
        _guard.start();
    }
};

Game* Game::_instance = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_com_flguard_game_MainActivity_nativeInit(JNIEnv* env, jobject obj, jint w, jint h) {
    Game* g = Game::get_instance();
    g->_screen_w = w;
    g->_screen_h = h;
    g->_jvm = nullptr;
    env->GetJavaVM(&g->_jvm);
    g->_activity = env->NewGlobalRef(obj);
    g->init_game();
}

JNIEXPORT void JNICALL
Java_com_flguard_game_MainActivity_nativeSurfaceChanged(JNIEnv* env, jobject obj, jint w, jint h) {
    Game* g = Game::get_instance();
    g->_screen_w = w;
    g->_screen_h = h;
    glViewport(0, 0, w, h);
    float aspect = (float)w / (float)h;
    g->_camera.set_screen_width(15.0f * aspect);
    g->_camera.set_screen_height(15.0f);
}

JNIEXPORT void JNICALL
Java_com_flguard_game_MainActivity_nativeRender(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    if (!g->_initialized.get()) return;

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    float current = (float)now.tv_sec + (float)now.tv_nsec * 1e-9f;

    if (g->_last_time.get() <= 0.0f) {
        g->_last_time = current;
    }
    float dt = current - g->_last_time.get();
    if (dt > 0.05f) dt = 0.05f;
    if (dt < 0.001f) dt = 0.001f;
    g->_last_time = current;
    g->_delta_time = dt;

    g->update_game(dt);
    g->render_game();
}

JNIEXPORT void JNICALL
Java_com_flguard_game_MainActivity_nativeTouchEvent(JNIEnv* env, jobject obj,
                                                      jint action, jint pointerId,
                                                      jfloat x, jfloat y) {
    Game* g = Game::get_instance();
    if (!g->_initialized.get()) return;
    g->process_input(action, pointerId, x, y);
}

JNIEXPORT void JNICALL
Java_com_flguard_game_MainActivity_nativeRestart(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    g->restart();
}

JNIEXPORT void JNICALL
Java_com_flguard_game_MainActivity_nativeCleanup(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    g->cleanup_game();
    if (g->_activity) {
        env->DeleteGlobalRef(g->_activity);
        g->_activity = nullptr;
    }
}

JNIEXPORT jboolean JNICALL
Java_com_flguard_game_MainActivity_nativeIsCheatDetected(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    return (jboolean)g->_cheat_detected.get();
}

JNIEXPORT jboolean JNICALL
Java_com_flguard_game_MainActivity_nativeIsGameOver(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    return (jboolean)g->_game_over.get();
}

JNIEXPORT jint JNICALL
Java_com_flguard_game_MainActivity_nativeGetScore(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    return (jint)g->_player.get_score();
}

JNIEXPORT jint JNICALL
Java_com_flguard_game_MainActivity_nativeGetHealth(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    return (jint)g->_player.get_health();
}

JNIEXPORT jint JNICALL
Java_com_flguard_game_MainActivity_nativeGetWave(JNIEnv* env, jobject obj) {
    Game* g = Game::get_instance();
    return (jint)g->_wave_mgr.get_wave();
}

}
