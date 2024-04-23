#ifndef DUMMY_NODES_H
#define DUMMY_NODES_H

#include <behaviortree_cpp/behavior_tree.h> // 包含BehaviorTree库的头文件

using namespace BT;

// 二维坐标结构体，包含x和y两个成员
struct Position2D {
  double x; // x坐标
  double y; // y坐标
};

// 计算目标位置的动作节点类，继承自同步动作节点
class CalculateGoal : public SyncActionNode {
public:
  CalculateGoal(const std::string &name, const NodeConfig &config);

  // 提供端口的列表，用于节点配置
  static PortsList providedPorts();

  // 执行动作，返回节点状态
  NodeStatus tick() override;
};

// 打印目标位置的动作节点类，继承自同步动作节点
class PrintTarget : public SyncActionNode {
public:
  PrintTarget(const std::string &name, const NodeConfig &config);

  // 提供端口的列表，用于节点配置
  static PortsList providedPorts();

  // 执行动作，返回节点状态
  NodeStatus tick() override;
};

#endif // DUMMY_NODES_H   // 结束宏定义
