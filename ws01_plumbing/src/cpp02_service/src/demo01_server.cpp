#include "rclcpp/rclcpp.hpp"
#include "base_interfaces/srv/addints.hpp"

using base_interfaces::srv::Addints;
using std::placeholders::_1;
using std::placeholders::_2;

class AddintsServer:public rclcpp::Node{
public:
    //创建节点
    AddintsServer():Node("add_ints_server_node_cpp"){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"服务端节点创建！");
    server_ = this->create_service<Addints>("add_ints",std::bind(&AddintsServer::add,this,_1,_2));
  }
private:
  void add(const Addints::Request::SharedPtr req,const Addints::Response::SharedPtr res)
    {
        res->sum = req->num1 + req->num2;
        RCLCPP_INFO(this->get_logger(),"%d + %d = %d",req->num1,req->num2,res->sum);
    }
    rclcpp::Service<Addints>::SharedPtr server_;
};


int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<AddintsServer>());
  rclcpp::shutdown();
  return 0;
}