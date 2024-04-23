#include "dummy_nodes.h" // 引入之前定义的dummy_nodes头文件
#include <iostream>      // 引入标准输入输出流库

// 使用DummyNodes命名空间
namespace DummyNodes {

// 实现SaySomething类的tick方法
NodeStatus SaySomething::tick() {
  auto res = getInput<std::string>("message"); // 尝试获取名为"message"的输入
  if (!res) {                                  // 如果获取失败
    throw RuntimeError("Missing required input [message]: ",
                       res.error()); // 抛出运行时错误，提示缺少必要的输入
  }
  std::cout << "Robot says: " << res.value()
            << std::endl;     // 输出"Robot says: "后跟获取到的消息
  return NodeStatus::SUCCESS; // 返回节点执行成功的状态
}

// 实现ThinkWhatToSay类的tick方法
NodeStatus ThinkWhatToSay::tick() {
  setOutput("text",
            "The answer is 42"); // 设置名为"text"的输出为"The answer is 42"
  return NodeStatus::SUCCESS; // 返回节点执行成功的状态
}

} // namespace DummyNodes
