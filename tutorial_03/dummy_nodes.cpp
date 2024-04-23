#include "dummy_nodes.h"

// CalculateGoal类的构造函数
CalculateGoal::CalculateGoal(const std::string &name, const NodeConfig &config)
    : SyncActionNode(name, config) {} // 初始化列表调用基类构造函数

// 返回CalculateGoal类所需的端口列表
PortsList CalculateGoal::providedPorts() {
  return {OutputPort<Position2D>(
      "goal")}; // 返回输出端口，包含Position2D类型的"goal"
}

// CalculateGoal节点的执行函数
NodeStatus CalculateGoal::tick() {
  Position2D mygoal = {1.1, 2.3};        // 定义目标位置
  setOutput<Position2D>("goal", mygoal); // 设置输出端口"goal"的值
  return NodeStatus::SUCCESS;            // 返回执行成功的状态
}

// PrintTarget类的构造函数
PrintTarget::PrintTarget(const std::string &name, const NodeConfig &config)
    : SyncActionNode(name, config) {} // 初始化列表调用基类构造函数

// 返回PrintTarget类所需的端口列表
PortsList PrintTarget::providedPorts() {
  const char *description = "Simply print the goal on console..."; // 端口描述
  return {InputPort<Position2D>(
      "target", description)}; // 返回输入端口，包含Position2D类型的"target"
}

// PrintTarget节点的执行函数
NodeStatus PrintTarget::tick() {
  auto res = getInput<Position2D>("target"); // 尝试从输入端口"target"获取数据
  if (!res) {
    throw RuntimeError("error reading port [target]:",
                       res.error()); // 如果读取失败，抛出异常
  }
  Position2D target = res.value(); // 获取输入值
  printf("Target positions: [ %.1f, %.1f ]\n", target.x,
         target.y);           // 打印目标位置
  return NodeStatus::SUCCESS; // 返回执行成功的状态
}

// Template specialization to converts a string to Position2D.
namespace BT {
template <> inline Position2D convertFromString(StringView str) {
  // We expect real numbers separated by semicolons
  auto parts = splitString(str, ';'); // 使用分号分割字符串
  if (parts.size() != 2) {
    throw RuntimeError("invalid input)"); // 如果分割结果不是两部分，抛出异常
  } else {
    Position2D output; // 创建Position2D结构体实例
    output.x =
        convertFromString<double>(parts[0]); // 将第一部分转换为double作为x值
    output.y =
        convertFromString<double>(parts[1]); // 将第二部分转换为double作为y值
    return output;                           // 返回Position2D实例
  }
}
} // end namespace BT
