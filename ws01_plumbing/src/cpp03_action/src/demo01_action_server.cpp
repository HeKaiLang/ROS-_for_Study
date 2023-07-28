#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces/action/progress.hpp"

using namespace std::chrono_literals; //时间变量直接后缀时间单位 1s 2s...
using base_interfaces::action::Progress;
using std::placeholders::_1;
using std::placeholders::_2;


class ProgressActionServer:public rclcpp::Node{
public:
    //创建节点
    ProgressActionServer():Node("pa_server_node_cpp"){
    //打印logger
    RCLCPP_INFO(this->get_logger(),"动作服务端节点创建！");
    server = rclcpp_action::create_server<Progress>(
        this,
        "get_sum",
        std::bind(&ProgressActionServer::handle_goal,this,_1,_2),
        std::bind(&ProgressActionServer::handle_cancel,this,_1),
        std::bind(&ProgressActionServer::handle_accepted,this,_1)
        );
  }
private:
/*
  三个函数的源码
  /// Signature of a callback that accepts or rejects goal requests.
  using GoalCallback = std::function<GoalResponse(
        const GoalUUID &, std::shared_ptr<const typename ActionT::Goal>)>;

  /// Signature of a callback that accepts or rejects requests to cancel a goal.
  using CancelCallback = std::function<CancelResponse(std::shared_ptr<ServerGoalHandle<ActionT>>)>;

  /// Signature of a callback that is used to notify when the goal has been accepted.
  using AcceptedCallback = std::function<void (std::shared_ptr<ServerGoalHandle<ActionT>>)>;
*/


//评估目标并接受
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const Progress::Goal> goal)
  {
    (void)uuid;
    if(goal->num<=1)
    {
      return rclcpp_action::GoalResponse::REJECT;
      RCLCPP_INFO(this->get_logger(),"提交的目标值必须大于1！");
    }
    RCLCPP_INFO(this->get_logger(),"提交的目标值合法！");
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }



//客户端申请中断
  rclcpp_action::CancelResponse handle_cancel(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle)
  {
    (void)goal_handle;
    RCLCPP_INFO(this->get_logger(),"接收到取消请求！");
    return rclcpp_action::CancelResponse::ACCEPT;
  }



//处理数据并返回
  void handle_accepted(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle)
  {
      //新建子线程，处理耗时的主逻辑实现
    std::thread(std::bind(&ProgressActionServer::execute,this,goal_handle)).detach();
  }



    //新线程函数，用来处理数据
  void execute(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle)
  {

    //1 生成连续反馈
      //获取目标值
    int num = goal_handle->get_goal()->num;
    int sum = 0;
    auto feedback = std::make_shared<Progress::Feedback>();
    auto result = std::make_shared<Progress::Result>();
    rclcpp::Rate rate(1.0); //以 1s为单位休眠，模拟耗时过程
    for(int i=1;i<=num;i++)
    {
      sum += i;
      double progress = i/(double)num*100; //计算进度
      feedback->progress = progress;
      //rclcpp_action::ServerGoalHandle<base_interfaces::action::Progress>::publish_feedback(std::shared_ptr<base_interfaces::action::Progress_Feedback> feedback_msg)
      goal_handle->publish_feedback(feedback);
      RCLCPP_INFO(this->get_logger(),"连续反馈中... 进度：%.2f percent",progress);
      //处理中断
      if(goal_handle->is_canceling())
      {
        result->sum = sum;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(),"任务取消！");
        return;
      }
      rate.sleep();
    }
    //2 生成最终响应结果
    if(rclcpp::ok())
    {
      result->sum = sum;
        //succeed(std::shared_ptr<base_interfaces::action::Progress_Result> result_msg)
      RCLCPP_INFO(this->get_logger(),"最终结果：%d",sum);
      goal_handle->succeed(result);
    }
  }
  rclcpp_action::Server<Progress>::SharedPtr server;
};


int main(int argc, char ** argv)
{

  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<ProgressActionServer>());
  rclcpp::shutdown();
  return 0;
}