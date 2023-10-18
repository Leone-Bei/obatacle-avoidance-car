#include <stdio.h>
#include <math.h>

extern float turn_radius;//小车的转弯半径
extern float turn_constant;
extern float car_position_x;//小车在参考系中的位置
extern float car_position_y;
extern float car_direction;//小车的行驶方向
extern float l;
extern float left;
extern float right;
extern float front;
extern float delta_x;
extern float delta_theta;
extern int section;

float turn_radius_calculate(float delta);
float angle_adjust(float radius);
float right_sec1(float x, float y);
float left_sec1(float x, float y);
float right_sec3(float x, float y);
float left_sec3(float x, float y);
float right_sec2(float x,float y);
float left_sec2(float x,float y);
float distance1(float x1,float y1,float x2,float y2);
float distance2(float X,float Y, float m, float n,float theta);
int section_judge(float x, float y);
float turn_radius_calculate(float delta);
float angle_adjust(float radius);
void new_position(float theta,float x,float y);