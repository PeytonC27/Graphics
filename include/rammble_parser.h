#pragma once

#include <vector3.h>
#include <shape.h>
#include <cube.h>

#include <string>
#include <regex>
#include <stdexcept>

// ==================== TYPES/PROPERTIES ==================== //
enum RammbleShapeType {
    CUBE,
};

enum ShapeProperty {
    POSITION,
    SCALE,
    ROTATION
};

enum ExpressionType {
    DEFAULT,
    CREATE_SHAPE,
    CREATE_NUMBER,
    SET,
};

// ==================== VALUE/LITERAL PLACEHOLDERS ==================== //
enum ParsedValueType {
    NULLVAL,
    VECTOR,
    NUMBER,
    VARIABLE
};

struct ParsedValue {
    ParsedValueType type = ParsedValueType::NULLVAL;

    ParsedValue() : type(ParsedValueType::NULLVAL) {}
    ParsedValue(ParsedValueType type) : type(type) {}
};

struct ParsedVector: public ParsedValue {
    std::string x, y, z;

    ParsedVector(std::string x, std::string y, std::string z)
        : ParsedValue(ParsedValueType::VECTOR), x(x), y(y), z(z) {}
};

struct ParsedNumber: public ParsedValue {
    std::string num;

    ParsedNumber(std::string num)
        : ParsedValue(ParsedValueType::NUMBER), num(num) {}
};

struct ParsedVariable: public ParsedValue {
    std::string varname;

    ParsedVariable(std::string varname)
        : ParsedValue(ParsedValueType::VARIABLE), varname(varname) {}
};


// ==================== EXPRESSIONS ==================== //
struct Expression {
    ExpressionType type = ExpressionType::DEFAULT;

    Expression() : type(ExpressionType::DEFAULT) {}
    Expression(ExpressionType type) : type(type) {}
};

struct SetExpression : public Expression {
    ShapeProperty toChange;
    std::string shapeName;
    ParsedValue* newVal;

    SetExpression(ShapeProperty toChange, const std::string& shapeName, ParsedValue* newVal)
        : Expression(ExpressionType::SET), toChange(toChange), shapeName(shapeName), newVal(newVal) {}
};

struct CreateExpression : public Expression {
    RammbleShapeType dataType;
    std::string name;
    std::vector<SetExpression> whereConditions;
    
    CreateExpression(RammbleShapeType dataType, const std::string& shapeName)
        : Expression(ExpressionType::CREATE_SHAPE), dataType(dataType), name(shapeName) {}
    CreateExpression(RammbleShapeType dataType, const std::string& shapeName, std::vector<SetExpression> whereConditions)
        : Expression(ExpressionType::CREATE_SHAPE), dataType(dataType), name(shapeName), whereConditions(whereConditions) {}
};

struct CreateValueExpression : public Expression {
    std::string name;
    ParsedValueType valueType;
    ParsedValue* valueToParse;
    
    CreateValueExpression(const std::string& name, ParsedValueType valueType, ParsedValue* valueToParse)
        : Expression(ExpressionType::CREATE_NUMBER), name(name), valueType(valueType), valueToParse(valueToParse) {}
};

// ==================== FUNCTIONS ==================== //
extern Expression* parseRammbleCode(std::string code);
extern std::vector<Shape*> interpretRammbleCode(std::vector<std::string> linesOfCode);