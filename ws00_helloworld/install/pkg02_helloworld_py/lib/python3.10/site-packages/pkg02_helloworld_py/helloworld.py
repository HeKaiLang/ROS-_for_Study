import rclpy

def main():
    rclpy.init()
    node = rclpy.create_node("helloworl_node_py")
    node.get_logger().info("hello world!(python)")
    rclpy.shutdown()
if __name__ == '__main__':
    main()
