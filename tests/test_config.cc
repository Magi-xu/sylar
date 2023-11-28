#include "../sylar/config.h"
#include "../sylar/log.h"
#include "yaml-cpp/yaml.h"


#if 0
sylar::ConfigVar<int>::ptr g_int_value_config = sylar::Config::Lookup(
        "system.port", (int)8080, "system port");

sylar::ConfigVar<float>::ptr g_int_valuex_config = sylar::Config::Lookup(
        "system.port", (float)8080, "system port");

sylar::ConfigVar<float>::ptr g_float_value_config = sylar::Config::Lookup(
        "system.value", (float)10.2f, "system value");

sylar::ConfigVar<std::vector<int>>::ptr g_int_vec_value_config = sylar::Config::Lookup(
        "system.int_vec", std::vector<int>{1,2}, "system int vector");

sylar::ConfigVar<std::list<int>>::ptr g_int_list_value_config = sylar::Config::Lookup(
        "system.int_list", std::list<int>{1,2}, "system int list");

sylar::ConfigVar<std::set<int>>::ptr g_int_set_value_config = sylar::Config::Lookup(
        "system.int_set", std::set<int>{1,2}, "system int set");

sylar::ConfigVar<std::unordered_set<int>>::ptr g_int_uset_value_config = sylar::Config::Lookup(
        "system.int_uset", std::unordered_set<int>{1,2}, "system int uset");

sylar::ConfigVar<std::map<std::string, int>>::ptr g_str_int_map_value_config = sylar::Config::Lookup(
        "system.str_int_map", std::map<std::string, int>{{"a", 2}}, "system str int map");

sylar::ConfigVar<std::unordered_map<std::string, int>>::ptr g_str_int_umap_value_config = sylar::Config::Lookup(
        "system.str_int_umap", std::unordered_map<std::string, int>{{"a", 2}}, "system str int umap");

void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ') << node.Scalar() << " - " << node.Type() << " - " << level;
    } else if (node.IsScalar()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ') << "NULL - " << node.Type() << " - " << level;
    } else if (node.IsMap()) {
        for(auto it = node.begin(); it != node.end(); ++it) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ') << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level+1);
        }
    } else if (node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ') << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level+1);
        }
    }
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("/root/sylar/bin/conf/log.yml");
    print_yaml(root,0);

    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root.Scalar();
}

void tese_config() {
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_float_value_config->toString();

#define XX(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for (auto& i : v) { \
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name ": " << i; \
        } \
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
    }

#define XX_M(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for (auto& i : v) { \
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name ": {" << i.first << " - " << i.second << "}"; \
        } \
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
    }

    XX(g_int_vec_value_config, int_vec, before);
    XX(g_int_list_value_config, int_list, before);
    XX(g_int_set_value_config, int_set, before);
    XX(g_int_uset_value_config, int_uset, before);
    XX_M(g_str_int_map_value_config, int_map, before);
    XX_M(g_str_int_umap_value_config, int_umap, before);

    YAML::Node root = YAML::LoadFile("/root/sylar/bin/conf/log.yml");
    sylar::Config::LoadFromYaml(root);

    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after: ->getValue()" << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after: ->toString()" << g_float_value_config->toString();

    XX(g_int_vec_value_config, int_vec, after);
    XX(g_int_list_value_config, int_list, after);
    XX(g_int_set_value_config, int_set, after);
    XX(g_int_uset_value_config, int_uset, after);
    XX_M(g_str_int_map_value_config, int_map, after);
    XX_M(g_str_int_umap_value_config, int_umap, after);
}
#endif

class Person {
public:
    std::string m_name;
    int m_age = 0;
    bool m_sex = 0;

    std::string toString() const {
        std::stringstream ss;
        ss << "[Person name=" << m_name
            << " age=" << m_age
            << " sex=" <<m_sex
            << "]";
        return ss.str();
    }

};

namespace sylar {
    template<>
    class LexicalCast<std::string, Person> {
    public:
        Person operator() (const std::string& v) {
            YAML::Node node = YAML::Load(v);
            Person p;
            p.m_name = node["name"].as<std::string>();
            p.m_age = node["age"].as<int>();
            p.m_sex = node["sex"].as<bool>();
            return p;
        }
    };

    template<>
    class LexicalCast<Person, std::string> {
    public:
        std::string operator() (const Person& p) {
            YAML::Node node;
            node["name"] = p.m_name;
            node["age"] = p.m_age;
            node["sex"] = p.m_sex;
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };
}

sylar::ConfigVar<Person>::ptr g_person =
        sylar::Config::Lookup("class.person", Person(), "system person");

sylar::ConfigVar<std::map<std::string, Person>>::ptr g_person_map =
        sylar::Config::Lookup("class.person_map", std::map<std::string, Person>(), "system person map");

void test_class() {
//    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_person->getValue().toString() << " - " << g_person->toString();

#define XX_PM(g_var, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for (auto& i : v) { \
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix ": " << i.first << " - " << i.second.toString(); \
        } \
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix ": size=" << v.size(); \
    }

    XX_PM(g_person_map, before)

//    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_person_map->getValue().toString() << " - " << g_person_map->toString();

    YAML::Node root = YAML::LoadFile("/root/sylar/bin/conf/log.yml");
    sylar::Config::LoadFromYaml(root);

//    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_person->getValue().toString() << " - " << g_person->toString();
//    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_person_map->getValue().toString() << " - " << g_person_map->toString();
    XX_PM(g_person_map, after)
}

int main(int argc, char** argv) {

//    test_yaml();
//    tese_config();
    test_class();
    return 0;
}