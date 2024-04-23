#include "dummy_nodes.h"                 // 包含自定义节点的头文件
#include <behaviortree_cpp/bt_factory.h> // 包含行为树工厂的头文件
#include <iostream>                      // 包含标准输入输出流库

using namespace BT; // 使用命名空间BT

int main() {
  BehaviorTreeFactory factory; // 创建行为树工厂对象
  factory.registerSimpleCondition(
      "BatteryOK", std::bind(CheckBattery)); // 注册一个简单条件节点"BatteryOK"
  factory.registerNodeType<MoveBaseAction>(
      "MoveBase"); // 注册MoveBaseAction节点类型
  factory.registerNodeType<SaySomething>(
      "SaySomething"); // 注册SaySomething节点类型

  // 从 XML 文件加载行为树
  auto tree = factory.createTreeFromFile(
      "../../tutorial_04/my_tree.xml"); // 从指定路径加载XML文件定义的行为树

  // 初始化status变量
  NodeStatus status = NodeStatus::IDLE; // 初始状态设为IDLE（空闲）

  // 这里我们使用自定义的循环代替tree.tickWhileRunning()
  std::cout << "--- ticking\n"; // 打印开始执行的消息
  status = tree.tickOnce();     // 执行行为树一次
  std::cout << "--- status: " << toStr(status) << "\n\n"; // 打印当前状态

  while (status ==
         NodeStatus::RUNNING) { // 当状态为RUNNING（运行中）时，持续执行
    // 为避免忙循环，休眠一段时间
    // 不要使用其他休眠函数！
    // 这里我们使用较长的休眠时间，只是为了在控制台上减少消息数量
    tree.sleep(std::chrono::milliseconds(100)); // 休眠100毫秒

    std::cout << "--- ticking\n"; // 打印再次执行的消息
    status = tree.tickOnce();     // 再次执行行为树
    std::cout << "--- status: " << toStr(status) << "\n\n"; // 打印当前状态
  }

  return 0;
}
