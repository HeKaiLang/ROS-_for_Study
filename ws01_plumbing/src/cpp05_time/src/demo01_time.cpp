#include "rclcpp/rclcpp.hpp"


using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...

class Mynode:public rclcpp::Node{
public:
    //创建节点
    Mynode():Node("time_node_cpp"){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"时间节点创建！");
    demo_rate();
  }
private:
  void demo_rate()
  {
      //创建rate对象
      rclcpp::Rate rate1(500ms);//设置休眠时间
      rclcpp::Rate rate2(1.0);
      //调用sleep函数
      while(rclcpp::ok())
      {
        RCLCPP_INFO(this->get_logger(),"------------");
        rate1.sleep();//以rate1设置的频率进行执行
      }
  void demo_time()
  {
    rclcpp::Time t1(500000000L);//单位ns
    rclcpp::Time t1(500000000L);
    
  }
  }
  
};


int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<Mynode>());
  rclcpp::shutdown();
  return 0;
}