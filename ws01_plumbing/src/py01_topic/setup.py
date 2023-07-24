from setuptools import setup

package_name = 'py01_topic'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='kl',
    maintainer_email='115347950+HeKaiLang@users.noreply.github.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'demo01_talker_str = py01_topic.demo01_talker_str:main',
            'demo02_listener_str = py01_topic.demo02_listener_str:main'
        ],
    },
   
)
