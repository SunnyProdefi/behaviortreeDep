#ifndef DUMMY_NODES_H
#define DUMMY_NODES_H

#include <behaviortree_cpp/behavior_tree.h> // 包含BehaviorTree库的头文件
#include <chrono>                           // 包含标准库中的时间功能

using namespace BT;

// 二维姿态结构体，包含x、y坐标和角度theta
struct Pose2D {
  double x, y, theta;
};

// 移动基地的行为节点类，继承自StatefulActionNode，表示有状态的行动节点
class MoveBaseAction : public StatefulActionNode {
public:
  // 构造函数
  MoveBaseAction(const std::string &name, const NodeConfig &config);
  // 静态方法，提供节点需要的端口列表
  static PortsList providedPorts();
  // 当动作开始时调用
  NodeStatus onStart() override;
  // 当动作正在执行时调用
  NodeStatus onRunning() override;
  // 当动作被终止时调用
  void onHalted() override;

private:
  Pose2D _goal;                                           // 目标位置
  std::chrono::system_clock::time_point _completion_time; // 动作完成的时间点
};

// 定义一个类SaySomething，继承自SyncActionNode，用于表示说话的动作
class SaySomething : public SyncActionNode {
public:
  // 构造函数，初始化基类SyncActionNode
  SaySomething(const std::string &name, const NodeConfiguration &config)
      : SyncActionNode(name, config) {}

  // 静态函数，定义节点需要的输入端口，这里是一个接收字符串的输入端口“message”
  static PortsList providedPorts() {
    return {InputPort<std::string>("message")};
  }

  // 重写基类的tick函数，定义节点的具体行为
  NodeStatus tick() override;
};

// 声明一个检查电池状态的函数
BT::NodeStatus CheckBattery();

#endif // DUMMY_NODES_H   // 结束宏定义
