#ifndef DUMMY_NODES_H
#define DUMMY_NODES_H

#include "behaviortree_cpp/action_node.h" // 引入行为树库中的动作节点基类

namespace DummyNodes {

using namespace BT;

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

// 定义一个类ThinkWhatToSay，继承自SyncActionNode，用于表示思考要说什么的动作
class ThinkWhatToSay : public SyncActionNode {
public:
  // 构造函数，初始化基类SyncActionNode
  ThinkWhatToSay(const std::string &name, const NodeConfiguration &config)
      : SyncActionNode(name, config) {}

  // 静态函数，定义节点需要的输出端口，这里是一个输出字符串的端口“text”
  static PortsList providedPorts() { return {OutputPort<std::string>("text")}; }

  // 重写基类的tick函数，定义节点的具体行为
  NodeStatus tick() override;
};

} // namespace DummyNodes

#endif
