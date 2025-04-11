#include "Material.h"

// Equality operator: checks if all material properties match
bool Material::operator==(const Material& other) const {
    return m_specular == other.m_specular &&
           m_diffuse == other.m_diffuse &&
           m_ambient == other.m_ambient &&
           m_shininess == other.m_shininess &&
           m_color == other.color(); // Assumes Color has operator== defined
}