#include "rclcpp/rclcpp.hpp"
#include "base_interfaces/msg/student.hpp"

using base_interfaces::msg::Student;

class ListenerStu: public rclcpp::Node{
public:
    ListenerStu():Node("ListenerStu_node_cpp"){
        RCLCPP_INFO(this->get_logger(),"订阅者已创建！");
        subscription_ = this->create_subscription<Student>("chatter_stu",10,std::bind(&ListenerStu::do_cb,this,std::placeholders::_1));
    }

private:
    void do_cb(const Student &msg){
        RCLCPP_INFO(this->get_logger(),"订阅消息是：(%s,%d,%.2f)",msg.name.c_str(),msg.age,msg.height);
    }
    rclcpp::Subscription<Student>::SharedPtr subscription_;
};
int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<ListenerStu>());
    rclcpp::shutdown();
    return 0;
}