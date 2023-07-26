import rclpy
from rclpy.node import Node
from base_interfaces.srv import Addints

class AddintsServer(Node):
    def __init__(self):
        super().__init__("addints_server_node_py")
        self.get_logger().info("服务端创建！(py)")
        self.server = self.create_service(Addints,"add_ints",self.add)
        
    def add(self,request,response):
        response.sum = request.num1+request.num2
        self.get_logger().info("%d + %d = %d"%(request.num1,request.num2,response.sum))
        return response
def main():
    rclpy.init()
    rclpy.spin(AddintsServer())
    rclpy.shutdown()



if __name__ == '__main__':
    main()
