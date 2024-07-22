#include <iostream>
using namespace std;

class MotorController {
private:
    bool isOn;
    int speed;
    string direction;

public:
    MotorController() : isOn(false), speed(0), direction("顺时针") {}

    void turnOn() {
        if (isOn) {
            cout << "电机已经打开。" << endl;
        } else {
            isOn = true;
            speed = 0;
            cout << "电机已打开。" << endl;
        }
    }

    void turnOff() {
        if (!isOn) {
            cout << "电机已经关闭。" << endl;
        } else {
            isOn = false;
            speed = 0;
            cout << "电机已关闭。" << endl;
        }
    }

    void setSpeed(int newSpeed) {
        if (isOn) {
            speed = newSpeed;
            cout << "电机速度已设置为 " << speed << "。" << endl;
        } else {
            cout << "电机未打开，无法设置速度。" << endl;
        }
    }

    int getSpeed() {
        if (isOn) {
            return speed;
        } else {
            cout << "电机未打开。" << endl;
            return -1;
        }
    }

    void setDirection(const string& newDirection) {
        if (isOn) {
            if (newDirection == "顺时针" || newDirection == "逆时针") {
                direction = newDirection;
                cout << "电机旋转方向已设置为 " << direction << "。" << endl;
            } else {
                cout << "无效的方向，请输入 '顺时针' 或 '逆时针'。" << endl;
            }
        } else {
            cout << "电机未打开，无法设置方向。" << endl;
        }
    }

    string getDirection() {
        if (isOn) {
            return direction;
        } else {
            cout << "电机未打开。" << endl;
            return "";
        }
    }

    bool isMotorOn() {
        return isOn;
    }
};

void displayMenu() {
    cout << "---------------------------------------" << endl;
    cout << "请输入数字来选择你的模式：" << endl;
    cout << "0.关闭电机" << endl;
    cout << "1.开启电机" << endl;
    cout << "2.修改电机速度" << endl;
    cout << "3.查看当前电机速度" << endl;
    cout << "4.改变电机旋转方向（顺时针 || 逆时针）" << endl;
    cout << "5.查看当前电机旋转方向（顺时针 || 逆时针）" << endl;
    cout << "---------------------------------------" << endl;
}

int main() {
    MotorController motor;
    int choice;
    int speed;
    string direction;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 0:
            motor.turnOff();
            return 0;
        case 1:
            motor.turnOn();
            break;
        case 2:
            if (motor.isMotorOn()) {
                cout << "请输入电机速度：";
                cin >> speed;
                motor.setSpeed(speed);
            } else {
                cout << "电机未打开。" << endl;
            }
            break;
        case 3:
            if (motor.isMotorOn()) {
                cout << "当前电机速度为：" << motor.getSpeed() << endl;
            }
            break;
        case 4:
            if (motor.isMotorOn()) {
                cout << "请输入电机旋转方向（顺时针 || 逆时针）：";
                cin >> direction;
                motor.setDirection(direction);
            } else {
                cout << "电机未打开。" << endl;
            }
            break;
        case 5:
            if (motor.isMotorOn()) {
                cout << "当前电机旋转方向为：" << motor.getDirection() << endl;
            }
            break;
        default:
            cout << "无效选择，请重新输入。" << endl;
            break;
        }
    }
    return 0;
}
