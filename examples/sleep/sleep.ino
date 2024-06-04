/**！
 * @file sleep.ino
 * @brief 这是人体毫米波雷达的睡眠检测示例
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
    Serial.println(1000);
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
    Serial.print("入床状态：");
    switch (hu.smSleepData(hu.eInOrNotInBed))
    {
    case 0:
        Serial.println("离床");
        break;
    case 1:
        Serial.println("入床");
        break;
    default:
        Serial.println("读取错误");
    }

    Serial.print("睡眠状态：");
    switch (hu.smSleepData(hu.eSleepState))
    {
    case 0:
        Serial.println("深睡");
        break;
    case 1:
        Serial.println("浅睡");
        break;
    case 2:
        Serial.println("清醒");
        break;
    case 3:
        Serial.println("无");
        break;
    default:
        Serial.println("读取错误");
    }
    Serial.printf("清醒时长：%d\n", hu.smSleepData(hu.eWakeDuration));
    Serial.printf("深睡时长：%d\n", hu.smSleepData(hu.eDeepSleepDuration));
    Serial.printf("睡眠质量评分：%d\n", hu.smSleepData(hu.eSleepQuality));

    sSleepComposite qwe = hu.getSleepComposite();
    Serial.println("睡眠综合状态：{");

    Serial.print("\t存在状态：");
    switch (qwe.presence)
    {
    case 0:
        Serial.println("无人");
        break;
    case 1:
        Serial.println("有人");
        break;
    default:
        Serial.println("读取错误");
    }

    Serial.print("\t睡眠状态：");
    switch (qwe.sleepState)
    {
    case 0:
        Serial.println("深睡");
        break;
    case 1:
        Serial.println("浅睡");
        break;
    case 2:
        Serial.println("清醒");
        break;
    case 3:
        Serial.println("无");
        break;
    default:
        Serial.println("读取错误");
    }

    Serial.printf("\t平均呼吸频率：%d\n", qwe.averageRespiration);
    Serial.printf("\t平均心跳频率：%d\n", qwe.averageHeartbeat);
    Serial.printf("\t翻身次数：%d\n", qwe.turnoverNumber);
    Serial.printf("\t大幅体动占比：%d\n", qwe.largeBodyMove);
    Serial.printf("\t小幅体动占比：%d\n", qwe.minorBodyMove);
    Serial.printf("\t呼吸暂停次数：%d\n", qwe.apneaEvents);
    Serial.println("}");

    Serial.print("睡眠异常：");
    switch (hu.smSleepData(hu.eSleepDisturbances))
    {
    case 0:
        Serial.println("睡眠时长不足4小时");
        break;
    case 1:
        Serial.println("睡眠时长大于12小时");
        break;
    case 2:
        Serial.println("长时间异常无人");
        break;
    case 3:
        Serial.println("无");
        break;
    default:
        Serial.println("读取错误");
    }

    sSleepStatistics abc = hu.getSleepStatistics();  //这个接口有问题
    Serial.println("睡眠统计：{");
    Serial.printf("\t睡眠质量评分：%d\n", abc.sleepQualityScore);
   Serial.printf("\t睡眠总时长：%d\n", abc.sleepTime);

    Serial.print("睡眠质量评级：");
    switch (hu.smSleepData(hu.eSleepQualityRating))
    {
    case 0:
        Serial.println("无");
        break;
    case 1:
        Serial.println("睡眠质量良好");
        break;
    case 2:
        Serial.println("睡眠质量一般");
        break;
    case 3:
        Serial.println("睡眠质量较差");
        break;
    default:
        Serial.println("读取错误");
    }

    Serial.print("异常挣扎状态：");
    switch (hu.smSleepData(hu.eAbnormalStruggle))
    {
    case 0:
        Serial.println("无");
        break;
    case 1:
        Serial.println("正常状态");
        break;
    case 2:
        Serial.println("异常挣扎状态");
        break;
    default:
        Serial.println("读取错误");
    }

    Serial.println();
    Serial.println();
    delay(1000);
}