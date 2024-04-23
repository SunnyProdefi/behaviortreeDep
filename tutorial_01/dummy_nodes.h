#pragma once // 防止头文件被多重包含

#include "behaviortree_cpp/action_node.h" // 引入Behavior Tree库中的动作节点基类

// 定义一个名为DummyNodes的命名空间
namespace DummyNodes {

using namespace BT; // 引入命名空间BT，以便直接使用其中的成员

// 定义一个继承自BT::SyncActionNode的类ApproachObject
class ApproachObject : public BT::SyncActionNode {
public:
  // 构造函数，接收一个名字，并通过调用基类的构造函数初始化
  ApproachObject(const std::string &name) : BT::SyncActionNode(name, {}) {}

  // 重写基类的tick函数，用于节点的执行逻辑
  BT::NodeStatus tick() override {
    std::cout << "ApproachObject: " << this->name()
              << std::endl;         // 输出当前动作的名字
    return BT::NodeStatus::SUCCESS; // 返回成功状态
  }
};

// 声明一个检查电池状态的函数
BT::NodeStatus CheckBattery();

// 定义一个类GripperInterface，代表一个抓取器接口
class GripperInterface {
public:
  NodeStatus open();  // 打开抓取器的函数
  NodeStatus close(); // 关闭抓取器的函数
};

} // namespace DummyNodes
