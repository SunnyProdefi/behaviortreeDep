#include "behaviortree_cpp/bt_factory.h" // 引入行为树库的工厂类头文件
#include "dummy_nodes.h"    // 引入之前定义的行为节点头文件
using namespace DummyNodes; // 使用DummyNodes命名空间中的内容

int main() {                   // 主函数
  BehaviorTreeFactory factory; // 创建一个行为树工厂对象

  // 向工厂中注册ApproachObject节点类型
  factory.registerNodeType<ApproachObject>("ApproachObject");

  // 注册一个简单的条件节点"CheckBattery"，当被调用时执行CheckBattery函数
  factory.registerSimpleCondition("CheckBattery",
                                  [&](TreeNode &) { return CheckBattery(); });

  GripperInterface gripper; // 创建一个GripperInterface对象
  // 注册一个简单的动作节点"OpenGripper"，当被调用时执行gripper.open()函数
  factory.registerSimpleAction("OpenGripper",
                               [&](TreeNode &) { return gripper.open(); });
  // 注册一个简单的动作节点"CloseGripper"，当被调用时执行gripper.close()函数
  factory.registerSimpleAction("CloseGripper",
                               [&](TreeNode &) { return gripper.close(); });

  // 从文件"./my_tree.xml"中加载行为树
  auto tree = factory.createTreeFromFile("../../tutorial_01/my_tree.xml");

  tree.tickWhileRunning(); // 循环执行行为树直到结束

  return 0;
}
