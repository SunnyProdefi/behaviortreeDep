#include "behaviortree_cpp/bt_factory.h" // 引入行为树库的工厂类头文件
#include "dummy_nodes.h"                 // 包括自定义节点的头文件

using namespace BT;

int main() {
  BehaviorTreeFactory factory; // 创建一个行为树工厂对象

  // 注册节点类型
  factory.registerNodeType<CalculateGoal>(
      "CalculateGoal"); // 注册CalculateGoal节点，节点类型为"CalculateGoal"
  factory.registerNodeType<PrintTarget>(
      "PrintTarget"); // 注册PrintTarget节点，节点类型为"PrintTarget"

  // 从 XML 文件加载行为树
  auto tree = factory.createTreeFromFile(
      "../../tutorial_03/my_tree.xml"); // 从指定路径加载XML文件定义的行为树

  // 执行行为树
  tree.tickWhileRunning(); // 循环执行行为树直至运行结束

  return 0; // 程序正常结束，返回0
}
