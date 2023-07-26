import rclpy
import sys
from rclpy.node import Node
from rclpy.logging import get_logger
from base_interfaces.srv import Addints

class AddintsClient(Node):
    def __init__(self):
        super().__init__("addints_client_node_py")
        self.get_logger().info("客户端创建！(py)")
        self.client = self.create_client(Addints,"add_ints")
        while not self.client.wait_for_service(1.0):
            self.get_logger().info("服务连接中...")
    def send_request(self):
        request = Addints.Request()
        request.num1 = int(sys.argv[1])
        request.num2 = int(sys.argv[2])
        self.future = self.client.call_async(request)

def main():
    if len(sys.argv) != 3:
        get_logger("rclpy").info("请提交两个整型数据！")
        return

    rclpy.init()
    client = AddintsClient()
    # 发送请求
    client.send_request()
    #处理响应
    rclpy.spin_until_future_complete(client,client.future)
    try:
        response = client.future.result()
        client.get_logger().info("响应结果：sum=%d"%response.sum)
    except Exception:
        client.get_logger().info("服务响应失败！")
    rclpy.shutdown()



if __name__ == '__main__':
    main()
