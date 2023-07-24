#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...

class Talker:public rclcpp::Node{
public:
    //创建节点
    Talker():Node("talker_node_cpp"),count(0){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"发送节点创建！");
    //消息发布方
    publisher_ = this->create_publisher<std_msgs::msg::String>("chatter",10);
    //定时器
    timer_ = this->create_wall_timer(1s,std::bind(&Talker::on_timer,this));
    // 参数：计时器时长 std::chrono_literals::时长   回调函数std::bind(&类名::回调函数,this);
  }
private:
  void on_timer(){
      //智能指针message
      auto message = std_msgs::msg::String();
      //消息内容
      message.data = "hello"+std::to_string(count++);
      //打印
      RCLCPP_INFO(this->get_logger(),"发布方发布的消息：%s",message.data.c_str());
      //发布消息
      publisher_ ->publish(message); 

  }
  //定时器变量创建
  rclcpp::TimerBase::SharedPtr timer_; 
  //发布者变量创建
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  //计数变量
  size_t count;
};


int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
