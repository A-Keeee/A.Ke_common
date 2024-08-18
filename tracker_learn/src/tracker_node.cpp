#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>

class TrackerNode : public rclcpp::Node
{
public:
    TrackerNode() : Node("tracker_node")
    {
        subscription_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
            "parameters", 10, std::bind(&TrackerNode::callback, this, std::placeholders::_1));
    }

private:
    void callback(const std_msgs::msg::Float32MultiArray::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Received parameters: %f, %f, %f, %f, %f, %f",
                    msg->data[0], msg->data[1], msg->data[2],
                    msg->data[3], msg->data[4], msg->data[5]);
    }

    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TrackerNode>());
    rclcpp::shutdown();
    return 0;
}
