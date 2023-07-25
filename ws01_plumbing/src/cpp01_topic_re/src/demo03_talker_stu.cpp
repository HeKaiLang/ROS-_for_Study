#include "rclcpp/rclcpp.hpp"
#include "base_interfaces/msg/student.hpp"

using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...
using  base_interfaces::msg::Student;
class TalkerStu:public rclcpp::Node{
public:
    //创建节点
    TalkerStu():Node("talkerstu_node_cpp"),count(0){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"发送节点创建！");
    //消息发布方
    publisher_ = this->create_publisher<Student>("chatter_stu",10);
    //定时器
    timer_ = this->create_wall_timer(1s,std::bind(&TalkerStu::on_timer,this));
    // 参数：计时器时长 std::chrono_literals::时长   回调函数std::bind(&类名::回调函数,this);
  }
private:
  void on_timer(){
      //智能指针message
      auto stu = Student();
      //消息内容
      stu.name = "He"+std::to_string(count++);
      stu.age=20;
      stu.height=180.1;
      //打印
      RCLCPP_INFO(this->get_logger(),"发布方发布的消息：(%s,%d,%.2f)",stu.name.c_str(),stu.age,stu.height);
      //发布消息
      publisher_ ->publish(stu); 

  }
  //定时器变量创建
  rclcpp::TimerBase::SharedPtr timer_; 
  //发布者变量创建
  rclcpp::Publisher<Student>::SharedPtr publisher_;
  //计数变量
  size_t count;
};


int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<TalkerStu>());
  rclcpp::shutdown();
  return 0;
}