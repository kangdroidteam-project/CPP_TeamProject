#include "StageInformation.h"
void StageInformation::init(const int& speed, const int& stick_rate, const int& clear_line) {
    this->speed = speed;
    this->stick_rate = stick_rate;
    this->clear_line = clear_line;
}
int StageInformation::getSpeed() const {
    return this->speed;
}
int StageInformation::getStickRate() const {
    return this->stick_rate;
}
int StageInformation::getClearLine() const {
    return this->clear_line;
}
void StageInformation::setSpeed(const int& speed) {
    this->speed = speed;
}
void StageInformation::setStickRate(const int& stick_rate) {
    this->stick_rate = stick_rate;
}
void StageInformation::setClearLine(const int& clear_line) {
    this->clear_line = clear_line;
}

