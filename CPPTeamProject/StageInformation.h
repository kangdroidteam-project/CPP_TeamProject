#pragma once
class StageInformation {
private:
    int	speed;	//숫자가 낮을수록 속도가 빠르다
    int stick_rate;		//막대가 나오는 확률 0~99 , 99면 막대기만 나옴
    int clear_line;
public:
    void init(const int& speed, const int& stick_rate, const int& clear_line);
    int getSpeed() const;
    int getStickRate() const;
    int getClearLine() const;
    void setSpeed(const int& speed);
    void setStickRate(const int& stick_rate);
    void setClearLine(const int& clear_line);
};

