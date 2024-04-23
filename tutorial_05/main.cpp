#include <behaviortree_cpp/bt_factory.h>
using namespace BT;

class CrossDoor {
public:
  void registerNodes(BT::BehaviorTreeFactory &factory);
  BT::NodeStatus isDoorClosed();
  BT::NodeStatus passThroughDoor();
  BT::NodeStatus pickLock();
  BT::NodeStatus openDoor();
  BT::NodeStatus smashDoor();

private:
  bool _door_open = false;
  bool _door_locked = true;
  int _pick_attempts = 0;
};

void CrossDoor::registerNodes(BT::BehaviorTreeFactory &factory) {
  factory.registerSimpleCondition("IsDoorClosed",
                                  std::bind(&CrossDoor::isDoorClosed, this));
  factory.registerSimpleAction("PassThroughDoor",
                               std::bind(&CrossDoor::passThroughDoor, this));
  factory.registerSimpleAction("OpenDoor",
                               std::bind(&CrossDoor::openDoor, this));
  factory.registerSimpleAction("PickLock",
                               std::bind(&CrossDoor::pickLock, this));
  factory.registerSimpleCondition("SmashDoor",
                                  std::bind(&CrossDoor::smashDoor, this));
}

// 添加成员函数的实现
BT::NodeStatus CrossDoor::isDoorClosed() {
  return _door_open ? BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CrossDoor::passThroughDoor() {
  if (!_door_open) {
    return BT::NodeStatus::FAILURE;
  }
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CrossDoor::pickLock() {
  if (_door_locked && _pick_attempts < 3) {
    _pick_attempts++;
    if (_pick_attempts == 3) {
      _door_locked = false;
      return BT::NodeStatus::SUCCESS;
    }
  }
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus CrossDoor::openDoor() {
  if (!_door_locked) {
    _door_open = true;
    return BT::NodeStatus::SUCCESS;
  }
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus CrossDoor::smashDoor() {
  _door_open = true;
  return BT::NodeStatus::SUCCESS; // 假设破门而入总是成功
}

static const char *xml_text = R"(
<root BTCPP_format="4">
  <BehaviorTree ID="MainTree">
    <Sequence>
      <Fallback>
        <Inverter>
          <IsDoorClosed/>
        </Inverter>
        <SubTree ID="DoorClosed"/>
      </Fallback>
      <PassThroughDoor/>
    </Sequence>
  </BehaviorTree>
  <BehaviorTree ID="DoorClosed">
    <Fallback>
      <OpenDoor/>
      <RetryUntilSuccessful num_attempts="5">
        <PickLock/>
      </RetryUntilSuccessful>
      <SmashDoor/>
    </Fallback>
  </BehaviorTree>
</root>
 )";

int main() {
  BehaviorTreeFactory factory;
  CrossDoor cross_door;
  cross_door.registerNodes(factory);
  factory.registerBehaviorTreeFromText(xml_text);
  auto tree = factory.createTree("MainTree");
  printTreeRecursively(tree.rootNode());
  tree.tickWhileRunning();
  return 0;
}
