#include "rclcpp/rclcpp.hpp"


using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...

class Myparam:public rclcpp::Node{
public:
    //创建节点
    Myparam():Node("my_param_node_cpp"){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"参数API节点创建！");
    //参数对象实现
    rclcpp::Parameter p1("car_name","tiger");
    rclcpp::Parameter p2("height",1.68);
    rclcpp::Parameter p3("wheels",4);
    //解析值
    RCLCPP_INFO(this->get_logger(),"car_name = %s",p1.as_string().c_str());
    RCLCPP_INFO(this->get_logger(),"height = %.2f",p2.as_double());
    RCLCPP_INFO(this->get_logger(),"wheels = %ld",p3.as_int());
    //分析参数的key
    RCLCPP_INFO(this->get_logger(),"getName= %s",p1.get_name().c_str());
    //参数数据类型
    RCLCPP_INFO(this->get_logger(),"getTypeName= %s",p1.get_type_name().c_str());
    //值转化为string
    RCLCPP_INFO(this->get_logger(),"value_to_string= %s",p2.value_to_string().c_str());

    

  }
private:
  
};


int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<Myparam>());
  rclcpp::shutdown();
  return 0;
}