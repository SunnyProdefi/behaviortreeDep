#include "dummy_nodes.h" // 包含定义的自定义节点头文件
#include <iostream>      // 引入标准输入输出流库
#include <thread>        // 引入线程库

// MoveBaseAction类的构造函数
MoveBaseAction::MoveBaseAction(const std::string &name,
                               const NodeConfig &config)
    : StatefulActionNode(name, config) {} // 调用基类构造函数初始化

// 返回MoveBaseAction类所需的端口列表
PortsList MoveBaseAction::providedPorts() {
  return {InputPort<Pose2D>("goal")}; // 返回输入端口，包含Pose2D类型的"goal"
}

// MoveBaseAction节点的onStart方法
NodeStatus MoveBaseAction::onStart() {
  if (!getInput("goal", _goal)) {
    throw RuntimeError(
        "missing required input [goal]"); // 如果未获取到输入，抛出异常
  }
  std::cout << "[ MoveBase: SEND REQUEST ]. goal: x=" << _goal.x
            << " y=" << _goal.y << " theta=" << _goal.theta << std::endl;
  _completion_time = std::chrono::system_clock::now() +
                     std::chrono::milliseconds(220); // 设置动作完成时间点
  return NodeStatus::RUNNING; // 返回节点运行中的状态
}

// MoveBaseAction节点的onRunning方法
NodeStatus MoveBaseAction::onRunning() {
  std::this_thread::sleep_for(
      std::chrono::milliseconds(10)); // 睡眠10毫秒，模拟任务进行中
  if (std::chrono::system_clock::now() >= _completion_time) {
    std::cout << "[ MoveBase: FINISHED ]"
              << std::endl; // 时间到达或超过完成时间点，打印完成信息
    return NodeStatus::SUCCESS; // 返回成功状态
  }
  return NodeStatus::RUNNING; // 否则返回运行中状态
}

// MoveBaseAction节点的onHalted方法
void MoveBaseAction::onHalted() {
  std::cout << "[ MoveBase: ABORTED ]" << std::endl; // 输出中断信息
}

// 实现SaySomething类的tick方法
NodeStatus SaySomething::tick() {
  auto res = getInput<std::string>("message"); // 尝试获取名为"message"的输入
  if (!res) {                                  // 如果获取失败
    throw RuntimeError("Missing required input [message]: ",
                       res.error()); // 抛出运行时错误，提示缺少必要的输入
  }
  std::cout << "Robot says: " << res.value() << std::endl; // 输出机器人说的话
  return NodeStatus::SUCCESS; // 返回节点执行成功的状态
}

// 定义CheckBattery函数，用于检查电池状态
BT::NodeStatus CheckBattery() {
  std::cout << "[ Battery: OK ]" << std::endl; // 输出电池状态正常
  return NodeStatus::SUCCESS;                  // 返回成功状态
}

// 辅助函数：分割字符串
std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens; // 存储分割后的字符串
  std::string token;
  std::istringstream tokenStream(s);
  while (getline(tokenStream, token, delimiter)) { // 以分隔符切割字符串
    tokens.push_back(token);
  }
  return tokens;
}

namespace BT {

// 专门化模板函数，用于从字符串转换到Pose2D类型
template <> inline Pose2D convertFromString<Pose2D>(StringView str) {
  std::vector<std::string> parts =
      split(std::string(str.data(), str.size()), ';'); // 以分号分割输入字符串
  if (parts.size() != 3) { // 如果分割后的部分不是三个，抛出异常
    throw RuntimeError("Invalid input for Pose2D, expected format x;y;theta");
  }
  Pose2D pose;                      // 创建Pose2D实例
  pose.x = std::stod(parts[0]);     // 将第一部分转换为double作为x
  pose.y = std::stod(parts[1]);     // 将第二部分转换为double作为y
  pose.theta = std::stod(parts[2]); // 将第三部分转换为double作为theta
  return pose;
}

} // namespace BT
