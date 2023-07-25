"""
方法一 不推荐

import rclpy

def main():
    rclpy.init()
    node = rclpy.create_node("helloworl_node_py")
    node.get_logger().info("hello world!(python)")
    rclpy.shutdown()
"""

"""
方案二 类继承（推荐）
"""
import rclpy
from rclpy.node import Node

class My_Node(Node):
    def __init__(self):
        super().__init__("hello_node_py")
        self.get_logger().info("hellow world (类继承)")

def main():
    rclpy.init()
    node = My_Node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
