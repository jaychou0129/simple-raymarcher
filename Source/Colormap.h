#pragma once
#include <yaml-cpp/yaml.h>

enum class ColormapType {
    TURBO,
    PURPLE
};

namespace YAML {
template <>

struct convert<ColormapType> {
    static Node encode(const ColormapType& rhs) {
        Node node;
        switch (rhs) {
            case ColormapType::TURBO:
                node = "TURBO";
                break;
            case ColormapType::PURPLE:
                node = "PURPLE";
                break;
        }
        return node;
    }

    static bool decode(const Node& node, ColormapType& rhs) {
        if (!node.IsScalar()) return false;
        std::string val = node.as<std::string>();
        if (val == "TURBO") {
            rhs = ColormapType::TURBO;
        } else if (val == "PURPLE") {
            rhs = ColormapType::PURPLE;
        } else {
            return false;
        }
        return true;
    }
};
}