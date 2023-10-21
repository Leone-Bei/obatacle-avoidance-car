#include "digital_simulation.hpp"

float turn_radius;//小车的转弯半径
float turn_constant;
float car_position_x;//小车在参考系中的位置
float car_position_y;
float car_direction;//小车的行驶方向
float l;
float left;
float right;
float front;
float delta_x;
float delta_theta;
int section;

float right_sec1(float x, float y)//在1区域中，车辆右侧参数获得
{
    float y_m;
    y_m=(-cos(car_direction)*(x-1))/sin(car_direction)+y;
    return distance1(car_position_x,car_position_y,1,y_m);
}

float left_sec1(float x, float y)//在1区域中，车辆左侧侧参数获得
{
    float y_m;
    y_m=(-cos(car_direction)*(x-0))/sin(car_direction)+y;
    return distance1(car_position_x,car_position_y,0,y_m);
}

float right_sec3(float x, float y)//在1区域中，车辆右侧参数获得
{
    float y_m;
    y_m=(-cos(car_direction)*(x-5))/sin(car_direction)+y;
    return distance1(car_position_x,car_position_y,5,y_m);
}

float left_sec3(float x, float y)//在1区域中，车辆左侧参数获得
{
    float y_m;
    y_m=(-cos(car_direction)*(x-6))/sin(car_direction)+y;
    return distance1(car_position_x,car_position_y,6,y_m);
}

float right_sec2(float x,float y)//在2区域中，车辆右侧参数获得
{
    float l1=pow(pow(distance1(car_position_x,car_position_y,3,5),2)-pow(distance2(3,5,car_position_x,car_position_y,car_direction),2),0.5);
    float l2=pow(4-pow(distance2(3,5,car_position_x,car_position_y,car_direction),2),0.5);
    return l1-l2;
}

float left_sec2(float x,float y)//在2区域中，车辆左侧参数获得
{
    float l1=pow(9-pow(distance2(3,5,car_position_x,car_position_y,car_direction),2),0.5);
    float l2=pow(pow(distance1(car_position_x,car_position_y,3,5),2)-pow(distance2(3,5,car_position_x,car_position_y,car_direction),2),0.5);
    return l1-l2;
}

float distance1(float x1,float y1,float x2,float y2)//计算两点(x1,y1)(x2,y2)的距离
{
    return pow(pow(x1-x2,2)+pow(y1-y2,2),0.5);
}

float distance2(float X,float Y, float m, float n,float theta)//计算点(X,Y)到直线的距离
{
    return abs(cos(theta)*(X-m)+sin(theta)*(Y-n));
}

int section_judge(float x, float y)//判断车辆是否在赛道赛道的那个区域
{
    if(x<1&&x>0&&y<5&&y>=0)
    {
        return 1;
    }
    else if(x<6&&x>5&&y<5&&y>=0)
    {
        return 3;
    }
    else if(y>=5&&distance1(x,y,3,5)<3&&distance1(x,y,3,5)>1)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

float turn_radius_calculate(float delta)//转弯半径计算
{
    return turn_constant/delta;
}

float angle_adjust(float radius)//计算调整的角度
{
    return l/(2*radius);
}

void new_position(float theta,float x,float y)//计算新的坐标
{
    car_position_x=car_position_x+l*cos(theta);
    car_position_y=car_position_y+l*sin(theta);
}




int main()
{
    //起点设置
    car_position_x=0.5;
    car_position_y=0;
    car_direction=M_PI/2;
    turn_constant=1;
    l=0.01;
    do
    {
        printf("(%f,%f)\n",car_position_x,car_position_y);
        section=section_judge(car_position_x,car_position_y);
        printf("section=%d\n",section);
        if(section==0)
        {
            printf("out\n");
            break;
        }
        else if (section==1)
        {
            left=left_sec1(car_position_x,car_position_y);
            right=right_sec1(car_position_x,car_position_y);
        }
        else if(section==2)
        {
            left=left_sec2(car_position_x,car_position_y);
            right=right_sec2(car_position_x,car_position_y);
        }
        else if(section==3)
        {
            left=left_sec3(car_position_x,car_position_y);
            right=right_sec3(car_position_x,car_position_y);
        }
        printf("left=%f\tright=%f\n\n",left,right);
        delta_x=right-left;
        turn_radius=turn_radius_calculate(delta_x);
        delta_theta=angle_adjust(turn_radius);
        car_direction=car_direction-delta_theta;
        new_position(car_direction,car_position_x,car_position_y);
    } 
    while (car_position_y>=0);
    if(car_position_y<0)
    {
        printf("successflly arrive\n");
    }
    return 0;
}

//g++ digital_simulation.cpp -o test.out
//./test.out