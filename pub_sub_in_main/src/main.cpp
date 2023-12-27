#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/bool.hpp>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("pub_sub_in_main");
    
    std::atomic<bool> continue_flag{true};

    std::string topic_name = "func_main_test";

    auto subscription = node->create_subscription<example_interfaces::msg::Bool>(topic_name, 10,
        [&](example_interfaces::msg::Bool::SharedPtr msg)->void{
            continue_flag = msg->data;
            RCLCPP_INFO(node->get_logger(), "I heard %d", msg->data);
        }
    );

    auto publisher = node->create_publisher<example_interfaces::msg::Bool>(topic_name, 10);

    auto timer = node->create_wall_timer(std::chrono::seconds(1),
        [&]()->void{
            auto msg = example_interfaces::msg::Bool();
            msg.data = false;
            RCLCPP_INFO(node->get_logger(), "publish %d", msg.data);
            publisher->publish(msg);
        }
    );

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    auto thread = std::thread([&executor](){executor.spin();});
    RCLCPP_INFO(node->get_logger(), "start spin.");

    RCLCPP_INFO(node->get_logger(), "wait topic....");
    while(continue_flag);
    RCLCPP_INFO(node->get_logger(), "exit loop.");

    rclcpp::shutdown();
    thread.join();

    return 0;
}
