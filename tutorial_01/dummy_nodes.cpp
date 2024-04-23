#include "dummy_nodes.h" // 引入之前定义的 dummy_nodes 头文件
#include <iostream>      // 引入标准输入输出库

// 定义使用DummyNodes命名空间
namespace DummyNodes {

// 定义CheckBattery函数，用于检查电池状态
BT::NodeStatus CheckBattery() {
  std::cout << "[ Battery: OK ]" << std::endl; // 输出电池状态为OK
  return NodeStatus::SUCCESS;                  // 返回成功状态
}

// 定义GripperInterface类的open方法，用于打开抓取器
NodeStatus GripperInterface::open() {
  std::cout << "GripperInterface::open" << std::endl; // 输出打开抓取器的操作
  return NodeStatus::SUCCESS;                         // 返回成功状态
}

// 定义GripperInterface类的close方法，用于关闭抓取器
NodeStatus GripperInterface::close() {
  std::cout << "GripperInterface::close" << std::endl; // 输出关闭抓取器的操作
  return NodeStatus::SUCCESS;                          // 返回成功状态
}

} // namespace DummyNodes
