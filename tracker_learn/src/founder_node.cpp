#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>

class FounderNode : public rclcpp::Node
{
public:
    FounderNode() : Node("founder_node")
    {
        this->declare_parameter<float>("ekf.xyz", 0.0);
        this->declare_parameter<float>("ekf.yaw", 0.0);
        this->declare_parameter<float>("ekf.r", 0.0);
        this->declare_parameter<int>("vx", 0);
        this->declare_parameter<int>("vy", 0);
        this->declare_parameter<int>("vz", 0);

        auto timer_callback = [this]() -> void {
            auto message = std_msgs::msg::Float32MultiArray();
            message.data = {
                this->get_parameter("ekf.xyz").as_double(),
                this->get_parameter("ekf.yaw").as_double(),
                this->get_parameter("ekf.r").as_double(),
                static_cast<float>(this->get_parameter("vx").as_int()),
                static_cast<float>(this->get_parameter("vy").as_int()),
                static_cast<float>(this->get_parameter("vz").as_int())
            };
            RCLCPP_INFO(this->get_logger(), "Publishing parameters: %f, %f, %f, %f, %f, %f",
                        message.data[0], message.data[1], message.data[2],
                        message.data[3], message.data[4], message.data[5]);

            publisher_->publish(message);
        };

        publisher_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("parameters", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), timer_callback);
    }

private:
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FounderNode>());
    rclcpp::shutdown();
    return 0;
}
