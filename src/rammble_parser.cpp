#include "rammble_parser.h"
#include "rammble_environment.h"

#define MATCH_ENUM(STR, ENUM) if (request == STR) return ENUM;

ShapeProperty getShapeProperty(const std::string& request) {
    MATCH_ENUM("POSITION", ShapeProperty::POSITION)
    MATCH_ENUM("SCALE", ShapeProperty::SCALE)
    MATCH_ENUM("ROTATION", ShapeProperty::ROTATION)

    throw std::invalid_argument("Unknown property request: " + request);
}

ParsedValueType getValueType(const std::string& request) {
    MATCH_ENUM("NUMBER", ParsedValueType::NUMBER)
    MATCH_ENUM("VECTOR", ParsedValueType::VECTOR)

    throw std::invalid_argument("Unknown value request: " + request);
}

std::regex setPattern(R"(^SET (.+) OF ([a-zA-Z0-9_]+) TO (.+)$)");
std::regex createShapePattern(R"(^CREATE (.+) ([a-zA-Z_]+[a-zA-Z0-9_]*)$)");
std::regex createShapeWithWhere(R"(^CREATE (.+) ([a-zA-Z_]+[a-zA-Z0-9_]*) WHERE (.+)$)");
std::regex createValuePattern(R"(^CREATE (.+) ([a-zA-Z_]+[a-zA-Z0-9_]*) AS (.+)$)");

bool validRammbleVariable(std::string varname) {
    if (std::isdigit(varname[0]))
        return false;

    return true;
} 

Expression* parseRammbleCode(std::string code) {
    std::smatch matches;

    // ======================================== SET PROPERTY ======================================== //
    if (std::regex_match(code, matches, setPattern)) {
        // shape property to change
        std::string propertyToChangeRequest = matches[1];
        ShapeProperty shapeProperty = getShapeProperty(propertyToChangeRequest);

        // shape name
        std::string shapeName = matches[2];
        if (!validRammbleVariable(shapeName))
            throw std::invalid_argument("Invalid shape name: " + shapeName);
        

        // new value
        std::string valueLiteral = matches[3];
        std::smatch valueMatches;
        if (std::regex_match(valueLiteral, valueMatches, std::regex(R"(([a-zA-Z_]+[a-zA-Z0-9_]*))"))) {
            return new SetExpression(shapeProperty, shapeName, new ParsedNumber(valueMatches[1]));
        }
        else if (std::regex_match(valueLiteral, valueMatches, std::regex(R"(\(\s*(.+)\s*,\s*(.+)\s*,\s*(.+)\s*\))"))) {
            return new SetExpression(shapeProperty, shapeName, new ParsedVector(valueMatches[1], valueMatches[2], valueMatches[3]));
        }
        else if (std::regex_match(valueLiteral, valueMatches, std::regex(R"(([a-zA-Z_]+[a-zA-Z0-9_]*))"))) {
            return new SetExpression(shapeProperty, shapeName, new ParsedVariable(valueMatches[1]));
        }
        else {
            throw std::invalid_argument("Could not parse the value of: " + valueLiteral + ", expected " + propertyToChangeRequest);
        }
    }
    // ======================================== CREATE VALUE ======================================== //
    else if (std::regex_match(code, matches, createValuePattern)) {
        // value type
        std::string requestedValueType = matches[1];
        ParsedValueType valueType = getValueType(requestedValueType);

        // name
        std::string name = matches[2];
        if (!validRammbleVariable(name))
            throw std::invalid_argument("Invalid var name: " + name);

        // value structure
        std::string valueLiteral = matches[3];
        std::smatch valueMatches;
        if (std::regex_match(valueLiteral, valueMatches, std::regex(R"(([0-9]+(\.[0-9]+)?))")) && valueType == ParsedValueType::NUMBER) {
            return new CreateValueExpression(name, valueType, new ParsedNumber(valueMatches[1]));
        }
        else if (std::regex_match(valueLiteral, valueMatches, std::regex(R"(\(\s*(.+)\s*,\s*(.+)\s*,\s*(.+)\s*\))")) && valueType == ParsedValueType::VECTOR) {
            return new CreateValueExpression(name, valueType, new ParsedVector(valueMatches[1], valueMatches[2], valueMatches[3]));
        }
        else if (std::regex_match(valueLiteral, valueMatches, std::regex(R"(([a-zA-Z_]+[a-zA-Z0-9_]*))"))) {
            return new CreateValueExpression(name, valueType, new ParsedVariable(valueMatches[1]));
        }
        else {
            throw std::invalid_argument("Could not parse the value of: " + valueLiteral + ", expected " + requestedValueType);
        }

        // \(\s*(.+)\s*,\s*(.+)\s*,\s*(.+)\s*\)
    }
    // ======================================== CREATE SHAPE ======================================== //
    else if (std::regex_match(code, matches, createShapePattern)) {
        // shape wanted
        RammbleShapeType dataType;
        std::string shapeRequested = matches[1];
        if (shapeRequested == "CUBE")
            dataType = RammbleShapeType::CUBE;
        else
            throw std::invalid_argument("Cannot create shae: " + shapeRequested);
        
        // shape name
        std::string varName = matches[2];
        if (!validRammbleVariable(varName))
            throw std::invalid_argument("Invalid var name: " + varName);
        
        return new CreateExpression(dataType, varName);
    }

    return new Expression();
}

std::vector<Shape*> interpretRammbleCode(std::vector<std::string> linesOfCode) {
    std::vector<Expression*> expressions;
    RammbleEnvironment environment;

    for (const std::string& line : linesOfCode) {
        std::cout << line << std::endl;
        expressions.push_back(parseRammbleCode(line));
    }

    for (const Expression* expression : expressions) {
        
        // ==================== CREATING ==================== //
        if (expression->type == ExpressionType::CREATE_SHAPE) {
            auto exp = (CreateExpression*)expression;

            if (!environment.tryAssignVariable(exp->name, new Cube()))
                throw std::invalid_argument("Tried assigning a non-shape to a shape: " + exp->name);
        }
        else if (expression->type == ExpressionType::CREATE_NUMBER) {
            auto exp = (CreateValueExpression*)expression;

            if (!environment.tryAssignVariable(exp))
                throw std::invalid_argument("Tried assigning a non-number to a number: " + exp->name);
        }
        // ==================== SETTING ==================== //
        else if (expression->type == ExpressionType::SET) {
            auto exp = (SetExpression*)expression;

            if (!environment.tryUpdateShapeProperty(exp->shapeName, exp))
                throw std::invalid_argument("Could not find shape: " + exp->shapeName);
        }
        else {
            throw std::invalid_argument("Could not cast expression: " + expression->type);
        }
        
        // ==================== PRINTING STUFF ==================== //
        // std::cout << expression->type << std::endl;

        // for (const auto& pair : sceneData) {
        //     std::cout << pair.first << " | POS: " << pair.second->position << " SCL: " << pair.second->scale << std::endl;
        // }

        // std::cout << "--------------------" << std::endl;
    }

    // std::vector<Shape*> finalSceneData;
    // for (const auto& pair : sceneData) {
    //     std::cout << "got shape: " << pair.first << std::endl;
    //     finalSceneData.push_back(pair.second);
    // }

    // return finalSceneData; 
    return environment.getShapeScene();  
}