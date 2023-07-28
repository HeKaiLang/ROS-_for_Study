#include "rclcpp/rclcpp.hpp"


using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...

class ParamClient:public rclcpp::Node{
public:
    //创建节点
    ParamClient():Node("param_client_node_cpp"){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"参数服务端节点创建！");
    client = std::make_shared<rclcpp::SyncParametersClient>(this,"param_server_node_cpp");//传入服务端节点名称
  }
  bool connect_sercer()
  {
    while (!client->wait_for_service(1s))
    {
        if(!rclcpp::ok())
        return 0;
        RCLCPP_INFO(this->get_logger(),"服务连接中...");
    }
    return 1;
  }
  void get_param()
  {
    RCLCPP_INFO(this->get_logger(),"-------查询操作-------");
    //获取一个参数
    std::string car_name = client->get_parameter<std::string>("car_name");
    RCLCPP_INFO(this->get_logger(),"car_name: %s",car_name.c_str());
    //获取多个参数
    auto params = client->get_parameters({"width","wheels"});
    {
        for(auto &&param :params)
        {
            RCLCPP_INFO(this->get_logger(),"%s = %s",param.get_name().c_str(),param.value_to_string().c_str());
        }
    }
    //判断是否存在
    RCLCPP_INFO(this->get_logger(),"是否包含 car_name? %d",client->has_parameter("car_name"));
    
  }
  void update_param()
  {
    RCLCPP_INFO(this->get_logger(),"-------修改操作-------");
    //也可以用来新增参数
    client->set_parameters( {rclcpp::Parameter("car_name","pig"),
                            rclcpp::Parameter("width",2.56)
    });
  }
private:
    rclcpp::SyncParametersClient::SharedPtr client;
};
int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  auto client = std::make_shared<ParamClient>();
  if(!client->connect_sercer())
  {
    return 0;
  }
  client->get_param();
  client->update_param();
  client->get_param();
  rclcpp::shutdown();
  return 0;
}