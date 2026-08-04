#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "irobot_create_msgs/msg/interface_buttons.hpp"
#include "irobot_create_msgs/msg/lightring_leds.hpp"
#include "std_srvs/srv/set_bool.hpp"

class TurtleBot4Prac1 : public rclcpp::Node
{
public:
  TurtleBot4Prac1(): Node("tb4_prac1")
  {
    //Create service server 
    service_ = this->create_service<std_srvs::srv::SetBool>(
        "lightring_service",
        std::bind(&TurtleBot4Prac1::service_callback, this, std::placeholders::_1,
        std::placeholders::_2));
    
    
    //Create publisher
      lightring_publisher_ = this->create_publisher<irobot_create_msgs::msg::LightringLeds>(
      "/cmd_lightring",
      rclcpp::SensorDataQoS());
  }

private:
  void service_callback(std::shared_ptr<std_srvs::srv::SetBool::Request> request,
        std::shared_ptr<std_srvs::srv::SetBool::Response> response)
    {

        auto lightring_msg = irobot_create_msgs::msg::LightringLeds();
        lightring_msg.header.stamp = this->get_clock()->now();



        if (request->data){
            RCLCPP_INFO(this->get_logger(), "INCOMING LIGHTRING OVERWRITE REQUEST RECIEVED");
            lightring_msg.override_system = true;

            lightring_msg.leds[0].red = 255;
            lightring_msg.leds[0].blue = 255;
            lightring_msg.leds[0].green = 255;

            lightring_msg.leds[1].red = 255;
            lightring_msg.leds[1].blue = 255;
            lightring_msg.leds[1].green = 255;

            lightring_msg.leds[2].red = 255;
            lightring_msg.leds[2].blue = 255;
            lightring_msg.leds[2].green = 255;

            lightring_msg.leds[3].red = 255;
            lightring_msg.leds[3].blue = 255;
            lightring_msg.leds[3].green = 255;

            lightring_msg.leds[4].red = 255;
            lightring_msg.leds[4].blue = 255;
            lightring_msg.leds[4].green = 255;

            lightring_msg.leds[5].red = 255;
            lightring_msg.leds[5].blue = 255;
            lightring_msg.leds[5].green = 255;
            response->success= true;
            response->message = "LIGHTRING OVERWRITE ENABLED";
            RCLCPP_INFO(this->get_logger(), "Lightring Overwrite ENABLED");
        }
        else{
            RCLCPP_INFO(this->get_logger(), "INCOMING CANCELLING LIGHTRING OVERWRITE REQUEST RECIEVED");
            response->success= true;
            lightring_msg.override_system = false;
            response->message = "LIGHTRING OVERWRITE CANCELLED";
            RCLCPP_INFO(this->get_logger(), "Lightring Overwrite Cancelled");

        }
        lightring_publisher_->publish(lightring_msg);
    }

    
    rclcpp::Publisher<irobot_create_msgs::msg::LightringLeds>::SharedPtr lightring_publisher_;

    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleBot4Prac1>());
  rclcpp::shutdown();
  return 0;
}
