
/*
#include "rclcpp/rclcpp.hpp"
    //1 包含头文件
   // 2 初始化客户端 
   // 3 创建节点指针
    //4 输出日志
    //5 释放资源

int main(int argc, char ** argv)
{
  //初始化客户端
  rclcpp::init(argc,argv);
  //创建节点指针
  auto node= rclcpp::Node::make_shared("helloworld");
  //输出日志
  RCLCPP_INFO(node->get_logger(),"hello world!222");
  
  //释放资源
  rclcpp::shutdown();
  return 0;
}
*/
// 上述方式不推荐，不同的节点会启动不同的进程

//方案二
#include "rclcpp/rclcpp.hpp"

class My_Node:public rclcpp::Node{
  public:
    My_Node():Node("hello_node_cpp"){
      RCLCPP_INFO(this->get_logger(),"hello world(继承方式)");
    }
};
int main(int argc,char **argv)
{
  // 初始化
  rclcpp::init(argc,argv);
  //实例化自定义类
  auto node = std::make_shared<My_Node>();
  //释放资源
  rclcpp::shutdown();
  return 0;
}
