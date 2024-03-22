#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

#include <memory>

class SubscriberNode : public rclcpp::Node
{
public:
  SubscriberNode()
  : Node("subscriber_node")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int32>("random_numbers", 10, std::bind(&SubscriberNode::topicCallback, this, std::placeholders::_1));
  }

private:
  void topicCallback(const std_msgs::msg::Int32::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Received random number: %d", msg->data);
  }

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PublisherNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}