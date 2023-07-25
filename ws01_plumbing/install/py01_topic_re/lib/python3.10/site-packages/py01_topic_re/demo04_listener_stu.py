import rclpy
from rclpy.node import Node
from base_interfaces.msg import  Student

class ListenerStu(Node):
    def __init__(self):
        super().__init__("listenerstu_node_py")
        self.get_logger().info("订阅者茶创建成功!PY")
        self.subscription = self.create_subscription(Student,"chatter_stu",self.do_cb,10)

    def do_cb(self,stu):
        self.get_logger().info("订阅数据：(%s,%d,%.2f)" %(stu.name,stu.age,stu.height))

def main():
    rclpy.init()
    rclpy.spin(ListenerStu())
    rclpy.shutdown()

if __name__ == '__main__':
    main()