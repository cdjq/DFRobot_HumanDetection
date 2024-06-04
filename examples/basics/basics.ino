/**！
 * @file basics.ino
 * @brief 这是人体毫米波雷达的基础使用例程
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [tangjie](jie.tang@dfrobot.com)
 * @version  V1.0
 * @date  2024-06-03
 * @url https://github.com/DFRobot/DFRobot_HumanDetection
 */

#include "DFRobot_HumanDetection.h"

DFRobot_HumanDetection hu(&Serial1);

void setup()
{
  Serial.begin(115200);
  // Serial.println(1000);
  Serial1.begin(115200, SERIAL_8N1, 4, 5);
  while (hu.begin() != 0)
  {
    Serial.println("init error!!!");
    delay(1000);
  }
  Serial.println("init success");
  delay(100);
  while (hu.configWorkMode(hu.eSleepMode) != 0)
  {
    Serial.println("init error!!!");
    delay(1000);
  }
  Serial.println("init success");

  Serial.print("工作模式：");
  switch (hu.getWorkMode())
  {
  case 1:
    Serial.println("跌倒模式");
    break;
  case 2:
    Serial.println("睡眠模式");
    break;
  default:
    Serial.println("读取错误");
  }

  hu.configLEDLight(hu.eHPLed, 1); // 设置HP LED开关

  Serial.print("HP LED状态：");
  switch (hu.getLEDLightState(hu.eHPLed))
  {
  case 0:
    Serial.println("关");
    break;
  case 1:
    Serial.println("开");
    break;
  default:
    Serial.println("读取错误");
  }
  Serial.println();
  Serial.println();
}

void loop()
{
  Serial.print("存在信息：");
  switch (hu.smHumanData(hu.eHumanPresence))
  {
  case 0:
    Serial.println("无人存在");
    break;
  case 1:
    Serial.println("有人存在");
    break;
  default:
    Serial.println("读取错误");
  }

  Serial.print("运动信息：");
  switch (hu.smHumanData(hu.eHumanMovement))
  {
  case 0:
    Serial.println("无");
    break;
  case 1:
    Serial.println("静止");
    break;
  case 2:
    Serial.println("活跃");
    break;
  default:
    Serial.println("读取错误");
  }

  Serial.printf("体动参数：%d\n", hu.smHumanData(hu.eHumanMovingRange));

  Serial.printf("呼吸频率：%d\n", hu.getBreatheValue());
  Serial.printf("心跳频率：%d\n", hu.gitHeartRate());

  Serial.println();
  delay(1000);
}
