#pragma once

#include <unordered_map>
#include <string>

#include "vector3.h"
#include "shape.h"
#include "rammble_parser.h"

class RammbleEnvironment {
public:
    RammbleEnvironment();

    bool tryAssignVariable(CreateValueExpression* exp);
    bool tryAssignVariable(const std::string& name, Shape* shape);

    /// @brief Find if a varaible exists in this environment
    /// @param name the variable to look for
    /// @return true if it exists, false otherwise
    bool findVariable(const std::string& name);

    float getNumber(const std::string& name);
    Vector3 getVector(const std::string& name);
    Shape* getShape(const std::string& name);

    bool tryUpdateShapeProperty(const std::string& name, SetExpression* updateProcess);

    std::vector<Shape*> getShapeScene();

private:
    std::unordered_map<std::string, float> numericalValues;
    std::unordered_map<std::string, Vector3> vectorValues;
    std::unordered_map<std::string, Shape*> shapes;
};