#include "behaviortree_cpp/bt_factory.h" // 引入行为树库的工厂类头文件

// 引入包含自定义节点定义的头文件
#include "dummy_nodes.h"
using namespace DummyNodes; // 使用DummyNodes命名空间

int main() {                   // 主函数
  BehaviorTreeFactory factory; // 创建行为树工厂对象
  // 在工厂中注册自定义节点SaySomething，节点名称为"SaySomething"
  factory.registerNodeType<SaySomething>("SaySomething");
  // 在工厂中注册自定义节点ThinkWhatToSay，节点名称为"ThinkWhatToSay"
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

  // 从指定路径的XML文件创建行为树
  auto tree = factory.createTreeFromFile("../../tutorial_02/my_tree.xml");
  tree.tickWhileRunning(); // 循环执行行为树，直到所有节点运行结束
  return 0;                // 程序正常结束，返回0
}
