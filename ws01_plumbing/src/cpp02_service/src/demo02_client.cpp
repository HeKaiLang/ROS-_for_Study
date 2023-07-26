#include "rclcpp/rclcpp.hpp"
#include "base_interfaces/srv/addints.hpp"

using namespace std::chrono_literals;
using base_interfaces::srv::Addints;
using std::placeholders::_1;
using std::placeholders::_2;

class AddintsClient:public rclcpp::Node{
public:
    //创建节点
    AddintsClient():Node("add_ints_client_node_cpp"){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"客户端节点创建！");
    client_ = this->create_client<Addints>("add_ints");
    }

    //连接服务器函数，连接成功返回1否则0
    bool connect_server(){

       // client_->wait_for_service(1s);  //在指定超时时间内连接服务器，连接成功返回true
        while (! client_->wait_for_service(1s) )
        {
           if(!rclcpp::ok()) //判断程序是否终止
           {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"强行终端连接！");
                return 0;
           }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务器连接中！");
        }
        
        return 1;
    }

    //发送请求函数
    rclcpp::Client<Addints>::FutureAndRequestId  send_request(int num1,int num2)
    {
        auto request =std::make_shared<Addints::Request>();
        request->num1=num1;
        request->num2=num2;
        return client_->async_send_request(request);
    }
private:
    rclcpp::Client<Addints>::SharedPtr client_;
    
};


int main(int argc, char ** argv)
{
    if(argc != 3)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"请提交两个整型数字！");
        return 1;
    }

  rclcpp::init(argc,argv);
    //创建对象指针
  auto client = std::make_shared<AddintsClient>();
  bool flag = client->connect_server();

  //服务器连接失败时退出
  if(!flag)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务器连接失败，程序退出！");
    return 0;
  }
  auto future =client->send_request(atoi(argv[1]),atoi(argv[2]));
  //future中包含了响应结果（封装成FutureReturnCode）
  if(rclcpp::spin_until_future_complete(client,future)==rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(client->get_logger(),"响应成功！sum= %d",future.get()->sum);
  }
  else
  {
    RCLCPP_INFO(client->get_logger(),"响应失败！");
  }
  rclcpp::shutdown();
  return 0;
  //客户端没必要一直回调
  // rclcpp::spin(std::make_shared<AddintsClient>());
}