#include "rammble_environment.h"

#define IN_MAP(STR, MAP) (MAP.find(STR) != MAP.end())

bool isNum(const std::string s) {
    int dotCount = 0;
    int digitsBeforeDot = 0;
    int digitsAfterDot = 0;

    for (char c : s) {
        if (std::isdigit(c)) {
            dotCount > 0 ? digitsAfterDot++ : digitsBeforeDot++;
        }
        else if (c == '.') {
            dotCount++;
            if (dotCount > 1)
                return false;
        }
        else {
            return false;
        }
    }

    // must have the leading 0
    if (digitsAfterDot > 0 && digitsBeforeDot == 0)
        return false;
    // can't have dot without digits after
    if (digitsAfterDot == 0 && dotCount == 1)
        return false;

    return true;
}

float interpretParsedNumber(ParsedNumber number, std::unordered_map<std::string, float>& numericalVariables) {
    std::cout << "'" << number.num << "'" << std::endl;
    if (!isNum(number.num)) {
        if (numericalVariables.find(number.num) == numericalVariables.end())
            throw std::invalid_argument("Tried reading unassigned variable: " + number.num);
        return numericalVariables[number.num];
    }
    return std::stof(number.num);
}

Vector3 interpretParsedVector(ParsedVector vector, std::unordered_map<std::string, float>& numericalVariables) {
    std::cout << "'" << vector.x << ", " << vector.y << ", " << vector.z << "'" << std::endl;
    float a = interpretParsedNumber(vector.x, numericalVariables);
    float b = interpretParsedNumber(vector.y, numericalVariables);
    float c = interpretParsedNumber(vector.z, numericalVariables);

    std::cout << "Finished vector" << std::endl;

    return Vector3(
        a, b, c
    );
}

Vector3 interpretParsedVector(ParsedValue* var, std::unordered_map<std::string, float>& numericalVariables, std::unordered_map<std::string, Vector3>& vectorVariables) {
    if (var->type == ParsedValueType::VECTOR)
        return interpretParsedVector(*(ParsedVector*)var, numericalVariables);
    else {
        auto varval = (ParsedVariable*)var;
        return vectorVariables[varval->varname];
    }
}

RammbleEnvironment::RammbleEnvironment() {

}

bool RammbleEnvironment::tryAssignVariable(CreateValueExpression* exp) {
    std::string name = exp->name;

    if (exp->valueType == ParsedValueType::NUMBER) {
        if (IN_MAP(name, vectorValues) || IN_MAP(name, shapes))
            return false;

        // looking if we are trying to assign a variable to an existing number
        if (exp->valueToParse->type == ParsedValueType::VARIABLE) {
            std::string varname = ((ParsedVariable*)exp->valueToParse)->varname;
            if (!IN_MAP(varname, numericalValues))
                return false;
            numericalValues[exp->name] = numericalValues[varname];
            return true;
        }
        // assign a variable to a literal number
        else {
            numericalValues[name] = interpretParsedNumber(*(ParsedNumber*)(exp->valueToParse), this->numericalValues);
            return true;
        }

    }
    else if (exp->valueType == ParsedValueType::VECTOR) {
        if (IN_MAP(name, numericalValues) || IN_MAP(name, shapes))
            return false;

        // looking if we are trying to assign a variable to an existing vector
        if (exp->valueToParse->type == ParsedValueType::VARIABLE) {
            std::string varname = ((ParsedVariable*)exp->valueToParse)->varname;
            if (!IN_MAP(varname, vectorValues))
                return false;
            vectorValues[exp->name] = vectorValues[varname];
            return true;
        }
        // assign a variable to a literal vector
        else {
            vectorValues[name] = interpretParsedVector(*(ParsedVector*)(exp->valueToParse), this->numericalValues);
            return true;
        }
    }
    else {
        return false;
    }
}

bool RammbleEnvironment::tryAssignVariable(const std::string& name, Shape* shape) {
    if (IN_MAP(name, vectorValues) || IN_MAP(name, numericalValues))
        return false;
    shapes[name] = shape;
    return true;
}

float RammbleEnvironment::getNumber(const std::string& name) {
    if (numericalValues.find(name) == numericalValues.end())
        throw std::invalid_argument("Cannot find number: " + name);
    return numericalValues[name];
}

Vector3 RammbleEnvironment::getVector(const std::string& name) {
    if (vectorValues.find(name) == vectorValues.end())
        throw std::invalid_argument("Cannot find vector: " + name);
    return vectorValues[name];
}

Shape* RammbleEnvironment::getShape(const std::string& name) {
    if (shapes.find(name) == shapes.end())
        throw std::invalid_argument("Cannot find shape: " + name);
    return shapes[name];
}

bool RammbleEnvironment::tryUpdateShapeProperty(const std::string& name, SetExpression* updateProcess) {
    if (IN_MAP(name, shapes)) {
        switch (updateProcess->toChange) {
            case POSITION:
                shapes[updateProcess->shapeName]->translate(interpretParsedVector(updateProcess->newVal, numericalValues, vectorValues));
                break;
            case SCALE:
                shapes[updateProcess->shapeName]->changeScale(interpretParsedVector(updateProcess->newVal, numericalValues, vectorValues));
                break;
            case ROTATION:
                shapes[updateProcess->shapeName]->setRotation(interpretParsedVector(updateProcess->newVal, numericalValues, vectorValues), true);
                break;
        }

        return true;
    }
    return false;
}

bool RammbleEnvironment::findVariable(const std::string& name) {
    return numericalValues.find(name) != numericalValues.end() 
            || vectorValues.find(name) != vectorValues.end()
            || shapes.find(name) != shapes.end();
}


std::vector<Shape*> RammbleEnvironment::getShapeScene() {
    std::vector<Shape*> finalSceneData;
    for (const auto& pair : shapes) {
        std::cout << "got shape: " << pair.first << std::endl;
        finalSceneData.push_back(pair.second);
    }

    return finalSceneData;  
}