import rclpy
from rclpy.node import Node
from base_interfaces.msg import  Student

class TalkerStu(Node):
    def __init__(self):
        super().__init__("talkstu_node_py")
        self.get_logger().info("发布方创建！(py)")
        self.count = 0
        self.publisher = self.create_publisher(Student,"chatter_stu",10)
        """ 
        计时器 参数 时间间隔 回调函数
        """
        self.timer = self.create_timer(1.0,self.on_timer)
        
    def on_timer(self):
        stu = Student()
        stu.name = "he "+str(self.count)
        stu.age = 20
        stu.height = 180.12
        self.count+=1
        self.get_logger().info("发布的数据：(%s,%d,%.2f)"%(stu.name,stu.age,stu.height))
        self.publisher.publish(stu)

def main():
    rclpy.init()
    rclpy.spin(TalkerStu())
    rclpy.shutdown()



if __name__ == '__main__':
    main()