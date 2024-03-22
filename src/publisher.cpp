#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode()
  : Node("publisher_node")
  {
    publisher_ = this->create_publisher<std_msgs::msg::Int32>("random_numbers", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&PublisherNode::publishRandomNumber, this));
  }

private:
  void publishRandomNumber()
  {
    auto msg = std::make_shared<std_msgs::msg::Int32>();
    msg->data = rand() % 100;
    RCLCPP_INFO(this->get_logger(), "Publishing random number: %d", msg->data);
    publisher_->publish(*msg);
  }

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PublisherNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
