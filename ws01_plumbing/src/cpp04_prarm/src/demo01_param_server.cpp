#include "rclcpp/rclcpp.hpp"


using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...

class ParamServer:public rclcpp::Node{
public:
    //创建节点,传递允许修改的参数NodeOptions
    ParamServer():Node("param_server_node_cpp",rclcpp::NodeOptions().allow_undeclared_parameters(true)){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"参数客户端节点创建！");
    }
    void declare_param(){
        RCLCPP_INFO(this->get_logger(),"---------------增---------------");
        this->declare_parameter("car_name","tiger");
        this->declare_parameter("width",1.55);
        this->declare_parameter("wheels",5);
        //不通过声明添加参数：
        this->set_parameter(rclcpp::Parameter("height",2.1));
    }
    void get_param(){
        RCLCPP_INFO(this->get_logger(),"---------------查---------------");
        //获取指定参数
        auto car = this->get_parameter("car_name");
        RCLCPP_INFO(this->get_logger(),"key= %s,value= %s",car.get_name().c_str(),car.as_string().c_str());
        //获取一些参数
        auto params = this->get_parameters({"car_name","width","wheels"});
        for(auto &&param : params)
        {
            RCLCPP_INFO(this->get_logger(),"%s = %s",param.get_name().c_str(),param.value_to_string().c_str());
        }
        //判断是否包含参数
        RCLCPP_INFO(this->get_logger(),"是否包含car_name:%d",this->has_parameter("car_name"));
        RCLCPP_INFO(this->get_logger(),"是否包含name:%d",this->has_parameter("name"));
        
    }
    void update_param(){
        RCLCPP_INFO(this->get_logger(),"---------------改---------------");
        this->set_parameter(rclcpp::Parameter("width",1.75));
        RCLCPP_INFO(this->get_logger(),"width= %.2f",this->get_parameter("width").as_double());
    }
    void del_param(){
        RCLCPP_INFO(this->get_logger(),"---------------删---------------");
    }
private:
  
};


int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  auto node =std::make_shared<ParamServer>();

  node->declare_param();
  node->get_param();
  node->update_param();
  node->del_param();

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}