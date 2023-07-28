#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces/action/progress.hpp"

using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...
using base_interfaces::action::Progress;
using std::placeholders::_1;
using std::placeholders::_2;


class ProgressActionClient:public rclcpp::Node{
public:
    //创建节点
    ProgressActionClient():Node("pa_client_node_cpp"){
    RCLCPP_INFO(this->get_logger(),"动作客户端节点创建！");
    client = rclcpp_action::create_client<Progress>(this,"get_sum");
  }
  void send_goal(int num)
  {
    //1 连接服务端
    if(!client-> wait_for_action_server(5s))
    {
        RCLCPP_ERROR(this->get_logger(),"服务连接超时！");
        return;
    }
    //2 发送请求
        //函数模板std::shared_future<rclcpp_action::ClientGoalHandle<base_interfaces::action::Progress>::SharedPtr> async_send_goal(const base_interfaces::action::Progress::Goal &goal, const rclcpp_action::Client<base_interfaces::action::Progress>::SendGoalOptions &options)
    auto goal = Progress::Goal();
    goal.num = num;

    rclcpp_action::Client<Progress>::SendGoalOptions options;
    options.goal_response_callback = std::bind(&ProgressActionClient::goal_response_callback,this,_1);
    options.feedback_callback = std::bind(&ProgressActionClient::feedback_callback,this,_1,_2);
    options.result_callback = std::bind(&ProgressActionClient::result_callback,this,_1);

    client->async_send_goal(goal,options);
    }
private:
    //源码如下
//  using GoalHandle = ClientGoalHandle<ActionT>;
//  using GoalResponseCallback = std::function<void (typename GoalHandle::SharedPtr)>;
    
    //处理服务端返回的是否接受的响应
    void goal_response_callback(rclcpp_action::ClientGoalHandle<Progress>::SharedPtr p)
    {
        if(!p)
        {
            RCLCPP_INFO(this->get_logger(),"目标请求被拒绝！");
        }
        else{
            RCLCPP_INFO(this->get_logger(),"目标请求处理中！");
        }
    }
    //源码
//  using FeedbackCallback =
//  std::function<void (
//  typename ClientGoalHandle<ActionT>::SharedPtr,
//  const std::shared_ptr<const Feedback>)>;

    //处理连续反馈
    void feedback_callback(rclcpp_action::ClientGoalHandle<Progress>::SharedPtr p,const std::shared_ptr<const Progress::Feedback> fb)
    {
        (void) p;
        double progress = fb->progress;
        RCLCPP_INFO(this->get_logger(),"当前进度：%.2f %%...",progress);
    }
    //源码
//  using ResultCallback = std::function<void (const WrappedResult & result)>;
    // 处理最终响应 
    void result_callback(const rclcpp_action::ClientGoalHandle<Progress>::WrappedResult & result)
    {
        //通过状态码判断最终结果状态
        //成功
        if(result.code == rclcpp_action::ResultCode::SUCCEEDED)
        {
            RCLCPP_INFO(this->get_logger(),"成功！最总结果：%d",result.result->sum);
        } 
        if(result.code == rclcpp_action::ResultCode::ABORTED)
        {
            RCLCPP_INFO(this->get_logger(),"被中断！");
        } 
        if(result.code == rclcpp_action::ResultCode::CANCELED)
        {
            RCLCPP_INFO(this->get_logger(),"被取消！");
        } 
        if(result.code == rclcpp_action::ResultCode::UNKNOWN)
        {
            RCLCPP_INFO(this->get_logger(),"未知异常！");
        } 
    }
    rclcpp_action::Client<Progress>::SharedPtr client;
    
};


int main(int argc, char ** argv)
{
  if(argc!= 2){
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"请提交一个整型数据！");
    return 1;
  }
  rclcpp::init(argc,argv);
  auto client = std::make_shared<ProgressActionClient>();
  client->send_goal(atoi(argv[1]));
  rclcpp::spin(client);
  rclcpp::shutdown();
  return 0;
}