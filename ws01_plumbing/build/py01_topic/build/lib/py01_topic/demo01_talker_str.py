import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class Talker(Node):
    def __init__(self):
        super().__init__("talk_node_py")
        self.get_logger().info("发布方创建！(py)")
        self.count = 0
        self.publisher = self.create_publisher(String,"chatter",10)
        """ 
        计时器 参数 时间间隔 回调函数
        """
        self.timer = self.create_timer(1.0,self.on_timer)
        
    def on_timer(self):
        message = String()
        message.data = "hello! "+str(self.count)
        self.count+=1
        self.get_logger().info("发布的数据：%s"%message.data)
        self.publisher.publish(message)

def main():
    rclpy.init()
    rclpy.spin(Talker())
    rclpy.shutdown()



if __name__ == '__main__':
    main()
